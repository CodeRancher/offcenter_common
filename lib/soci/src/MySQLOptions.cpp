/**
 * Copyright 2021 Scott Brauer
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
 * @file   MySQLOptions.cpp
 * @author Scott Brauer
 * @date   03-20-2021
 */

#include <string>
#include <initializer_list>
#include <sstream>

#include "offcenter/common/soci/MySQLOptions.hpp"

namespace offcenter {
namespace common {
namespace soci {

MySQLOptions::MySQLOptions():
		dbname("db"),
		user("user"),
		password("password"),
		host("host"),
		port("port"),
		unix_socket("unix_socket"),
		sslca("sslca"),
		sslcert("sslcert"),
		local_infile("local_infile"),
		charset("charset"),
		connect_timeout("connect_timeout"),
		read_timeout("read_timeout"),
		write_timeout("write_timeout")
{
	// TODO Auto-generated constructor stub

}

MySQLOptions::MySQLOptions(
		const std::string &host,
		const std::string &dbname,
        const std::string &user,
        const std::string &password
	): MySQLOptions()
{
	this->host(host);
	this->dbname(dbname);
	this->user(user);
	this->password(password);
}

MySQLOptions::~MySQLOptions()
{
	// TODO Auto-generated destructor stub
}

MySQLOptions& MySQLOptions::operator=(const MySQLOptions& other)
{
	dbname = other.dbname;
	user = other.user;
	password = other.password;
	host = other.host;
	port = other.port;
	unix_socket = other.unix_socket;
	sslca = other.sslca;
	sslcert = other.sslcert;
	local_infile = other.local_infile;
	charset = other.charset;
	connect_timeout = other.connect_timeout;
	read_timeout = other.read_timeout;
	write_timeout = other.write_timeout;
	return *this;
}

const std::string MySQLOptions::getConnectionString() const
{
	auto elements = {
			dbname.optionString(),
			user.optionString(),
			password.optionString(),
			host.optionString(),
			port.optionString(),
			unix_socket.optionString(),
			sslca.optionString(),
			sslcert.optionString(),
			local_infile.optionString(),
			charset.optionString(),
			connect_timeout.optionString(),
			read_timeout.optionString(),
			write_timeout.optionString()
	};
	std::ostringstream ss;
	bool firstElement = true;
	for (auto element : elements) {
		if (element.size() > 0) {
			ss << (!firstElement ? " " : "") << element;
			firstElement = false;
		}
	}
	return ss.str();
}

const std::string MySQLOptions::loggableConnectionString() const
{
	auto elements = {
			&dbname,
			&user,
			&password,
			&host,
			&port,
			&unix_socket,
			&sslca,
			&sslcert,
			(const MySQLOptions::Option*)&local_infile,
			&charset,
			(const MySQLOptions::Option*)&connect_timeout,
			(const MySQLOptions::Option*)&read_timeout,
			(const MySQLOptions::Option*)&write_timeout
	};
	std::ostringstream ss;
	for (auto element : elements) {
		ss  << element->name()
			<< "(" << ((element->name() == password.name()) ? "********" : element->value())
			<< (element->isDirty() ? "(M)) " : ") ");
	}
	return ss.str();
}

} /* namespace soci */
} /* namespace common */
} /* namespace offcenter */
