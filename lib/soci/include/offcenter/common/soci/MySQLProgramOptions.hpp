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
 * @file   MySQLProgramOptions.hpp
 * @author Scott Brauer
 * @date   03-24-2021
 */
#ifndef OFFCENTER_SOCI_MYSQLPROGRAMOPTIONS_HPP_
#define OFFCENTER_SOCI_MYSQLPROGRAMOPTIONS_HPP_

#include <functional>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/soci/MySQLOptions.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace soci {

class MySQLProgramOptions:
		public program_options::ProgramOptionsGroup<soci::MySQLOptions>
{
public:
	MySQLProgramOptions():
		ProgramOptionsGroup("Config File Options")
	{
		optionsDescription().add_options()
				("dbname", po::value<std::string>()
						->notifier(boost::bind(&soci::MySQLOptions::Option::operator(), &(optionConfig().dbname), boost::placeholders::_1)), "Database name")
				("user", po::value<std::string>()
						->notifier(boost::bind(&soci::MySQLOptions::Option::operator(), &(optionConfig().user), boost::placeholders::_1)), "Database user")
				("password", po::value<std::string>()
						->notifier(boost::bind(&soci::MySQLOptions::Option::operator(), &(optionConfig().password), boost::placeholders::_1)), "User password")
				("host", po::value<std::string>()
						->notifier(boost::bind(&soci::MySQLOptions::Option::operator(), &(optionConfig().host), boost::placeholders::_1)), "Host containing database")
				("port", po::value<std::string>()
						->notifier(boost::bind(&soci::MySQLOptions::Option::operator(), &(optionConfig().port), boost::placeholders::_1)), "Port on host")
				("unix_socket", po::value<std::string>()
						->notifier(boost::bind(&soci::MySQLOptions::Option::operator(), &(optionConfig().unix_socket), boost::placeholders::_1)), "Unix socket")
				("sslca", po::value<std::string>()
						->notifier(boost::bind(&soci::MySQLOptions::Option::operator(), &(optionConfig().sslca), boost::placeholders::_1)), "sslca")
				("sslcert", po::value<std::string>()
						->notifier(boost::bind(&soci::MySQLOptions::Option::operator(), &(optionConfig().sslcert), boost::placeholders::_1)), "sslcert")
				("local_infile", po::value<int>()
						->notifier(boost::bind(&soci::MySQLOptions::LocalInfile::operator(), &(optionConfig().local_infile), boost::placeholders::_1)), "Local infile")
				("charset", po::value<std::string>()
						->notifier(boost::bind(&soci::MySQLOptions::Option::operator(), &(optionConfig().charset), boost::placeholders::_1)), "Charset")
				("connect_timeout", po::value<int>()
						->notifier(boost::bind(&soci::MySQLOptions::ConnectTimeout::operator(), &(optionConfig().connect_timeout), boost::placeholders::_1)), "Connect timeout")
				("read_timeout", po::value<int>()
						->notifier(boost::bind(&soci::MySQLOptions::ReadTimeout::operator(), &(optionConfig().read_timeout), boost::placeholders::_1)), "Read timeout")
				("write_timeout", po::value<int>()
						->notifier(boost::bind(&soci::MySQLOptions::WriteTimeout::operator(), &(optionConfig().write_timeout), boost::placeholders::_1)), "Write timeout")
				;
	}

	virtual ~MySQLProgramOptions() = default;
};

} /* namespace soci */
} /* namespace offcenter */

#endif /* OFFCENTER_SOCI_MYSQLPROGRAMOPTIONS_HPP_ */
