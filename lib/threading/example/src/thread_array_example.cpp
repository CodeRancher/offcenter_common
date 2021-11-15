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
 * @file   multi_thread_example.cpp
 * @author Scott Brauer
 * @date   09-14-2021
 */

#include <mutex>
#include <iostream>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/threading/RunningThreadArray.hpp"

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
class ExampleThread3: public offcenter::common::threading::RunningThread
{
public:
	ExampleThread3(const std::string& name, int millisecondsSleep = 100):
		RunningThread(),
		m_loopCount(0),
		m_name(name),
		m_millisecondsSleep(millisecondsSleep)
	{}
	virtual ~ExampleThread3() = default;

protected:
	virtual void task() {
		m_loopCount++;
		::printString("ExampleThread2: " + m_name + " - " + std::to_string(m_loopCount));
		std::this_thread::sleep_for(std::chrono::milliseconds(m_millisecondsSleep));
	}

	virtual void stopped() {
		::printString("ExampleThread2: " + m_name + " - Stopped");
	}
private:
	int m_loopCount;
	std::string m_name;
	int m_millisecondsSleep;
};

//*****************************************************************************
int main(int argc, char **argv) {
	START_EASYLOGGINGPP(argc, argv);

	std::cout << "Example Running Thread Array!" << std::endl;

	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./RunningThreadExample.log");

	LOG(INFO) << "--------------------------------------------------------------------------------";

	offcenter::common::threading::RunningThreadArray<ExampleThread3> threads;

	threads.add(std::make_unique<ExampleThread3>("thread1",  1 * 25));
	threads.add(std::make_unique<ExampleThread3>("thread2",  2 * 25));
	threads.add(std::make_unique<ExampleThread3>("thread3",  3 * 25));
	threads.add(std::make_unique<ExampleThread3>("thread4",  4 * 25));
	threads.add(std::make_unique<ExampleThread3>("thread5",  5 * 25));
	threads.add(std::make_unique<ExampleThread3>("thread6",  6 * 25));
	threads.add(std::make_unique<ExampleThread3>("thread7",  7 * 25));
	threads.add(std::make_unique<ExampleThread3>("thread8",  8 * 25));
	threads.add(std::make_unique<ExampleThread3>("thread9",  9 * 25));
	threads.add(std::make_unique<ExampleThread3>("thread10", 10 * 25));

	printString("Starting threads");
	threads.run();

	printString("Sleeping");
	std::this_thread::sleep_for(std::chrono::seconds(1));

	printString("Stopping threads");
	threads.stop();

	printString("Joining threads");
	threads.join();
}
