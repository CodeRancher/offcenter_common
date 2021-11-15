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
 * @file   AMQPApp.cpp
 * @author Scott Brauer
 * @date   05-03-2019
 */

#include "offcenter/common/framework/program_options/AMQPAppProgramOptions.hpp"
#include "offcenter/common/framework/application/AMQPApp.hpp"

#include "offcenter/amqp/Helper.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace application {

AMQPApp::AMQPApp():
		BasicApp(),
		m_amqpConfig()
{
	m_optionsManager.add<AMQPAppProgramOptions>();

}

AMQPApp::~AMQPApp()
{
	// TODO Auto-generated destructor stub
}

void AMQPApp::start()
{
	std::string brokerURI = "failover:(tcp://rpiactivemq:61616?connection.sendTimeout=100&timeout=100)";

	// Create a ConnectionFactory
	offcenter::amqp::ActiveMQConnectionFactoryPtr connectionFactory(
			offcenter::amqp::Helper::activeMQConnectionFactoryFactory(brokerURI));

    // Create a Connection
    m_connection = offcenter::amqp::Helper::connectionFactory(connectionFactory->createConnection());
    m_connection->start();
    m_scopeGuard += [&](){
        try {
        	m_connection->close();
        } catch (cms::CMSException& e) {
            e.printStackTrace();
        }
    };

    // Create a Session
    m_session = offcenter::amqp::Helper::sessionFactory(m_connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));

    BasicApp::start();
}

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */
