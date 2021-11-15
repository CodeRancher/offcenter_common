// Copyright 2020 Scott Brauer
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @brief  Creates a connection to an ActiveMQ Server
 * @file   Helper.cpp
 * @author Scott Brauer
 * @date   04-21-2021
 */

#include "easylogging++.h"

#include "offcenter/amqp/Helper.hpp"

namespace offcenter {
namespace amqp {
namespace helper {

ActiveMQConnectionFactoryPtr activeMQConnectionFactoryFactory(const std::string &brokerURI, const std::string &username, const std::string &password) {
	return std::make_shared<activemq::core::ActiveMQConnectionFactory>(brokerURI);
}


ActiveMQConnectionFactoryPtr activeMQConnectionFactoryFactory(const ConnectionURIOptions &brokerConnectionOptions, const std::string &username, const std::string &password) {
	return helper::activeMQConnectionFactoryFactory(brokerConnectionOptions.uri(), username, password);
}

/**
 * Create an ActiveMQ Connection shared pointer with an appropriate deleter.
 *
 * @param connection
 */
ConnectionPtr connectionFactory(cms::Connection* connection)
{
	return ConnectionPtr(connection, [](auto connection) {
		if (connection) {
			try {
				connection->close();
			} catch (cms::CMSException& ex) {
				LOG(ERROR) << ex.getStackTraceString();
			}
			delete connection;
		}
	});
}

ConnectionUPtr connectionUFactory(cms::Connection* connection) {
	return ConnectionUPtr(connection, [](auto connection) {
		if (connection) {
			try {
				connection->close();
			} catch (cms::CMSException& ex) {
				LOG(ERROR) << ex.getStackTraceString();
			}
			delete connection;
		}
	});
}

SessionPtr sessionFactory(cms::Session* session) {
	return SessionPtr(session, [](auto session) {
		if (session) {
			try {
				session->close();
			} catch (cms::CMSException& ex) {
				LOG(ERROR) << ex.getStackTraceString();
			}
			delete session;
		}
	});
}

SessionUPtr sessionUFactory(cms::Session* session) {
	return SessionUPtr(session, [](auto session) {
		if (session) {
			try {
				session->close();
			} catch (cms::CMSException& ex) {
				LOG(ERROR) << ex.getStackTraceString();
			}
			delete session;
		}
	});
}

DestinationPtr destinationFactory(cms::Destination* destination) {
	return DestinationPtr(destination);
}

DestinationUPtr destinationUFactory(cms::Destination* destination) {
	return DestinationUPtr(destination);
}

MessageProducerPtr messageProducerFactory(cms::MessageProducer* messageProducer) {
	return MessageProducerPtr(messageProducer, [](auto messageProducer) {
		if (messageProducer) {
			try {
				messageProducer->close();
			} catch (cms::CMSException& ex) {
				LOG(ERROR) << ex.getStackTraceString();
			}
			delete messageProducer;
		}
	});
}

MessageProducerUPtr messageProducerUFactory(cms::MessageProducer* messageProducer) {
	return MessageProducerUPtr(messageProducer, [](auto messageProducer) {
		if (messageProducer) {
			try {
				messageProducer->close();
			} catch (cms::CMSException& ex) {
				LOG(ERROR) << ex.getStackTraceString();
			}
			delete messageProducer;
		}
	});
}

MessageConsumerPtr messageConsumerFactory(cms::MessageConsumer* messageConsumer) {
	return MessageConsumerPtr(messageConsumer, [](auto messageConsumer) {
		if (messageConsumer) {
			try {
				messageConsumer->close();
			} catch (cms::CMSException& ex) {
				LOG(ERROR) << ex.getStackTraceString();
			}
			delete messageConsumer;
		}
	});
}

MessageConsumerUPtr messageConsumerUFactory(cms::MessageConsumer* messageConsumer) {
	return MessageConsumerUPtr(messageConsumer, [](auto messageConsumer) {
		if (messageConsumer) {
			try {
				messageConsumer->close();
			} catch (cms::CMSException& ex) {
				LOG(ERROR) << ex.getStackTraceString();
			}
			delete messageConsumer;
		}
	});
}

//class ActiveMQCPP {
//	explicit ActiveMQCPP() {
//		activemq::library::ActiveMQCPP::initializeLibrary();
//	}
//
//	virtual ~ActiveMQCPP() {
//		activemq::library::ActiveMQCPP::shutdownLibrary();
//	}
//};

} /* namespace helper */
} /* namespace amqp */
} /* namespace offcenter */
