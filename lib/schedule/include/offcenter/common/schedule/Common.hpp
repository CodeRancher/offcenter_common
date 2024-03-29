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
 * @file   Common.hpp
 * @author Scott Brauer
 * @date   02-09-2019
 */

#ifndef OffcenterCommon_SCHEDULE_COMMON_HPP_
#define OffcenterCommon_SCHEDULE_COMMON_HPP_

#include <memory>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>


namespace offcenter {
namespace common {
namespace schedule {

using DeadlineTimer = boost::asio::deadline_timer;
using DurationType = DeadlineTimer::duration_type;
using TimeType = DeadlineTimer::time_type;
using DeadlineTimerPtr = std::shared_ptr<DeadlineTimer>;
using IOService = boost::asio::io_service;

} /* namespace schedule */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_SCHEDULE_COMMON_HPP_ */
