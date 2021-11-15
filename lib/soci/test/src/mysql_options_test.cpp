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
 * @file   mysql_options_test.cpp
 * @author Scott Brauer
 * @date   03-22-2021
 */

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::HasSubstr;

#include "offcenter/soci/MySQLOptions.hpp"

class MySQLOptionsFixture : public ::testing::Test
{
public:
	MySQLOptionsFixture(): ::testing::Test() {}
	virtual ~MySQLOptionsFixture() = default;
protected:
	offcenter::soci::MySQLOptions mysqlOptions;
};

TEST_F (MySQLOptionsFixture, DBName)
{
	const std::string value = "Test";
	mysqlOptions.dbname(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "db=" + value);
}

TEST_F (MySQLOptionsFixture, User)
{
	const std::string value = "Test";
	mysqlOptions.user(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "user=" + value);
}

TEST_F (MySQLOptionsFixture, Password)
{
	const std::string value = "Test";
	mysqlOptions.password(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "password=" + value);
}

TEST_F (MySQLOptionsFixture, PasswordWithSpaces)
{
	const std::string value = "A Long Password";
	mysqlOptions.password(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "password='" + value + "'");
}

TEST_F (MySQLOptionsFixture, Host)
{
	const std::string value = "Test";
	mysqlOptions.host(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "host=" + value);
}

TEST_F (MySQLOptionsFixture, Port)
{
	const std::string value = "Test";
	mysqlOptions.port(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "port=" + value);
}

TEST_F (MySQLOptionsFixture, UnixSocket)
{
	const std::string value = "Test";
	mysqlOptions.unix_socket(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "unix_socket=" + value);
}

TEST_F (MySQLOptionsFixture, SSLCA)
{
	const std::string value = "Test";
	mysqlOptions.sslca(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "sslca=" + value);
}

TEST_F (MySQLOptionsFixture, SSLCert)
{
	const std::string value = "Test";
	mysqlOptions.sslcert(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "sslcert=" + value);
}

TEST_F (MySQLOptionsFixture, LocalInfile)
{
	const int value = 0;
	mysqlOptions.local_infile(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "local_infile=" + std::to_string(value));
}

TEST_F (MySQLOptionsFixture, Charset)
{
	const std::string value = "Test";
	mysqlOptions.charset(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "charset=" + value);
}

TEST_F (MySQLOptionsFixture, ConnectTimeout)
{
	const int value = 1;
	mysqlOptions.connect_timeout(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "connect_timeout=" + std::to_string(value));
}

TEST_F (MySQLOptionsFixture, ReadTimeout)
{
	const int value = 1;
	mysqlOptions.read_timeout(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "read_timeout=" + std::to_string(value));
}

TEST_F (MySQLOptionsFixture, WriteTimeout)
{
	const int value = 1;
	mysqlOptions.write_timeout(value);
	EXPECT_EQ(mysqlOptions.getConnectionString(), "write_timeout=" + std::to_string(value));
}

TEST_F (MySQLOptionsFixture, AllValues)
{
	const std::string dbname = "DBNAME";
	mysqlOptions.dbname(dbname);

	const std::string user = "USER";
	mysqlOptions.user(user);

	const std::string password = "PASSWORD";
	mysqlOptions.password(password);

	const std::string host = "HOST";
	mysqlOptions.host(host);

	const std::string port = "PORT";
	mysqlOptions.port(port);

	const std::string unix_socket = "UNIX_SOCKET";
	mysqlOptions.unix_socket(unix_socket);

	const std::string sslca = "SSLCA";
	mysqlOptions.sslca(sslca);

	const std::string sslcert = "SSLCERT";
	mysqlOptions.sslcert(sslcert);

	const int local_infile = 1;
	mysqlOptions.local_infile(local_infile);

	const std::string charset = "CHARSET";
	mysqlOptions.charset(charset);

	const int connect_timeout = INT_MAX;
	mysqlOptions.connect_timeout(connect_timeout);

	const int read_timeout = INT_MAX;
	mysqlOptions.read_timeout(read_timeout);

	const int write_timeout = INT_MAX;
	mysqlOptions.write_timeout(write_timeout);

	const std::string connectionString = " " + mysqlOptions.getConnectionString() + " ";

	// Special Test: Verify parameters have spaces between them
	EXPECT_THAT(connectionString, HasSubstr(" db=" + dbname + " "));
	EXPECT_THAT(connectionString, HasSubstr(" user=" + user + " "));
	EXPECT_THAT(connectionString, HasSubstr(" password=" + password + " "));
	EXPECT_THAT(connectionString, HasSubstr(" host=" + host + " "));
	EXPECT_THAT(connectionString, HasSubstr(" port=" + port + " "));
	EXPECT_THAT(connectionString, HasSubstr(" unix_socket=" + unix_socket + " "));
	EXPECT_THAT(connectionString, HasSubstr(" sslca=" + sslca + " "));
	EXPECT_THAT(connectionString, HasSubstr(" sslcert=" + sslcert + " "));
	EXPECT_THAT(connectionString, HasSubstr(" local_infile=" + std::to_string(local_infile) + " "));
	EXPECT_THAT(connectionString, HasSubstr(" charset=" + charset + " "));
	EXPECT_THAT(connectionString, HasSubstr(" connect_timeout=" + std::to_string(connect_timeout) + " "));
	EXPECT_THAT(connectionString, HasSubstr(" read_timeout=" + std::to_string(read_timeout) + " "));
	EXPECT_THAT(connectionString, HasSubstr(" write_timeout=" + std::to_string(write_timeout) + " "));
}

TEST_F (MySQLOptionsFixture, IntOutOfRange)
{
	EXPECT_THROW(
			mysqlOptions.local_infile(10),
			std::runtime_error
	);
}
