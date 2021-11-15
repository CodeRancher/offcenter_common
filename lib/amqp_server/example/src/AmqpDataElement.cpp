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
 * @file   AmqpDataElement.cpp
 * @author Scott Brauer
 * @date   04-20-2021
 */
#include "AmqpDataElement.hpp"

void to_cmsMessage(AmqpDataElementInner::MessageType* j, const AmqpDataElementInner& p)
{
	j->setString("name", p.name);
	j->setString("description", p.description);
	j->setInt("date", p.date);
	j->setFloat("value", p.value);
}

void from_cmsMessage(const AmqpDataElementInner::MessageType* j, AmqpDataElementInner& p)
{
	p.name = j->getString("name");
	p.description = j->getString("description");
	p.date = j->getInt("date");
	p.value = j->getFloat("value");
}

void to_cmsMessage(AmqpDataElementOuter::MessageType* j, const AmqpDataElementOuter& p)
{
	j->setString("name", p.name);
	j->setString("description", p.description);
	j->setInt("date", p.date);
	j->setFloat("value", p.value);
	j->setInt("dateSquare", p.dateSquare);
	j->setFloat("valueSquare", p.valueSquare);
}

void from_cmsMessage(const AmqpDataElementOuter::MessageType* j, AmqpDataElementOuter& p)
{
	p.name = j->getString("name");
	p.description = j->getString("description");
	p.date = j->getInt("date");
	p.value = j->getFloat("value");
	p.dateSquare = j->getInt("dateSquare");
	p.valueSquare = j->getFloat("valueSquare");
}
