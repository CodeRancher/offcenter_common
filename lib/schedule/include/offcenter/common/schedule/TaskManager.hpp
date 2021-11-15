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
 * @file   TaskManager.hpp
 * @author Scott Brauer
 * @date   02-05-2019
 */

#ifndef LIB_SCHEDULE_SRC_TASKMANAGER_HPP_
#define LIB_SCHEDULE_SRC_TASKMANAGER_HPP_

#include <boost/asio/io_service.hpp>

#include "offcenter/common/schedule/TaskWrapped.hpp"

namespace offcenter {
namespace common {
namespace schedule {

class TaskManager:
		private boost::noncopyable {
protected:
	boost::asio::io_context m_ios;

public:
	TaskManager():
		m_ios()
	{}

	virtual ~TaskManager() {}

	TaskManager(TaskManager const&) = delete;
    void operator=(TaskManager const&)	= delete;

	static TaskManager& instance() {
		static TaskManager m_instance;
		return m_instance;
	}

	void start() {
	    m_ios.run();
	}

	void stop() {
	    m_ios.stop();
	}

	void reset() {
		m_ios.restart();
	}

};

} /* namespace schedule */
} /* namespace common */
} /* namespace offcenter */

#endif /* LIB_SCHEDULE_SRC_TASKMANAGER_HPP_ */
