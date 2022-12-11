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
 * @file   Session.cpp
 * @author Scott Brauer
 * @date   05-06-2021
 */

#include "offcenter/common/amqp/Session.hpp"

namespace offcenter {
namespace amqp {

Session::Session(ConnectionPtr connection, const ConnectionSettings& connectionSettings):
		m_connectionSettings(connectionSettings),
		m_session(helper::sessionFactory(connection->createSession(m_connectionSettings.getAcknowledgeMode())))
{
}

Session::~Session()
{
	// TODO Auto-generated destructor stub
}

} /* namespace amqp */
} /* namespace offcenter */
