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
 * @file   RestServerExampleApp.hpp
 * @author Scott Brauer
 * @date   04-09-2021
 */

#ifndef RESTSERVEREXAMPLEAPP_H_
#define RESTSERVEREXAMPLEAPP_H_

#include "offcenter/common/restserver/IRestServerApp.hpp"
using namespace offcenter::common;

/**
 *
 */
class RestServerExampleApp: public restserver::IRestServerApp
{
public:
	explicit RestServerExampleApp();
	virtual ~RestServerExampleApp();

	//void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) override;
	//void onSetUp() override;
	void onInitMethodHandlers(restserver::AutoMethodHandler& methodHandler) override;
	void onInitEndpoint(web::uri& uri) override;
	//virtual void onExecute() = 0; override;
	//void onTearDown() override;
	//void onHelp(const std::string& help) override;
	//void onVersion() override;

};

#endif /* RESTSERVEREXAMPLEAPP_H_ */
