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
 * @file   AdminStatusMessage.hpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#ifndef OffcenterCommonFramework_ADMIN_ADMINSTATUSMESSAGE_HPP_
#define OffcenterCommonFramework_ADMIN_ADMINSTATUSMESSAGE_HPP_

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
enum class AdminStatusState {
	Ready,
	Starting,
	Running,
	Stopping,
	Stopped,
	Pausing,
	Paused,
	Resuming,
	Error,
	Unknown
};

void to_string(const AdminStatusState& state, std::string& value);
void from_string(AdminStatusState& state, const std::string& value);

/**
 *
 */
class AdminStatusMessage
{
public:
public:
	explicit AdminStatusMessage();
	explicit AdminStatusMessage(const std::string& appID);
	virtual ~AdminStatusMessage();

	void setAppID(const std::string& appID);
	void set(const AdminStatusState adminStatusState);

	const std::string& appID() const { return m_appID; }
	const AdminStatusState state() const { return m_adminStatusState; }

	using MessageType = cms::MapMessage;

private:
	std::string m_appID;
	AdminStatusState m_adminStatusState;

	friend void to_cmsMessage(AdminStatusMessage::MessageType* j, const AdminStatusMessage& p);
	friend void from_cmsMessage(const AdminStatusMessage::MessageType* j, AdminStatusMessage& p);
};

void to_cmsMessage(AdminStatusMessage::MessageType* j, const AdminStatusMessage& p);
void from_cmsMessage(const AdminStatusMessage::MessageType* j, AdminStatusMessage& p);

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_ADMIN_ADMINSTATUSMESSAGE_HPP_ */
