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
 * @file   ProcessAmqpMessageThread.hpp
 * @author Scott Brauer
 * @date   10-16-2021
 */

#ifndef OFFCENTER_AMQP_THREADING_PROCESSAMQPMESSAGETHREAD_HPP_
#define OFFCENTER_AMQP_THREADING_PROCESSAMQPMESSAGETHREAD_HPP_

#include <mutex>

#include "easylogging++.h"

#include "offcenter/amqp/Helper.hpp"
#include "offcenter/amqp/Listener.hpp"
#include "offcenter/common/threading/RunningThreadBlockable.hpp"

namespace offcenter {
namespace amqp {
namespace threading {

/**
 *
 */
template <typename Data, typename DataType>
class ProcessAmqpMessageThread:
		public offcenter::common::threading::RunningThreadBlockable
{
public:
	using Data_Ptr = std::shared_ptr<Data>;

public:
	ProcessAmqpMessageThread() = delete;
	explicit ProcessAmqpMessageThread(offcenter::amqp::SessionPtr session, const std::string& topic):
		m_destination(session->createQueue(topic)),
		m_consumer(offcenter::amqp::helper::messageConsumerFactory(session->createConsumer(m_destination.get()))),
		m_listener(m_consumer, [&](const cms::Message *cmsMessage, const Data& data) {
			{
				std::lock_guard<std::mutex> l(m_protectData);
				m_data = data;
			}
			this->onNewData();
		})
	{

	}

	virtual ~ProcessAmqpMessageThread() {
		LOG(DEBUG) << "ProcessAmqpMessageThread:~ProcessAmqpMessageThread";
		//m_consumer->close();
	}

protected:
	/**
	 * Event when setData has been called.
	 */
	virtual void onNewData() = 0;

	/**
	 * Access data.
	 *
	 * Thread safe access
	 */
	const Data data() {
		std::lock_guard<std::mutex> l(m_protectData);
		return m_data;
	}

	const Data_Ptr dataPtr() {
		return std::make_shared<Data>(data());
	}

	void stopping() override {
		LOG(DEBUG) << "Stopping ProcessAmqpMessageThread";
//		m_consumer->close();
		m_consumer.reset();
		RunningThreadBlockable::stopping();
		LOG(DEBUG) << "Stopped ProcessAmqpMessageThread";
	}

private:
	offcenter::amqp::DestinationPtr m_destination;
	offcenter::amqp::MessageConsumerPtr m_consumer;
	offcenter::amqp::Listener<Data, DataType> m_listener;

	Data m_data;
	std::mutex m_protectData;
};

} /* namespace threading */
} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_THREADING_PROCESSAMQPMESSAGETHREAD_HPP_ */
