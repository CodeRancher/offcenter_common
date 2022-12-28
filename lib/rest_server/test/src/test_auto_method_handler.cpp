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
 * @file   test_auto_method_handler.cpp
 * @author Scott Brauer
 * @date   04-15-2021
 */

#include <string>
#include <regex>

#include <gtest/gtest.h>

#include "offcenter/common/restserver/AutoMethodHandler.hpp"

class AutoMethodHandlerFixture : public ::testing::Test {
public:
	AutoMethodHandlerFixture(): Test() {}
	virtual ~AutoMethodHandlerFixture() {}

protected:
	void SetUp() override{
		std::string path1 = "/item1/item2/item3";
		handler.addHandler(web::http::methods::GET, path1, "description1", [&](web::http::http_request& message, std::smatch& smatch) {
			executed1 = true;
			for (std::string match : smatch) {
				std::cout << match << std::endl;
			}
		});

		std::string path2 = "/item1/([^/]*)/item3";
		handler.addHandler(web::http::methods::GET, path2, "description2", [&](web::http::http_request& message, std::smatch& smatch) {
			executed2 = true;
			for (std::string match : smatch) {
				std::cout << match << std::endl;
			}
		});

		std::string path3 = "/item1/([^/]*)";
		handler.addHandler(web::http::methods::GET, path3, "description3", [&](web::http::http_request& message, std::smatch& smatch) {
			executed3 = true;
			for (std::string match : smatch) {
				std::cout << match << std::endl;
			}
		});

		std::string path4 = "/item1/([^/]*)/item3";
		handler.addHandler(web::http::methods::PUT, path4, "description4", [&](web::http::http_request& message, std::smatch& smatch) {
			executed4 = true;
			for (std::string match : smatch) {
				std::cout << match << std::endl;
			}
		});
	}

	void TearDown() override {}

protected:
	offcenter::common::restserver::AutoMethodHandler handler;
	bool executed1 = false;
	bool executed2 = false;
	bool executed3 = false;
	bool executed4 = false;
};

TEST_F (AutoMethodHandlerFixture, PathCompletelyDefined)
{
	web::http::http_request request;
	request.set_request_uri(web::uri("http://base/item1/item2/item3?query=something"));

	handler.findAndExecute(request);
	EXPECT_TRUE(executed1);
	EXPECT_TRUE(executed2);
	EXPECT_FALSE(executed3);
	EXPECT_FALSE(executed4);

}

TEST_F (AutoMethodHandlerFixture, PathMiddleValue)
{
	web::http::http_request request;
	request.set_request_uri(web::uri("http://base/item1/blahblah/item3?query=something"));

	handler.findAndExecute(request);
	EXPECT_FALSE(executed1);
	EXPECT_TRUE(executed2);
	EXPECT_FALSE(executed3);
	EXPECT_FALSE(executed4);

}

TEST_F (AutoMethodHandlerFixture, PathOverlap)
{
	web::http::http_request request;
	request.set_request_uri(web::uri("http://base/item1/blahblah?query=something"));

	handler.findAndExecute(request);
	EXPECT_FALSE(executed1);
	EXPECT_FALSE(executed2);
	EXPECT_TRUE(executed3);
	EXPECT_FALSE(executed4);

}

TEST_F (AutoMethodHandlerFixture, PathPut)
{
	web::http::http_request request(web::http::methods::PUT);
	request.set_request_uri(web::uri("http://base/item1/item2/item3?query=something"));

	handler.findAndExecute(request);
	EXPECT_FALSE(executed1);
	EXPECT_FALSE(executed2);
	EXPECT_FALSE(executed3);
	EXPECT_TRUE(executed4);

}


