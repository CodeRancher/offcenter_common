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
 * @file   Utility.cpp
 * @author Scott Brauer
 * @date   04-13-2021
 */

#include "offcenter/common/restserver/network/Utility.hpp"

namespace offcenter {
namespace common {
namespace restserver {
namespace network {

//using namespace boost::asio;
//using namespace boost::asio::ip;

const HostInetInfo queryHostInetInfo() {
	boost::asio::io_service ios;
	boost::asio::ip::tcp::resolver resolver(ios);
	boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
	return resolver.resolve(query);
}

const std::string hostIP(unsigned short family) {
	auto hostInetInfo = queryHostInetInfo();
	HostInetInfo end;
	while(hostInetInfo != end) {
		boost::asio::ip::tcp::endpoint ep = *hostInetInfo++;
		sockaddr sa = *ep.data();
		if (sa.sa_family == family) {
			return ep.address().to_string();
		}
	}
	return nullptr;
}

// gets the host IP4 string formatted
const std::string hostIP4() {
	using namespace boost::asio::ip;
	return hostIP(AF_INET);
}

// gets the host IP6 string formatted
const std::string hostIP6() {
	using namespace boost::asio::ip;
	return hostIP(AF_INET6);
}

const std::string hostName() {
	return boost::asio::ip::host_name();
}

} /* namespace network */
} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */
