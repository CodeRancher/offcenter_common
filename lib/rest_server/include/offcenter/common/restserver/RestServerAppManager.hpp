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
 * @file   RestServerAppManager.hpp
 * @author Scott Brauer
 * @date   04-09-2021
 */

#ifndef OFFCENTER_COMMON_RESTSERVER_RESTSERVERAPPMANAGER_HPP_
#define OFFCENTER_COMMON_RESTSERVER_RESTSERVERAPPMANAGER_HPP_

#include <boost/bind/bind.hpp>

#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>

#include "easylogging++.h"

#include "offcenter/common/InterruptHandler.hpp"
#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/restserver/IRestServerApp.hpp"
#include "offcenter/common/restserver/network/Utility.hpp"
#include "offcenter/common/restserver/AutoMethodHandler.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace common {
namespace restserver {

/**
 *
 */
template <class IRESTSERVERAPP>
class RestServerAppManager:
		public framework::application::AppManager<IRESTSERVERAPP>
{
public:
	explicit RestServerAppManager():
		framework::application::AppManager<IRESTSERVERAPP>()
	{}
	virtual ~RestServerAppManager() = default;

	void onSetUp() override {
		framework::application::AppManager<IRESTSERVERAPP>::m_app.onSetUp();

		// Set the listener uri
		web::uri uri;
		framework::application::AppManager<IRESTSERVERAPP>::m_app.onInitEndpoint(uri);

		web::uri_builder endpointBuilder;

        endpointBuilder.set_scheme(uri.scheme());
        if (uri.host() == "host_auto_ip4") {
            endpointBuilder.set_host(network::hostIP4());
        }
        else if (uri.host() == "host_auto_ip6") {
            endpointBuilder.set_host(network::hostIP6());
        }
        endpointBuilder.set_port(uri.port());
        endpointBuilder.set_path(uri.path());

        LOG(INFO) << "Listener uri: " << endpointBuilder.to_string();
		m_listener = web::http::experimental::listener::http_listener(endpointBuilder.to_uri());

		framework::application::AppManager<IRESTSERVERAPP>::m_app.onInitMethodHandlers(m_methodHandler);
	}

	void onExecute() override {
		initRestOpHandlers();
		beginListen().wait();
		offcenter::common::interrupthandler::waitForUserInterrupt();
		endListen().wait();
	}

private:
	void unhandledRequest(web::http::http_request& message);
    void initRestOpHandlers() {
    	m_listener.support(boost::bind(&RestServerAppManager::handleAll, this, boost::placeholders::_1));
    }

	void handleAll(web::http::http_request request) {
		switch(m_methodHandler.findAndExecute(request)) {
			case 0:
				LOG(ERROR) << "Handle Request: " << request.method() << ":" << web::uri::uri::decode(request.relative_uri().path()) << " - Not Found";
				request.reply(web::http::status_codes::NotFound, request.method() + " Not Found");
				break;
			case 1:
				// Do nothing
				break;
			default:
				LOG(ERROR) << "Handle Request: " << request.method() << ":" << web::uri::uri::decode(request.relative_uri().path()) << " - Too many paths ";
				request.reply(web::http::status_codes::InternalError, request.method() + " Too many paths");
		}
	}

	pplx::task<void> beginListen() {
		initRestOpHandlers();
		return m_listener.open();
	}

	pplx::task<void> endListen() {
		return m_listener.close();
	}

protected:
	web::http::experimental::listener::http_listener m_listener; // main micro service network endpoint

private:
	AutoMethodHandler m_methodHandler;

};

} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_RESTSERVER_RESTSERVERAPPMANAGER_HPP_ */
