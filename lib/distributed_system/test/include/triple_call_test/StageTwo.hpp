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
 * @file   StageTwo.hpp
 * @author Scott Brauer
 * @date   04-08-2020
 */

#ifndef LIB_DISTRIBUTED_SYSTEM_TEST_SRC_TRIPLE_CALL_TEST_STAGETWO_HPP_
#define LIB_DISTRIBUTED_SYSTEM_TEST_SRC_TRIPLE_CALL_TEST_STAGETWO_HPP_

#include <memory>

#include "offcenter/common/distributedsystem/ConsumerDataListener.hpp"

/***
 *
 */
class IStageTwoCommandHandler
{
public:
	//using Ptr = std::shared_ptr<ICommandHandler>;
public:
	explicit IStageTwoCommandHandler() = default;
};

/***
 *
 */
class StageTwoCLConfig
{
public:
	explicit StageTwoCLConfig() {}
};

/**
 *
 */
class StageTwoCommandHandler : public IStageTwoCommandHandler
{
public:
	using Ptr = std::shared_ptr<IStageTwoCommandHandler>;
	static Ptr factory() {
		return std::make_shared<StageTwoCommandHandler>();
	}

public:
	explicit StageTwoCommandHandler() {}
};

/**
 *
 */
class StageTwoCommandListener : public offcenter::distributedsystem::ConsumerDataListener<IStageTwoCommandHandler>
{
public:
	explicit StageTwoCommandListener(StageTwoCLConfig const& clConfig, std::shared_ptr<IStageTwoCommandHandler> handler):
		offcenter::distributedsystem::ConsumerDataListener<IStageTwoCommandHandler>(handler)
	{

	}
};

#endif /* LIB_DISTRIBUTED_SYSTEM_TEST_SRC_TRIPLE_CALL_TEST_STAGETWO_HPP_ */
