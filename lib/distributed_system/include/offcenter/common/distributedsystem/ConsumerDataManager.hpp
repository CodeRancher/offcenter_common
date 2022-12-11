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
 * @file   ConsumerDataManager.hpp
 * @author Scott Brauer
 * @date   03-28-2020
 */

#ifndef OFFCENTER_DISTRIBUTEDSYSTEM_CONSUMERDATAMANAGER_H_
#define OFFCENTER_DISTRIBUTEDSYSTEM_CONSUMERDATAMANAGER_H_

#include <memory>
#include <vector>

#include "ConsumerDataListener.hpp"
#include "IConsumerDataListener.hpp"

namespace offcenter {
namespace distributedsystem {

class ConsumerDataManager {
public:
	explicit ConsumerDataManager();
	virtual ~ConsumerDataManager();

	template <typename Listener, typename Config, typename Handler>
	void addCommandListener(Config const& clConfig, std::shared_ptr<Handler> commandHandler);

private:
	std::vector<IConsumerDataListener::UPtr> m_listeners;
};

template <typename Listener, typename Config, typename Handler>
void ConsumerDataManager::addCommandListener(Config const& clConfig, std::shared_ptr<Handler> handler)
{
	m_listeners.push_back(std::move(std::make_unique<Listener>(clConfig, handler)));
}


} /* namespace distributedsystem */
} /* namespace offcenter */

#endif /* OFFCENTER_DISTRIBUTEDSYSTEM_CONSUMERDATAMANAGER_H_ */
