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
 * @file   SimpleConsumerDataFixture.hpp
 * @author Scott Brauer
 * @date   03-28-2020
 */

#ifndef LIB_DISTRIBUTED_SYSTEM_TEST_SRC_SIMPLECONSUMERDATAFIXTURE_HPP_
#define LIB_DISTRIBUTED_SYSTEM_TEST_SRC_SIMPLECONSUMERDATAFIXTURE_HPP_

#include <gtest/gtest.h>

class SimpleConsumerDataFixture : public ::testing::Test
{
public:
	SimpleConsumerDataFixture();
	virtual ~SimpleConsumerDataFixture();

protected:
	void SetUp() override{

	}

	void TearDown() override {}

	static void SetUpTestCase(){

	}

	static void TearDownTestCase(){

	}

};

#endif /* LIB_DISTRIBUTED_SYSTEM_TEST_SRC_SIMPLECONSUMERDATAFIXTURE_HPP_ */
