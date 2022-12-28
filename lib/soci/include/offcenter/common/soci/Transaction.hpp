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
 * @file   Transaction.hpp
 * @author Scott Brauer
 * @date   06-08-2021
 */

#ifndef OFFCENTER_SOCI_TRANSACTION_HPP_
#define OFFCENTER_SOCI_TRANSACTION_HPP_

#include "soci/soci.h"

#include "offcenter/common/soci/Session.hpp"

namespace offcenter {
namespace common {
namespace soci {

/**
 *
 */
class Transaction
{
public:
	explicit Transaction(::soci::session& session);
	explicit Transaction(::soci::session session);
	explicit Transaction(offcenter::common::soci::Session& session);
	virtual ~Transaction();

	void setError(bool value);

private:
	bool m_error;
	::soci::transaction m_transaction;
};

} /* namespace soci */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_SOCI_TRANSACTION_HPP_ */
