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
 * @file   ConnectionOptions.hpp
 * @author Scott Brauer
 * @date   04-09-2020
 */

#ifndef LIB_AMQP_INCLUDE_OFFCENTER_AMQP_CONNECTIONOPTIONS_HPP_
#define LIB_AMQP_INCLUDE_OFFCENTER_AMQP_CONNECTIONOPTIONS_HPP_

#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <initializer_list>

#include <boost/algorithm/string.hpp>
#include <decaf/internal/net/URIHelper.h>

#include "offcenter/common/amqp/ConnectionOptionElements.hpp"
#include "offcenter/common/amqp/URLSchemeHost.hpp"
#include "offcenter/common/amqp/URLFailover.hpp"
#include "offcenter/common/amqp/AMQPException.hpp"

namespace offcenter {
namespace amqp {

/**
 *
 */
class Options {
public:
	using OptionElement = IInternalElement*;
	using OptionSet = std::vector<OptionElement>;
	using OptionIterator = OptionSet::const_iterator;

public:
	Options() {}
	virtual ~Options() {}

	const OptionSet& options() const { return m_options; }
	const std::string urisText() const {
		OptionSet fileredSet;

		std::copy_if(m_options.cbegin(), m_options.cend(), std::back_inserter(fileredSet),[](auto val){ return val->isDirty(); });

		std::ostringstream uris;
		for (OptionElement &element : fileredSet) {
			if (!uris.tellp()) {
				uris << element->uriText();
			} else {
				uris << "&" << element->uriText();
			}
		}

		return uris.str();
	}

protected:
	void addOption(OptionElement option) {
		m_options.push_back(option);
	}

private:
	OptionSet m_options;

};

/**
 *
 */
class SocketOptions : public Options {
public:
	SocketOptions():
		Options(),
		inputBufferSize("inputBufferSize"),
		outputBufferSize("outputBufferSize"),
		soLinger("soLinger"),
		soKeepAlive("soKeepAlive"),
		soReceiveBufferSize("soReceiveBufferSize"),
		soSendBufferSize("soSendBufferSize"),
		soConnectTimeout("soConnectTimeout"),
		tcpNoDelay("tcpNoDelay")
	{
		addOption(&inputBufferSize);
		addOption(&outputBufferSize);
		addOption(&soLinger);
		addOption(&soKeepAlive);
		addOption(&soReceiveBufferSize);
		addOption(&soSendBufferSize);
		addOption(&soConnectTimeout);
		addOption(&tcpNoDelay);
	}

	SocketOptions& operator=(const SocketOptions& o) {
		inputBufferSize = o.inputBufferSize;
		outputBufferSize = o.outputBufferSize;
		soLinger = o.soLinger;
		soKeepAlive = o.soKeepAlive;
		soReceiveBufferSize = o.soReceiveBufferSize;
		soSendBufferSize = o.soSendBufferSize;
		soConnectTimeout = o.soConnectTimeout;
		tcpNoDelay = o.tcpNoDelay;

		return *this;
	}

	/**
	 * The number of bytes in the buffered input stream’s buffer
	 */
	IntegerElement<10000> inputBufferSize;

	/**
	 * The number of bytes in the buffered output stream’s buffer
	 */
	IntegerElement<10000> outputBufferSize;

	/**
	 * Socket SOLinger value
	 */
	IntegerElement<0> soLinger;

	/**
	 * Socket SOKeepAlive value
	 */
	BooleanElement<false> soKeepAlive;

	/**
	 * Socket receive buffer. If -1, use OS default.
	 */
	IntegerElement<-1> soReceiveBufferSize;

	/**
	 * Socket send buffer. If -1, use OS default.
	 */
	IntegerElement<-1> soSendBufferSize;

	/**
	 * Socket connection timeout in microseconds. If -1, use OS default. (Since ActiveMQ-CPP 2.2)
	 */
	IntegerElement<-1> soConnectTimeout;

	/**
	 * Sets the Socket level TCP_NODELAY option
	 */
	BooleanElement<true> tcpNoDelay;
};

/**
 *
 */
//class ResponseCorrelatorOptions : public Options {
//public:
//	ResponseCorrelatorOptions():
//		Options(),
//		maxResponseWaitTime("transport.ResponseCorrelator.maxResponseWaitTime")
//		{
//			addOption(&maxResponseWaitTime);
//		}
//
//	/**
//	 * Milliseconds to wait for responses from the broker. (Removed as of ActiveMQ-CPP 2.2.1, use connection.sendTimeout instead)
//	 */
//	IntegerElement<3000> maxResponseWaitTime;
//};

/**
 *
 */
class GeneralTransportOptions : public Options {
public:
	GeneralTransportOptions():
		Options(),
		commandTracingEnabled("transport.commandTracingEnabled"),
		tcpTracingEnabled("transport.tcpTracingEnabled"),
		useAsyncSend("transport.useAsyncSend"),
		maxResponseWaitTime("transport.ResponseCorrelator.maxResponseWaitTime")
	{
		addOption(&commandTracingEnabled);
		addOption(&tcpTracingEnabled);
		addOption(&useAsyncSend);
		addOption(&maxResponseWaitTime);
	}

	/**
	 * If true, enables tracing of incoming and outgoing transport commands
	 */
	BooleanElement<false> commandTracingEnabled;

	/**
	 * If true, enables tracing of raw network IO (in hex)
	 */
	BooleanElement<false> tcpTracingEnabled;

	/**
	 * If true, enables asynchronous sending of messages.
	 *
	 * *WARNING: Using this could result in a loss of data if messages are pending and the client is shut down or crashes.
	 * *(Deprecated Since ActiveMQ-CPP 2.2.2 has no effect as of this release, use connection.useAsyncSend instead)
	 */
	BooleanElement<false> useAsyncSend;

	/**
	 * Milliseconds to wait for responses from the broker. (Removed as of ActiveMQ-CPP 2.2.1, use connection.sendTimeout instead)
	 */
	IntegerElement<3000> maxResponseWaitTime;
};

/**
 *
 */
class FailoverTransportOptions : public Options {
public:
	FailoverTransportOptions():
		Options(),
		initialReconnectDelay("initialReconnectDelay"),
		maxReconnectDelay("maxReconnectDelay"),
		useExponentialBackOff("useExponentialBackOff"),
		maxReconnectAttempts("maxReconnectAttempts"),
		startupMaxReconnectAttempts("startupMaxReconnectAttempts"),
		randomize("randomize"),
		backup("backup"),
		backupPoolSize("backupPoolSize"),
		timeout("timeout")
	{
		addOption(&initialReconnectDelay);
		addOption(&maxReconnectDelay);
		addOption(&useExponentialBackOff);
		addOption(&maxReconnectAttempts);
		addOption(&startupMaxReconnectAttempts);
		addOption(&randomize);
		addOption(&backup);
		addOption(&backupPoolSize);
		addOption(&timeout);
	}

	/**
	 * How long to wait if the initial attempt to connect to the broker fails.
	 */
	IntegerElement<10> initialReconnectDelay;

	/**
	 * Maximum time that the transport waits before trying to connect to the Broker again.
	 */
	IntegerElement<3000> maxReconnectDelay;

	/**
	 * Should the delay between connection attempt grow on each try up to the max reconnect delay
	 */
	BooleanElement<true> useExponentialBackOff;

	/**
	 * Max number of times to attempt to reconnect before failing the transport, default is forever (0).
	 */
	IntegerElement<0> maxReconnectAttempts;

	/**
	 * Max number of times to attempt to reconnect before failing the transport, default is forever (0). Only applies during the initial attempt to connect, after one successful connection the maxReconnectAttempts flag applies from then on. (Since v3.2.0)
	 */
	IntegerElement<0> startupMaxReconnectAttempts;

	/**
	 * Should the transport attempt to connect to the listed Broker URI’s in Random order.
	 */
	BooleanElement<true> randomize;

	/**
	 * Should the Failover transport maintain hot backups.
	 */
	BooleanElement<false> backup;

	/**
	 * If enabled, how many hot backup connections are made.
	 */
	IntegerElement<1> backupPoolSize;

	/**
	 * If a send is blocked waiting on a failed connection to reconnect how long should it wait before failing the send, default is forever (-1).
	 */
	IntegerElement<-1> timeout;

};

/*
 *
*/
class TransactionOptions : public Options {
public:
	TransactionOptions():
		Options(),
		maxRedeliveryCount("transaction.maxRedeliveryCount")
	{
		addOption(&maxRedeliveryCount);
	}

	/**
	 * Maximum number of redelivery attempts. (Removed in v3.2.0, see instead Connection Redelivery Policy)
	 */
	IntegerElement<5> maxRedeliveryCount;
};

/*
Connection Options
Option Name	Default	Description
connection.sendTimeout	0
connection.producerWindowSize	0	The ProducerWindowSize is the maximum number of bytes in memory that a producer will transmit to a broker before waiting for acknowledgement messages from the broker that it has accepted the previously sent messages. In other words, this how you configure the producer flow control window that is used for async sends where the client is responsible for managing memory usage. The default value of 0 means no flow control at the client. See also Producer Flow Control. This option only affects Openwire clients as Stomp does not have a means of notifying the clients of accepted messages asynchronously. (Since ActiveMQ-CPP 2.2.2)
connnection.closeTimeout	15000	The amount of time to wait for a response from the broker when shutting down. Normally we want a response to indicate that the client has been disconnected cleanly, but we don’t want to wait forever, however if you do, set this to zero. (Since ActiveMQ-CPP 2.2.1)
connection.useAsyncSend	false	Forces the use of Async Sends which adds a massive performance boost; but means that the send() method will return immediately whether the message has been sent or not which could lead to message loss. Normally only Persistant messages that are not part of a transaction are sent synchronously, using this options forces those messages to also be async. (Since ActiveMQ-CPP 2.2.2)
connection.alwaysSyncSend	false	Forces all messages that are sent to be sent synchronously overriding any usage of the useAsyncSend flag. This can reduce performance in some cases since the only messages we normally send synchronously are Persistent messages not sent in a transaction. This options guarantees that no send will return until the broker has acknowledge receipt of the message. (Since ActiveMQ-CPP 2.2.2)
connection.useCompression	false	Should outgoing messages have their body portion compressed using the ZLib compression algorithms (Since v3.2.0)
connection.dispatchAsync	true	Should the broker dispatch messages asynchronously to the consumer, this causes all consumers from this Connection to use this setting. (Since v3.2.0)
Connection Policy Options
As of version 3.2.0 the Connection object supports policies that control various aspects its behaviour and of the Consumer objects it creates.
*/
class ConnectionOptions : public Options {
public:
	ConnectionOptions():
		Options(),
		sendTimeout("connection.sendTimeout"),
		producerWindowSize("connection.producerWindowSize"),
		closeTimeout("connection.closeTimeout"),
		useAsyncSend("connection.useAsyncSend"),
		alwaysSyncSend("connection.alwaysSyncSend"),
		useCompression("connection.useCompression"),
		dispatchAsync("connection.dispatchAsync")
	{
		addOption(&sendTimeout);
		addOption(&producerWindowSize);
		addOption(&closeTimeout);
		addOption(&useAsyncSend);
		addOption(&alwaysSyncSend);
		addOption(&useCompression);
		addOption(&dispatchAsync);
	}

	/**
	 * Time to wait on Message Sends for a Response, default value of zero indicates to wait forever. Waiting forever allows the broker to have flow control over messages coming from this client if it is a fast producer or there is no consumer such that the broker would run out of memory if it did not slow down the producer. Does not affect Stomp clients as the sends are ack’d by the broker. (Since ActiveMQ-CPP 2.2.1)
	 */
	IntegerElement<0> sendTimeout;

	/**
	 * The ProducerWindowSize is the maximum number of bytes in memory that a producer will transmit to a broker before waiting for acknowledgement messages from the broker that it has accepted the previously sent messages. In other words, this how you configure the producer flow control window that is used for async sends where the client is responsible for managing memory usage. The default value of 0 means no flow control at the client. See also Producer Flow Control. This option only affects Openwire clients as Stomp does not have a means of notifying the clients of accepted messages asynchronously. (Since ActiveMQ-CPP 2.2.2)
	 */
	IntegerElement<0> producerWindowSize;

	/**
	 * The amount of time to wait for a response from the broker when shutting down. Normally we want a response to indicate that the client has been disconnected cleanly, but we don’t want to wait forever, however if you do, set this to zero. (Since ActiveMQ-CPP 2.2.1)
	 */
	IntegerElement<15000> closeTimeout;

	/**
	 * Forces the use of Async Sends which adds a massive performance boost; but means that the send() method will return immediately whether the message has been sent or not which could lead to message loss. Normally only Persistant messages that are not part of a transaction are sent synchronously, using this options forces those messages to also be async. (Since ActiveMQ-CPP 2.2.2)
	 */
	BooleanElement<false> useAsyncSend;

	/**
	 * Forces all messages that are sent to be sent synchronously overriding any usage of the useAsyncSend flag. This can reduce performance in some cases since the only messages we normally send synchronously are Persistent messages not sent in a transaction. This options guarantees that no send will return until the broker has acknowledge receipt of the message. (Since ActiveMQ-CPP 2.2.2)
	 */
	BooleanElement<false> alwaysSyncSend;

	/**
	 * Should outgoing messages have their body portion compressed using the ZLib compression algorithms (Since v3.2.0)
	 */
	BooleanElement<false> useCompression;

	/**
	 * Should the broker dispatch messages asynchronously to the consumer, this causes all consumers from this Connection to use this setting. (Since v3.2.0)
	 */
	BooleanElement<true> dispatchAsync;
};


/**
 * As of version 3.2.0 the Connection object supports policies that control various aspects its behaviour and of the Consumer objects it creates.
*/
class PrefetchPolicyOptions : public Options {
public:
	PrefetchPolicyOptions():
		Options(),
		durableTopicPrefetch("cms.PrefetchPolicy.durableTopicPrefetch"),
		queueBrowserPrefetch("cms.PrefetchPolicy.queueBrowserPrefetch"),
		queuePrefetch("cms.PrefetchPolicy.queuePrefetch"),
		topicPrefetch("cms.PrefetchPolicy.topicPrefetch")
	{
		addOption(&durableTopicPrefetch);
		addOption(&queueBrowserPrefetch);
		addOption(&queuePrefetch);
		addOption(&topicPrefetch);
	}

	/**
	 * Max prefetch for Durable Topics
	 */
	IntegerElement<100> durableTopicPrefetch;

	/**
	 * Max prefetch for a Queue Browser
	 */
	IntegerElement<500> queueBrowserPrefetch;

	/**
	 * Max prefetch for a Queue or Temp Queue
	 */
	IntegerElement<1000> queuePrefetch;

	/**
	 * Max prefetch for a Topic or Temp Topic
	 */
	IntegerElement<65535> topicPrefetch;
};

/**
 *
 */
class RedeliveryPolicyOptions : public Options {
public:
	RedeliveryPolicyOptions():
		Options(),
		backOffMultiplier("cms.RedeliveryPolicy.backOffMultiplier", 5.0),
		collisionAvoidancePercent("cms.RedeliveryPolicy.collisionAvoidancePercent"),
		initialRedeliveryDelay("cms.RedeliveryPolicy.initialRedeliveryDelay"),
		maximumRedeliveries("cms.RedeliveryPolicy.maximumRedeliveries"),
		useCollisionAvoidance("cms.RedeliveryPolicy.useCollisionAvoidance"),
		useExponentialBackOff("cms.RedeliveryPolicy.useExponentialBackOff")
	{
		addOption(&backOffMultiplier);
		addOption(&collisionAvoidancePercent);
		addOption(&initialRedeliveryDelay);
		addOption(&maximumRedeliveries);
		addOption(&useCollisionAvoidance);
		addOption(&useExponentialBackOff);
	}

	RedeliveryPolicyOptions& operator=(const RedeliveryPolicyOptions& o) {
		backOffMultiplier = o.backOffMultiplier;
		collisionAvoidancePercent = o.collisionAvoidancePercent;
		initialRedeliveryDelay = o.initialRedeliveryDelay;
		maximumRedeliveries = o.maximumRedeliveries;
		useCollisionAvoidance = o.useCollisionAvoidance;
		useExponentialBackOff = o.useExponentialBackOff;

		return *this;
	}

	/**
	 * Used to extend the redelivery window when the _useExponentialBackOff option is enabled.
	 */
	DoubleElement backOffMultiplier;

	/**
	 * Percentage of randomness to add to redelivery backoff to keep multiple consumers in a rollback from redelivering at the same time.
	 */
	IntegerElement<15> collisionAvoidancePercent;

	/**
	 * Amount of time to wait before starting redeliveries, in milliseconds.
	 */
	IntegerElement<1000> initialRedeliveryDelay;

	/**
	 * Maximum number of time to attempt a redelivery before giving up and NAck’ing the message.
	 */
	IntegerElement<6> maximumRedeliveries;

	/**
	 * Should the Random avoidance percentage be added into the redelivery delay.
	 */
	BooleanElement<false> useCollisionAvoidance;

	/**
	 * Should redeliveries be slowed on each cycle.
	 */
	BooleanElement<false> useExponentialBackOff;

};


/**
 *
 */
class WireFormatProtocolOptions : public Options {
public:

public:
	WireFormatProtocolOptions():
		Options(),
		wireFormat("wireFormat", WireFormat::openwire),
		stackTraceEnabled("wireFormat.stackTraceEnabled"),
		cacheEnabled("wireFormat.cacheEnabled"),
		tcpNoDelayEnabled("wireFormat.tcpNoDelayEnabled"),
		sizePrefixDisabled("wireFormat.sizePrefixDisabled"),
		tightEncodingEnabled("wireFormat.tightEncodingEnabled"),
		maxInactivityDuration("wireFormat.maxInactivityDuration"),
		maxInactivityDurationInitalDelay("maxInactivityDurationInitalDelay")
	{
		addOption(&wireFormat);
		addOption(&stackTraceEnabled);
		addOption(&cacheEnabled);
		addOption(&tcpNoDelayEnabled);
		addOption(&sizePrefixDisabled);
		addOption(&tightEncodingEnabled);
		addOption(&maxInactivityDuration);
		addOption(&maxInactivityDurationInitalDelay);
	}

	WireFormatProtocolOptions& operator=(const WireFormatProtocolOptions& o) {
		wireFormat = o.wireFormat;
		stackTraceEnabled = o.stackTraceEnabled;
		cacheEnabled = o.cacheEnabled;
		tcpNoDelayEnabled = o.tcpNoDelayEnabled;
		sizePrefixDisabled = o.sizePrefixDisabled;
		tightEncodingEnabled = o.tightEncodingEnabled;
		maxInactivityDuration = o.maxInactivityDuration;
		maxInactivityDurationInitalDelay = o.maxInactivityDurationInitalDelay;

		return *this;
	}

	/**
	 * Selects the wire format to use. Out of the box, can be either stomp or openwire.
	 */
	WireFormatElement wireFormat;

	/**
	 * Should the stack trace of exception that occur on the broker be sent to the client? Only used by openwire protocol.
	 */
	BooleanElement<false> stackTraceEnabled;

	/**
	 * Should commonly repeated values be cached so that less marshalling occurs? Only used by openwire protocol.
	 */
	BooleanElement<false> cacheEnabled;

	/**
	 * Does not affect the wire format, but provides a hint to the peer that TCP nodelay should be enabled on the
	 * communications Socket. Only used by openwire protocol.
	 */
	BooleanElement<true> tcpNoDelayEnabled;

	/**
	 * Should serialized messages include a payload length prefix? Only used by openwire protocol.
	 */
	BooleanElement<false> sizePrefixDisabled;

	/**
	 * Should wire size be optimized over CPU usage? Only used by the openwire protocol.
	 */
	BooleanElement<false> tightEncodingEnabled;

	/**
	 * The maximum inactivity duration (before which the socket is considered dead) in milliseconds.
	 * On some platforms it can take a long time for a socket to appear to die, so we allow the broker
	 * to kill connections if they are inactive for a period of time. Use by some transports to enable a keep
	 * alive heart beat feature. Set to a value <= 0 to disable inactivity monitoring.
	 */
	IntegerElement<30000> maxInactivityDuration;

	/**
	 * The initial delay in starting the maximum inactivity checks (and, yes, the word ‘Inital’ is supposed to be misspelled like that)
	 */
	IntegerElement<10000> maxInactivityDurationInitalDelay;
};


/**
 *
 */
class GeneralOptions : public Options {
public:
	GeneralOptions():
		Options(),
		prefetchSize("consumer.prefetchSize"),
		maximumPendingMessageLimit("consumer.maximumPendingMessageLimit"),
		noLocal("consumer.noLocal"),
		dispatchAsync("consumer.dispatchAsync"),
		retroactive("consumer.retroactive"),
		selector("consumer.selector", "null"),
		exclusive("consumer.exclusive"),
		priority("consumer.priority")
	{
		addOption(&prefetchSize);
		addOption(&maximumPendingMessageLimit);
		addOption(&noLocal);
		addOption(&dispatchAsync);
		addOption(&retroactive);
		addOption(&selector);
		addOption(&exclusive);
		addOption(&priority);

	}

	GeneralOptions& operator=(const GeneralOptions& o) {
		prefetchSize = o.prefetchSize;
		maximumPendingMessageLimit = o.maximumPendingMessageLimit;
		noLocal = o.noLocal;
		dispatchAsync = o.dispatchAsync;
		retroactive = o.retroactive;
		selector = o.selector;
		exclusive = o.exclusive;
		priority = o.priority;

		return *this;
	}

	/**
	 * The number of message the consumer will prefetch.
	 */
	IntegerElement<1000> prefetchSize;

	/**
	 * Use to control if messages are dropped if a slow consumer situation exists.
	 */
	IntegerElement<0> maximumPendingMessageLimit;

	/**
	 * Same as the noLocal flag on a Topic consumer. Exposed here so that it can be used with a queue.
	 */
	BooleanElement<false> noLocal;

	/**
	 * Should the broker dispatch messages asynchronously to the consumer.
	 */
	BooleanElement<false> dispatchAsync;

	/**
	 * Is this a Retroactive Consumer.
	 */
	BooleanElement<false> retroactive;

	/**
	 * JMS Selector used with the consumer.
	 */
	StringElement selector;

	/**
	 * Is this an Exclusive Consumer.
	 */
	BooleanElement<false> exclusive;

	/**
	 * Allows you to configure a Consumer Priority.
	 */
	IntegerElement<0> priority;

};


/*
OpenWire-only Options
Option Name	Default	Description
consumer.browser	false
consumer.networkSubscription	false
consumer.optimizedAcknowledge	false	Enables an optimised acknowledgement mode where messages are acknowledged in batches rather than individually. Alternatively, you could use Session.DUPS_OK_ACKNOWLEDGE acknowledgement mode for the consumers which can often be faster. WARNING enabling this issue could cause some issues with auto-acknowledgement on reconnection
consumer.noRangeAcks	false
consumer.retroactive	false	Sets whether or not retroactive consumers are enabled. Retroactive consumers allow non-durable topic subscribers to receive old messages that were published before the non-durable subscriber started.
*/
class OpenWireOnlyOptions : public Options {
public:
	OpenWireOnlyOptions():
		Options(),
		browser("consumer.browser"),
		networkSubscription("consumer.networkSubscription"),
		optimizedAcknowledge("consumer.optimizedAcknowledge"),
		noRangeAcks("consumer.noRangeAcks"),
		retroactive("consumer.retroactive")
	{
		addOption(&browser);
		addOption(&networkSubscription);
		addOption(&optimizedAcknowledge);
		addOption(&noRangeAcks);
		addOption(&retroactive);
	}

	OpenWireOnlyOptions& operator=(const OpenWireOnlyOptions& o) {
		browser = o.browser;
		networkSubscription = o.networkSubscription;
		optimizedAcknowledge = o.optimizedAcknowledge;
		noRangeAcks = o.noRangeAcks;
		retroactive = o.retroactive;

		return *this;
	}

	/**
	 *
	 */
	BooleanElement<false> browser;

	/**
	 *
	 */
	BooleanElement<false> networkSubscription;

	/**
	 * Enables an optimised acknowledgement mode where messages are acknowledged in batches rather than individually.
	 * Alternatively, you could use Session.DUPS_OK_ACKNOWLEDGE acknowledgement mode for the consumers which can often be faster.
	 * WARNING enabling this issue could cause some issues with auto-acknowledgement on reconnection
	 */
	BooleanElement<false> optimizedAcknowledge;

	/**
	 *
	 */
	BooleanElement<false> noRangeAcks;

	/**
	 * Sets whether or not retroactive consumers are enabled. Retroactive consumers allow non-durable topic subscribers
	 * to receive old messages that were published before the non-durable subscriber started.
	 */
	BooleanElement<false> retroactive;

};

enum ConnectionTransportType {
	tcp,	 ///<
	ssl,	 ///<
	failover ///<
};

class ConnectionTransport {
public:
	explicit ConnectionTransport(const ConnectionTransportType transportType = ConnectionTransportType::tcp) :
		m_transportType(transportType) {}

private:
	ConnectionTransportType m_transportType;
};

/// Protocol Options
/// Option Name	Description
/// tcp	Uses TCP/IP Sockets to connect to the broker.
/// ssl	Uses OpenSSL to secure TCP/IP sockets. (Since v3.2.0)
/// failover	Composite of other Transports, when a Transport connection fails, the Failover Transport connects to the next Transport in the list or retries the connection to the failed broker URI.
class ProtocolOptions {
public:
	/// Create a protocol option using a specific transport type
	/// \param transportType transport type
	explicit ProtocolOptions(const ConnectionTransportType transportType = ConnectionTransportType::tcp):
		m_transportType(transportType),
		m_tcpProtocol(URLSchemeHost::URLScheme::tcp, URLSchemeHost::g_defaultHost, URLSchemeHost::g_defaultPort),
		m_sslProtocol(URLSchemeHost::URLScheme::ssl, URLSchemeHost::g_defaultHost, URLSchemeHost::g_defaultPort),
		m_failoverProtocol() {}

	/// Create a protocol option using a specific transport type as a string
	/// \param transportType transport type as a string
	explicit ProtocolOptions(const std::string &transportType) :
		m_transportType(ProtocolOptions::stringToTransportType(transportType)),
		m_tcpProtocol(URLSchemeHost::tcp, URLSchemeHost::g_defaultHost, URLSchemeHost::g_defaultPort),
		m_sslProtocol(URLSchemeHost::ssl, URLSchemeHost::g_defaultHost, URLSchemeHost::g_defaultPort),
		m_failoverProtocol() {}

	/// Set the transport type
	/// \param value new transport type
	void setTransportType(const ConnectionTransportType value) { m_transportType = value; }

	/// Set the transport type from a string
	/// \param value string value to convert to a transport type
	/// \exception offcenter::amqp::AMQPException Unable to convert \a value to \a ConnectionTransportType
	void setTransportType(const std::string &value) { setTransportType(ProtocolOptions::stringToTransportType(value)); }

	/// Set the transport type
	/// \param value new transport type
	void operator=(const ConnectionTransportType &value){ setTransportType(value); }

	/// Set the transport type from a string
	/// \param value string value to convert to a transport type
	/// \exception offcenter::amqp::AMQPException Unable to convert \a value to \a ConnectionTransportType
	void operator=(const std::string &value){ setTransportType(value); }

	void setProtocol(const std::string &value){ setTransportType(value); }
	void setHost(const std::string &value) {
		m_tcpProtocol.setHost(value);
		m_sslProtocol.setHost(value);
	}

	void setPort(const std::string &value) {
		int port = std::stoi(value);
		m_tcpProtocol.setPort(port);
		m_sslProtocol.setPort(port);
	}

	void setFailover(const std::vector<std::string> &value) {
		for (const std::string& element : value) {
			decaf::internal::net::URIHelper helper;
			decaf::internal::net::URIType type = helper.parseURI(element, true);

			std::cout << "setFailover: " << element << " host(" << type.getHost() << ") port(" << type.getPort() << ")" << std::endl;

			URLSchemeHost host(URLSchemeHost::URLSchemeFromString(type.getScheme()), type.getHost(), type.getPort());
			m_failoverProtocol.addHost(host);
		}
	}

	/// Set the transport type from a string
	/// \param value string value to convert to a transport type
	/// \exception offcenter::amqp::AMQPException Unable to convert \a value to \a ConnectionTransportType
	void operator()(const std::string &value){ setTransportType(value); }

	/// Set the transport type to tcp and the tcp connection values
	/// \param schemeHost tcp connection values
	void setTCPProtocol(const URLSchemeHost &schemeHost) {
		m_tcpProtocol = schemeHost;
		setTransportType(ConnectionTransportType::tcp);
	}

	/// Set the transport type to ssl and the ssl connection values
	/// \param schemeHost ssl connection values
	void setSSLProtocol(const URLSchemeHost &schemeHost) {
		m_sslProtocol = schemeHost;
		setTransportType(ConnectionTransportType::ssl);
	}

	/// Set the transport type to failover and add a new connection
	/// \param schemeHost connection values to add to failover
	void addFailoverProtocol(const URLSchemeHost &schemeHost) {
		m_failoverProtocol.addHost(schemeHost);
		setTransportType(ConnectionTransportType::failover);
	}

	/// Reset the failover transport type
	void resetFailoverProtocol() {
		m_failoverProtocol.reset();
		setTransportType(ConnectionTransportType::failover);
	}

	/// Return the protocol URI text for this connection
	/// \return protocol URI text
	///   - \ref tcp  - \c tcp://localhost:61616
	///   - \ref ssl  - \c ssl://localhost:61616
	///   - \ref failover - \c failover://(tcp://localhost:61616,tcp://anotherhost:61616)
	/// \exception offcenter::amqp::AMQPException Invalid transport type
	const std::string uriText() const {
		switch (m_transportType) {
			case tcp: return m_tcpProtocol.uri();
			case ssl: return m_sslProtocol.uri();
			case failover: return m_failoverProtocol.uri();
		}
		throw offcenter::amqp::AMQPException("Invalid transport type");
	}

	/// Convert a string to a ConnectionTransportType
	/// \param value string representation of ConnectionTransportType
	/// \exception offcenter::amqp::AMQPException Unable to convert \a value to \a ConnectionTransportType
	static ConnectionTransportType stringToTransportType(std::string value) {
		boost::algorithm::trim(value);
		boost::algorithm::to_lower(value);
		if (value == "tcp") {
			return ConnectionTransportType::tcp;
		} else if (value == "ssl") {
			return ConnectionTransportType::ssl;
		} else if (value == "failover") {
			return ConnectionTransportType::failover;
		}
		throw offcenter::amqp::AMQPException("Invalid transport type string (" + value + ")");
	}

private:
	ConnectionTransportType m_transportType;
	URLSchemeHost m_tcpProtocol;
	URLSchemeHost m_sslProtocol;
	URLFailover m_failoverProtocol;
};


/**
 *
 */
class ConnectionURIOptions {

public:
	ConnectionURIOptions() {}

	virtual ~ConnectionURIOptions() {}

	const std::string uri() const {
		std::vector<std::string> optionsSet;

		addOptions(socketOptions, optionsSet);
		addOptions(generalTransport, optionsSet);
		addOptions(failoverTransport, optionsSet);
		addOptions(transaction, optionsSet);
		addOptions(connection, optionsSet);
		addOptions(prefetchPolicy, optionsSet);
		addOptions(redeliveryPolicy, optionsSet);
		addOptions(wireFormatProtocol, optionsSet);
		addOptions(general, optionsSet);
		addOptions(openWireOnly, optionsSet);

		std::ostringstream uris;

		// Add protocol
		if (optionsSet.size() == 0) {
			uris << protocol.uriText();
		} else {
			uris << protocol.uriText() << "?";
		}

		// Add elements
		bool firstElement = true;
		for (std::string &element : optionsSet) {
			uris << (firstElement ? "" : "&") << element;
			firstElement = false;
		}

		return uris.str();
	}

	ConnectionURIOptions& operator=(const ConnectionURIOptions& o) {
		socketOptions = o.socketOptions;
		generalTransport = o.generalTransport;
		failoverTransport = o.failoverTransport;
		transaction = o.transaction;
		connection = o.connection;
		prefetchPolicy = o.prefetchPolicy;
		redeliveryPolicy = o.redeliveryPolicy;
		wireFormatProtocol = o.wireFormatProtocol;
		general = o.general;
		openWireOnly = o.openWireOnly;
		protocol = o.protocol;

		return *this;
	}

	SocketOptions socketOptions;
	GeneralTransportOptions generalTransport;
	FailoverTransportOptions failoverTransport;
	TransactionOptions transaction;
	ConnectionOptions connection;
	PrefetchPolicyOptions prefetchPolicy;
	RedeliveryPolicyOptions redeliveryPolicy;
	WireFormatProtocolOptions wireFormatProtocol;
	GeneralOptions general;
	OpenWireOnlyOptions openWireOnly;
	ProtocolOptions protocol;


private:
	void addOptions(const Options &option, std::vector<std::string> &optionsSet) const {
		if (option.urisText().length() > 0) {
			optionsSet.push_back(option.urisText());
		}
	}
};


} /* namespace amqp */
} /* namespace offcenter */

#endif /* LIB_AMQP_INCLUDE_OFFCENTER_AMQP_CONNECTIONOPTIONS_HPP_ */
