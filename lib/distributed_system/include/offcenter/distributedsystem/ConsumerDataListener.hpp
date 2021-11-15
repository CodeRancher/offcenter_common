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
 * @file   ConsumerDataListener.hpp
 * @author Scott Brauer
 * @date   03-30-2020
 */

#ifndef OFFCENTER_DISTRIBUTEDSYSTEM_CONSUMERDATALISTENER_HPP_
#define OFFCENTER_DISTRIBUTEDSYSTEM_CONSUMERDATALISTENER_HPP_

#include <memory>

#include "IConsumerDataListener.hpp"

namespace offcenter {
namespace distributedsystem {

template <typename Handler>
class ConsumerDataListener : public IConsumerDataListener
{
public:
	using UPtr = std::unique_ptr<ConsumerDataListener>;
	using HandlerPtr = std::shared_ptr<Handler>;

public:
	explicit ConsumerDataListener(HandlerPtr handler):
		IConsumerDataListener()
	{
		m_handler = handler;
	}

	virtual ~ConsumerDataListener() = default;

protected:
	HandlerPtr handler() { return m_handler; }

private:
	HandlerPtr m_handler;

};

/*
template <typename Handler>
RemoteCommandListener::RemoteCommandListener(HandlerPtr handler)
{

}
*/

} /* namespace distributedsystem */
} /* namespace offcenter */

#endif /* OFFCENTER_DISTRIBUTEDSYSTEM_CONSUMERDATALISTENER_HPP_ */
