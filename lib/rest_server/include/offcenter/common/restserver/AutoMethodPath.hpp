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
 * @file   AuthoMethodPath.hpp
 * @author Scott Brauer
 * @date   04-14-2021
 */

#ifndef FFCENTER_COMMON_RESTSERVER_AUTHOMETHODPATH_HPP_
#define FFCENTER_COMMON_RESTSERVER_AUTHOMETHODPATH_HPP_

#include <string>
#include <regex>
#include <memory>

#include <cpprest/http_msg.h>

namespace offcenter {
namespace common {
namespace restserver {

class IAutoMethodPath
{
public:
	using Ptr = std::unique_ptr<IAutoMethodPath>;

public:
	virtual ~IAutoMethodPath() = default;

	virtual const std::string& path() const = 0;
	virtual const std::string& description() const = 0;
	virtual const std::regex& regex() const = 0;
	virtual void action(web::http::http_request& message, std::smatch& smatch) const = 0;
};


/**
 *
 */
template<typename ACTION>
class AutoMethodPath : public IAutoMethodPath
{
public:

public:
	explicit AutoMethodPath(std::string path, std::string description, ACTION action):
			m_path(path),
			m_description(description),
			m_regex(path),
			m_action(action)
	{}

	virtual ~AutoMethodPath() = default;

	const std::string& path() const override { return m_path; }
	const std::string& description() const override { return m_description; }
	const std::regex& regex() const override { return m_regex; }
	void action(web::http::http_request& message, std::smatch& smatch) const override {
		m_action(message, smatch);
	}

private:
	std::string m_path;
	std::string m_description;
	std::regex m_regex;
	ACTION m_action;
};

template<typename ACTION>
IAutoMethodPath::Ptr autoMethodPathFactory(const std::string& path, const std::string& description, ACTION action) {
	return std::make_unique<AutoMethodPath<ACTION> >(path, description, action);
}

} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* FFCENTER_COMMON_RESTSERVER_AUTHOMETHODPATH_HPP_ */
