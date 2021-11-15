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
 * @file   RunningThread.hpp
 * @author Scott Brauer
 * @date   09-14-2021
 */

#ifndef OFFCENTER_COMMON_THREADING_RUNNINGTHREAD_HPP_
#define OFFCENTER_COMMON_THREADING_RUNNINGTHREAD_HPP_

#include <thread>
#include <atomic>
#include <memory>
#include <functional>
#include <stdexcept>

namespace offcenter {
namespace common {
namespace threading {

/**
 *
 */
class RunningThread
{
public:
	RunningThread(const std::string& l_id = "rt-" + std::to_string(++g_counter));
	virtual ~RunningThread();

	void run();
	void stop();
	void join();

	bool running() const;

protected:
	virtual void task() = 0;
	virtual void taskPreCondition() {}
	virtual void stopped() = 0;
	virtual void stopping() {}

	virtual void handleError();
	virtual void handleError(const std::exception& e);

	const std::string& id() const { return m_id; }

private:
	void internalRun();

private:
	std::thread m_thread;
	std::atomic_bool m_running;
	std::atomic_bool m_stopThread;
	std::string m_id;
	static int g_counter;
};

} /* namespace threading */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_THREADING_RUNNINGTHREAD_HPP_ */
