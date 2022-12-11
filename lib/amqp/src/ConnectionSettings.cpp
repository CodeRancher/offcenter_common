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
 * @file   ConnectionSettings.cpp
 * @author Scott Brauer
 * @date   05-06-2021
 */
#include "offcenter/common/amqp/ConnectionSettings.hpp"

namespace offcenter {
namespace amqp {

ConnectionSettings::ConnectionSettings(cms::Session::AcknowledgeMode acknowledgeMode, QueueType queueType, const std::string& queueName, QueueParameters queueParameters):
		m_acknowledgeMode(acknowledgeMode),
		m_queueType(queueType),
		m_queueName(queueName),
		m_queueParameters(queueParameters)
{
	// TODO Auto-generated constructor stub

}

ConnectionSettings::~ConnectionSettings()
{
	// TODO Auto-generated destructor stub
}

} /* namespace amqp */
} /* namespace offcenter */
