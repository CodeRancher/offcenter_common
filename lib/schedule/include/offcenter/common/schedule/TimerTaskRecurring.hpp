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
 * @file   TimerTaskRecurring.hpp
 * @author Scott Brauer
 * @date   02-08-2019
 */

#ifndef LIB_SCHEDULE_INCLUDE_OFFCENTER_COMMON_SCHEDULE_TIMERTASKRECURRING_HPP_
#define LIB_SCHEDULE_INCLUDE_OFFCENTER_COMMON_SCHEDULE_TIMERTASKRECURRING_HPP_

#include "offcenter/common/schedule/TaskRecurringWrapped.hpp"

namespace offcenter {
namespace common {
namespace schedule {

template <typename RecurFunctor, typename PreFunctor, typename ActionFunctor, typename PostFunctor, typename Data>
class TimerTaskRecurring:
		public TaskRecurringWrapped<ActionFunctor, Data>
{
private:
	using BaseT = TaskRecurringWrapped<ActionFunctor, Data>;
	DeadlineTimerPtr m_timer;
	const RecurFunctor& m_recurCalc;
	const PreFunctor& m_preContinueTest;
	const PostFunctor& m_postContinueTest;
	Data m_data;
	int m_startTime;

public:
    template <class Time>
    explicit TimerTaskRecurring(
    		IOService& ios,
			const Time& durationOrTime,
			const RecurFunctor& recurCalc,
			const PreFunctor& preContinueTest,
			const ActionFunctor& action,
			const PostFunctor& postContinueTest,
			Data data
	):
			BaseT(action, data),
			m_timer(std::make_shared<DeadlineTimer>(std::ref(ios), durationOrTime)),
			m_recurCalc(recurCalc),
			m_preContinueTest(preContinueTest),
			m_postContinueTest(postContinueTest),
			m_data(data),
			m_startTime(static_cast<int>(time(NULL)))
    {}

	virtual ~TimerTaskRecurring() = default;

	int runningTime() const {
		return static_cast<int>(time(NULL)) - m_startTime;
	}

	void pushTask() const {
		m_timer->async_wait(*this);
	}

	void operator()(const boost::system::error_code& error) const {
		if (!error) {
			if (m_preContinueTest(m_data)) {
				BaseT::operator()();
				if (m_postContinueTest(m_data)) {
					m_timer->expires_at(m_recurCalc(m_timer->expires_at(), m_data));
					m_timer->async_wait(*this);
				}
			} else {
		    	std::cout << "TimerTaskRecurring::operator() preContinueTest failed: " << runningTime() << std::endl;;;
			}
		} else {
	    	std::cout << "TimerTaskRecurring::operator() error: " << error << ":" << runningTime() << std::endl;;;
		}
	}
};


} /* namespace schedule */
} /* namespace common */
} /* namespace offcenter */

#endif /* LIB_SCHEDULE_INCLUDE_OFFCENTER_COMMON_SCHEDULE_TIMERTASKRECURRING_HPP_ */
