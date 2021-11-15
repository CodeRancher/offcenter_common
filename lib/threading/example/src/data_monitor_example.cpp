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

#include "offcenter/common/threading/DataMonitorThread.hpp"

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

/**
 * Example data element
 */
struct ExampleData {
	int start;
	int end;
};

/*
 *
 */
class ExampleThread:
		public offcenter::common::threading::DataMonitorThread<ExampleData>
{
public:
	ExampleThread():
		DataMonitorThread(),
		m_current(0)
	{}
	virtual ~ExampleThread() = default;

protected:
	void onNewData() {
		::printString("onNewData: " + std::to_string(data().start) + ", " + std::to_string(data().end));
		LOG(INFO) << "onNewData: " << data().start << ", " << data().end;
		if (m_current < data().end) {
			unblock();
		}
	}

	void task() override {
		m_current++;
		LOG(INFO) << "Task: " << "Current(" << m_current << ") End(" << data().end << ")";
		if (m_current <= data().end) {
			::printString("Current: " + std::to_string(m_current));
			LOG(INFO) << "Current: " << m_current;
		}

		if (m_current >= data().end) {
			block();
			::printString("Blocking: " + std::to_string(m_current));
			LOG(INFO) << "Blocking: " << m_current;
		}
	}

	void stopped() override {
		::printString("ExampleThread: Stopped");
	}

private:
	int m_current;
};

//*****************************************************************************
int main(int argc, char **argv) {
	START_EASYLOGGINGPP(argc, argv);

	std::cout << "Example Running Thread!" << std::endl;

	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./data_monitor_example.log");

	LOG(INFO) << "--------------------------------------------------------------------------------";

	printString("Starting thread1");
	int millisecondsSleep = 500;
	auto thread = std::make_unique<ExampleThread>();
	thread->run();

	ExampleData data {0, 0};
	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	data.end += 3;
	thread->setData(data);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	data.end += 0;
	thread->setData(data);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	data.end += 20;
	thread->setData(data);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	data.end += 100;
	thread->setData(data);

	data.end += 20;
	thread->setData(data);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	printString("Stopping thread1");
	thread->stop();
	thread->join();
}
