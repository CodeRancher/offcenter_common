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
 * @file   ILocalSystemStatusActions.hpp
 * @author Scott Brauer
 * @date   03-16-2019
 */

#ifndef OFFCENTER_DISTRIBUTEDSYSTEM_LOCAL_ILOCALSYSTEMSTATUSACTIONS_HPP_
#define OFFCENTER_DISTRIBUTEDSYSTEM_LOCAL_ILOCALSYSTEMSTATUSACTIONS_HPP_

namespace offcenter {
namespace common {
namespace distributedsystem {
namespace local {

class ILocalSystemStatusActions
{
public:
	ILocalSystemStatusActions();
	virtual ~ILocalSystemStatusActions();
};

} /* namespace local */
} /* namespace distributedsystem */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_DISTRIBUTEDSYSTEM_LOCAL_ILOCALSYSTEMSTATUSACTIONS_HPP_ */
