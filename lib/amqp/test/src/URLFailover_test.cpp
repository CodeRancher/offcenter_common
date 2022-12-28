// Copyright 2020 Scott Brauer
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

///
/// \file   URLFailover_test.hpp
/// \author Scott Brauer
/// \date   Nov 16, 2020
///

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::HasSubstr;

#include "offcenter/common/amqp/URLFailover.hpp"

TEST (URLFailover, EmptyCreationTest)
{
	offcenter::common::amqp::URLFailover url;
	ASSERT_EQ(url.uri(), "failover://()");
}

TEST (URLFailover, AddOneElement)
{
	offcenter::common::amqp::URLSchemeHost url1(offcenter::common::amqp::URLSchemeHost::URLScheme::ssl, "host1", 12345);

	offcenter::common::amqp::URLFailover url;
	url.addHost(url1);
	ASSERT_EQ(url.uri(), "failover://(ssl://host1:12345)");
}

TEST (URLFailover, AddTwoElements)
{
	offcenter::common::amqp::URLSchemeHost url1(offcenter::common::amqp::URLSchemeHost::URLScheme::ssl, "host1", 12345);
	offcenter::common::amqp::URLSchemeHost url2(offcenter::common::amqp::URLSchemeHost::URLScheme::tcp, "host2", 54321);

	offcenter::common::amqp::URLFailover url;
	url.addHost(url1);
	url.addHost(url2);
	ASSERT_EQ(url.uri(), "failover://(ssl://host1:12345,tcp://host2:54321)");
}

TEST (URLFailover, CopyTwoElements)
{
	offcenter::common::amqp::URLSchemeHost url1(offcenter::common::amqp::URLSchemeHost::URLScheme::ssl, "host1", 12345);
	offcenter::common::amqp::URLSchemeHost url2(offcenter::common::amqp::URLSchemeHost::URLScheme::tcp, "host2", 54321);

	offcenter::common::amqp::URLFailover url;
	url.addHost(url1);
	url.addHost(url2);
	offcenter::common::amqp::URLFailover urlCopy = url;

	ASSERT_EQ(urlCopy.uri(), "failover://(ssl://host1:12345,tcp://host2:54321)");
}
