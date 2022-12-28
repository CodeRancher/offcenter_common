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
 * @file   AmqpConnectionProgramOptions.hpp
 * @author Scott Brauer
 * @date   10-04-2021
 */
#ifndef AMQPCONNECTIONPROGRAMOPTIONS_HPP_
#define AMQPCONNECTIONPROGRAMOPTIONS_HPP_

#include <functional>
#include <vector>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"

#include "offcenter/common/amqp/ConnectionOptions.hpp"

namespace offcenter {
namespace common {
namespace amqpserver {

class AmqpConnectionProgramOptions:
		public program_options::ProgramOptionsGroup<offcenter::common::amqp::ConnectionURIOptions>
{
public:
	AmqpConnectionProgramOptions():
		ProgramOptionsGroup("amqp")
	{
		optionsDescription().add_options()
				( "amqp.protocol", po::value<std::string>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().protocol),boost::placeholders::_1)), "Connection protocol")
				( "amqp.host", po::value<std::string>()
						->notifier(boost::bind(&offcenter::common::amqp::ProtocolOptions::setHost, &(optionConfig().protocol), boost::placeholders::_1)), "Connection host")
				( "amqp.port", po::value<std::string>()
						->notifier(boost::bind(&offcenter::common::amqp::ProtocolOptions::setPort, &(optionConfig().protocol),boost::placeholders::_1)), "Connection port")
				( "amqp.failover", po::value<std::vector<std::string>>()->multitoken()
						->notifier(boost::bind(&offcenter::common::amqp::ProtocolOptions::setFailover, &(optionConfig().protocol),boost::placeholders::_1)), "Connection failover")

				// Socket Options
				( "amqp.socket_options.input_buffer_size", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().socketOptions.inputBufferSize),boost::placeholders::_1)), "Input buffer size")
				( "amqp.socket_options.output_buffer_size", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().socketOptions.outputBufferSize), boost::placeholders::_1)), "Output buffer size")
				( "amqp.socket_options.so_linger", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().socketOptions.soLinger), boost::placeholders::_1)), "Socket SO Linger")
				( "amqp.socket_options.so_keep_alive", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().socketOptions.soKeepAlive), boost::placeholders::_1)), "Socket SO Keep Alive")
				( "amqp.socket_options.so_receive_buffer_size", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().socketOptions.soReceiveBufferSize), boost::placeholders::_1)), "Socket SO Receive Buffer Size")
				( "amqp.socket_options.so_send_buffer_size", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().socketOptions.soSendBufferSize), boost::placeholders::_1)), "Socket SO Send Buffer Size")
				( "amqp.socket_options.so_connect_timeout", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().socketOptions.soConnectTimeout), boost::placeholders::_1)), "Socket SO Connect Timeout")
				( "amqp.socket_options.tcp_no_delay", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().socketOptions.tcpNoDelay), boost::placeholders::_1)), "Socket TCP No Delay")

				( "amqp.general_transport.command_tracing_enabled", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().generalTransport.commandTracingEnabled), boost::placeholders::_1)), "Command Tracing Enabled")
				( "amqp.general_transport.tcp_tracing_enabled", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().generalTransport.tcpTracingEnabled), boost::placeholders::_1)), "TCP Tracing Enabled")
				( "amqp.general_transport.use_async_send", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().generalTransport.useAsyncSend), boost::placeholders::_1)), "Use Async Send")
				( "amqp.general_transport.max_response_wait_time", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().generalTransport.maxResponseWaitTime), boost::placeholders::_1)), "Max Response Wait Time")

				( "amqp.failover_transport.initial_reconnect_delay", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().failoverTransport.initialReconnectDelay), boost::placeholders::_1)), "Initial Reconnect Delay")
				( "amqp.failover_transport.max_reconnect_delay", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().failoverTransport.maxReconnectDelay), boost::placeholders::_1)), "Max Reconnect Delay")
				( "amqp.failover_transport.use_exponential_back_off", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().failoverTransport.useExponentialBackOff), boost::placeholders::_1)), "Use Exponential BackOff")
				( "amqp.failover_transport.max_reconnect_attempts", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().failoverTransport.maxReconnectAttempts), boost::placeholders::_1)), "Max Reconnect Attempts")
				( "amqp.failover_transport.startup_max_reconnect_attempts", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().failoverTransport.startupMaxReconnectAttempts), boost::placeholders::_1)), "Startup Max Reconnect Attempts")
				( "amqp.failover_transport.randomize", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().failoverTransport.randomize), boost::placeholders::_1)), "Randomize")
				( "amqp.failover_transport.backup", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().failoverTransport.backup), boost::placeholders::_1)), "Backup")
				( "amqp.failover_transport.backup_pool_size", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().failoverTransport.backupPoolSize), boost::placeholders::_1)), "Backup Pool Size")
				( "amqp.failover_transport.timeout", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().failoverTransport.timeout), boost::placeholders::_1)), "Timeout")

				( "amqp.transaction.max_redelivery_count", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().transaction.maxRedeliveryCount), boost::placeholders::_1)), "Max Redelivery Count")

				( "amqp.connection.send_timeout", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().connection.sendTimeout), boost::placeholders::_1)), "Send Timeout")
				( "amqp.connection.producer_window_size", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().connection.producerWindowSize), boost::placeholders::_1)), "Producer Window Size")
				( "amqp.connection.close_timeout", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().connection.closeTimeout), boost::placeholders::_1)), "Close Timeout")
				( "amqp.connection.use_async_send", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().connection.useAsyncSend), boost::placeholders::_1)), "Use Async Send")
				( "amqp.connection.always_sync_send", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().connection.alwaysSyncSend), boost::placeholders::_1)), "Always Sync Send")
				( "amqp.connection.use_compression", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().connection.useCompression), boost::placeholders::_1)), "Use Compression")
				( "amqp.connection.dispatch_async", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().connection.dispatchAsync), boost::placeholders::_1)), "Dispatch Async")

				( "amqp.prefetch_policy.durable_topic_prefetch", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().prefetchPolicy.durableTopicPrefetch), boost::placeholders::_1)), "Durable Topic Prefetch")
				( "amqp.prefetch_policy.queue_browser_prefetch", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().prefetchPolicy.queueBrowserPrefetch), boost::placeholders::_1)), "Queue Browser Prefetch")
				( "amqp.prefetch_policy.queue_prefetch", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().prefetchPolicy.queuePrefetch), boost::placeholders::_1)), "Queue Prefetch")
				( "amqp.prefetch_policy.topic_prefetch", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().prefetchPolicy.topicPrefetch), boost::placeholders::_1)), "Topic Prefetch")

				( "amqp.redelivery_policy.back_off_multiplier", po::value<double>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().redeliveryPolicy.backOffMultiplier), boost::placeholders::_1)), "Back Off Multiplier")
				( "amqp.redelivery_policy.collision_avoidance_percent", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().redeliveryPolicy.collisionAvoidancePercent), boost::placeholders::_1)), "Collision Avoidance Percent")
				( "amqp.redelivery_policy.initial_redelivery_delay", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().redeliveryPolicy.initialRedeliveryDelay), boost::placeholders::_1)), "Initial Redelivery Delay")
				( "amqp.redelivery_policy.maximum_redeliveries", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().redeliveryPolicy.maximumRedeliveries), boost::placeholders::_1)), "Maximum Redeliveries")
				( "amqp.redelivery_policy.use_collision_avoidance", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().redeliveryPolicy.useCollisionAvoidance), boost::placeholders::_1)), "Use Collision Avoidance")
				( "amqp.redelivery_policy.use_exponential_backOff", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().redeliveryPolicy.useExponentialBackOff), boost::placeholders::_1)), "Use Exponential Back Off")

				( "amqp.wireFormat_protocol.wire_format", po::value<std::string>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().wireFormatProtocol.wireFormat), boost::placeholders::_1)), "wireFormat")
				( "amqp.wireFormat_protocol.stack_trace_enabled", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().wireFormatProtocol.stackTraceEnabled), boost::placeholders::_1)), "stackTraceEnabled")
				( "amqp.wireFormat_protocol.cache_enabled", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().wireFormatProtocol.cacheEnabled), boost::placeholders::_1)), "cacheEnabled")
				( "amqp.wireFormat_protocol.tcp_no_delay_enabled", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().wireFormatProtocol.tcpNoDelayEnabled), boost::placeholders::_1)), "tcpNoDelayEnabled")
				( "amqp.wireFormat_protocol.size_prefix_disabled", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().wireFormatProtocol.sizePrefixDisabled), boost::placeholders::_1)), "sizePrefixDisabled")
				( "amqp.wireFormat_protocol.tight_encoding_enabled", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().wireFormatProtocol.tightEncodingEnabled), boost::placeholders::_1)), "tightEncodingEnabled")
				( "amqp.wireFormat_protocol.max_inactivity_duration", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().wireFormatProtocol.maxInactivityDuration), boost::placeholders::_1)), "maxInactivityDuration")
				( "amqp.wireFormat_protocol.max_inactivity_duration_inital_delay", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().wireFormatProtocol.maxInactivityDurationInitalDelay), boost::placeholders::_1)), "maxInactivityDurationInitalDelay")

				( "amqp.general.prefetch_size", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().general.prefetchSize), boost::placeholders::_1)), "Prefetch Size")
				( "amqp.general.maximum_pending_message_limit", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().general.maximumPendingMessageLimit), boost::placeholders::_1)), "Maximum Pending Message Limit")
				( "amqp.general.no_local", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().general.noLocal), boost::placeholders::_1)), "No Local")
				( "amqp.general.dispatch_async", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().general.dispatchAsync), boost::placeholders::_1)), "Dispatch Async")
				( "amqp.general.retroactive", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().general.retroactive), boost::placeholders::_1)), "retroactive")
				( "amqp.general.selector", po::value<std::string>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().general.selector), boost::placeholders::_1)), "selector")
				( "amqp.general.exclusive", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().general.exclusive), boost::placeholders::_1)), "exclusive")
				( "amqp.general.priority", po::value<int>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().general.priority), boost::placeholders::_1)), "priority")

				( "amqp.open_wire_only.browser", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().openWireOnly.browser), boost::placeholders::_1)), "Browser")
				( "amqp.open_wire_only.network_subscription", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().openWireOnly.networkSubscription), boost::placeholders::_1)), "Network Subscription")
				( "amqp.open_wire_only.optimized_acknowledge", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().openWireOnly.optimizedAcknowledge), boost::placeholders::_1)), "Optimized Acknowledge")
				( "amqp.open_wire_only.no_range_acks", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().openWireOnly.noRangeAcks), boost::placeholders::_1)), "No Range Acks")
				( "amqp.open_wire_only.retroactive", po::value<bool>()
						->notifier(boost::bind<void>(boost::ref(optionConfig().openWireOnly.retroactive), boost::placeholders::_1)), "Retroactive")

//				( "amqp.protocol.retroactive", po::value<std::string>()
//						->notifier(boost::bind<void>(boost::ref(optionConfig().protocol.setTransportType), boost::placeholders::_1)), "Protocol [tcp, ssl, failover]")

				;
	}

	virtual ~AmqpConnectionProgramOptions() = default;
};

} /* namespace amqpserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* AMQPCONNECTIONPROGRAMOPTIONS_HPP_ */
