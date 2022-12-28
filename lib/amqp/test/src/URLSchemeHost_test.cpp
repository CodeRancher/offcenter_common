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
 * @file   URLSchemeHost_test.cpp
 * @author Scott Brauer
 * @date   11-16-2020
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::HasSubstr;

#include "offcenter/common/amqp/URLSchemeHost.hpp"

TEST (URLSchemeHost, EmptyCreationTest)
{
	offcenter::common::amqp::URLSchemeHost url;
	ASSERT_EQ(url.uri(), "tcp://localhost:61616");
	ASSERT_EQ(url.scheme(), offcenter::common::amqp::URLSchemeHost::URLScheme::tcp);
	ASSERT_EQ(url.schemeText(), "tcp");
	ASSERT_EQ(url.host(), "localhost");
	ASSERT_EQ(url.port(), 61616);
}

TEST (URLSchemeHost, CreationTest)
{
	offcenter::common::amqp::URLSchemeHost::URLScheme scheme = offcenter::common::amqp::URLSchemeHost::URLScheme::ssl;
	std::string host("amqpserver");
	int port = 12345;
	offcenter::common::amqp::URLSchemeHost url(scheme, host, port);
	ASSERT_EQ(url.uri(), "ssl://" + host + ":" + std::to_string(port));
	ASSERT_EQ(url.scheme(), scheme);
	ASSERT_EQ(url.schemeText(), "ssl");
	ASSERT_EQ(url.host(), host);
	ASSERT_EQ(url.port(), port);
}

TEST (URLSchemeHost, CopyConstructory)
{
	offcenter::common::amqp::URLSchemeHost::URLScheme scheme = offcenter::common::amqp::URLSchemeHost::URLScheme::ssl;
	std::string host("amqpserver");
	int port = 12345;
	offcenter::common::amqp::URLSchemeHost url(scheme, host, port);
	offcenter::common::amqp::URLSchemeHost urlCopy;
	urlCopy = url;
	ASSERT_EQ(urlCopy.uri(), "ssl://" + host + ":" + std::to_string(port));
	ASSERT_EQ(urlCopy.scheme(), scheme);
	ASSERT_EQ(urlCopy.schemeText(), "ssl");
	ASSERT_EQ(urlCopy.host(), host);
	ASSERT_EQ(urlCopy.port(), port);
}

