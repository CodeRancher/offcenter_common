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
 * @file   Processes.hpp
 * @author Scott Brauer
 * @date   01-24-2022
 */

#ifndef OFFCENTER_COMMON_PROCESSES_HPP_
#define OFFCENTER_COMMON_PROCESSES_HPP_

#include <string>
#include <vector>
#include <memory>
#include <sys/wait.h>

#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>

#include "offcenter/common/RuntimeException.hpp"

namespace offcenter {
namespace common {

/**
 *
 */
class ProcessPipeReadWrite
{
public:
	using SinkOutStream = boost::iostreams::stream<boost::iostreams::file_descriptor_sink>;
	using SourceInStream = boost::iostreams::stream<boost::iostreams::file_descriptor_source>;

	enum class PipeState{
		unknown,
		sink_out,
		source_in
	};

public:
	ProcessPipeReadWrite();
	//ProcessPipeReadWrite(const ProcessPipeReadWrite& other);
	virtual ~ProcessPipeReadWrite();

	void setSinkOutOnly(int stdStream = -1);
	SinkOutStream& sinkOutStream();

	void setSourceInOnly(int stdStream = -1);
	SourceInStream& sourceInStream();

private:
	int inputFds() { return m_pipeFds[0]; }
	int readFds() { return m_pipeFds[0]; }

	int outputFds() { return m_pipeFds[1]; }
	int writeFds() { return m_pipeFds[1]; }

private:
	int m_pipeFds[2];
	PipeState m_pipeState;
	SinkOutStream m_sinkOutStream;
	SourceInStream m_sourceInStream;
};

/**
 *
 */
class Process
{
public:
	using Ptr = std::shared_ptr<Process>;

	static Ptr factory() { return std::make_shared<Process>(); }

public:
	Process();
	virtual ~Process();

	void init(const std::string& procPath, const std::vector<std::string>& arguments);
	void run();
	void sigint() const;
	void waitSigint() const;

	template<typename Signal>
	void waitExit(Signal&& signal = [](){}) const
	{
		signal();
		int status;
		do {
			pid_t wait;
			wait = waitpid(m_procID, &status, WUNTRACED | WCONTINUED);
			if (wait == -1) {
				std::cerr << "Error waiting for pid: " << m_procPath << std::endl;
				throw offcenter::common::RuntimeException("Error waiting for pid: " + m_procPath);
			}

			if (WIFEXITED(status)) {
				std::cout << "exited, status =" << WEXITSTATUS(status) << std::endl;
			} else if (WIFSIGNALED(status)) {
				std::cout << "killed by signal " << WTERMSIG(status) << std::endl;
			} else if (WIFSTOPPED(status)) {
				std::cout << "stopped by signal " << WSTOPSIG(status) << std::endl;
			} else if (WIFCONTINUED(status)) {
				std::cout << "continued" << std::endl;
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

//	ProcessPipeReadWrite& stdIn() { return m_stdIn; }
//	ProcessPipeReadWrite& stdOut() { return m_stdOut; }
//	ProcessPipeReadWrite& stdErr() { return m_stdErr; }

	boost::iostreams::stream<boost::iostreams::file_descriptor_source>& stdOutStream() { return m_stdOutStream; }

private:
	std::string m_procPath;
	std::vector<std::string> m_arguments;
	pid_t m_procID;

	int m_stdOutPipe[2];
	boost::iostreams::file_descriptor_source m_stdOutFDS;
	boost::iostreams::stream<boost::iostreams::file_descriptor_source> m_stdOutStream;


//	ProcessPipeReadWrite m_stdIn;
//	ProcessPipeReadWrite m_stdOut;
//	ProcessPipeReadWrite m_stdErr;

};

/**
 *
 */
class Processes
{
public:
	Processes();
	virtual ~Processes();

	void add(const std::string& filePath);
	void add(std::ifstream& fileStream);

	void add(const std::string& procPath, const std::vector<std::string>& arguments);

	void run();
	void sigint();

private:
	std::vector<Process::Ptr> m_processes;
};

} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_PROCESSES_HPP_ */
