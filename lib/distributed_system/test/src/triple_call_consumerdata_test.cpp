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
 * @file   triple_call_consumerdata_test.cpp
 * @author Scott Brauer
 * @date   03-28-2020
 */

#include <memory>

#include <gtest/gtest.h>
#include "offcenter/distributedsystem/ConsumerDataListener.hpp"
#include "offcenter/distributedsystem/ConsumerDataManager.hpp"

#include "offcenter/common/WaitForMessage.hpp"
#include "triple_call_test/StageOne.hpp"
#include "triple_call_test/StageTwo.hpp"
#include "triple_call_test/StageThree.hpp"

/***
 *
 */
TEST (TripleCallConsumerData, AddThreeConsumers)
{
	offcenter::distributedsystem::ConsumerDataManager rcManager;
	offcenter::common::WaitForMessage waitForMessage;

	StageOneCLConfig stageOneCLConfig;
	StageOneCommandHandler::Ptr stageOneCommandHandler = StageOneCommandHandler::factory();
	rcManager.addCommandListener<StageOneCommandListener, StageOneCLConfig, IStageOneCommandHandler>(stageOneCLConfig, stageOneCommandHandler);

	StageTwoCLConfig stageTwoCLConfig;
	StageTwoCommandHandler::Ptr stageTwoCommandHandler = StageTwoCommandHandler::factory();
	rcManager.addCommandListener<StageTwoCommandListener, StageTwoCLConfig, IStageTwoCommandHandler>(stageTwoCLConfig, stageTwoCommandHandler);

	StageThreeCLConfig stageThreeCLConfig;
	StageThreeCommandHandler::Ptr stageThreeCommandHandler = StageThreeCommandHandler::factory();
	rcManager.addCommandListener<StageThreeCommandListener, StageThreeCLConfig, IStageThreeCommandHandler>(stageThreeCLConfig, stageThreeCommandHandler);

	//waitForMessage.waitForMessage();
}


