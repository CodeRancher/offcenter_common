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
 * @file   ConnectionSettings.hpp
 * @author Scott Brauer
 * @date   05-06-2021
 */

#ifndef OFFCENTER_AMQP_CONNECTIONSETTINGS_HPP_
#define OFFCENTER_AMQP_CONNECTIONSETTINGS_HPP_

#include <string>
#include <map>
#include <regex>

#include <cms/Session.h>

namespace offcenter {
namespace common {
namespace amqp {

/**
 *
 */
class ConnectionSettings
{
public:
	enum class QueueType {
		Queue,
		TemporaryQueue,
		Topic,
		TemporaryTopic
	};

	using QueueParameters = std::map<std::string, std::string>;

public:
	explicit ConnectionSettings(
			cms::Session::AcknowledgeMode acknowledgeMode = cms::Session::AcknowledgeMode::AUTO_ACKNOWLEDGE,
			QueueType queueType = QueueType::TemporaryTopic,
			const std::string& queueName = "",
			QueueParameters queueParameters = {});
	virtual ~ConnectionSettings();

	cms::Session::AcknowledgeMode getAcknowledgeMode() const { return m_acknowledgeMode; }
	void setAcknowledgeMode(cms::Session::AcknowledgeMode value) { m_acknowledgeMode = value; }

	const std::string getQueueName() const {
		std::string queueName(m_queueName);
		for (const auto element : m_queueParameters) {
			std::ostringstream ss;
			ss << R"xx({)xx" << element.first << R"xx(})xx";
			queueName = std::regex_replace(queueName, std::regex(ss.str()), element.second);
		}
		return queueName;
	}

	void setQueueName(const std::string &value) { m_queueName = value; }
	QueueType getQueueType() const { return m_queueType; }
	void setQueueType(QueueType value) { m_queueType = value; }
	void addQueueParameter(const std::string& key, const std::string& value) { m_queueParameters[key] = value; }

private:
	cms::Session::AcknowledgeMode m_acknowledgeMode;
	QueueType m_queueType;
	std::string m_queueName;
	std::map<std::string, std::string> m_queueParameters;

};

} /* namespace amqp */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_CONNECTIONSETTINGS_HPP_ */
