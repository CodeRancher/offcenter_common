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
 * @file   simple_consumerdata_test.cpp
 * @author Scott Brauer
 * @date   03-28-2020
 */

#include <memory>

#include <gtest/gtest.h>
#include "offcenter/distributedsystem/ConsumerDataListener.hpp"
#include "offcenter/distributedsystem/ConsumerDataManager.hpp"

#include "offcenter/amqp/Message.hpp"


/***
 *
 */
class DataElement : public offcenter::amqp::Message
{
public:
	DataElement() :
		intValue(0),
		stringValue(""),
		doubleValue(0.0) {}
	virtual ~DataElement() = default;

	int intValue;
	std::string stringValue;
	double doubleValue;

	void readFromMessage(const cms::Message *message) override {
		assert(message != nullptr);
		intValue = message->getIntProperty("intValue");
		stringValue = message->getStringProperty("stringValue");
		doubleValue = message->getDoubleProperty("doubleValue");
	}

	void writeToMessage(cms::Message *message) const override {
		assert(message != nullptr);
		message->setIntProperty("intValue", intValue);
		message->setStringProperty("stringValue", stringValue);
		message->setDoubleProperty("doubleValue", doubleValue);
	}
};

/***
 *
 */
class ICommandHandler
{
public:
	//using Ptr = std::shared_ptr<ICommandHandler>;
public:
	explicit ICommandHandler() = default;
};

/***
 *
 */
class CLConfig
{
public:
	explicit CLConfig() {}
};

/**
 *
 */
class CommandHandler : public ICommandHandler
{
public:
	using Ptr = std::shared_ptr<ICommandHandler>;
	static Ptr factory() {
		return std::make_shared<CommandHandler>();
	}

public:
	explicit CommandHandler() {}
};

/**
 *
 */
class CommandListener : public offcenter::distributedsystem::ConsumerDataListener<ICommandHandler>
{
public:
	explicit CommandListener(CLConfig const& clConfig, std::shared_ptr<ICommandHandler> handler):
		offcenter::distributedsystem::ConsumerDataListener<ICommandHandler>(handler)
	{

	}
};

/***
 *
 */
TEST (SimpleConsumerData, AddSingleConsumer)
{
	offcenter::distributedsystem::ConsumerDataManager rcManager;

	CLConfig clConfig;
	CommandHandler::Ptr commandHandler = CommandHandler::factory();

	rcManager.addCommandListener<CommandListener, CLConfig, ICommandHandler>(clConfig, commandHandler);
}


