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
 * @file   InterruptHandler.hpp
 * @author Scott Brauer
 * @date   04-12-2021
 */

#ifndef OffcenterCommon_INTERRUPTHANDLER_HPP_
#define OffcenterCommon_INTERRUPTHANDLER_HPP_

#include <condition_variable>
#include <mutex>
#include <iostream>
#include <signal.h>

#include "easylogging++.h"

namespace offcenter {
namespace common {
namespace interrupthandler {

static std::condition_variable _condition;
static std::mutex _mutex;

void handleUserInterrupt(int signal){
	if (signal == SIGINT) {
		LOG(INFO) << "SIGINT trapped ...";
		_condition.notify_one();
	}
}

void hookSIGINT() {
	signal(SIGINT, handleUserInterrupt);
}

void waitForUserInterrupt() {
	hookSIGINT();
	std::unique_lock<std::mutex> lock { _mutex };
	LOG(INFO) << "Waiting for SIGINT";
	_condition.wait(lock);
	LOG(INFO) << "user has signaled to interrupt program ...";
	lock.unlock();
}

} /* namespace interrupthandler */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_INTERRUPTHANDLER_HPP_ */
