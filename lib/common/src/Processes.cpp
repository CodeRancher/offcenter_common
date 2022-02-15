/**
 * Copyright 2022 Scott Brauer
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
 * @file   Processes.cpp
 * @author Scott Brauer
 * @date   01-24-2022
 */

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include <boost/algorithm/string.hpp>

#include "offcenter/common/Processes.hpp"
#include "offcenter/common/RuntimeException.hpp"

namespace offcenter {
namespace common {

ProcessPipeReadWrite::ProcessPipeReadWrite():
		m_pipeFds(),
		m_pipeState(PipeState::unknown),
		m_sinkOutStream(),
		m_sourceInStream()
{
	if (pipe(m_pipeFds) == -1) {
		throw offcenter::common::RuntimeException("Error creating pipe");
	}
}

/*
ProcessPipeReadWrite::ProcessPipeReadWrite(const ProcessPipeReadWrite& other):
		m_pipeState(other.m_pipeState),
		m_sinkOutStream(other.m_sinkOutStream),
		m_sourceInStream(other.m_sourceInStream)
{
	m_pipeFds[0] = other.m_pipeFds[0];
	m_pipeFds[1] = other.m_pipeFds[1];
}
*/

ProcessPipeReadWrite::~ProcessPipeReadWrite()
{
	//if (m_pipeState != PipeState::sink_out) {
		//m_sinkOutStream.close();
		//close(inputFds());
	//}
	//if (m_pipeState != PipeState::source_in) {
		//m_writeStream.close();
		//close(outputFds());
	//}
}

void ProcessPipeReadWrite::setSinkOutOnly(int stdStream)
{
	if (stdStream >= 0) {
		dup2(outputFds(), stdStream);
		close(inputFds());
	}
	boost::iostreams::file_descriptor_sink sinkOutDescriptor{outputFds(), boost::iostreams::close_handle};
	m_sinkOutStream.open(sinkOutDescriptor);
	m_pipeState = PipeState::sink_out;
}

ProcessPipeReadWrite::SinkOutStream& ProcessPipeReadWrite::sinkOutStream()
{
	if (m_pipeState != PipeState::sink_out) {
		throw offcenter::common::RuntimeException("Attempt to retrieve an invalid sink/out stream");
	}

	return m_sinkOutStream;
}

void ProcessPipeReadWrite::setSourceInOnly(int stdStream)
{
	if (stdStream >= 0) {
		dup2(readFds(), stdStream);
		close(writeFds());
	}
	boost::iostreams::file_descriptor_source sourceInDescriptor(readFds(), boost::iostreams::close_handle);
	m_sourceInStream.open(sourceInDescriptor);
	m_pipeState = PipeState::source_in;
}

ProcessPipeReadWrite::SourceInStream& ProcessPipeReadWrite::sourceInStream()
{
	if (m_pipeState != PipeState::source_in) {
		throw offcenter::common::RuntimeException("Attempt to retrieve an invalid source/in stream");
	}

	return m_sourceInStream;
}

/**
 *
 */
Process::Process():
		m_procPath(),
		m_arguments(),
		m_procID(0),
		m_stdOutPipe(),
		m_stdOutFDS(),
		m_stdOutStream()
		//,
		//m_stdIn(),
		//m_stdOut(),
		//m_stdErr()
{

}

Process::~Process()
{
	if (m_stdOutPipe[1] != -1) {
		close(m_stdOutPipe[1]);
	}
	//if (m_stdOutPipe[1] != -1) {
	//	close(m_stdOutPipe[1]);
	//}
}

void Process::init(const std::string& procPath, const std::vector<std::string>& arguments)
{
	m_procPath = procPath;
	m_arguments = arguments;
}

char *convert(const std::string& s)
{
	char *pc = new char[s.size()+1];
	std::strcpy(pc, s.c_str());
	return pc;
}

void Process::run()
{
    pipe(m_stdOutPipe);

	m_procID = fork();
	std::cout << m_procID << ": " << "Run" << std::endl;
	if (m_procID == 0) {
		// Child process
    	dup2(m_stdOutPipe[1],1);
        close(m_stdOutPipe[0]);
        m_stdOutPipe[0] = -1;
		//m_stdIn.setSourceInOnly(0);
		//m_stdOut.setSinkOutOnly(1);
		//m_stdErr.setSinkOutOnly(2);

		//char* arguments[m_procPath.size() + 2];
		std::cout << m_procID << ": " << "Run: m_procPath: " << m_procPath << std::endl << std::flush;
		//m_stdOut.writeStream() << m_procID << ": " << "Run: m_procPath: " << m_procPath;
//		arguments[0] = const_cast<char*>(m_procPath.c_str());
//		for (int index = 0; index < m_procPath.size(); index++) {
//			std::cout << "Run: m_arguments" << "[" << index << "]: " << m_arguments[index] << std::endl << std::flush;
//			//m_stdOut.writeStream() << "Run: m_arguments" << "[" << index - 1 << "]: " << m_arguments[index - 1] << std::endl;
//			arguments[index + 1] = const_cast<char*>(m_arguments[index].c_str());
//		}
//		arguments[m_procPath.size() + 1] = nullptr;

//		std::vector<const char *> vc(m_arguments.size() + 2);
//		std::transform(m_arguments.begin(), m_arguments.end(), vc.begin(), std::mem_fun_ref(&std::string::c_str));
//		vc.push_back(nullptr);
//		vc.push_back(convert(m_procPath));

//		std::transform(m_arguments.begin(), m_arguments.end(), std::back_inserter(vc), convert);

//		for ( size_t i = 0 ; i < vc.size() ; i++ )
//	/		std::cout << i << ": " << vc[i] << std::endl;
//		vc.push_back(convert(nullptr));

/*
		const char *programname = m_procPath.c_str();

		const char **argv = new const char* [m_arguments.size()+2];   // extra room for program name and sentinel
		argv [0] = programname;         // by convention, argv[0] is program name
		for (int j = 0;  j < m_arguments.size()+1;  ++j)     // copy args
		        argv [j+1] = m_arguments[j] .c_str();

		argv [m_arguments.size()+1] = NULL;  // end of arguments sentinel is NULL

		std::cout << m_procID << ": " << "execv: " << programname << std::endl << std::flush;
		int execRet = execv (programname, (char **)argv);
*/

		std::vector<char*> commandVector;
		commandVector.push_back(const_cast<char*>(m_procPath.c_str()));
		for (std::string argument : m_arguments) {
			commandVector.push_back(const_cast<char*>(argument.c_str()));
		}
		commandVector.push_back(nullptr);

		// pass the vector's internal array to execvp
		char **command = commandVector.data();

		int execRet = execv(command[0], &command[0]);



//		std::cout << m_procID << ": " << "execv: " << m_procPath << std::endl << std::flush;
		//m_stdOut.writeStream() << m_procID << ": " << "execv: " << m_procPath << std::endl;
//		int execRet = execv(m_procPath.c_str(), &vc[0]);

		//int execRet = execlp("ls", "ls", "-al", "--color");
		std::cout << m_procID << ": " << "execv return: " << execRet << std::endl << std::flush;

//		for ( size_t i = 0 ; i < vc.size() ; i++ )
//			delete [] vc[i];

		//m_stdOut.writeStream() << ": " << "execv return: " << execRet;
		if (execRet == -1) {
			std::cerr << m_procID << ": " << "Unable to execute: " << m_procPath << std::endl;
			throw offcenter::common::RuntimeException("Unable to execute: " + m_procPath);
		}
	} else if (m_procID < 0) {
		// Error condition
		std::cerr << m_procID << ": " << "Error forking: " << m_procPath << std::endl;;
		throw offcenter::common::RuntimeException("Error forking: " + m_procPath);
	} else {
        close(m_stdOutPipe[1]);
        m_stdOutPipe[1] = -1;
		// Parent process
		std::cout << m_procID << ": " << "fork: parent" << std::endl << std::flush;

		m_stdOutFDS.open(m_stdOutPipe[0], boost::iostreams::close_handle);
		m_stdOutStream.open(m_stdOutFDS);
		//m_stdOut.writeStream() << m_procID << ": " << "fork: parent";

		//m_stdIn.setSinkOutOnly();
		//m_stdOut.setSourceInOnly();
		//m_stdErr.setSourceInOnly();
	}
}

void Process::sigint() const
{
	kill(m_procID, SIGINT);
}

void Process::waitSigint() const
{
	waitExit([&](){ sigint(); });
}

Processes::Processes():
		m_processes()
{
	// TODO Auto-generated constructor stub

}

Processes::~Processes()
{
	// TODO Auto-generated destructor stub
}

void Processes::add(const std::string &filePath)
{
	std::ifstream fileStream(filePath);
	if (fileStream.is_open())
	{
		add(fileStream);
		fileStream.close();
	} else {
		throw offcenter::common::RuntimeException("Unable to open file: " + filePath);
	}
}

void Processes::add(std::ifstream& fileStream)
{
	std::string line;
	while (std::getline(fileStream, line)) {
		std::vector<std::string> result;
		boost::split(result, line, boost::is_any_of(","));
		add(result.at(0), result);
	}
}

void Processes::add(const std::string &procPath, const std::vector<std::string> &arguments)
{
	Process::Ptr process = Process::factory();
	process->init(procPath, arguments);
	m_processes.push_back(process);
}

void Processes::run()
{
	for (Process::Ptr& process : m_processes) {
		process->run();
	}
}

void Processes::sigint()
{
	for (auto it = m_processes.rbegin(); it != m_processes.rend(); ++it) {
		(*it)->sigint();
	}
}

} /* namespace common */
} /* namespace offcenter */
