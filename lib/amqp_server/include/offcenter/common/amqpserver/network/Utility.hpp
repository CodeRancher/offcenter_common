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
 * @file   Utility.hpp
 * @author Scott Brauer
 * @date   04-13-2021
 */
#ifndef OFFCENTER_COMMON_RESTSERVER_NETWORK_UTILITY_HPP_
#define OFFCENTER_COMMON_RESTSERVER_NETWORK_UTILITY_HPP_

#include <string>

#include <boost/asio.hpp>

namespace offcenter {
namespace common {
namespace restserver {
namespace network {

using HostInetInfo = boost::asio::ip::tcp::resolver::iterator;

const HostInetInfo queryHostInetInfo();
const std::string hostIP(unsigned short family);

// gets the host IP4 string formatted
const std::string hostIP4();

// gets the host IP6 string formatted
const std::string hostIP6();

const std::string hostName();

} /* namespace network */
} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_RESTSERVER_NETWORK_UTILITY_HPP_ */
