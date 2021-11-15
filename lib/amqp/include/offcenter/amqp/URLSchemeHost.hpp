/**
 * Copyright 2020 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http: *www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   URLSchemeHost.hpp
 * @author Scott Brauer
 * @date   Nov 16, 2020
 *
 * @brief URLSchemeHost class
 */

#ifndef OFFCENTER_COMMON_NETWORK_URLSCHEMEHOST_HPP_
#define OFFCENTER_COMMON_NETWORK_URLSCHEMEHOST_HPP_

#include <sstream>


#include "offcenter/amqp/AMQPException.hpp"

namespace offcenter {
namespace amqp {

/**
 * A URL for HTTP (or HTTPS) is normally made up of three or four components. Connection options requires a subset of these parts.
 *   - scheme - The scheme identifies the protocol to be used to access the resource on the Internet.
 *   - host - The host name identifies the host that holds the resource. A server provides services in the name of the host.
 *   - port - Host names can also be followed by a port number.
 */
class URLSchemeHost {
public:
	 /// Available schemes
	enum URLScheme {
		tcp,  ///< Uses TCP/IP Sockets to connect to the broker.
		ssl   ///< Uses OpenSSL to secure TCP/IP sockets. (Since v3.2.0)
	};

	static URLScheme g_defaultScheme;  ///< Default scheme
	static std::string g_defaultHost;  ///< Default host
	static int g_defaultPort;		   ///< Default port

public:
	/**
	 * Creates a basic scheme host
	 * @param scheme The scheme for this connection
	 * @param host The host to connect to
	 * @param port The port for connection
	 */
	URLSchemeHost(URLScheme scheme = g_defaultScheme, const std::string &host = g_defaultHost, int port = g_defaultPort) :
		m_scheme(scheme),
		m_host(host),
		m_port(port) {}

	/**
	 * Copies a basic scheme host
	 * @param other URLSchemeHost to copy
	 */
	URLSchemeHost(const URLSchemeHost &other):
		m_scheme(other.m_scheme),
		m_host(other.m_host),
		m_port(other.m_port) {}

	virtual ~URLSchemeHost() {}

	/**
	 * Translate a URL Scheme string into a URLScheme value
	 * @param value URL Scheme name
	 * @exception AMQPException if invalid string
	 */
	static URLScheme URLSchemeFromString(const std::string& value) {
		if (value == "tcp") { return URLScheme::tcp; }
		if (value == "ssl") { return URLScheme::ssl; }
		else {
			throw offcenter::amqp::AMQPException("Invalid scheme");
		}
	}

	/**
	 * Return the scheme
	 * @return URLScheme value
	 */
	URLScheme scheme() const { return m_scheme; }

	/**
	 * Return the scheme as text
	 * @return string value of the scheme
	 * @exception AMQPException if an invalid scheme
	 */
	const std::string schemeText() const {
		switch (m_scheme) {
			case tcp: return "tcp";
			case ssl: return "ssl";
		}
		throw offcenter::amqp::AMQPException("Invalid scheme");
	}

	/**
	 * Return the host
	 * @return string with the host name
	 */
	const std::string host() const  { return m_host; }

	/**
	 * Set the host name or IP address
	 * @param Name of the host
	 */
	void setHost(const std::string& host) { m_host = host; }

	/**
	 * Return the port
	 * @return integer with the port value
	 */
	int port() const { return m_port; }

	/**
	 * Set the port number
	 * @param The port number
	 */
	void setPort(int port) { m_port = port; }

	/**
	 * The combined URI value for this host and port.
	 * If port < 0
	 *   - scheme://host
	 * Else
	 *   - scheme://host:port
	 */
	const std::string uri() const {
		std::ostringstream uriText;
		uriText << schemeText() << "://"
				<< m_host
				<< (m_port >= 0 ? ":" : "") << (m_port >= 0 ? std::to_string(m_port) : "");
		return uriText.str();
	}

private:
	URLScheme m_scheme;
	std::string m_host;
	int m_port;
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_NETWORK_URLSCHEMEHOST_HPP_ */
