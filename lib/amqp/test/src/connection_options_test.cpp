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
 * @file   connection_options_test.cpp
 * @author Scott Brauer
 * @date   04-09-2020
 */

#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::HasSubstr;

#include "offcenter/common/amqp/ConnectionOptions.hpp"

TEST (ConnectionURIOptions, SocketOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.socketOptions.inputBufferSize = 123;
	options.socketOptions.outputBufferSize = 321;
	options.socketOptions.soLinger = 12;
	options.socketOptions.soKeepAlive = true;
	options.socketOptions.soReceiveBufferSize = 4;
	options.socketOptions.soSendBufferSize = 5;
	options.socketOptions.soConnectTimeout = 6;
	options.socketOptions.tcpNoDelay = false;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("inputBufferSize=123"));
	EXPECT_THAT(uri, HasSubstr("outputBufferSize=321"));
	EXPECT_THAT(uri, HasSubstr("soLinger=12"));
	EXPECT_THAT(uri, HasSubstr("soKeepAlive=true"));
	EXPECT_THAT(uri, HasSubstr("soReceiveBufferSize=4"));
	EXPECT_THAT(uri, HasSubstr("soSendBufferSize=5"));
	EXPECT_THAT(uri, HasSubstr("soConnectTimeout=6"));
	EXPECT_THAT(uri, HasSubstr("tcpNoDelay=false"));
}

TEST (ConnectionURIOptions, GeneralTransportOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.generalTransport.commandTracingEnabled = true;
	options.generalTransport.tcpTracingEnabled = true;
	options.generalTransport.useAsyncSend = true;
	options.generalTransport.maxResponseWaitTime = 2000;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("transport.commandTracingEnabled=true"));
	EXPECT_THAT(uri, HasSubstr("transport.tcpTracingEnabled=true"));
	EXPECT_THAT(uri, HasSubstr("transport.useAsyncSend=true"));
	EXPECT_THAT(uri, HasSubstr("transport.ResponseCorrelator.maxResponseWaitTime=2000"));
}

TEST (ConnectionURIOptions, FailoverTransportOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.failoverTransport.initialReconnectDelay = 20;
	options.failoverTransport.maxReconnectDelay = 2000;
	options.failoverTransport.useExponentialBackOff = false;
	options.failoverTransport.maxReconnectAttempts = 1;
	options.failoverTransport.startupMaxReconnectAttempts = 1;
	options.failoverTransport.randomize = false;
	options.failoverTransport.backup = true;
	options.failoverTransport.backupPoolSize = 2;
	options.failoverTransport.timeout = 0;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("initialReconnectDelay=20"));
	EXPECT_THAT(uri, HasSubstr("maxReconnectDelay=2000"));
	EXPECT_THAT(uri, HasSubstr("useExponentialBackOff=false"));
	EXPECT_THAT(uri, HasSubstr("maxReconnectAttempts=1"));
	EXPECT_THAT(uri, HasSubstr("startupMaxReconnectAttempts=1"));
	EXPECT_THAT(uri, HasSubstr("randomize=false"));
	EXPECT_THAT(uri, HasSubstr("backup=true"));
	EXPECT_THAT(uri, HasSubstr("backupPoolSize=2"));
	EXPECT_THAT(uri, HasSubstr("timeout=0"));
}

TEST (ConnectionURIOptions, TransactionOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.transaction.maxRedeliveryCount = 4;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("maxRedeliveryCount=4"));
}

TEST (ConnectionURIOptions, ConnectionOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.connection.sendTimeout = 1;
	options.connection.producerWindowSize = 1;
	options.connection.closeTimeout = 1600;
	options.connection.useAsyncSend = true;
	options.connection.alwaysSyncSend = true;
	options.connection.useCompression = true;
	options.connection.dispatchAsync = false;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("connection.sendTimeout=1"));
	EXPECT_THAT(uri, HasSubstr("connection.producerWindowSize=1"));
	EXPECT_THAT(uri, HasSubstr("connection.closeTimeout=1600"));
	EXPECT_THAT(uri, HasSubstr("connection.useAsyncSend=true"));
	EXPECT_THAT(uri, HasSubstr("connection.alwaysSyncSend=true"));
	EXPECT_THAT(uri, HasSubstr("connection.useCompression=true"));
	EXPECT_THAT(uri, HasSubstr("connection.dispatchAsync=false"));
}

TEST (ConnectionURIOptions, PrefetchPolicyOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.prefetchPolicy.durableTopicPrefetch = 110;
	options.prefetchPolicy.queueBrowserPrefetch = 510;
	options.prefetchPolicy.queuePrefetch = 1100;
	options.prefetchPolicy.topicPrefetch = 1;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("cms.PrefetchPolicy.durableTopicPrefetch=110"));
	EXPECT_THAT(uri, HasSubstr("cms.PrefetchPolicy.queueBrowserPrefetch=510"));
	EXPECT_THAT(uri, HasSubstr("cms.PrefetchPolicy.queuePrefetch=1100"));
	EXPECT_THAT(uri, HasSubstr("cms.PrefetchPolicy.topicPrefetch=1"));
}

TEST (ConnectionURIOptions, RedeliveryPolicyOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.redeliveryPolicy.backOffMultiplier = 6.0;
	options.redeliveryPolicy.collisionAvoidancePercent = 20;
	options.redeliveryPolicy.initialRedeliveryDelay = 1100;
	options.redeliveryPolicy.maximumRedeliveries = 7;
	options.redeliveryPolicy.useCollisionAvoidance = true;
	options.redeliveryPolicy.useExponentialBackOff = true;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("cms.RedeliveryPolicy.backOffMultiplier=6"));
	EXPECT_THAT(uri, HasSubstr("cms.RedeliveryPolicy.collisionAvoidancePercent=20"));
	EXPECT_THAT(uri, HasSubstr("cms.RedeliveryPolicy.initialRedeliveryDelay=1100"));
	EXPECT_THAT(uri, HasSubstr("cms.RedeliveryPolicy.maximumRedeliveries=7"));
	EXPECT_THAT(uri, HasSubstr("cms.RedeliveryPolicy.useCollisionAvoidance=true"));
	EXPECT_THAT(uri, HasSubstr("cms.RedeliveryPolicy.useExponentialBackOff=true"));
}

TEST (ConnectionURIOptions, WireFormatProtocolOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.wireFormatProtocol.wireFormat = offcenter::amqp::WireFormat::stomp;
	options.wireFormatProtocol.stackTraceEnabled = true;
	options.wireFormatProtocol.cacheEnabled = true;
	options.wireFormatProtocol.tcpNoDelayEnabled = false;
	options.wireFormatProtocol.sizePrefixDisabled = true;
	options.wireFormatProtocol.tightEncodingEnabled = true;
	options.wireFormatProtocol.maxInactivityDuration = 40000;
	options.wireFormatProtocol.maxInactivityDurationInitalDelay = 20000;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("wireFormat=stomp"));
	EXPECT_THAT(uri, HasSubstr("wireFormat.stackTraceEnabled=true"));
	EXPECT_THAT(uri, HasSubstr("wireFormat.cacheEnabled=true"));
	EXPECT_THAT(uri, HasSubstr("wireFormat.tcpNoDelayEnabled=false"));
	EXPECT_THAT(uri, HasSubstr("wireFormat.sizePrefixDisabled=true"));
	EXPECT_THAT(uri, HasSubstr("wireFormat.tightEncodingEnabled=true"));
	EXPECT_THAT(uri, HasSubstr("wireFormat.maxInactivityDuration=40000"));
	EXPECT_THAT(uri, HasSubstr("maxInactivityDurationInitalDelay=20000"));
}

TEST (ConnectionURIOptions, GeneralOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.general.prefetchSize = 1100;
	options.general.maximumPendingMessageLimit = 1;
	options.general.noLocal = true;
	options.general.dispatchAsync = true;
	options.general.retroactive = true;
	options.general.selector = "JMS1";
	options.general.exclusive = true;
	options.general.priority = 1;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("consumer.prefetchSize=1100"));
	EXPECT_THAT(uri, HasSubstr("consumer.maximumPendingMessageLimit=1"));
	EXPECT_THAT(uri, HasSubstr("consumer.noLocal=true"));
	EXPECT_THAT(uri, HasSubstr("consumer.dispatchAsync=true"));
	EXPECT_THAT(uri, HasSubstr("consumer.retroactive=true"));
	EXPECT_THAT(uri, HasSubstr("consumer.selector=JMS1"));
	EXPECT_THAT(uri, HasSubstr("consumer.exclusive=true"));
	EXPECT_THAT(uri, HasSubstr("consumer.priority=1"));
}

TEST (ConnectionURIOptions, OpenWireOnlyOptions)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.openWireOnly.browser = true;
	options.openWireOnly.networkSubscription = true;
	options.openWireOnly.optimizedAcknowledge = true;
	options.openWireOnly.noRangeAcks = true;
	options.openWireOnly.retroactive = true;

	std::string uri = options.uri();

	EXPECT_THAT(uri, HasSubstr("consumer.browser=true"));
	EXPECT_THAT(uri, HasSubstr("consumer.networkSubscription=true"));
	EXPECT_THAT(uri, HasSubstr("consumer.optimizedAcknowledge=true"));
	EXPECT_THAT(uri, HasSubstr("consumer.noRangeAcks=true"));
	EXPECT_THAT(uri, HasSubstr("consumer.retroactive=true"));
}

TEST (ConnectionURIOptions, ProtocolDefaults)
{
	offcenter::amqp::ConnectionURIOptions options;
	EXPECT_EQ(options.uri(), "tcp://localhost:61616");
	options.protocol.setTransportType(offcenter::amqp::ConnectionTransportType::ssl);
	EXPECT_EQ(options.uri(), "ssl://localhost:61616");
	options.protocol.setTransportType("failover");
	EXPECT_EQ(options.uri(), "failover://()");
	options.protocol.setTransportType("ssl");
	EXPECT_EQ(options.uri(), "ssl://localhost:61616");
	options.protocol.setTransportType("tcp");
	EXPECT_EQ(options.uri(), "tcp://localhost:61616");
	options.protocol = offcenter::amqp::ConnectionTransportType::ssl;
	EXPECT_EQ(options.uri(), "ssl://localhost:61616");
	options.protocol = "failover";
	EXPECT_EQ(options.uri(), "failover://()");
}

TEST (ConnectionURIOptions, ChangeProtocol)
{
	offcenter::amqp::ConnectionURIOptions options;
	options.protocol = offcenter::amqp::ConnectionTransportType::ssl;

	offcenter::amqp::URLSchemeHost sh1(offcenter::amqp::URLSchemeHost::URLScheme::tcp, "host1", 12345);
	options.protocol.setTCPProtocol(sh1);
	EXPECT_EQ(options.uri(), "tcp://host1:12345");

	offcenter::amqp::URLSchemeHost sh2(offcenter::amqp::URLSchemeHost::URLScheme::ssl, "host2", 23456);
	options.protocol.setSSLProtocol(sh2);
	EXPECT_EQ(options.uri(), "ssl://host2:23456");

	offcenter::amqp::URLSchemeHost sh3(offcenter::amqp::URLSchemeHost::URLScheme::tcp, "host3", 34567);
	options.protocol.addFailoverProtocol(sh3);
	EXPECT_EQ(options.uri(), "failover://(tcp://host3:34567)");
	offcenter::amqp::URLSchemeHost sh4(offcenter::amqp::URLSchemeHost::URLScheme::ssl, "host4", 45678);
	options.protocol.addFailoverProtocol(sh4);
	EXPECT_EQ(options.uri(), "failover://(tcp://host3:34567,ssl://host4:45678)");

	options.protocol.resetFailoverProtocol();
	offcenter::amqp::URLSchemeHost sh5(offcenter::amqp::URLSchemeHost::URLScheme::tcp, "host5", 56789);
	options.protocol.addFailoverProtocol(sh5);
	EXPECT_EQ(options.uri(), "failover://(tcp://host5:56789)");

}
