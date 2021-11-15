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
 * @file   test_auto_method_path.cpp
 * @author Scott Brauer
 * @date   04-15-2021
 */

#include <string>
#include <regex>

#include <gtest/gtest.h>

#include "offcenter/common/amqpserver/AutoMethodPath.hpp"
using namespace offcenter::common;

TEST (AutoMethodPath, BasicPath)
{
	std::string path = "/item1/item2/item3";
	std::string description = "description";
	bool executed = false;
	auto action = [&path,&executed](web::http::http_request& message, std::smatch& smatch) {
		EXPECT_EQ(smatch.size(), 1);
		EXPECT_EQ(smatch[0], path);
		executed = true;
		std::cout << "In action" << std::endl;
	};

	restserver::IAutoMethodPath::Ptr autoMethodPath = restserver::autoMethodPathFactory(path, description, action);

	EXPECT_EQ(autoMethodPath->path(), path);
	EXPECT_EQ(autoMethodPath->description(), description);

	web::uri uri(path);
	web::http::http_request request;
	request.set_request_uri(web::uri("http://base" + path));
	std::smatch smatch;
	auto relativePath = web::uri::uri::decode(request.relative_uri().path());
	std::cout << relativePath << std::endl;
	std::cout << path << std::endl;
	EXPECT_TRUE(std::regex_match(relativePath, smatch, autoMethodPath->regex()));

	autoMethodPath->action(request, smatch);
	EXPECT_TRUE(executed);

}

TEST (AutoMethodPath, MatchPath)
{
	std::string path = "/item1/(.*)/item3";
	std::string description = "description";
	bool executed = false;
	auto action = [&path,&executed](web::http::http_request& message, std::smatch& smatch) {
		EXPECT_EQ(smatch.size(), 2);
		EXPECT_EQ(smatch[1], "item2");
		executed = true;
		std::cout << "In action" << std::endl;
	};

	restserver::IAutoMethodPath::Ptr autoMethodPath = restserver::autoMethodPathFactory(path, description, action);

	EXPECT_EQ(autoMethodPath->path(), path);
	EXPECT_EQ(autoMethodPath->description(), description);

	web::http::http_request request;
	request.set_request_uri(web::uri("http://base/item1/item2/item3"));
	std::smatch smatch;
	auto relativePath = web::uri::uri::decode(request.relative_uri().path());
	std::cout << relativePath << std::endl;
	std::cout << path << std::endl;
	EXPECT_TRUE(std::regex_match(relativePath, smatch, autoMethodPath->regex()));

	autoMethodPath->action(request, smatch);
	EXPECT_TRUE(executed);

}

