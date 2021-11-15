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
 * @file   TaskWrapped.hpp
 * @author Scott Brauer
 * @date   02-05-2019
 */

#ifndef LIB_SCHEDULE_SRC_TASKWRAPPED_HPP_
#define LIB_SCHEDULE_SRC_TASKWRAPPED_HPP_

#include <boost/thread/thread.hpp>

namespace offcenter {
namespace common {
namespace schedule {

template <class T>
class TaskWrapped
{
private:
    T m_taskUnwrapped;

public:
	explicit TaskWrapped(const T& taskUnwrapped):
		m_taskUnwrapped(taskUnwrapped){

	}

	virtual ~TaskWrapped() {

	}

	void operator()() const {
	    // resetting interruption
	    try {
	        boost::this_thread::interruption_point();
	    } catch(const boost::thread_interrupted&){

	    }

	    try {
	        // Executing task
	    	std::cout << "TaskWrapped::operator(): " << static_cast<int>(time(NULL)) << std::endl;;;
	    	m_taskUnwrapped();
	    } catch (const std::exception& e) {
	        std::cerr<< "Exception: " << e.what() << '\n';
	    } catch (const boost::thread_interrupted&) {
	        std::cerr<< "Thread interrupted\n";
	    } catch (...) {
	        std::cerr<< "Unknown exception\n";
	    }
	}
};

} /* namespace schedule */
} /* namespace common */
} /* namespace offcenter */

#endif /* LIB_SCHEDULE_SRC_TASKWRAPPED_HPP_ */
