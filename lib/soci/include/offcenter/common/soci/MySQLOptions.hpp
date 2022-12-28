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
 * @file   SOCIMySQLConnectionOptions.hpp
 * @author Scott Brauer
 * @date   03-20-2021
 */
#ifndef OFFCENTER_SOCI_MYSQLOPTIONS_HPP_
#define OFFCENTER_SOCI_MYSQLOPTIONS_HPP_

#include <string>
#include <climits>
#include <stdexcept>
#include <algorithm>
#include <cassert>

#include "soci/mysql/soci-mysql.h"

namespace offcenter {
namespace common {
namespace soci {

class MySQLOptions
{
public:
	class Option {
	private:
		bool m_isDirty;
		std::string m_name;
		std::string m_value;

		const std::string standardizedValue() const {
			if (std::find_if(m_value.begin(), m_value.end(), isspace) != m_value.end()) {
				return "'" + m_value + "'";
			} else {
				return m_value;
			}
		}

	public:
		explicit Option(const std::string& name):
			m_isDirty(false),
			m_name(name),
			m_value("") {}
		const std::string name() const { return m_name; }
		const std::string value() const { return m_value; }
		bool isDirty() const { return m_isDirty; }
		void clear() { m_value = ""; m_isDirty = false; }
		const std::string operator()() const { return m_value; }
		void operator()(const std::string& value) {
			if (m_value != value) {
				m_value = value;
				m_isDirty = true;
			}
		}
		const std::string optionString() const {
			if (m_isDirty) {
				return m_name + "=" + standardizedValue();
			} else {
				return "";
			}
		}
		Option& operator=(const std::string& value) {
			operator()(value);
			return *this;
		}
		Option& operator=(const Option& other) {
			assert(m_name == other.m_name);
			m_isDirty = other.m_isDirty;
			m_value = other.m_value;
			return *this;
		}
	};

	template <int MIN, int MAX>
	class IntOption: public Option {
	public:
		explicit IntOption(const std::string& name):
				Option(name) {}
		int operator()() const {
			if (isDirty()) {
				return std::stoi(Option::operator()());
			} else {
				return -1;
			}
		}
		void operator()(int value) {
			if ((value < MIN) || (value > MAX)) {
				throw std::runtime_error("Setting option is out of range: " + std::to_string(MIN) + "<=" + std::to_string(value) + "<=" + std::to_string(MAX));
			}
			Option::operator()(std::to_string(value));
		}
		IntOption& operator=(int value) {
			operator()(value);
			return *this;
		}
		IntOption& operator=(const IntOption& other) {
			Option::operator=(other);
			return *this;
		}
	};

public:
	using LocalInfile = IntOption<0,1>;
	using ConnectTimeout = IntOption<1,INT_MAX>;
	using ReadTimeout = IntOption<1,INT_MAX>;
	using WriteTimeout = IntOption<1,INT_MAX>;

	explicit MySQLOptions();
	explicit MySQLOptions(const std::string& host, const std::string& dbname, const std::string& user, const std::string& password);
	virtual ~MySQLOptions();

	const ::soci::backend_factory& backendFactory() const { return ::soci::mysql; }

	MySQLOptions& operator=(const MySQLOptions& other);

	const std::string getConnectionString() const;
	const std::string loggableConnectionString() const;

	/** Name of the database to connect to.
	 *  [Required]
	 */
	Option dbname;

	/** The username accessing the database.
	 *  [Default: Owner of the server]
	 */
	Option user;

	/** The password for the MySQL account being used.
	 */
	Option password;

	/** The name or network address of the instance of MySQL to which to connect.
	 */
	Option host;

	/** Port on the host for connection.
	 * 	The value is ignored if Unix socket is used.
	 * 	[Default: 3306
	 */
	Option port;

	/** The name of the socket file that is used for local client connections.
	 *  [Default: /tmp/mysql.sock]
	 */
	Option unix_socket;

	/** The path to a file with a list of trust SSL CAs
	 */
	Option sslca;


	/** The name of the SSL certificate file to use for establishing a secure connection.
	 */
	Option sslcert;

	/** should be 0 or 1, 1 means MYSQL_OPT_LOCAL_INFILE will be set.
	 */
	LocalInfile local_infile;

	/** Specifies the character set that should be used to encode all queries sent to the server.
	 *  Resultsets are still returned in the character set of the data returned.
	 */
	Option charset;

	/** Positive integer value that means seconds corresponding to MYSQL_OPT_CONNECT_TIMEOUT.
	 *  [Default: 30000]
	 */
	ConnectTimeout connect_timeout;

	/** Positive integer value that means seconds corresponding to MYSQL_OPT_READ_TIMEOUT.
	 */
	ReadTimeout read_timeout;

	/** Positive integer value that means seconds corresponding to MYSQL_OPT_WRITE_TIMEOUT.
	 */
	WriteTimeout write_timeout;

	friend class MySQLProgramOptions;
};

} /* namespace soci */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_SOCI_MYSQLOPTIONS_HPP_ */
