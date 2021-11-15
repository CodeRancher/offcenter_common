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
 * @file   single_thread_example.cpp
 * @author Scott Brauer
 * @date   09-14-2021
 */

#include <mutex>
#include <iostream>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/threading/RunningThread.hpp"

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
class ExampleThread1: public offcenter::common::threading::RunningThread
{
public:
	ExampleThread1(int millisecondsSleep = 100):
		RunningThread(),
		m_loopCount(0),
		m_millisecondsSleep(millisecondsSleep)
	{}
	virtual ~ExampleThread1() = default;

protected:
	virtual void task() {
		m_loopCount++;
		::printString("ExampleThread1: " + std::to_string(m_loopCount));
		std::this_thread::sleep_for(std::chrono::milliseconds(m_millisecondsSleep));
	}

	virtual void stopped() {
		::printString("ExampleThread1: Stopped");
	}
private:
	int m_loopCount;
	int m_millisecondsSleep;
};

//*****************************************************************************
int main(int argc, char **argv) {
	START_EASYLOGGINGPP(argc, argv);

	std::cout << "Example Running Thread!" << std::endl;

	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./RunningThreadExample.log");

	LOG(INFO) << "--------------------------------------------------------------------------------";

	printString("Starting thread1");
	auto thread1 = std::make_unique<ExampleThread1>();
	thread1->run();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	printString("Stopping thread1");
	thread1->stop();
	thread1->join();
}
