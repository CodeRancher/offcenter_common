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
 * @file   blocked_thread_example.cpp
 * @author Scott Brauer
 * @date   10-14-2021
 */

#include <mutex>
#include <iostream>
#include <atomic>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/threading/RunningThreadBlockable.hpp"

/*
 * A thread safe print method
 *
 * value - The string to print
 */
void printString(const std::string& value) {
	static std::mutex printMutex;

	std::lock_guard<std::mutex> lock {printMutex};
	std::cout << value << std::endl;
}

/*
 *
 */
class ExampleThread1: public offcenter::common::threading::RunningThreadBlockable
{
public:
	ExampleThread1():
		RunningThreadBlockable(),
		m_rangeEnd(0),
		m_rangeCurrent(0)
	{}
	virtual ~ExampleThread1() = default;

	void changeEnd(int end) {
		::printString("Change End: " + std::to_string(end));
		LOG(INFO) << "Change End: " << end;
		if (end > m_rangeEnd.load()) {
			m_rangeEnd.store(end);
			unblock();
		}
	}

protected:
	void task() override {
		m_rangeCurrent++;
		LOG(INFO) << "Task: " << "Current(" << m_rangeCurrent << ") End(" << m_rangeEnd.load() << ")";
		if (m_rangeCurrent <= m_rangeEnd.load()) {
			::printString("Current: " + std::to_string(m_rangeCurrent));
			LOG(INFO) << "Current: " << m_rangeCurrent;
		}

		if (m_rangeCurrent >= m_rangeEnd.load()) {
			block();
			::printString("Blocking: " + std::to_string(m_rangeCurrent));
			LOG(INFO) << "Blocking: " << m_rangeCurrent;
		}
	}

	void stopped() override {
		::printString("ExampleThread1: Stopped");
	}

private:
	std::atomic<int> m_rangeEnd;
	int m_rangeCurrent;
};

//*****************************************************************************
int main(int argc, char **argv) {
	START_EASYLOGGINGPP(argc, argv);

	std::cout << "Example Running Thread!" << std::endl;

	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./BlockingThreadExample.log");

	LOG(INFO) << "--------------------------------------------------------------------------------";

	printString("Starting thread1");
	int millisecondsSleep = 500;
	auto thread1 = std::make_unique<ExampleThread1>();
	thread1->run();

	int currentEnd = 0;
	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	currentEnd += 3;
	thread1->changeEnd(currentEnd);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	currentEnd += 0;
	thread1->changeEnd(currentEnd);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	currentEnd += 100;
	thread1->changeEnd(currentEnd);

	currentEnd += 20;
	thread1->changeEnd(currentEnd);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	printString("Stopping thread1");
	thread1->stop();
	thread1->join();
}
