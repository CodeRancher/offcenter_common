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
 * @file   RestServerApp.hpp
 * @author Scott Brauer
 * @date   04-09-2021
 */
#ifndef OffcenterCommon_AMQPSERVER_AMQPSERVERAPP_HPP_
#define OffcenterCommon_AMQPSERVER_AMQPSERVERAPP_HPP_

#include <boost/bind/bind.hpp>

//#include <cpprest/http_msg.h>
//#include <cpprest/http_listener.h>
//#include <pplx/pplxtasks.h>

#include "offcenter/common/amqp/Helper.hpp"

#include "easylogging++.h"

//#include "offcenter/common/amqpserver/AutoMethodHandler.hpp"
#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/amqpserver/IAmqpServerApp.hpp"
//#include "offcenter/common/amqpserver/network/Utility.hpp"
//#include "offcenter/common/amqpserver/AmqpServerAppFoundation.hpp"

#include "offcenter/common/amqp/ActiveMQCPP.hpp"
#include "offcenter/common/amqp/AMQPException.hpp"

namespace offcenter {
namespace common {
namespace amqpserver {

/**
 *
 */
template <class IAMQPSERVERAPP>
class AmqpServerAppManager:
		public framework::application::AppManager<IAMQPSERVERAPP>
{
public:
	explicit AmqpServerAppManager():
		framework::application::AppManager<IAMQPSERVERAPP>(),
		activeMQCpp()
	{}
	virtual ~AmqpServerAppManager() = default;

	//void internalOnInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) {
	//	//m_app.onInitProgramOptions(optionsManager);
	//}

	void onSetUp() override {
		// Prompt general setup
		framework::application::AppManager<IAMQPSERVERAPP>::m_app.onSetUp();

		// Prompt AMQP setup
		amqp::ConnectionURIOptions options;
		framework::application::AppManager<IAMQPSERVERAPP>::m_app.onInitAMQP(options);

		try {
			// Connect to the AMQP server
			amqp::ActiveMQConnectionFactoryPtr connectionFactory(amqp::helper::activeMQConnectionFactoryFactory(options.uri()));

			// Create a Connection
			cms::Connection* connection = connectionFactory->createConnection();
			m_connection = amqp::helper::connectionFactory(connection);
		} catch(const cms::CMSException& e) {
			LOG(ERROR) << e.what() << ": " << options.uri();
			throw offcenter::common::amqp::AMQPException("Unable to connect to server: " + options.uri() + ": " + e.what());
		} catch (const std::exception& e) {
			LOG(ERROR) << e.what() << ": " << options.uri();
			throw offcenter::common::amqp::AMQPException("Unable to connect to server: " + options.uri() + ": " + e.what());
		} catch (...) {
			LOG(ERROR) << "Unknown Exception: " << ": " << options.uri();
			throw offcenter::common::amqp::AMQPException("Unable to connect to server: " + options.uri());
		}

		// Create Sesstions
		framework::application::AppManager<IAMQPSERVERAPP>::m_app.onInitAMQPSessions(m_connection);
	}

	void onExecute() override {
		LOG(DEBUG) << "Starting ActiveMQCPP connection";
		m_connection->start();
		LOG(DEBUG) << "ActiveMQCPP connection started";

		LOG(DEBUG) << "onExeucte started";
		framework::application::AppManager<IAMQPSERVERAPP>::m_app.onExecute();
		LOG(DEBUG) << "onExeucte ended";
	}

	void onTearDown() override {
		// Prompt app specific shutdown
		framework::application::AppManager<IAMQPSERVERAPP>::m_app.onTearDown();

		LOG(DEBUG) << "Closing ActiveMQCPP connection";
		if (m_connection) {
			m_connection->close();
			m_connection.reset();
		}
	}

private:
	offcenter::common::amqp::ActiveMQCPP activeMQCpp;
	amqp::ConnectionPtr m_connection;

};

} /* namespace amqpserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_AMQPSERVER_AMQPSERVERAPP_HPP_ */
