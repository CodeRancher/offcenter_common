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
 * @file   RunningThreadBlockable.cpp
 * @author Scott Brauer
 * @date   10-14-2021
 */

#include "easylogging++.h"

#include "offcenter/common/threading/RunningThreadBlockable.hpp"

namespace offcenter {
namespace common {
namespace threading {

/**
 * Create a trace message
 */
#ifdef RUNNINGTHREADTRACE
	#define rtbTrace(msg) LOG(TRACE) << "RunningThreadBlockable(" << id() << "): " << msg
	#define rtbTraceV(msg, valn, val) LOG(TRACE) << "RunningThreadBlockable(" << id() << "): " << msg << " " << valn << "(" << (val) << ")"
#else
	#define rtbTrace(msg)
	#define rtbTraceV(msg, valn, val)
#endif

/**
 * Global variables
 */
int RunningThreadBlockable::g_counter = 0;

RunningThreadBlockable::RunningThreadBlockable(const std::string& l_id):
		RunningThread(l_id)
{
	m_block.store(true);
	rtbTrace("Create blockable thread");
}

RunningThreadBlockable::~RunningThreadBlockable()
{
	rtbTraceV("Destroy blockable thread", "block", m_block.load() ? "true" : "false");
}

void RunningThreadBlockable::block()
{
	m_block.store(true);
	rtbTraceV("Block blockable thread", "block", m_block.load() ? "true" : "false");
}

void RunningThreadBlockable::unblock()
{
	{
		std::lock_guard<std::mutex> lk(m_mutex);
		m_block.store(false);
		rtbTraceV("Unblock blockable thread", "block", m_block.load() ? "true" : "false");
	}
	m_cv.notify_one();
}

void RunningThreadBlockable::taskPreCondition()
{
	std::unique_lock<std::mutex> lk(m_mutex);
	if (m_block.load() == true) {
		rtbTraceV("Blockable thread waiting...", "block", m_block.load() ? "true" : "false");
		m_cv.wait(lk);
		rtbTraceV("Blockable thread finished waiting", "block", m_block.load() ? "true" : "false");
	} else {
		rtbTraceV("Blockable thread doesn't need to wait", "block", m_block.load() ? "true" : "false");
	}
	lk.unlock();
}

void RunningThreadBlockable::stopping()
{
	rtbTrace("Blockable thread stopping");
	unblock();
}

} /* namespace threading */
} /* namespace common */
} /* namespace offcenter */
