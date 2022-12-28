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
 * @file   AmqpExampleProgramOptions.hpp
 * @author Scott Brauer
 * @date   04-15-2021
 */
#ifndef AMQPEXAMPLEPROGRAMOPTIONS_HPP_
#define AMQPEXAMPLEPROGRAMOPTIONS_HPP_

#include <functional>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"

#include "AmqpExampleOptions.hpp"

class AmqpExampleProgramOptions:
		public offcenter::common::program_options::ProgramOptionsGroup<AmqpExampleOptions>
{
public:
	AmqpExampleProgramOptions():
		ProgramOptionsGroup("AMQP")
	{
		optionsDescription().add_options()
				("AMQP.tcpHost", po::value<std::string>(&optionConfig().m_tcpHost)->default_value("localhost"), "Active MQ Server")
				("AMQP.connectionSendTimeout", po::value<int>(&optionConfig().m_connectionSendTimeout)->default_value(1000), "connection.sendTimeout")
				("AMQP.failoverTransportTimeout", po::value<int>(&optionConfig().m_failoverTransportTimeout)->default_value(1000), "failoverTransport.timeout")
				;
	}

	virtual ~AmqpExampleProgramOptions() = default;
};

#endif /* AMQPEXAMPLEPROGRAMOPTIONS_HPP_ */
