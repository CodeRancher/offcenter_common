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
/// \file   Connection.cpp
/// \author Scott Brauer
/// \date   Nov 18, 2020
///
/// \brief Constants used by URLSchemeHost
///

#include "offcenter/common/amqp/URLSchemeHost.hpp"

namespace offcenter {
namespace common {
namespace amqp {

URLSchemeHost::URLScheme URLSchemeHost::g_defaultScheme = URLSchemeHost::URLScheme::tcp;
std::string URLSchemeHost::g_defaultHost = "localhost";
int URLSchemeHost::g_defaultPort = 61616;

} /* namespace amqp */
} /* namespace common */
} /* namespace offcenter */
