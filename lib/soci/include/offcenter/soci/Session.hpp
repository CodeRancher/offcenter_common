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
 * @file   Session.hpp
 * @author Scott Brauer
 * @date   03-19-2021
 */
#ifndef OFFCENTER_SOCI_SESSION_HPP_
#define OFFCENTER_SOCI_SESSION_HPP_

#include "soci/soci.h"

#include "offcenter/soci/MySQLOptions.hpp"

namespace offcenter {
namespace soci {

std::string parseTableName(const std::string &schema);

/**
 *
 */
class SessionPoolManager
{
public:
	const static int g_verboseLevel = 5;

public:
	SessionPoolManager() = delete;
	explicit SessionPoolManager(const size_t poolSize = 10, bool createDBIfNotExist = false);
	explicit SessionPoolManager(const MySQLOptions& options, const size_t poolSize = 10, bool createDBIfNotExist = false);
	virtual ~SessionPoolManager();

	void open(const MySQLOptions& options, bool createDBIfNotExist = false);
	void close();
	void createDB(const MySQLOptions &options);
	void dropDB(const MySQLOptions &options);

	::soci::connection_pool& connectionPool() { return m_connectionPool; }
	const ::soci::backend_factory& backendFactory() { return m_options.backendFactory(); }
	const std::string connectionString() { return m_options.getConnectionString(); }


private:
	MySQLOptions m_options;
	const size_t m_poolSize;
	bool m_createDBIfNotExist;
	::soci::connection_pool m_connectionPool;

};

/**
 *
 */
class Session
{
public:
	Session() = delete;
	explicit Session(SessionPoolManager& sessionPoolManager);
	virtual ~Session() = default;

	bool isOpen() { return session().is_connected(); }
	::soci::session& sql() { return session(); }
	::soci::session& operator()() { return session(); }

	template<typename T>
	::soci::details::once_temp_type operator<<(T const & t) { return sql() << t; }

protected:
	::soci::session& session() { return m_session; }

private:
	::soci::session m_session;
};

/**
 *
 */
class SessionActions : public Session
{
public:
	SessionActions() = delete;
	explicit SessionActions(SessionPoolManager& sessionPoolManager);
	virtual ~SessionActions() = default;

	void createTable(const std::string& tableSchema);
	void createAndPopulateTable(const std::string& tableSchema, const std::string& tableData);
	void createView(const std::string& viewSchema);
};

} /* namespace soci */
} /* namespace offcenter */

#endif /* OFFCENTER_SOCI_SESSION_HPP_ */
