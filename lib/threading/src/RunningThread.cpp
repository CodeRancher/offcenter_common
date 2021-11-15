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
 * @file   RunningThread.cpp
 * @author Scott Brauer
 * @date   09-14-2021
 */

#include "easylogging++.h"

#include "offcenter/common/threading/RunningThread.hpp"

namespace offcenter {
namespace common {
namespace threading {

/**
 * Create a trace message
 */
#ifdef RUNNINGTHREADTRACE
	#define rtTrace(msg) LOG(TRACE) << "RunningThread(" << id() << "): " << msg
	#define rtTrace1(msg, valn, val) LOG(TRACE) << "RunningThread(" << id() << "): " << msg << " " << valn << "(" << (val) << ")"
	#define rtTrace2(msg, valn1, val1, valn2, val2) LOG(TRACE) << "RunningThread(" << id() << "): " << msg << " " << valn1 << "(" << (val1) << ") " << valn2 << "(" << (val2) << ")"
#else
	#define rtTrace(msg)
	#define rtTrace1(msg, valn, val)
	#define rtTrace2(msg, valn1, val1, valn2, val2)
#endif

/**
 * Global variables
 */
int RunningThread::g_counter = 0;

RunningThread::RunningThread(const std::string& l_id):
	m_id(l_id)
{
	m_stopThread.store(false);
	m_running.store(false);
	rtTrace("Create Running thread");
}

RunningThread::~RunningThread()
{
	rtTrace("Destroy Running thread: stop");
	stop();
	rtTrace("Destroy Running thread: join");
	join();
	rtTrace("Destroy Running thread: joined");
}

void RunningThread::run()
{
	try {
		rtTrace("Running thread: run");
		m_thread = std::thread(&RunningThread::internalRun, this);
		rtTrace("Running thread: running");
	} catch(const std::exception& e) {
		LOG(ERROR) << "Error creating thread: " << e.what();
		throw;
	}
}

void RunningThread::stop()
{
	m_stopThread.store(true);
	rtTrace("Running thread: stopping");
	stopping();
	rtTrace("Running thread: stopped");
}

void RunningThread::join()
{
	rtTrace("Running thread: joining");
	if (m_thread.joinable()) {
		m_thread.join();
	}
	rtTrace("Running thread: joined");
}

bool RunningThread::running() const
{
	return m_running.load();
}

void RunningThread::handleError()
{
	LOG(ERROR) << "Unknown error";
}

void RunningThread::handleError(const std::exception &e)
{
	LOG(ERROR) << "Error: " << e.what();
}

void RunningThread::internalRun()
{
	m_running.store(true);

	rtTrace1("Running thread: internalRun", "stopThread", m_stopThread.load());
	while(m_stopThread.load() == false) {

		try {
			rtTrace("Running thread: taskPreCondition");
			taskPreCondition();
			if (m_stopThread.load() == false) {
				rtTrace("Running thread: task");
				task();
			}
		} catch(const std::exception& e) {
			handleError(e);
			m_stopThread.store(true);
		} catch(...) {
			handleError();
			m_stopThread.store(true);
		}
		rtTrace1("Running thread: internalRun loop", "stopThread", m_stopThread.load());
	}

	rtTrace("Running thread: before stopped");
	stopped();
	rtTrace("Running thread: after stopped");

	m_running.store(false);
}

} /* namespace threading */
} /* namespace common */
} /* namespace offcenter */
