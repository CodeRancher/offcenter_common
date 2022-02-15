/**
 * Copyright 2022 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the );
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
 * @file   WaitforSigintApp.cpp
 * @author Scott Brauer
 * @date   01-25-2022
 */

#include <iostream>
#include <regex>

#include "easylogging++.h"

#include "offcenter/common/InterruptHandler.hpp"
#include "offcenter/common/waitfor_sigint/WaitforSigintApp.hpp"

namespace offcenter {
namespace common {
namespace waitforsigint {

/*
 * A thread safe print method
 *
 * value - The string to print
 */
void printString(const std::string& value) {
	static std::mutex printMutex;

	std::lock_guard<std::mutex> lock {printMutex};
	std::cout << "Counter: " << value << std::endl;
}

/*
 *
 */
Counter::Counter(int millisecondsSleep):
	RunningThread(),
	m_counter(0),
	m_millisecondsSleep(millisecondsSleep)
{}

void Counter::task() {
	printString(std::to_string(m_counter++));
	std::this_thread::sleep_for(std::chrono::milliseconds(m_millisecondsSleep));
}

void Counter::stopped() {}

WaitforSigintApp::WaitforSigintApp():
		IApp(),
		m_counter()
{

}

WaitforSigintApp::~WaitforSigintApp() {
	// TODO Auto-generated destructor stub
}

void WaitforSigintApp::onInitProgramOptions(
        program_options::ProgramOptionsManager &optionsManager)
{
}

void WaitforSigintApp::onSetUp()
{
}

void WaitforSigintApp::onExecute()
{
	m_counter.run();
	std::cout << "WaitingForSigint: Waiting for Ctrl-C" << std::endl;
	offcenter::common::interrupthandler::waitForUserInterrupt();
	std::cout << "WaitingForSigint: Ctrl-C pressed" << std::endl;

	m_counter.stop();
	m_counter.join();
}

void WaitforSigintApp::onTearDown()
{
}

/**
 * Called when help should be displayed.
 *
 * @param help A string that contains the help
 */
void WaitforSigintApp::onHelp(const std::string &help)
{
	std::cout << help << std::endl;
}

void WaitforSigintApp::onVersion()
{
}

} /* namespace waitforsigint */
} /* namespace common */
} /* namespace offcenter */
