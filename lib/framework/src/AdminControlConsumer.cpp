d/**
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
 * @file   AdminControlConsumer.cpp
 * @author Scott Brauer
 * @date   05-06-2021
 */

#include "easylogging++.h"

#include "offcenter/amqp/Helper.hpp"
#include "offcenter/common/framework/admin/AdminControlConsumer.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {


//AdminControlConsumer::AdminControlConsumer(offcenter::amqp::SessionConsumer::Ptr generalSessionConsumer, offcenter::amqp::SessionConsumer::Ptr specificSessionConsumer, TCallback callback/*, ICallback::Ptr adminControlHandler*/):
//		cms::MessageListener(),
//		offcenter::amqp::MessageCallback(callback),
//		m_generalSessionConsumer(std::move(generalSessionConsumer)),
//		m_specificSessionConsumer(std::move(specificSessionConsumer)),
//		m_adminControlHandler(std::move(adminControlHandler))
//{
//	m_generalSessionConsumer->consumer()->setMessageListener(this);
//	m_specificSessionConsumer->consumer()->setMessageListener(this);
//}

AdminControlConsumer::~AdminControlConsumer()
{
	// TODO Auto-generated destructor stub
}

void AdminControlConsumer::onMessage(const cms::Message* message) {
	try {
		callback<AdminControlMessage::MessageType, AdminControlMessage>(message);
	} catch(std::runtime_error& e) {
		LOG(ERROR) << e.what();
	}
}

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */
