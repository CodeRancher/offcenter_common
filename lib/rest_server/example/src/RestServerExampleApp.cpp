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
 * @file   RestServerExampleApp.cpp
 * @author Scott Brauer
 * @date   04-09-2021
 */

#include <iostream>
#include <regex>

#include "easylogging++.h"

#include "RestServerExampleApp.hpp"

RestServerExampleApp::RestServerExampleApp():
	IRestServerApp()
{

}

RestServerExampleApp::~RestServerExampleApp() {
	// TODO Auto-generated destructor stub
}

//void RestServerExampleApp::onInitProgramOptions(
//        program_options::ProgramOptionsManager &optionsManager)
//{
//}

//void RestServerExampleApp::onSetUp()
//{
//}

void RestServerExampleApp::onInitMethodHandlers(restserver::AutoMethodHandler &methodHandler)
{
	methodHandler.addHandler(web::http::methods::GET,
		"/goober/([^/]*)",
		"Description of goober",
		[](web::http::http_request& message, std::smatch& smatch) {
			std::string result = "goober::" + std::string(smatch[1]);
			message.reply(web::http::status_codes::OK, result);
		}
	);

	methodHandler.addHandler(web::http::methods::GET,
		"/goober/([^/]*)/details",
		"Description of goober:details",
		[](web::http::http_request& message, std::smatch& smatch) {
			std::string result = "goober::" + std::string(smatch[1]) + "::details";
			message.reply(web::http::status_codes::OK, result);
		}
	);

	methodHandler.addHandler(web::http::methods::GET,
		"/goober/([^/]*)/action",
		"Description of goober:action",
		[](web::http::http_request& message, std::smatch& smatch) {
			std::string result = "goober::" + std::string(smatch[1]) + "::action";
			message.reply(web::http::status_codes::OK, result);
		}
	);
}

void RestServerExampleApp::onInitEndpoint(web::uri &uri)
{
	uri = web::uri("http://host_auto_ip4:6502/v1/ivmero/api");
}

//void RestServerExampleApp::onTearDown()
//{
//}
//
//void RestServerExampleApp::onHelp(const std::string &help)
//{
//}
//
//void RestServerExampleApp::onVersion()
//{
//}
