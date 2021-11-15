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
 * @file   AmqpDataElement.hpp
 * @author Scott Brauer
 * @date   04-20-2021
 */

#ifndef AMQPDATAELEMENT_HPP_
#define AMQPDATAELEMENT_HPP_

#include <string>

#include <cms/MapMessage.h>

/**
 *
 */
struct AmqpDataElementInner
{
	std::string name;
	std::string description;
	int date;
	float value;

	using MessageType = cms::MapMessage;
};

void to_cmsMessage(AmqpDataElementInner::MessageType* j, const AmqpDataElementInner& p);
void from_cmsMessage(const AmqpDataElementInner::MessageType* j, AmqpDataElementInner& p);

/**
 *
 */
struct AmqpDataElementOuter
{
	std::string name;
	std::string description;
	int date;
	float value;
	int dateSquare;
	float valueSquare;

	using MessageType = cms::MapMessage;

	void operator=(const AmqpDataElementInner& inner) {
		name = inner.name + ":Outer";
		description = inner.description;
		date = inner.date;
		value = inner.value;
		dateSquare = date * date;
		valueSquare = value * value;
	}
};

void to_cmsMessage(AmqpDataElementOuter::MessageType* j, const AmqpDataElementOuter& p);
void from_cmsMessage(const AmqpDataElementOuter::MessageType* j, AmqpDataElementOuter& p);

#endif /* AMQPDATAELEMENT_HPP_ */
