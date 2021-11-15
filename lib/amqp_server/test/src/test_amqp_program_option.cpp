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
 * @file   test_amqp_program_options.hpp
 * @author Scott Brauer
 * @date   10-05-2021
 */

#include <vector>
#include <array>
#include <initializer_list>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "offcenter/common/amqpserver/AmqpConnectionProgramOptions.hpp"
#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/SimulatedCommandLine.hpp"

class AmqpProgramOptionsPTests :
		public ::testing::TestWithParam<std::tuple<std::string, std::string, std::string>> {
};

TEST(AmqpProgramOptions, TCP) {
	offcenter::common::SimulatedCommandLine commandLine(
			"TCP", { "--amqp.protocol", "tcp",
					 "--amqp.host", "NonStandardHost",
					 "--amqp.port", "1234" });

	offcenter::common::program_options::ProgramOptionsManager optManager;
	offcenter::common::amqpserver::AmqpConnectionProgramOptions::ConfigPtr configPtr;
	configPtr = optManager.add<offcenter::common::amqpserver::AmqpConnectionProgramOptions>();
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	std::string uri = configPtr->uri() + "&";
	EXPECT_THAT(uri, ::testing::ContainsRegex("^tcp:"));
	EXPECT_THAT(uri, ::testing::ContainsRegex("//NonStandardHost:"));
	EXPECT_THAT(uri, ::testing::ContainsRegex(":1234&"));
}

TEST(AmqpProgramOptions, SSL) {
	offcenter::common::SimulatedCommandLine commandLine(
			"SSL", { "--amqp.protocol", "ssl",
					 "--amqp.host", "NonStandardHost",
					 "--amqp.port", "1234" });

	offcenter::common::program_options::ProgramOptionsManager optManager;
	offcenter::common::amqpserver::AmqpConnectionProgramOptions::ConfigPtr configPtr;
	configPtr = optManager.add<offcenter::common::amqpserver::AmqpConnectionProgramOptions>();
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	std::string uri = configPtr->uri() + "&";
	EXPECT_THAT(uri, ::testing::ContainsRegex("^ssl:"));
	EXPECT_THAT(uri, ::testing::ContainsRegex("//NonStandardHost:"));
	EXPECT_THAT(uri, ::testing::ContainsRegex(":1234&"));
}

TEST(AmqpProgramOptions, Failover) {
	offcenter::common::SimulatedCommandLine commandLine(
			"Failover", { "--amqp.protocol", "failover",
						  "--amqp.failover", "tcp://anotherhost:12345", "ssl://adifferenthost:54321" });

	offcenter::common::program_options::ProgramOptionsManager optManager;
	offcenter::common::amqpserver::AmqpConnectionProgramOptions::ConfigPtr configPtr;
	configPtr = optManager.add<offcenter::common::amqpserver::AmqpConnectionProgramOptions>();
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	std::string uri = configPtr->uri() + "&";
	EXPECT_THAT(uri, ::testing::ContainsRegex("^failover"));
	EXPECT_THAT(uri, ::testing::ContainsRegex("tcp://anotherhost:12345"));
	std::cout << uri << std::endl;
}

TEST_P(AmqpProgramOptionsPTests, TestCommandLine) {
	offcenter::common::SimulatedCommandLine commandLine(
			std::get<0>(GetParam()) + "-"+ std::get<2>(GetParam()), { "--amqp." + std::get<0>(GetParam()), std::get<2>(GetParam()) });

	offcenter::common::program_options::ProgramOptionsManager optManager;
	offcenter::common::amqpserver::AmqpConnectionProgramOptions::ConfigPtr configPtr;
	configPtr = optManager.add<offcenter::common::amqpserver::AmqpConnectionProgramOptions>();
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	std::string uri = configPtr->uri() + "&";
	EXPECT_THAT(uri, ::testing::ContainsRegex("[?&]" + std::get<1>(GetParam()) + "=" + std::get<2>(GetParam()) + "&"));
}

INSTANTIATE_TEST_CASE_P(
		AmqpProgramOptionsTests,
        AmqpProgramOptionsPTests,
        ::testing::Values(
         		std::make_tuple("socket_options.input_buffer_size", "inputBufferSize", "9876"),
        		std::make_tuple("socket_options.output_buffer_size", "outputBufferSize", "8765"),
        		std::make_tuple("socket_options.so_linger", "soLinger", "7654"),
        		std::make_tuple("socket_options.so_keep_alive", "soKeepAlive", "true"),
        		std::make_tuple("socket_options.so_receive_buffer_size", "soReceiveBufferSize", "6543"),
        		std::make_tuple("socket_options.so_send_buffer_size", "soSendBufferSize", "5432"),
        		std::make_tuple("socket_options.so_connect_timeout", "soConnectTimeout", "4321"),
        		std::make_tuple("socket_options.tcp_no_delay", "tcpNoDelay", "false"),

        		std::make_tuple("general_transport.command_tracing_enabled", "transport.commandTracingEnabled", "true"),
        		std::make_tuple("general_transport.tcp_tracing_enabled", "transport.tcpTracingEnabled", "true"),
        		std::make_tuple("general_transport.use_async_send", "transport.useAsyncSend", "true"),
        		std::make_tuple("general_transport.max_response_wait_time", "transport.ResponseCorrelator.maxResponseWaitTime", "1234"),

        		std::make_tuple("failover_transport.initial_reconnect_delay", "initialReconnectDelay", "9"),
        		std::make_tuple("failover_transport.max_reconnect_delay", "maxReconnectDelay", "2999"),
        		std::make_tuple("failover_transport.use_exponential_back_off", "useExponentialBackOff", "false"),
        		std::make_tuple("failover_transport.max_reconnect_attempts", "maxReconnectAttempts", "1234"),
        		std::make_tuple("failover_transport.startup_max_reconnect_attempts", "startupMaxReconnectAttempts", "1234"),
        		std::make_tuple("failover_transport.randomize", "randomize", "false"),
        		std::make_tuple("failover_transport.backup", "backup", "true"),
        		std::make_tuple("failover_transport.backup_pool_size", "backupPoolSize", "11"),
        		std::make_tuple("failover_transport.timeout", "timeout", "27"),

        		std::make_tuple("transaction.max_redelivery_count", "transaction.maxRedeliveryCount", "9"),

           		std::make_tuple("connection.send_timeout", "connection.sendTimeout", "1"),
        		std::make_tuple("connection.producer_window_size", "connection.producerWindowSize", "2"),
        		std::make_tuple("connection.close_timeout", "connection.closeTimeout", "14987"),
        		std::make_tuple("connection.use_async_send", "connection.useAsyncSend", "true"),
        		std::make_tuple("connection.always_sync_send", "connection.alwaysSyncSend", "true"),
        		std::make_tuple("connection.use_compression", "connection.useCompression", "true"),
        		std::make_tuple("connection.dispatch_async", "connection.dispatchAsync", "false"),

        		std::make_tuple("prefetch_policy.durable_topic_prefetch", "cms.PrefetchPolicy.durableTopicPrefetch", "99"),
        		std::make_tuple("prefetch_policy.queue_browser_prefetch", "cms.PrefetchPolicy.queueBrowserPrefetch", "499"),
        		std::make_tuple("prefetch_policy.queue_prefetch", "cms.PrefetchPolicy.queuePrefetch", "999"),
        		std::make_tuple("prefetch_policy.topic_prefetch", "cms.PrefetchPolicy.topicPrefetch", "123"),

        		std::make_tuple("redelivery_policy.back_off_multiplier", "cms.RedeliveryPolicy.backOffMultiplier", "123.456"),
        		std::make_tuple("redelivery_policy.collision_avoidance_percent", "cms.RedeliveryPolicy.collisionAvoidancePercent", "14"),
        		std::make_tuple("redelivery_policy.initial_redelivery_delay", "cms.RedeliveryPolicy.initialRedeliveryDelay", "999"),
        		std::make_tuple("redelivery_policy.maximum_redeliveries", "cms.RedeliveryPolicy.maximumRedeliveries", "5"),
        		std::make_tuple("redelivery_policy.use_collision_avoidance", "cms.RedeliveryPolicy.useCollisionAvoidance", "true"),
        		std::make_tuple("redelivery_policy.use_exponential_backOff", "cms.RedeliveryPolicy.useExponentialBackOff", "true"),

        		std::make_tuple("wireFormat_protocol.wire_format", "wireFormat", "stomp"),
        		std::make_tuple("wireFormat_protocol.stack_trace_enabled", "wireFormat.stackTraceEnabled", "true"),
        		std::make_tuple("wireFormat_protocol.cache_enabled", "wireFormat.cacheEnabled", "true"),
        		std::make_tuple("wireFormat_protocol.tcp_no_delay_enabled", "wireFormat.tcpNoDelayEnabled", "false"),
        		std::make_tuple("wireFormat_protocol.size_prefix_disabled", "wireFormat.sizePrefixDisabled", "true"),
        		std::make_tuple("wireFormat_protocol.tight_encoding_enabled", "wireFormat.tightEncodingEnabled", "true"),
        		std::make_tuple("wireFormat_protocol.max_inactivity_duration", "wireFormat.maxInactivityDuration", "15999"),
        		std::make_tuple("wireFormat_protocol.max_inactivity_duration_inital_delay", "maxInactivityDurationInitalDelay", "5123"),

        		std::make_tuple("general.prefetch_size", "consumer.prefetchSize", "999"),
        		std::make_tuple("general.maximum_pending_message_limit", "consumer.maximumPendingMessageLimit", "1"),
        		std::make_tuple("general.no_local", "consumer.noLocal", "true"),
        		std::make_tuple("general.dispatch_async", "consumer.dispatchAsync", "true"),
        		std::make_tuple("general.retroactive", "consumer.retroactive", "true"),
        		std::make_tuple("general.selector", "consumer.selector", "Selector"),
        		std::make_tuple("general.exclusive", "consumer.exclusive", "true"),
        		std::make_tuple("general.priority", "consumer.priority", "1"),

        		std::make_tuple("open_wire_only.browser", "consumer.browser", "true"),
        		std::make_tuple("open_wire_only.network_subscription", "consumer.networkSubscription", "true"),
        		std::make_tuple("open_wire_only.optimized_acknowledge", "consumer.optimizedAcknowledge", "true"),
        		std::make_tuple("open_wire_only.no_range_acks", "consumer.noRangeAcks", "true"),
        		std::make_tuple("open_wire_only.retroactive", "consumer.retroactive", "true")
        )
);
