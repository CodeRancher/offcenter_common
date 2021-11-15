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
#ifndef OFFCENTER_COMMON_AMQPSERVER_AMQPSERVERAPP_HPP_
#define OFFCENTER_COMMON_AMQPSERVER_AMQPSERVERAPP_HPP_

#include <boost/bind/bind.hpp>

//#include <cpprest/http_msg.h>
//#include <cpprest/http_listener.h>
//#include <pplx/pplxtasks.h>

#include "offcenter/amqp/Helper.hpp"

#include "easylogging++.h"

//#include "offcenter/common/amqpserver/AutoMethodHandler.hpp"
#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/amqpserver/IAmqpServerApp.hpp"
#include "offcenter/amqp/Listener.hpp"
//#include "offcenter/common/amqpserver/network/Utility.hpp"
//#include "offcenter/common/amqpserver/AmqpServerAppFoundation.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace common {
namespace amqpserver {

/**
 *
 */
template <class IAMQPSERVERAPP>
class AmqpManagedServerAppManager: public framework::application::AppManager<IAMQPSERVERAPP>
{
public:
	//using Listener = offcenter::amqp::Listener<AmqpDataElementInner, AmqpDataElementInner::MessageType>;

public:
	explicit AmqpManagedServerAppManager():
		framework::application::AppManager<IAMQPSERVERAPP>()//,
		//m_app()
	{}
	virtual ~AmqpManagedServerAppManager() = default;

	//void internalOnInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) {
	//	//m_app.onInitProgramOptions(optionsManager);
	//}

	void onSetUp() override {
		LOG(DEBUG) << "Initializing ActiveMQCPP Library";
		activemq::library::ActiveMQCPP::initializeLibrary();

		// Prompt general setup
		framework::application::AppManager<IAMQPSERVERAPP>::m_app.onSetUp();

		// Prompt AMQP setup
		amqp::ConnectionURIOptions options;
		framework::application::AppManager<IAMQPSERVERAPP>::m_app.onInitAMQP(options);

		// Connect to the AMQP server
		LOG(INFO) << "AMQP URI: " << options.uri();
		amqp::ActiveMQConnectionFactoryPtr connectionFactory(amqp::helper::activeMQConnectionFactoryFactory(options.uri()));

	    // Create a Connection
		m_connection = amqp::helper::connectionFactory(connectionFactory->createConnection());

		// Create Sesstions
		framework::application::AppManager<IAMQPSERVERAPP>::m_app.onInitAMQPSessions(m_connection);


		using namespace std::placeholders;

		m_managedSession = offcenter::amqp::helper::sessionFactory(m_connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));
		m_managedAllDestination = offcenter::amqp::helper::destinationFactory(m_managedSession->createTopic("offcenter.trade.admin.all"));
		m_managedAllConsumer = offcenter::amqp::helper::messageConsumerFactory(m_managedSession->createConsumer(m_managedAllDestination.get()));
		//m_managedAllListener = Listener::factory(m_managedAllConsumer, std::bind(&AmqpManagedServerAppManager::onProcessAdmin, this, _1, _2));


		m_managedAppDestination = offcenter::amqp::helper::destinationFactory(m_managedSession->createTopic("offcenter.trade.admin.<app_id>"));
		m_managedAppConsumer = offcenter::amqp::helper::messageConsumerFactory(m_managedSession->createConsumer(m_managedAppDestination.get()));
		//m_managedAppListener = Listener::factory(m_managedAppConsumer, std::bind(&AmqpManagedServerAppManager::onProcessAdmin, this, _1, _2));
	}

	//void onProcessAdmin(const cms::Message *cmsMessage, const AmqpDataElementInner& amqpInner) {

	//}

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
		m_connection->close();
		m_connection.reset();

		LOG(DEBUG) << "Shutting down ActiveMQCPP Library";
		activemq::library::ActiveMQCPP::shutdownLibrary();
		LOG(DEBUG) << "ActiveMQCPP Library shut down ";
	}

private:
	amqp::ConnectionPtr m_connection;

	amqp::SessionPtr m_managedSession;

	amqp::DestinationPtr m_managedAllDestination;
	amqp::MessageConsumerPtr m_managedAllConsumer;
//	Listener::Ptr m_managedAllListener;

	amqp::DestinationPtr m_managedAppDestination;
	amqp::MessageConsumerPtr m_managedAppConsumer;
//	Listener::Ptr m_managedAppListener;

};

} /* namespace amqpserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_AMQPSERVER_AMQPSERVERAPP_HPP_ */
