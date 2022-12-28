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
 * @file   AmqpConsumerExampleApp.hpp
 * @author Scott Brauer
 * @date   04-15-2021
 */

#ifndef AMQPCONSUMEREXAMPLEAPP_H_
#define AMQPCONSUMEREXAMPLEAPP_H_

#include "offcenter/common/amqpserver/IAmqpServerApp.hpp"

#include "AmqpExampleProgramOptions.hpp"
#include "AmqpDataElement.hpp"

/**
 *
 */
class PersistOandaForexDataToCSV: public offcenter::common::amqpserver::IAmqpServerApp {
public:
	explicit PersistOandaForexDataToCSV();
	virtual ~PersistOandaForexDataToCSV();

	void onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onInitAMQP(offcenter::common::amqp::ConnectionURIOptions& options) override;
	void onInitAMQPSessions(offcenter::common::amqp::ConnectionPtr connection) override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

private:
	AmqpExampleProgramOptions::ConfigPtr m_amqpOption;

	offcenter::common::amqp::SessionPtr m_session;
	offcenter::common::amqp::DestinationPtr m_destination;

};

#endif /* AMQPCONSUMEREXAMPLEAPP_H_ */
