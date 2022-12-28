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
 * @file   StageThree.hpp
 * @author Scott Brauer
 * @date   04-08-2020
 */

#ifndef LIB_DISTRIBUTED_SYSTEM_TEST_SRC_TRIPLE_CALL_TEST_STAGETHREE_HPP_
#define LIB_DISTRIBUTED_SYSTEM_TEST_SRC_TRIPLE_CALL_TEST_STAGETHREE_HPP_

#include <memory>

#include "offcenter/common/distributedsystem/ConsumerDataListener.hpp"

/***
 *
 */
class IStageThreeCommandHandler
{
public:
	//using Ptr = std::shared_ptr<ICommandHandler>;
public:
	explicit IStageThreeCommandHandler() = default;
};

/***
 *
 */
class StageThreeCLConfig
{
public:
	explicit StageThreeCLConfig() {}
};

/**
 *
 */
class StageThreeCommandHandler : public IStageThreeCommandHandler
{
public:
	using Ptr = std::shared_ptr<IStageThreeCommandHandler>;
	static Ptr factory() {
		return std::make_shared<StageThreeCommandHandler>();
	}

public:
	explicit StageThreeCommandHandler() {}
};

/**
 *
 */
class StageThreeCommandListener : public offcenter::common::distributedsystem::ConsumerDataListener<IStageThreeCommandHandler>
{
public:
	explicit StageThreeCommandListener(StageThreeCLConfig const& clConfig, std::shared_ptr<IStageThreeCommandHandler> handler):
		offcenter::common::distributedsystem::ConsumerDataListener<IStageThreeCommandHandler>(handler)
	{

	}
};

#endif /* LIB_DISTRIBUTED_SYSTEM_TEST_SRC_TRIPLE_CALL_TEST_STAGETHREE_HPP_ */
