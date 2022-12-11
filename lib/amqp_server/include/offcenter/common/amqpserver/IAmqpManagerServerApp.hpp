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
 * @file   IAmqpManagerServerApp.hpp
 * @author Scott Brauer
 * @date   04-27-2021
 */

#ifndef OffcenterCommon_AMQPSERVER_IAMQPMANAGERSERVERAPP_HPP_
#define OffcenterCommon_AMQPSERVER_IAMQPMANAGERSERVERAPP_HPP_

namespace offcenter {
namespace common {
namespace amqpserver {

/**
 *
 */
class IAmqpManagerServerApp
{
public:
	virtual ~IAmqpManagerServerApp() = default;



	virtual void onInitAMQP(amqp::ConnectionURIOptions& options) = 0;
	virtual void onInitAMQPSessions(amqp::ConnectionPtr connection) = 0;
};

} /* namespace amqpserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_AMQPSERVER_IAMQPMANAGERSERVERAPP_HPP_ */
