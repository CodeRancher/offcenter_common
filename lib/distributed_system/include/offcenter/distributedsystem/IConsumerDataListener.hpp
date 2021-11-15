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
 * @file   IConsumerDataListener.hpp
 * @author Scott Brauer
 * @date   04-03-2020
 */

#ifndef OFFCENTER_DISTRIBUTEDSYSTEM_ICONSUMERDATALISTENER_HPP_
#define OFFCENTER_DISTRIBUTEDSYSTEM_ICONSUMERDATALISTENER_HPP_

#include <memory>

namespace offcenter {
namespace distributedsystem {

class IConsumerDataListener {
public:
	using UPtr = std::unique_ptr<IConsumerDataListener>;

public:
	explicit IConsumerDataListener() = default;
	virtual ~IConsumerDataListener() = default;
};

} /* namespace distributedsystem */
} /* namespace offcenter */

#endif /* OFFCENTER_DISTRIBUTEDSYSTEM_ICONSUMERDATALISTENER_HPP_ */
