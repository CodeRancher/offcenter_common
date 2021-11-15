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
 * @file   WaitForMessage.hpp
 * @author Scott Brauer
 * @date   03-25-2020
 */

#ifndef OFFCENTER_COMMON_WAITFORMESSAGE_HPP_
#define OFFCENTER_COMMON_WAITFORMESSAGE_HPP_

#include <mutex>
#include <condition_variable>

namespace offcenter {
namespace common {

class WaitForMessage {
public:
	explicit WaitForMessage():
		m_mtx(),
		m_cv(),
		m_flag(false)
	{
	}

	virtual ~WaitForMessage() {
	}

	void messageReceived() {
	    std::unique_lock<std::mutex> lck(m_mtx);
	    m_flag = true;
	    m_cv.notify_one();
	}

	void waitForMessage() {
	    std::unique_lock<std::mutex> lck(m_mtx);
	    m_cv.wait(lck, [&] { return m_flag; });
	    m_flag = false;
	}

private:
	std::mutex m_mtx;
	std::condition_variable m_cv;
	bool m_flag = false;
};

} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_WAITFORMESSAGE_HPP_ */
