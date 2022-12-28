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
 * @file   AMQPApp.hpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#ifndef LIB_FRAMEWORK_SRC_AMQPAPP_HPP_
#define LIB_FRAMEWORK_SRC_AMQPAPP_HPP_

#include "offcenter/common/framework/application/BasicApp.hpp"
#include "offcenter/common/framework/application/AMQPAppConfig.hpp"

#include "offcenter/common/ScopeGuard.hpp"
#include "offcenter/common/amqp/Helper.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace application {

class AMQPApp: public BasicApp
{
private:
	AMQPAppConfig m_amqpConfig;

	ScopeGuard m_scopeGuard;
	offcenter::common::amqp::ConnectionPtr m_connection;
	offcenter::common::amqp::SessionPtr m_session;


public:
	AMQPApp();
	virtual ~AMQPApp();

	void start();

protected:
	const AMQPAppConfig& amqpConfig() const { return m_amqpConfig; }

};

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* LIB_FRAMEWORK_SRC_AMQPAPP_HPP_ */
