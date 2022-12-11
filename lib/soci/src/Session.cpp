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
 * @file   Session.cpp
 * @author Scott Brauer
 * @date   03-19-2021
 */

#include <regex>

#include "easylogging++.h"

#include "offcenter/common/soci/Session.hpp"
#include "offcenter/common/soci/SOCIRuntimeException.hpp"

namespace offcenter {
namespace soci {

//*****************************************************************************
//*** Namespace Functions
//*****************************************************************************

/**
 * Parse a table name from DB Schema
 * The table name will be parsed from a 'CREATE TABLE' or 'INSERT INTO' db schema.
 * @param schema db schema that contains the table name
 */
std::string parseTableName(const std::string &schema)
{
	std::smatch results;
	std::regex pattern ("(CREATE TABLE|INSERT INTO|CREATE VIEW)\\s+([^\\s]*)");
	LOG(INFO) << "Schema: " << schema;
	if (std::regex_search(schema, results, pattern)) {
		LOG(INFO) << "Found: ";
		for (std::string res : results) {
			LOG(INFO) << "Results: " << res;
		}
		return results[2];
	}
	throw SOCIRuntimeException("Unable to parse table name: " + schema);
}

/**
 * Create a session pool manager to oversee connections to the database
 *
 * @param poolSize Number of connections to create to the database
 * @param createDBIfNotExist Create the database if it doesn't exist
 */
SessionPoolManager::SessionPoolManager(const size_t poolSize, bool createDBIfNotExist):
		m_options(),
		m_poolSize(poolSize),
		m_createDBIfNotExist(createDBIfNotExist),
		m_connectionPool(poolSize)
{
}

/**
 * Create a session pool manager to oversee connections to the database
 *
 * @param poolSize Number of connections to create to the database
 * @param createDBIfNotExist Create the database if it doesn't exist
 */
SessionPoolManager::~SessionPoolManager()
{
	close();
}

/**
 * Create a session pool manager to oversee connections to the database
 *
 * @param options Connection options to the database
 * @param poolSize Number of connections to create to the database
 * @param createDBIfNotExist Create the database if it doesn't exist
 */
SessionPoolManager::SessionPoolManager(const MySQLOptions &options, const size_t poolSize, bool createDBIfNotExist):
		m_options(),
		m_poolSize(poolSize),
		m_createDBIfNotExist(createDBIfNotExist),
		m_connectionPool(poolSize)
{
	open(options);
}

/**
 * Open the connections to the database
 *
 * @param options Connection options to the database
 */
void SessionPoolManager::open(const MySQLOptions &options, bool createDBIfNotExist)
{
	m_options = options;

	LOG(INFO) << "Connecting MariaDB Pool: connections(" << m_poolSize << ") " << options.loggableConnectionString();

	for (int i = 0; i < m_poolSize; i++ ) {
		LOG(INFO) << "Connecting MariaDB: connection(" << i << ")";

		if (i == 0 && m_createDBIfNotExist) {
			try {
				m_connectionPool.at(i).open(m_options.backendFactory(), m_options.getConnectionString());
			} catch(::soci::mysql_soci_error& e) {
				if (e.err_num_ == 1049) {
					LOG(INFO) << "Error (" << e.err_num_ << ":" << e.what();
					createDB(m_options);
					m_connectionPool.at(i).open(m_options.backendFactory(), m_options.getConnectionString());
				} else {
					throw;
				}
			}
		} else {
			m_connectionPool.at(i).open(m_options.backendFactory(), m_options.getConnectionString());
		}

	}
}

/**
 * Close the connections to the database
 */
void SessionPoolManager::close()
{
	for (int i = 0; i < m_poolSize; i++ ) {
		LOG(INFO) << "Closing connection " << i << " to MariaDB";
		m_connectionPool.at(i).close();
	}
}

/**
 * Create the database
 *
 * @param options Connection and database name to create
 */
void SessionPoolManager::createDB(const MySQLOptions &options)
{
	LOG(INFO) << "Creating database (" << options.dbname() << ") on (" << options.host() << ")";
	offcenter::soci::MySQLOptions tmpConfig = options;
	tmpConfig.dbname.clear();

	// Open and create db
	::soci::session session;
	try {
		session.open(tmpConfig.backendFactory(), tmpConfig.getConnectionString());
		session.once << "CREATE DATABASE " << options.dbname() << ";";
		session.close();
		LOG(INFO) << "Database (" << options.dbname() << ") on (" << options.host() << ") successfully created";
	} catch(::soci::mysql_soci_error& e) {
		// Catch mysql_soci_error to display error number
		LOG(ERROR) << "Error(" << e.err_num_ << ") creating database (" << options.dbname() << ") on (" << options.host() << "). " << e.what();
		if (session.is_connected()) {
			session.close();
		}
		throw;
	} catch(const std::exception& e) {
		LOG(ERROR) << "Error creating database (" << options.dbname() << ") on (" << options.host() << "). " << e.what();
		if (session.is_connected()) {
			session.close();
		}
		throw;
	} catch(...) {
		LOG(ERROR) << "Unknown error creating database (" << options.dbname() << ") on (" << options.host() << ")";
		if (session.is_connected()) {
			session.close();
		}
		throw;
	}
}

/**
 * Drop the database
 *
 * @param options Connection and database name to drop
 */
void SessionPoolManager::dropDB(const MySQLOptions &options)
{
	LOG(INFO) << "Dropping database (" << options.dbname() << ") on (" << options.host() << ")";

	// Close existing connections
	close();

	// Open and drop db
	::soci::session session;
	try {
		session.open(options.backendFactory(), options.getConnectionString());
		session.once << "DROP DATABASE IF EXISTS " << options.dbname() << ";";
		session.close();
		LOG(INFO) << "Database (" << options.dbname() << ") on (" << options.host() << ") successfully dropped";
	} catch(::soci::mysql_soci_error& e) {
		// Catch mysql_soci_error to display error number
		LOG(ERROR) << "Error(" << e.err_num_ << ") dropping database (" << options.dbname() << ") on (" << options.host() << "). " << e.what();
		if (session.is_connected()) {
			session.close();
		}
		throw;
	} catch(const std::exception& e) {
		LOG(ERROR) << "Error dropping database (" << options.dbname() << ") on (" << options.host() << "). " << e.what();
		if (session.is_connected()) {
			session.close();
		}
		throw;
	} catch(...) {
		LOG(ERROR) << "Unknown error dropping database (" << options.dbname() << ") on (" << options.host() << ")";
		if (session.is_connected()) {
			session.close();
		}
		throw;
	}
}

/**
 * Create a session by using a connection from the session pool
 *
 * @param sessionPoolManager Session pool manager
 */
Session::Session(SessionPoolManager& sessionPoolManager):
		m_session(sessionPoolManager.connectionPool())
{
}

/**
 * Create as session with actions
 *
 * @param sessionPoolManager Session pool manager
 */
SessionActions::SessionActions(SessionPoolManager& sessionPoolManager):
		Session(sessionPoolManager)
{
}

/**
 * Create a database table
 *
 * @param tableSchema Schema for table creation
 */
void SessionActions::createTable(const std::string &tableSchema)
{
	std::string tableName = parseTableName(tableSchema);

	LOG(INFO) << "Create Table: " << tableName;
	VLOG(SessionPoolManager::g_verboseLevel) << "Execute Schema: " << tableSchema;

	try {
		session().once << tableSchema;
	} catch(const ::soci::mysql_soci_error& e) {
		LOG(ERROR) << "Error (" << e.err_num_ << ") creating table (" << tableName << "): " << e.what();
		throw;
	}
}

/**
 * Create and populate a database table
 *
 * @param tableSchema Schema for table creation
 * @param tableData Schema for table population
 */
void SessionActions::createAndPopulateTable(const std::string &tableSchema, const std::string &tableData)
{
	createTable(tableSchema);

	std::string tableName = parseTableName(tableSchema);

	LOG(INFO) << "Populate Table: " << tableName;
	VLOG(SessionPoolManager::g_verboseLevel) << "Execute Schema: " << tableData;

	try {
		session().once << tableData;
	} catch(const ::soci::mysql_soci_error& e) {
		LOG(ERROR) << "Error (" << e.err_num_ << ") populating table (" << tableName << "): " << e.what();
		throw;
	}
}

/**
 * Create a database view
 *
 * @param viewSchema Schemd for view creation
 */
void SessionActions::createView(const std::string &viewSchema)
{
	std::string viewName = parseTableName(viewSchema);

	LOG(INFO) << "Create View: " << viewName;
	VLOG(SessionPoolManager::g_verboseLevel) << "Execute Schema: " << viewSchema;

	try {
		session().once << viewSchema;
	} catch(const ::soci::mysql_soci_error& e) {
		LOG(ERROR) << "Error (" << e.err_num_ << ") creating view (" << viewName << "): " << e.what();
		throw;
	}
}

} /* namespace soci */
} /* namespace offcenter */
