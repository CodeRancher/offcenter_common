/**
 * Copyright 2021 Scott Brauer
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
 * @file   AppManagerApp.cpp
 * @author Scott Brauer
 * @date   11-29-2021
 */

#include <iostream>
#include <regex>

#include "easylogging++.h"

#include "offcenter/common/InterruptHandler.hpp"
#include "offcenter/common/app_manager/AppManagerApp.hpp"
#include "offcenter/common/Processes.hpp"
#include "offcenter/common/threading/RunningThread.hpp"

namespace offcenter {
namespace common {
namespace appmanager {

/*
 * A thread safe print method
 *
 * value - The string to print
 */
void printString(const std::string& value) {
	static std::mutex printMutex;

	std::lock_guard<std::mutex> lock {printMutex};
	std::cout << "Monitor: " << value << std::endl;
}

/*
 *
 */
class MonitorStdOut:
		public offcenter::common::threading::RunningThread
{
public:
	MonitorStdOut(boost::iostreams::stream<boost::iostreams::file_descriptor_source>& stdOutStream, int millisecondsSleep = 100):
		RunningThread(),
		m_stdOutStream(stdOutStream),
		m_millisecondsSleep(millisecondsSleep)
	{}
	virtual ~MonitorStdOut() = default;

protected:
	void task() override {
		std::string message;
		std::getline(m_stdOutStream, message);
		if (!message.empty()) {
			offcenter::common::appmanager::printString(message);
		} else {
			std::this_thread::sleep_for(std::chrono::milliseconds(m_millisecondsSleep));
		}

		//char gfg[50] = {};
		//m_stdOutSourceInStream.readsome(gfg, 3);
		//std::cout << gfg;

//		char
//		std::cout << message;
	}

	void stopped() override {
//		::printString("ExampleThread1: Stopped");
	}
private:
	//offcenter::common::ProcessPipeReadWrite& m_stdOutSourceInStream;
	boost::iostreams::stream<boost::iostreams::file_descriptor_source>& m_stdOutStream;
	int m_millisecondsSleep;
};

AppManagerApp::AppManagerApp():
		IApp()
{

}

AppManagerApp::~AppManagerApp() {
	// TODO Auto-generated destructor stub
}

void AppManagerApp::onInitProgramOptions(
        program_options::ProgramOptionsManager &optionsManager)
{
	m_appManagerOptions = optionsManager.add<offcenter::common::appmanager::AppManagerProgramOptions>();
}

void AppManagerApp::onSetUp()
{
}

void AppManagerApp::onExecute()
{
	std::vector<std::string> arguments;
	offcenter::common::Process::Ptr process = offcenter::common::Process::factory();
	MonitorStdOut monitorStdOut(process->stdOutStream());
	process->init("${HOME}/dev/github/offcenter_trading_system/build/Debug/bin/waitfor_sigint", arguments);
	process->run();
	monitorStdOut.run();

	std::cout << "AppManagerApp: Waiting for Ctrl-C" << std::endl;
	offcenter::common::interrupthandler::waitForUserInterrupt();
	std::cout << "AppManagerApp: Ctrl-C pressed" << std::endl;

	process->waitSigint();
	monitorStdOut.stop();
	monitorStdOut.join();
}

void AppManagerApp::onTearDown()
{
}

/**
 * Called when help should be displayed.
 *
 * @param help A string that contains the help
 */
void AppManagerApp::onHelp(const std::string &help)
{
	std::cout << help << std::endl;
}

void AppManagerApp::onVersion()
{
}

} /* namespace appmanager */
} /* namespace common */
} /* namespace offcenter */
