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
 * @file   AdminControlProducer.cpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#include <thread>

#include "easylogging++.h"

#include "offcenter/common/framework/admin/AdminControlProducer.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {

AdminControlProducer::AdminControlProducer(offcenter::amqp::SessionProducerDynamicDestination::Ptr sessionProducer, const std::string& appID):
		m_sessionProducer(std::move(sessionProducer)),
		m_lastMessage(appID)
{

}

AdminControlProducer::~AdminControlProducer()
{
}

void AdminControlProducer::start()
{
	sendMessage("#all#", AdminControlState::Start);
}

void AdminControlProducer::start(const std::string& appID)
{
	sendMessage(appID, AdminControlState::Start);
}

void AdminControlProducer::stop()
{
	sendMessage("#all#", AdminControlState::Stop);
}

void AdminControlProducer::stop(const std::string& appID)
{
	sendMessage(appID, AdminControlState::Stop);
}

void AdminControlProducer::pause()
{
	sendMessage("#all#", AdminControlState::Pause);
}

void AdminControlProducer::pause(const std::string& appID)
{
	sendMessage(appID, AdminControlState::Pause);
}

void AdminControlProducer::resume()
{
	sendMessage("#all#", AdminControlState::Resume);
}

void AdminControlProducer::resume(const std::string& appID)
{
	sendMessage(appID, AdminControlState::Resume);
}

void AdminControlProducer::sendMessage(const std::string& appID, const AdminControlState adminControlState)
{
	const std::lock_guard<std::mutex> lock(m_sendMutex);
	m_lastMessage.setAppID(appID);
	m_lastMessage.set(adminControlState);
	m_sessionProducer->send<AdminControlMessage::MessageType>(m_lastMessage, appID);
}

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */
