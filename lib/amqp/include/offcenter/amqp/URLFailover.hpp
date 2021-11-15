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
/// \file   URLFailover.hpp
/// \author Scott Brauer
/// \date   Nov 16, 2020
///
/// \brief URLFailover class
///

#ifndef LIB_AMQP_INCLUDE_OFFCENTER_AMQP_URLFAILOVER_HPP_
#define LIB_AMQP_INCLUDE_OFFCENTER_AMQP_URLFAILOVER_HPP_

#include <sstream>
#include <vector>

#include "offcenter/amqp/URLSchemeHost.hpp"

namespace offcenter {
namespace amqp {

/// \brief The Failover Transport
///
/// The Failover transport layers reconnect logic on top of any of the other transports.
/// The configuration syntax allows you to specify any number of composite URIs. The
/// Failover transport randomly chooses one of the composite URIs and attempts to establish
/// a connection to it. If it does not succeed, or if it subsequently fails, a new connection
/// is established choosing one of the other URIs randomly from the list.
///
/// Configuration Syntax
///   - \c failover:(uri1,...,uriN)
class URLFailover {
public:
	/// Create an empty failover transport
	explicit URLFailover() :
		m_urlSchemeHosts()
	{}

	/// Create a failover transport copied from another failover transport
	/// \param failover transport to copy
	URLFailover(const URLFailover &other):
		m_urlSchemeHosts()
	{
		for (const URLSchemeHost &element : other.m_urlSchemeHosts) {
			addHost(element);
		}
	}

	virtual ~URLFailover() = default;

	/// Add a host to the failover list
	/// \param host host to add
	void addHost(URLSchemeHost &host) {
		m_urlSchemeHosts.push_back(host);
	}

	/// Add a host to the failover list
	/// \param host host to add
	void addHost(const URLSchemeHost &host) {
		m_urlSchemeHosts.push_back(host);
	}

	/// Clear all hosts
	void reset() {
		m_urlSchemeHosts.clear();
	}

	/// Copy a failover transport
	/// \param other failover transport to copy from
	void operator=(const URLFailover &other)
	{
		reset();
		for (const URLSchemeHost &element : other.m_urlSchemeHosts) {
			addHost(element);
		}
	}

	/// Return a failover transport type string
	/// \return failover uri text string
	const std::string uri() const {
		std::ostringstream uriText;
		uriText << "failover://(";
		bool firstElement = true;
		for (const URLSchemeHost &element : m_urlSchemeHosts) {
			if (firstElement) {
				uriText << element.uri();
				firstElement = false;
			} else {
				uriText << "," << element.uri();
			}
		}
		uriText << ")";
		return uriText.str();
	}

	/// The number of hosts in the uri list
	/// \return number of hosts in the list
	unsigned int size() const {
		return m_urlSchemeHosts.size();
	}

private:
	std::vector<URLSchemeHost> m_urlSchemeHosts;
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* LIB_AMQP_INCLUDE_OFFCENTER_AMQP_URLFAILOVER_HPP_ */
