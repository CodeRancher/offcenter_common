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
 * @file   main.cpp
 * @author Scott Brauer
 * @date   01-27-2019
 */

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP


int main(int argc, char **argv)
{
	try {
		START_EASYLOGGINGPP(argc, argv);

		addaout::ProgramOptions programOptions(argc, argv);
		initLogging(programOptions.logSeverityName(), programOptions.logSeverityLevel());
		logProgramOptions(programOptions);
		if (!(programOptions.showHelp() || programOptions.showVersion())) {
			addaout::DisplayAdDaBoardData displayData(std::move(programOptions), g_cv);

			LOG(INFO) << "Start processing data";
			thread displayDataThread(&addaout::DisplayAdDaBoardData::start, &displayData);
			displayDataThread.detach();

			g_cv.wait(g_lk);

			displayData.stop();
			LOG(INFO) << "Stop processing data";
		}
	} catch( const boost::exception& e ) {
		cout << boost::diagnostic_information(e);
		LOG(ERROR) << boost::diagnostic_information(e);
	} catch( const std::exception& e) {
		cout << e.what() << endl;
		LOG(ERROR) << e.what();
	}

	return 0;
}



