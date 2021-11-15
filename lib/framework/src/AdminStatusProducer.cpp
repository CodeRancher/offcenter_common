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
 * @file   AdminStatusProvider.cpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#include "offcenter/common/framework/admin/AdminStatusProducer.hpp"

#include <thread>

#include "easylogging++.h"


namespace offcenter {
namespace common {
namespace framework {
namespace admin {

AdminStatusProducer::AdminStatusProducer(offcenter::amqp::SessionProducer::Ptr&& sessionProducer, const std::string& appID):
		Parent(std::forward<offcenter::amqp::SessionProducer::Ptr>(sessionProducer), appID),
		m_lastMessage(appID)
{

}

AdminStatusProducer::~AdminStatusProducer()
{
}

void AdminStatusProducer::ready()
{
	sendMessage(AdminStatusState::Ready);
}

void AdminStatusProducer::starting()
{
	sendMessage(AdminStatusState::Starting);
}

void AdminStatusProducer::running()
{
	sendMessage(AdminStatusState::Running);
}

void AdminStatusProducer::stopping()
{
	sendMessage(AdminStatusState::Stopping);
}

void AdminStatusProducer::stopped()
{
	sendMessage(AdminStatusState::Stopped);
}

void AdminStatusProducer::pausing()
{
	sendMessage(AdminStatusState::Pausing);
}

void AdminStatusProducer::paused()
{
	sendMessage(AdminStatusState::Paused);
}

void AdminStatusProducer::resuming()
{
	sendMessage(AdminStatusState::Resuming);
}

void AdminStatusProducer::error()
{
	sendMessage(AdminStatusState::Error);
}

void AdminStatusProducer::unknown()
{
	sendMessage(AdminStatusState::Unknown);
}

void AdminStatusProducer::sendMessage(const AdminStatusState adminStatusState)
{
	m_lastMessage.set(adminStatusState);
	std::string adminStatusStateStr;
	to_string(adminStatusState, adminStatusStateStr);
	LOG(DEBUG) << "sendMessage Begin: " << adminStatusStateStr;
	Parent::sendMessage(m_lastMessage);
	LOG(DEBUG) << "sendMessage After: " << adminStatusStateStr;
}

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */
