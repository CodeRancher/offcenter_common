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
 * @file   DataMonitorThread.hpp
 * @author Scott Brauer
 * @date   10-17-2021
 */

#ifndef OffcenterCommon_THREADING_DATAMONITORTHREAD_HPP_
#define OffcenterCommon_THREADING_DATAMONITORTHREAD_HPP_

#include <mutex>

#include "offcenter/common/threading/RunningThreadBlockable.hpp"

namespace offcenter {
namespace common {
namespace threading {

/**
 * A Running Thread that executes the Task when the data has been updated.
 */
template <typename Data>
class DataMonitorThread:
		public RunningThreadBlockable
{
public:
	/**
	 * Create a data monitor thread.
	 */
	DataMonitorThread() = default;
	virtual ~DataMonitorThread() = default;

	/**
	 * Set the data element.
	 *
	 * Thread safe access
	 *
	 * @param data Data element to set
	 */
	void setData(const Data& data) {
		{
			std::lock_guard<std::mutex> l(m_protectData);
			m_data = data;
		}
		onNewData();
	}

protected:
	/**
	 * Event when setData has been called.
	 */
	virtual void onNewData() = 0;

	/**
	 * Access data.
	 *
	 * Thread safe access
	 */
	const Data data() {
		std::lock_guard<std::mutex> l(m_protectData);
		return m_data;
	}

private:
	Data m_data;
	std::mutex m_protectData;
};

} /* namespace threading */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_THREADING_DATAMONITORTHREAD_HPP_ */
