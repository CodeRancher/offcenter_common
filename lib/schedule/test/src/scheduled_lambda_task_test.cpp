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
 * @file   scheduled_lambda_task_test.hpp
 * @author Scott Brauer
 * @date   02-03-2019
 */

#include <gtest/gtest.h>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "offcenter/common/schedule/ScheduledTaskManager.hpp"
#include "offcenter/common/schedule/Common.hpp"

struct LambdaClass {
public:
	int i;
	const int m = 4;
};

TEST (TopicProducerFixture, BasicLambda)
{
    const int seconds_to_wait = 1;
    LambdaClass data;
    data.i = 0;

    auto recur = [&](const offcenter::common::schedule::TimeType& timer, LambdaClass &idata) -> offcenter::common::schedule::TimeType {
    	std::cout << "recur: before" << std::endl;
    	return timer + boost::posix_time::seconds(1);
    };

	auto pre = [&](LambdaClass &idata) -> bool {
    	std::cout << "pre(before) i(" << idata.i << ") m(" << idata.m << ")" << std::endl;
		return idata.i < idata.m;
	};

	auto action =[&](LambdaClass &idata) {
		std::cout << "action(before) i(" << idata.i << ")" << std::endl;
		idata.i++;
		std::cout << "action(after) i(" << idata.i << ")" << std::endl;
	};

	auto post =[&](LambdaClass &idata) -> bool {
    	std::cout << "post(before) i(" << idata.i << ") m(" << idata.m << ")" << std::endl;
		return idata.i < idata.m;
	};

    offcenter::common::schedule::ScheduledTaskManager::Ptr taskManager =
    		offcenter::common::schedule::ScheduledTaskManager::createInstance();

	std::cout << "Before runAfter" << std::endl;
	taskManager->runAfter(
    		boost::posix_time::seconds(seconds_to_wait),
			recur, pre, action, post, std::ref(data)
    );
	std::cout << "After runAfter" << std::endl;

    int t1 = static_cast<int>(time(NULL));
    EXPECT_EQ(data.i, 0);

	std::cout << "Before start" << std::endl;
	taskManager->start();
	std::cout << "After start" << std::endl;

    EXPECT_EQ(data.i, data.m);
    int t2 = static_cast<int>(time(NULL));
    const int waitedSeconds = seconds_to_wait * data.m;
    EXPECT_TRUE(t2 - t1 >= waitedSeconds) << t2 << "-" << t1 << " must be >= " << waitedSeconds;

    taskManager->reset();
}

