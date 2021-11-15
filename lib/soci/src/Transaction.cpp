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
 * @file   Transaction.cpp
 * @author Scott Brauer
 * @date   06-08-2021
 */
#include "offcenter/soci/Transaction.hpp"

namespace offcenter {
namespace soci {

Transaction::Transaction(::soci::session& session):
		m_error(false),
		m_transaction(session)
{
	// TODO Auto-generated constructor stub

}

Transaction::Transaction(::soci::session session):
		m_error(false),
		m_transaction(session)
{
	// TODO Auto-generated constructor stub

}

Transaction::Transaction(offcenter::soci::Session& session):
		m_error(false),
		m_transaction(session.sql())
{
	// TODO Auto-generated constructor stub

}

Transaction::~Transaction()
{
	if (m_error) {
		m_transaction.rollback();
	} else {
		m_transaction.commit();
	}
}

void Transaction::setError(bool value)
{
		m_error = value;
}

} /* namespace soci */
} /* namespace offcenter */
