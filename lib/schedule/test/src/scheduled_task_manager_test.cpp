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
 * @file   scheduled_task_manager_test.cpp
 * @author Scott Brauer
 * @date   02-03-2019
 */

#include <gtest/gtest.h>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "offcenter/common/schedule/ScheduledTaskManager.hpp"

void test_func(int& i) {
	std::cout << "test_func: " << i << std::endl;
    i = 1;
    offcenter::common::schedule::ScheduledTaskManager::instance().stop();
}

void test_func1() {
	std::cout << "test_func1" << std::endl;
     //throw std::logic_error("It works!");
}

TEST (TopicProducerFixture, SimpleRunAt)
{
    const int seconds_to_wait = 3;
    int i = 0;

    offcenter::common::schedule::ScheduledTaskManager::Ptr taskManager =
    		offcenter::common::schedule::ScheduledTaskManager::createInstance();

    taskManager->runAfter(
    		boost::posix_time::seconds(seconds_to_wait),
			boost::bind(&test_func, boost::ref(i))
    );

    taskManager->runAt(
    		boost::posix_time::from_time_t(time(NULL) + 1),
			&test_func1);

    int t1 = static_cast<int>(time(NULL));
    EXPECT_EQ(i, 0);

	std::cout << "Before start" << std::endl;
	taskManager->start();
	std::cout << "After start" << std::endl;

	EXPECT_EQ(i, 1);
    int t2 = static_cast<int>(time(NULL));
    EXPECT_TRUE(t2 - t1 >= seconds_to_wait) << t2 << "-" << t1 << " must be >= " << seconds_to_wait;

    taskManager->reset();
}

void run_three_times_then_stop(int& i, offcenter::common::schedule::ScheduledTaskManager::Ptr task) {
	std::cout << "run_three_times_then_stop: " << i << std::endl;
    if (++i == 3) {
    	offcenter::common::schedule::ScheduledTaskManager::instance().stop();
    }
}

TEST (TopicProducerFixture, DISABLED_RunThreeTimes)
{
    const int seconds_to_wait = 1;
    int i = 0;

    offcenter::common::schedule::ScheduledTaskManager::Ptr taskManager =
    		offcenter::common::schedule::ScheduledTaskManager::createInstance();

    taskManager->runAfter(
    		boost::posix_time::seconds(seconds_to_wait),
			boost::bind(&run_three_times_then_stop, boost::ref(i), taskManager)
    );

    int t1 = static_cast<int>(time(NULL));
    EXPECT_EQ(i, 0);

    taskManager->start();
    EXPECT_EQ(i, 3);
    int t2 = static_cast<int>(time(NULL));
    EXPECT_TRUE(t2 - t1 >= seconds_to_wait * 3) << t2 << "-" << t1 << " must be >= " << seconds_to_wait * 3;

    taskManager->reset();
}

