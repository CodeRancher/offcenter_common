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
 * @file   ScheduledTaskManager.hpp
 * @author Scott Brauer
 * @date   03-26-2019
 */

#ifndef OffcenterCommon_SCHEDULE_SCHEDULEDTASKMANAGER_HPP_
#define OffcenterCommon_SCHEDULE_SCHEDULEDTASKMANAGER_HPP_

#include <boost/asio/io_service.hpp>
#include <boost/system/error_code.hpp>
#include <boost/make_shared.hpp>

#include "offcenter/common/schedule/Common.hpp"
#include "offcenter/common/schedule/TaskManager.hpp"
#include "offcenter/common/schedule/TimerTask.hpp"
#include "offcenter/common/schedule/TimerTaskRecurring.hpp"

namespace offcenter {
namespace common {
namespace schedule {

class ScheduledTaskManager: public TaskManager
{
public:
	using Ptr = std::shared_ptr<ScheduledTaskManager>;

public:
	ScheduledTaskManager() = default;
	virtual ~ScheduledTaskManager() = default;

	static Ptr createInstance() {
		return std::make_shared<ScheduledTaskManager>();
	}

	template <class Time, class Functor>
	inline TimerTask<Functor> makeTimerTask(
		IOService& ios,
		const Time& durationOrTime,
		const Functor& taskUnwrapped)
	{
		return TimerTask<Functor>(ios, durationOrTime, taskUnwrapped);
	}

    template <class Time, typename RecurFunctor, typename PreFunctor, typename ActionFunctor, typename PostFunctor, typename Data>
	inline TimerTaskRecurring<RecurFunctor, PreFunctor, ActionFunctor, PostFunctor, Data> makeTimerTask(
		IOService& ios,
		const Time& durationOrTime,
		const RecurFunctor& recurCalc,
		const PreFunctor& preContinueTest,
		const ActionFunctor& action,
		const PostFunctor& postContinueTest,
		Data data)
	{
		return TimerTaskRecurring<RecurFunctor, PreFunctor, ActionFunctor, PostFunctor, Data>(ios, durationOrTime, recurCalc, preContinueTest, action, postContinueTest, data);
	}

    template <class Functor>
    void runAfter(DurationType duration, const Functor& f) {
        makeTimerTask(m_ios, duration, f).pushTask();
    }

    template <class Functor>
    void runAt(TimeType time, const Functor& f) {
    	makeTimerTask(m_ios, time, f).pushTask();
    }

    template <class Functor>
    void runAfter(DurationType durationTillStart, DurationType recurringDuration, const Functor& f) {
        makeTimerTask(m_ios, durationTillStart, f).pushTask();
    }

    template <class Functor>
    void runAt(TimeType time, DurationType recurringDuration, const Functor& f) {
    	makeTimerTask(m_ios, time, f).pushTask();
    }

    template <typename RecurFunctor, typename PreFunctor, typename ActionFunctor, typename PostFunctor, typename Data>
    void runAfter(
    		DurationType durationTillStart,
			const RecurFunctor& recurCalc,
			const PreFunctor& preContinueTest,
			const ActionFunctor& action,
			const PostFunctor& postContinueTest,
			Data data)
    {
        makeTimerTask(m_ios, durationTillStart, recurCalc, preContinueTest, action, postContinueTest, data).pushTask();
    }

    /*
    template <class Data>
    void runAt(TimeType time, DurationType recurringDuration, const Functor& f) {
    	makeTimerTask(m_ios, time, f).pushTask();
    }
    */

};

} /* namespace schedule */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_SCHEDULE_SCHEDULEDTASKMANAGER_HPP_ */

