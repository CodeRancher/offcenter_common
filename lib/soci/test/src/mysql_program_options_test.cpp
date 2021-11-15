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
 * @file   mysql_program_options_test.cpp
 * @author Scott Brauer
 * @date   03-23-2021
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::HasSubstr;

#include "offcenter/soci/MySQLProgramOptions.hpp"
#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/SimulatedCommandLine.hpp"
using namespace offcenter::common;

TEST (MySQLProgramOptions, OptionsFromCommandLine)
{
	program_options::ProgramOptionsManager optionsManager;
	offcenter::soci::MySQLProgramOptions::ConfigPtr config;
	config = optionsManager.add<offcenter::soci::MySQLProgramOptions>();

	std::string dbname = "DBName";
	std::string user = "User";
	std::string password = "Very long password";
	std::string host = "Host";
	std::string port = "Port";
	std::string unix_socket = "Unix Socket";
	std::string sslca = "SSLCa";
	std::string sslcert = "SSLCert";
	int local_infile = 1;
	std::string charset = "Charset";
	int connect_timeout = 1234;
	int read_timeout = 2345;
	int write_timeout = 3456;

	SimulatedCommandLine commandLine("MySQLProgramOptions",
		{
			"--dbname", dbname,
			"--user", user,
			"--password", password,
			"--host", host,
			"--port", port,
			"--unix_socket", unix_socket,
			"--sslca", sslca,
			"--sslcert", sslcert,
			"--local_infile", std::to_string(local_infile),
			"--charset", charset,
			"--connect_timeout", std::to_string(connect_timeout),
			"--read_timeout", std::to_string(read_timeout),
			"--write_timeout", std::to_string(write_timeout)
		}
	);

	optionsManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config->dbname(), dbname);
	EXPECT_EQ(config->user(), user);
	EXPECT_EQ(config->password(), password);
	EXPECT_EQ(config->host(), host);
	EXPECT_EQ(config->port(), port);
	EXPECT_EQ(config->unix_socket(), unix_socket);
	EXPECT_EQ(config->sslca(), sslca);
	EXPECT_EQ(config->sslcert(), sslcert);
	EXPECT_EQ(config->local_infile(), local_infile);
	EXPECT_EQ(config->charset(), charset);
	EXPECT_EQ(config->connect_timeout(), connect_timeout);
	EXPECT_EQ(config->read_timeout(), read_timeout);
	EXPECT_EQ(config->write_timeout(), write_timeout);
}
