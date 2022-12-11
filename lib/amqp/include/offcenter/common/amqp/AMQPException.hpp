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


/// \file   AMQPException.hpp
/// \author Scott Brauer
/// \date   Nov 18, 2020
/// \brief  AMQP Exception

#ifndef OFFCENTER_AMQP_AMQPEXCEPTION_HPP_
#define OFFCENTER_AMQP_AMQPEXCEPTION_HPP_

#include <stdexcept>

namespace offcenter {
namespace amqp {

/// \brief AMQP Exception
///
/// It reports errors that are due to events occurring during AMQP processing.
class AMQPException:
	public std::runtime_error
{
public:
	using runtime_error::runtime_error;

	virtual ~AMQPException() = default;
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_AMQPEXCEPTION_HPP_ */

