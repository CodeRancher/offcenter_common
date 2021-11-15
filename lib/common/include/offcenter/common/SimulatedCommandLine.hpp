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
 * @file   SimulatedCommandLine.hpp
 * @author Scott Brauer
 * @date   04-06-2019
 */

#ifndef OFFCENTER_COMMON_SIMULATEDCOMMANDLINE_HPP_
#define OFFCENTER_COMMON_SIMULATEDCOMMANDLINE_HPP_

#include <vector>
#include <initializer_list>
#include <memory>
#include <string.h>

namespace offcenter {
namespace common {

struct free_deleter{
    template <typename T>
    void operator()(T *p) const {
        std::free(const_cast<std::remove_const_t<T>*>(p));
    }
};
template <typename T>
using unique_C_ptr=std::unique_ptr<T,free_deleter>;
static_assert(sizeof(char *)==sizeof(unique_C_ptr<char>),""); // ensure no overhead

static unique_C_ptr<char> unique_C_ptr_factory(std::string t) { return unique_C_ptr<char> { strdup(t.c_str()) }; }

class SimulatedCommandLine
{
public:
	SimulatedCommandLine(std::string execCommand):
		m_finalized(false)
	{
		add(execCommand);
	};

	SimulatedCommandLine(std::string execCommand, std::initializer_list<std::string> elements):
		m_finalized(false)
	{
		add(execCommand);
		add(elements);
	};

	SimulatedCommandLine(std::string execCommand, std::vector<std::string> elements):
		m_finalized(false)
	{
		add(execCommand);
		add(elements);
	};

	virtual ~SimulatedCommandLine() = default;

	void add(std::initializer_list<std::string> elements) {
		std::vector<std::string> vecElements(elements);
		add(vecElements);
	}

	void add(std::vector<std::string> elements)
	{
	    for(std::string element: elements) {
	        add(element);
	    }
	}

	void add(std::string arg)
	{
		testIfFinalized();

		m_arguments.push_back(unique_C_ptr_factory(arg));
		m_argv.push_back(m_arguments.back().get());
	}

	void add(std::string arg1, std::string arg2)
	{
		add(arg1);
		add(arg2);
	}

	int argc()
	{
		finalize();
		return m_argv.size() - 1;
	}

	char** argv()
	{
		finalize();
		return m_argv.data();
	}

private:
	std::vector<unique_C_ptr<char> > m_arguments;
	std::vector<char*> m_argv;

	bool m_finalized;

	void finalize()
	{
		if (!m_finalized) {
			m_finalized = true;
			m_argv.push_back(nullptr);
		}
	}

	void testIfFinalized()
	{
		if (m_finalized) {
			throw std::runtime_error("Attempt to add command line arguments after calling argc/argv");
		}
	}

};

} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_SIMULATEDCOMMANDLINE_HPP_ */
