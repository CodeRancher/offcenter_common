/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the "License" );
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
 * @file   AdminControlMessage.hpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#ifndef OffcenterCommonFramework_ADMIN_ADMINCONTROLMESSAGE_HPP_
#define OffcenterCommonFramework_ADMIN_ADMINCONTROLMESSAGE_HPP_

#include <string>

#include "date/tz.h"

#include "offcenter/common/amqp/Helper.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {

/**
 *
 */
enum class AdminControlState {
	Start,
	Stop,
	Pause,
	Resume,
	Unknown
};

void to_string(const AdminControlState& state, std::string& value);
void from_string(AdminControlState& state, const std::string& value);

/**
 *
 */
class AdminControlMessage
{
public:
public:
	explicit AdminControlMessage();
	explicit AdminControlMessage(const std::string& appID);
	virtual ~AdminControlMessage();

	void setAppID(const std::string& appID);
	void set(const AdminControlState AdminControlState);

	const std::string& appID() const { return m_appID; }
	const AdminControlState state() const { return m_AdminControlState; }

	using MessageType = cms::MapMessage;

private:
	std::string m_appID;
	AdminControlState m_AdminControlState;

	friend void to_cmsMessage(AdminControlMessage::MessageType* j, const AdminControlMessage& p);
	friend void from_cmsMessage(const AdminControlMessage::MessageType* j, AdminControlMessage& p);
};

void to_cmsMessage(AdminControlMessage::MessageType* j, const AdminControlMessage& p);
void from_cmsMessage(const AdminControlMessage::MessageType* j, AdminControlMessage& p);

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_ADMIN_ADMINCONTROLMESSAGE_HPP_ */
