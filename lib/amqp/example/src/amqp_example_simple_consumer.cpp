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
 * @file   amqp_example_simple_consumer.cpp
 * @author Scott Brauer
 * @date   11-21-2020
 */

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
	START_EASYLOGGINGPP(argc, argv);
	LOG(TRACE) << "amqp_example_simple_consumer";
}
