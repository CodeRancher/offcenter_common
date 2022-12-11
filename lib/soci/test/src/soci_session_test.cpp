/**
 * Copyright 2020 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an  BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   soci_session.cpp
 * @author Scott Brauer
 * @date   09-16-2021
 */

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::HasSubstr;

#include "easylogging++.h"

#include "offcenter/common/soci/Session.hpp"
#include "globalvariables.hpp"

TEST (SOCISession, EmptySessionPool)
{
	const size_t poolSize = 4;

	offcenter::soci::MySQLOptions mysqlOptions;
	mysqlOptions.dbname(g_dbname);
	mysqlOptions.user(g_user);
	mysqlOptions.password(g_password);
	mysqlOptions.host(g_host);

	offcenter::soci::SessionPoolManager sessionPoolManager(mysqlOptions, poolSize);

	// Test that all sessions are connected
	for (int i = 0; i < poolSize; i++ ) {
		::soci::session& session = sessionPoolManager.connectionPool().at(i);
		EXPECT_TRUE(session.is_connected());
	}

	// Grab a session and make sure it is also connected
	offcenter::soci::Session session(sessionPoolManager);
	EXPECT_TRUE(session.isOpen());
	EXPECT_TRUE(session.sql().is_connected());
	EXPECT_TRUE(session().is_connected());

	// Test that all sessions are closed
	sessionPoolManager.close();
	for (int i = 0; i < poolSize; i++ ) {
		::soci::session& session = sessionPoolManager.connectionPool().at(i);
		EXPECT_FALSE(session.is_connected());
	}

	// Test open after close
	sessionPoolManager.open(mysqlOptions);
	for (int i = 0; i < poolSize; i++ ) {
		::soci::session& session = sessionPoolManager.connectionPool().at(i);
		EXPECT_TRUE(session.is_connected());
	}
}

TEST (SOCISession, SimpleSelect)
{
	const size_t poolSize = 4;

	offcenter::soci::MySQLOptions mysqlOptions;
	mysqlOptions.dbname(g_dbname);
	mysqlOptions.user(g_user);
	mysqlOptions.password(g_password);
	mysqlOptions.host(g_host);

	offcenter::soci::SessionPoolManager sessionPoolManager(mysqlOptions, poolSize);

	std::string version;
	for (int i = 0; i < poolSize * 2; i++ ) {
		offcenter::soci::Session session(sessionPoolManager);
		session() << "SELECT version();", ::soci::into(version);
		EXPECT_THAT(version, HasSubstr("MariaDB"));
		session << "SELECT version();", ::soci::into(version);
		EXPECT_THAT(version, HasSubstr("MariaDB"));
		session.sql() << "SELECT version();", ::soci::into(version);
		EXPECT_THAT(version, HasSubstr("MariaDB"));
	}
}

TEST (SOCISession, DatabaseDoesntExist)
{
	const size_t poolSize = 4;

	offcenter::soci::MySQLOptions mysqlOptions;
	mysqlOptions.dbname("DatabaseNameThatDoesntExist");
	mysqlOptions.user(g_user);
	mysqlOptions.password(g_password);
	mysqlOptions.host(g_host);

	offcenter::soci::SessionPoolManager sessionPoolManager(mysqlOptions, poolSize, true);
	sessionPoolManager.dropDB(mysqlOptions);
}
