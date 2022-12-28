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
 * @file   AmqpManagedExampleApp.hpp
 * @author Scott Brauer
 * @date   04-28-2021
 */

#ifndef AMQPMANAGEDEXAMPLEAPP_H_
#define AMQPMANAGEDEXAMPLEAPP_H_

#include "offcenter/common/amqpserver/IAmqpManagedServerApp.hpp"

#include "AmqpExampleProgramOptions.hpp"
#include "AmqpDataElement.hpp"

/**
 *
 */
class AmqpManagedExampleApp: public amqpserver::IAmqpManagedServerApp {
public:
	explicit AmqpManagedExampleApp();
	virtual ~AmqpManagedExampleApp();

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onInitAMQP(amqp::ConnectionURIOptions& options) override;
	void onInitAMQPSessions(amqp::ConnectionPtr connection) override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

	void onStart() override;
	void onStop() override;
	void onPause() override;
	void onResume() override;

private:
	AmqpExampleProgramOptions::ConfigPtr m_amqpOption;

	offcenter::common::amqp::SessionPtr m_session;
};

#endif /* AMQPMANAGEDEXAMPLEAPP_H_ */
