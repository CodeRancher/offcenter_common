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
 * @file   TimerTask.hpp
 * @author Scott Brauer
 * @date   02-08-2019
 */

#ifndef OffcenterCommon_SCHEDULE_TIMERTASK_HPP_
#define OffcenterCommon_SCHEDULE_TIMERTASK_HPP_

#include "offcenter/common/schedule/TaskWrapped.hpp"

namespace offcenter {
namespace common {
namespace schedule {

template <class Functor>
class TimerTask:
		public TaskWrapped<Functor>
{
private:
	using BaseT = TaskWrapped<Functor>;
	DeadlineTimerPtr m_timer;

public:
    template <class Time>
    explicit TimerTask(
    		IOService& ios,
			const Time& durationOrTime,
			const Functor& taskUnwrapped
	):
		BaseT(taskUnwrapped),
		m_timer(std::make_shared<DeadlineTimer>(std::ref(ios), durationOrTime))
    {}

	virtual ~TimerTask() = default;

	void pushTask() const {
		m_timer->async_wait(*this);
	}

	void operator()(const boost::system::error_code& error) const {
		static int loopCnt = 0;
		std::cout << "TimerTask::operator(): " << static_cast<int>(time(NULL)) << " (" << error << ")" << std::endl;
		if (!error) {
			BaseT::operator()();
		} else {
			std::cerr << error << '\n';
		}
		if (loopCnt++ < 4) {
			m_timer->expires_at(m_timer->expires_at() + boost::posix_time::seconds(1));
			m_timer->async_wait(*this);
		}
	}
};


} /* namespace schedule */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_SCHEDULE_TIMERTASK_HPP_ */
