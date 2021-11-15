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
 * @file   AdminStatusMessage.cpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#include <map>

#include "easylogging++.h"

#include "offcenter/common/framework/admin/AdminStatusMessage.hpp"
#include "offcenter/common/Utility.hpp"
#include "offcenter/common/RuntimeException.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {

void to_string(const AdminStatusState &state, std::string &value)
{
	switch(state) {
		case AdminStatusState::Ready:
			value = "Ready";
			break;
		case AdminStatusState::Starting:
			value = "Starting";
			break;
		case AdminStatusState::Running:
			value = "Running";
			break;
		case AdminStatusState::Stopping:
			value = "Stopping";
			break;
		case AdminStatusState::Stopped:
			value = "Stopped";
			break;
		case AdminStatusState::Pausing:
			value = "Pausing";
			break;
		case AdminStatusState::Paused:
			value = "Paused";
			break;
		case AdminStatusState::Resuming:
			value = "Resuming";
			break;
		case AdminStatusState::Error:
			value = "Error";
			break;
		case AdminStatusState::Unknown:
			value = "Unknown";
			break;

	}
}

void from_string(AdminStatusState &state, const std::string &value)
{
	static std::map<std::string, AdminStatusState> lookup = {
		{"ready", AdminStatusState::Ready},
		{"starting", AdminStatusState::Starting},
		{"running", AdminStatusState::Running},
		{"stopping", AdminStatusState::Stopping},
		{"stopped", AdminStatusState::Stopped},
		{"pausing", AdminStatusState::Pausing},
		{"paused", AdminStatusState::Paused},
		{"resuming", AdminStatusState::Resuming},
		{"error", AdminStatusState::Error},
		{"unknown", AdminStatusState::Unknown}
	};

	try {
		state = lookup.at(offcenter::common::toLower(value));
	} catch(std::out_of_range& e) {
		std::string msg("Unknown AdminStatusState string (");
		msg += value;
		msg += ")";
		LOG(ERROR) << msg;
		state = AdminStatusState::Unknown;
	}
}


AdminStatusMessage::AdminStatusMessage():
		m_appID(""),
		m_adminStatusState(AdminStatusState::Unknown)
{
}

AdminStatusMessage::AdminStatusMessage(const std::string& appID):
		m_appID(appID),
		m_adminStatusState(AdminStatusState::Unknown)
{
	// TODO Auto-generated constructor stub

}

AdminStatusMessage::~AdminStatusMessage()
{
	// TODO Auto-generated destructor stub
}

void AdminStatusMessage::setAppID(const std::string &appID)
{
	m_appID = appID;
}

void AdminStatusMessage::set(const AdminStatusState adminStatusState)
{
	m_adminStatusState = adminStatusState;
}

void to_cmsMessage(AdminStatusMessage::MessageType* j, const AdminStatusMessage &p)
{
	j->setString("app_id", p.m_appID);
	std::string adminStatusState;
	to_string(p.m_adminStatusState, adminStatusState);
	j->setString("admin_status_state", adminStatusState);
}

void from_cmsMessage(const AdminStatusMessage::MessageType* j, AdminStatusMessage &p)
{
	p.setAppID(j->getString("app_id"));
	AdminStatusState adminStatusState;
	std::string tmp = j->getString("admin_status_state");
	from_string(adminStatusState, tmp);
	p.set(
		adminStatusState
	);

}

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */
