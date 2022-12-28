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
 * @file   Session.hpp
 * @author Scott Brauer
 * @date   05-06-2021
 */
#ifndef OFFCENTER_AMQP_SESSION_HPP_
#define OFFCENTER_AMQP_SESSION_HPP_

#include "easylogging++.h"

#include "offcenter/common/amqp/Helper.hpp"
#include "offcenter/common/amqp/AMQPException.hpp"
#include "offcenter/common/amqp/ConnectionSettings.hpp"

namespace offcenter {
namespace common {
namespace amqp {

/**
 *
 */
class Session
{
public:
	explicit Session(ConnectionPtr connection, const ConnectionSettings& connectionSettings):
		m_connectionSettings(connectionSettings),
		m_session(helper::sessionFactory(connection->createSession(m_connectionSettings.getAcknowledgeMode()))),
		m_sessionID(0)
	{
		static uint sessionCnt = 0;
		static std::mutex sessionMutex;
		{
			const std::lock_guard<std::mutex> lock(sessionMutex);
			m_sessionID = ++sessionCnt;
		}

		LOG(DEBUG) << "Open Session: " << m_sessionID;
	}

	virtual ~Session() {
		LOG(DEBUG) << "Close Session: " << m_sessionID;
		m_session->close();
		m_session.reset();
	}

	const ConnectionSettings& connectionSettings() { return m_connectionSettings; }
	SessionPtr sessionPtr() const { return m_session; }
	cms::Session* session() { return m_session.get(); }

protected:
	DestinationUPtr createDestination(const std::string& queueName = "") {
		std::string fullQueueName = m_connectionSettings.getQueueName() + queueName;
		switch(m_connectionSettings.getQueueType()) {
			case ConnectionSettings::QueueType::Queue: return helper::destinationUFactory(m_session->createQueue(fullQueueName));
			case ConnectionSettings::QueueType::TemporaryQueue: return helper::destinationUFactory(m_session->createTemporaryQueue());
			case ConnectionSettings::QueueType::Topic: return helper::destinationUFactory(m_session->createTopic(fullQueueName));
			case ConnectionSettings::QueueType::TemporaryTopic: return helper::destinationUFactory(m_session->createTemporaryTopic());
			default:
				throw offcenter::common::amqp::AMQPException("Invalid Queue Type");
		}
	}

private:
	ConnectionSettings m_connectionSettings;

	SessionPtr m_session;
	uint m_sessionID;

};

} /* namespace amqp */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_SESSION_HPP_ */
