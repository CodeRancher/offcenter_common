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
 * @file   RunningThreadBlockable.hpp
 * @author Scott Brauer
 * @date   10-14-2021
 */

#ifndef OffcenterCommon_THREADING_RUNNINGTHREADBLOCKABLE_HPP_
#define OffcenterCommon_THREADING_RUNNINGTHREADBLOCKABLE_HPP_

#include <mutex>
#include <condition_variable>

#include "offcenter/common/threading/RunningThread.hpp"

namespace offcenter {
namespace common {
namespace threading {

/**
 *
 */
class RunningThreadBlockable:
		public RunningThread
{
public:
	RunningThreadBlockable(const std::string& l_id = "rtb-" + std::to_string(++g_counter));
	virtual ~RunningThreadBlockable();

	void block();
	void unblock();

protected:
	void taskPreCondition();
	void stopping() override;

private:
	std::atomic_bool m_block;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	static int g_counter;

};

} /* namespace threading */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_THREADING_RUNNINGTHREADBLOCKABLE_HPP_ */
