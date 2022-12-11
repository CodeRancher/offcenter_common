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
 * @file   RunningThreadArray.hpp
 * @author Scott Brauer
 * @date   09-14-2021
 */

#ifndef OffcenterCommon_THREADING_RUNNINGTHREADARRAY_HPP_
#define OffcenterCommon_THREADING_RUNNINGTHREADARRAY_HPP_

#include <memory>
#include <vector>
#include <type_traits>

#include "offcenter/common/threading/RunningThread.hpp"

namespace offcenter {
namespace common {
namespace threading {

/**
 *
 */
//template <typename T, typename = std::enable_if<std::is_base_of<B, T>::value>::type>
template<typename Element, typename = std::enable_if_t<std::is_base_of_v<offcenter::common::threading::RunningThread, Element> > >
class RunningThreadArray
{
public:
	using Ptr = std::unique_ptr<Element>;

public:
	RunningThreadArray():
		m_elements()
	{}

	virtual ~RunningThreadArray() {
		stop();
		join();
	}

	void add(Ptr elementPtr) {
		m_elements.push_back(std::move(elementPtr));
	}

	void run() {
		for (Ptr& elementPtr : m_elements) {
			elementPtr->run();
		}
	}

	void stop() {
		for (Ptr& elementPtr : m_elements) {
			elementPtr->stop();
		}
	}

	void join() {
		for (Ptr& elementPtr : m_elements) {
			elementPtr->join();
		}
	}

	void clear() {
		for (Ptr& elementPtr : m_elements) {
			elementPtr.reset();
		}
		m_elements.clear();
	}

private:
	std::vector<Ptr> m_elements;

};

} /* namespace threading */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_THREADING_RUNNINGTHREADARRAY_HPP_ */
