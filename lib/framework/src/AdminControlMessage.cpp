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
 * @file   AdminControlMessage.cpp
 * @author Scott Brauer
 * @date   05-04-2021
 */

#include <map>

#include "easylogging++.h"

#include "offcenter/common/framework/admin/AdminControlMessage.hpp"
#include "offcenter/common/Utility.hpp"
#include "offcenter/common/RuntimeException.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {

void to_string(const AdminControlState &state, std::string &value)
{
	switch(state) {
		case AdminControlState::Start:
			value = "Start";
			break;
		case AdminControlState::Stop:
			value = "Stop";
			break;
		case AdminControlState::Pause:
			value = "Pause";
			break;
		case AdminControlState::Resume:
			value = "Resume";
			break;
		case AdminControlState::Unknown:
			value = "Unknown";
			break;

	}
}

void from_string(AdminControlState &state, const std::string &value)
{
	static std::map<std::string, AdminControlState> lookup = {
		{"start", AdminControlState::Start},
		{"stop", AdminControlState::Stop},
		{"pause", AdminControlState::Pause},
		{"resume", AdminControlState::Resume},
		{"unknown", AdminControlState::Unknown}
	};

	try {
		state = lookup.at(offcenter::common::toLower(value));
	} catch(std::out_of_range& e) {
		std::string msg("Unknown AdminControlState string (");
		msg += value;
		msg += ")";
		LOG(ERROR) << msg;
		state = AdminControlState::Unknown;
	}
}


AdminControlMessage::AdminControlMessage():
		m_appID(""),
		m_AdminControlState(AdminControlState::Unknown)
{
}

AdminControlMessage::AdminControlMessage(const std::string& appID):
		m_appID(appID),
		m_AdminControlState(AdminControlState::Unknown)
{
	// TODO Auto-generated constructor stub

}

AdminControlMessage::~AdminControlMessage()
{
	// TODO Auto-generated destructor stub
}

void AdminControlMessage::setAppID(const std::string &appID)
{
	m_appID = appID;
}

void AdminControlMessage::set(const AdminControlState AdminControlState)
{
	m_AdminControlState = AdminControlState;
}

void to_cmsMessage(AdminControlMessage::MessageType* j, const AdminControlMessage &p)
{
	j->setString("app_id", p.m_appID);
	std::string AdminControlState;
	to_string(p.m_AdminControlState, AdminControlState);
	j->setString("admin_status_state", AdminControlState);
}

void from_cmsMessage(const AdminControlMessage::MessageType* j, AdminControlMessage &p)
{
	p.setAppID(j->getString("app_id"));
	AdminControlState AdminControlState;
	std::string tmp = j->getString("admin_status_state");
	from_string(AdminControlState, tmp);
	p.set(
		AdminControlState
	);

}

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */
