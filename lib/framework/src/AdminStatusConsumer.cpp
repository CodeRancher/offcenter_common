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
 * @file   AdminStatusConsumer.cpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#include "easylogging++.h"

#include "offcenter/common/amqp/Helper.hpp"
#include "offcenter/common/framework/admin/AdminStatusConsumer.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {

/*
AdminStatusConsumer::AdminStatusConsumer(offcenter::common::amqp::SessionConsumer::Ptr sessionConsumer, ICallback::Ptr adminStatusHandler):
	m_sessionConsumer(std::move(sessionConsumer)),
	m_adminStatusHandler(std::move(adminStatusHandler))
{
	m_sessionConsumer->consumer()->setMessageListener(this);
}

AdminStatusConsumer::~AdminStatusConsumer()
{
	// TODO Auto-generated destructor stub
}

void AdminStatusConsumer::onMessage(const cms::Message* message) {
	try {
		callback<AdminStatusMessage::MessageType, AdminStatusMessage>(message);
	} catch(std::runtime_error& e) {
		LOG(ERROR) << e.what();
	}
}
*/

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */
