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
 * @file   soci_create_simple_db.cpp
 * @author Scott Brauer
 * @date   03-19-2021
 */

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/framework/application/IApp.hpp"
#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/framework/application/ManagedAppConfig.hpp"
#include "offcenter/common/framework/application/Utility.hpp"
#include "offcenter/common/soci/MySQLProgramOptions.hpp"
#include "offcenter/common/soci/Session.hpp"
using namespace offcenter::common;

std::tm stringToTime(const std::string& date) {
	struct std::tm tm;
	std::istringstream ss(date + " 00:00:00");
	ss >> std::get_time(&tm, "%m/%d/%Y %H:%M:%S");
	return tm;
}

//*****************************************************************************
// Agents
//*****************************************************************************
const std::string g_agentsCreateSQL = R"###(
	CREATE TABLE AGENTS (	
		AGENT_CODE CHAR(6) NOT NULL PRIMARY KEY, 
		AGENT_NAME CHAR(40), 
		WORKING_AREA CHAR(35), 
		COMMISSION DECIMAL(10,2), 
		PHONE_NO CHAR(15), 
		COUNTRY VARCHAR(25) 
	);
)###";

const std::string g_agentsInsertSQL = R"###(
	INSERT INTO
		AGENTS(AGENT_CODE, AGENT_NAME, WORKING_AREA, COMMISSION, PHONE_NO, COUNTRY)
		VALUES(:AGENT_CODE, :AGENT_NAME, :WORKING_AREA, :COMMISSION, :PHONE_NO, :COUNTRY)
)###";

struct AgentData {
	std::string agentCode;
	std::string agentName;
	std::string workingArea;
	double commission;
	std::string phoneNo;
	std::string country;

	friend std::ostream & operator << (std::ostream& out, const AgentData& c);
};

std::ostream & operator << (std::ostream& out, const AgentData& c)
{
	out << c.agentCode << ", " << c.agentName << ", " << c.workingArea << ", " << c.commission << ", " << c.phoneNo << ", " << c.country;
	return out;
}

namespace soci
{
    template<>
    struct type_conversion<::AgentData>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, ::AgentData & p)
        {
            p.agentCode = v.get<std::string>("AGENT_CODE");
            p.agentName = v.get<std::string>("AGENT_NAME");
            p.workingArea = v.get<std::string>("WORKING_AREA");
            p.commission = v.get<double>("COMMISSION");
            p.phoneNo = v.get<std::string>("PHONE_NO");
            p.country = v.get<std::string>("COUNTRY");
        }

        static void to_base(::AgentData const & p, values & v, indicator & ind)
        {
            v.set("AGENT_CODE", p.agentCode);
            v.set("AGENT_NAME", p.agentName);
            v.set("WORKING_AREA", p.workingArea);
            v.set("COMMISSION", p.commission);
            v.set("PHONE_NO", p.phoneNo);
            v.set("COUNTRY", p.country);
            ind = i_ok;
        }
    };
}

static const std::vector<AgentData> g_agentData {
	{"A007", "Ramasundar",	"Bangalore",	0.15, "077-25814763", ""},
	{"A003", "Alex ",		"London",		0.13, "075-12458969", ""},
	{"A008", "Alford",		"New York",		0.12, "044-25874365", ""},
	{"A011", "Ravi Kumar",	"Bangalore",	0.15, "077-45625874", ""},
	{"A010", "Santakumar",	"Chennai",		0.14, "007-22388644", ""},
	{"A012", "Lucida",		"San Jose",		0.12, "044-52981425", ""},
	{"A005", "Anderson",	"Brisban",		0.13, "045-21447739", ""},
	{"A001", "Subbarao",	"Bangalore",	0.14, "077-12346674", ""},
	{"A002", "Mukesh",		"Mumbai",		0.11, "029-12358964", ""},
	{"A006", "McDen",		"London",		0.15, "078-22255588", ""},
	{"A004", "Ivan",		"Torento",		0.15, "008-22544166", ""},
	{"A009", "Benjamin",	"Hampshair",	0.11, "008-22536178", ""}
};

//*****************************************************************************
// Customer
//*****************************************************************************
const std::string g_customerCreateSQL = R"###(
	CREATE TABLE CUSTOMER (
		CUST_CODE VARCHAR(6) NOT NULL PRIMARY KEY, 
		CUST_NAME VARCHAR(40) NOT NULL, 
		CUST_CITY CHAR(35), 
		WORKING_AREA VARCHAR(35) NOT NULL, 
		CUST_COUNTRY VARCHAR(20) NOT NULL, 
		GRADE DECIMAL, 
		OPENING_AMT DECIMAL(12,2) NOT NULL, 
		RECEIVE_AMT DECIMAL(12,2) NOT NULL, 
		PAYMENT_AMT DECIMAL(12,2) NOT NULL, 
		OUTSTANDING_AMT DECIMAL(12,2) NOT NULL, 
		PHONE_NO VARCHAR(17) NOT NULL, 
		AGENT_CODE CHAR(6) NOT NULL REFERENCES AGENTS
	);   
)###";

const std::string g_customerInsertSQL = R"###(
	INSERT INTO
		CUSTOMER(CUST_CODE, CUST_NAME, CUST_CITY, WORKING_AREA, CUST_COUNTRY, GRADE, OPENING_AMT, RECEIVE_AMT, PAYMENT_AMT, OUTSTANDING_AMT, PHONE_NO, AGENT_CODE)
		VALUES(:CUST_CODE, :CUST_NAME, :CUST_CITY, :WORKING_AREA, :CUST_COUNTRY, :GRADE, :OPENING_AMT, :RECEIVE_AMT, :PAYMENT_AMT, :OUTSTANDING_AMT, :PHONE_NO, :AGENT_CODE)
)###";

struct CustomerData {
	std::string custCode;
	std::string custName;
	std::string custCity;
	std::string workingArea;
	std::string custCountry;
	double grade;
	double openingAmt;
	double receiveAmt;
	double paymentAmt;
	double outstandingAmt;
	std::string phoneNo;
	std::string agentCode;

	friend std::ostream & operator << (std::ostream& out, const CustomerData& c);
};

std::ostream & operator << (std::ostream& out, const CustomerData& c)
{
	out << c.agentCode << ", " << c.custCode << ", " << c.custName << ", " << c.custCity << ", " << c.workingArea << ", " << c.custCountry << ", "
			<< c.grade << ", " << c.openingAmt << ", " << c.receiveAmt << ", " << c.paymentAmt << ", " << c.outstandingAmt << ", " << c.phoneNo << ", " << c.agentCode;
	return out;
}

namespace soci
{
    template<>
    struct type_conversion<::CustomerData>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, ::CustomerData & p)
        {
			p.custCode = v.get<std::string>("CUST_CODE");
			p.custName = v.get<std::string>("CUST_NAME");
			p.custCity = v.get<std::string>("CUST_CITY");
			p.workingArea = v.get<std::string>("WORKING_AREA");
			p.custCountry = v.get<std::string>("CUST_COUNTRY");
			p.grade = v.get<double>("GRADE");
			p.openingAmt = v.get<double>("OPENING_AMT");
			p.receiveAmt = v.get<double>("RECEIVE_AMT");
			p.paymentAmt = v.get<double>("PAYMENT_AMT");
			p.outstandingAmt = v.get<double>("OUTSTANDING_AMT");
			p.phoneNo = v.get<std::string>("PHONE_NO");
			p.agentCode = v.get<std::string>("AGENT_CODE");
        }

        static void to_base(::CustomerData const & p, values & v, indicator & ind)
        {
        	v.set("CUST_CODE", p.custCode);
        	v.set("CUST_NAME", p.custName);
        	v.set("CUST_CITY", p.custCity);
        	v.set("WORKING_AREA", p.workingArea);
        	v.set("CUST_COUNTRY", p.custCountry);
        	v.set("GRADE", p.grade);
        	v.set("OPENING_AMT", p.openingAmt);
        	v.set("RECEIVE_AMT", p.receiveAmt);
        	v.set("PAYMENT_AMT", p.paymentAmt);
        	v.set("OUTSTANDING_AMT", p.outstandingAmt);
        	v.set("PHONE_NO", p.phoneNo);
        	v.set("AGENT_CODE", p.agentCode);
            ind = i_ok;
        }
    };
}

static const std::vector<CustomerData> g_customerData {
		{"C00013", "Holmes",		"London",		"London",		"UK",			2, 6000.00,  5000.00,  7000.00, 4000.00,  "BBBBBBB",		"A003"},
		{"C00001", "Micheal",		"New York",		"New York",		"USA",			2, 3000.00,  5000.00,  2000.00, 6000.00,  "CCCCCCC",		"A008"},
		{"C00020", "Albert",		"New York",		"New York",		"USA",			3, 5000.00,  7000.00,  6000.00, 6000.00,  "BBBBSBB",		"A008"},
		{"C00025", "Ravindran",		"Bangalore",	"Bangalore",	"India",		2, 5000.00,  7000.00,  4000.00, 8000.00,  "AVAVAVA",		"A011"},
		{"C00024", "Cook",			"London",		"London",		"UK",			2, 4000.00,  9000.00,  7000.00, 6000.00,  "FSDDSDF",		"A006"},
		{"C00015", "Stuart",		"London",		"London",		"UK",			1, 6000.00,  8000.00,  3000.00, 11000.00, "GFSGERS",		"A003"},
		{"C00002", "Bolt",			"New York",		"New York",		"USA",			3, 5000.00,  7000.00,  9000.00, 3000.00,  "DDNRDRH",		"A008"},
		{"C00018", "Fleming",		"Brisban",		"Brisban",		"Australia",	2, 7000.00,  7000.00,  9000.00, 5000.00,  "NHBGVFC",		"A005"},
		{"C00021", "Jacks",			"Brisban",		"Brisban",		"Australia",	1, 7000.00,  7000.00,  7000.00, 7000.00,  "WERTGDF",		"A005"},
		{"C00019", "Yearannaidu",	"Chennai",		"Chennai",		"India",		1, 8000.00,  7000.00,  7000.00, 8000.00,  "ZZZZBFV",		"A010"},
		{"C00005", "Sasikant",		"Mumbai",		"Mumbai",		"India",		1, 7000.00,  11000.00, 7000.00, 11000.00, "147-25896312",	"A002"},
		{"C00007", "Ramanathan",	"Chennai",		"Chennai",		"India",		1, 7000.00,  11000.00, 9000.00, 9000.00,  "GHRDWSD",		"A010"},
		{"C00022", "Avinash",		"Mumbai",		"Mumbai",		"India",		2, 7000.00,  11000.00, 9000.00, 9000.00,  "113-12345678",	"A002"},
		{"C00004", "Winston",		"Brisban",		"Brisban",		"Australia",	1, 5000.00,  8000.00,  7000.00, 6000.00,  "AAAAAAA",		"A005"},
		{"C00023", "Karl",			"London",		"London",		"UK",			0, 4000.00,  6000.00,  7000.00, 3000.00,  "AAAABAA",		"A006"},
		{"C00006", "Shilton",		"Torento",		"Torento",		"Canada",		1, 10000.00, 7000.00,  6000.00, 11000.00, "DDDDDDD",		"A004"},
		{"C00010", "Charles",		"Hampshair",	"Hampshair",	"UK",			3, 6000.00,  4000.00,  5000.00, 5000.00,  "MMMMMMM",		"A009"},
		{"C00017", "Srinivas",		"Bangalore",	"Bangalore",	"India",		2, 8000.00,  4000.00,  3000.00, 9000.00,  "AAAAAAB",		"A007"},
		{"C00012", "Steven",		"San Jose",		"San Jose",		"USA",			1, 5000.00,  7000.00,  9000.00, 3000.00,  "KRFYGJK",		"A012"},
		{"C00008", "Karolina",		"Torento",		"Torento",		"Canada",		1, 7000.00,  7000.00,  9000.00, 5000.00,  "HJKORED",		"A004"},
		{"C00003", "Martin",		"Torento",		"Torento",		"Canada",		2, 8000.00,  7000.00,  7000.00, 8000.00,  "MJYURFD",		"A004"},
		{"C00009", "Ramesh",		"Mumbai",		"Mumbai",		"India",		3, 8000.00,  7000.00,  3000.00, 12000.00, "Phone No",		"A002"},
		{"C00014", "Rangarappa",	"Bangalore",	"Bangalore",	"India",		2, 8000.00,  11000.00, 7000.00, 12000.00, "AAAATGF",		"A001"},
		{"C00016", "Venkatpati",	"Bangalore",	"Bangalore",	"India",		2, 8000.00,  11000.00, 7000.00, 12000.00, "JRTVFDD",		"A007"},
		{"C00011", "Sundariya",		"Chennai",		"Chennai",		"India",		3, 7000.00,  11000.00, 7000.00, 11000.00, "PPHGRTS",		"A010"}
};

//*****************************************************************************
// Orders
//*****************************************************************************
const std::string g_ordersCreateSQL = R"###(
	CREATE TABLE ORDERS (
		ORD_NUM DECIMAL(6,0) NOT NULL PRIMARY KEY, 
		ORD_AMOUNT DECIMAL(12,2) NOT NULL, 
		ADVANCE_AMOUNT DECIMAL(12,2) NOT NULL, 
		ORD_DATE DATE NOT NULL, 
		CUST_CODE VARCHAR(6) NOT NULL REFERENCES CUSTOMER, 
		AGENT_CODE CHAR(6) NOT NULL REFERENCES AGENTS, 
		ORD_DESCRIPTION VARCHAR(60) NOT NULL
	);
)###";

const std::string g_ordersInsertSQL = R"###(
	INSERT INTO
		ORDERS(ORD_NUM, ORD_AMOUNT, ADVANCE_AMOUNT, ORD_DATE, CUST_CODE, AGENT_CODE, ORD_DESCRIPTION)
		VALUES(:ORD_NUM, :ORD_AMOUNT, :ADVANCE_AMOUNT, :ORD_DATE, :CUST_CODE, :AGENT_CODE, :ORD_DESCRIPTION)
)###";

struct OrderData {
	double ordNum;
	double ordAmount;
	double advanceAmount;
	std::tm ordDate;
	std::string custCode;
	std::string agentCode;
	std::string ordDescription;

	friend std::ostream & operator << (std::ostream& out, const OrderData& c);
};

std::ostream & operator << (std::ostream& out, const OrderData& c)
{
	char buffer[100];
	std::strftime(buffer, sizeof(buffer),"%d/%m/%Y", &(c.ordDate));
	out << c.ordNum << ", " << c.ordAmount << ", " << c.advanceAmount << ", " << buffer << ", " << c.custCode << ", " << c.agentCode << ", "
			<< c.ordDescription;
	return out;
}

namespace soci
{
    template<>
    struct type_conversion<::OrderData>
    {
        typedef values base_type;

        static void from_base(values const & v, indicator /* ind */, ::OrderData & p)
        {
			p.ordNum = v.get<double>("ORD_NUM");
			p.ordAmount = v.get<double>("ORD_AMOUNT");
			p.advanceAmount = v.get<double>("ADVANCE_AMOUNT");
			p.ordDate = v.get<std::tm>("ORD_DATE");
			p.custCode = v.get<std::string>("CUST_CODE");
			p.agentCode = v.get<std::string>("AGENT_CODE");
			p.ordDescription = v.get<std::string>("ORD_DESCRIPTION");
        }

        static void to_base(::OrderData const & p, values & v, indicator & ind)
        {
        	v.set("ORD_NUM", p.ordNum);
        	v.set("ORD_AMOUNT", p.ordAmount);
        	v.set("ADVANCE_AMOUNT", p.advanceAmount);
        	v.set("ORD_DATE", p.ordDate);
        	v.set("CUST_CODE", p.custCode);
        	v.set("AGENT_CODE", p.agentCode);
        	v.set("ORD_DESCRIPTION", p.ordDescription);
            ind = i_ok;
        }
    };
}

static const std::vector<OrderData> g_orderData {
	{200100, 1000.00, 600.00,  stringToTime("08/01/2008"), "C00013", "A003", "SOD"},
	{200110, 3000.00, 500.00,  stringToTime("04/15/2008"), "C00019", "A010", "SOD"},
	{200107, 4500.00, 900.00,  stringToTime("08/30/2008"), "C00007", "A010", "SOD"},
	{200112, 2000.00, 400.00,  stringToTime("05/30/2008"), "C00016", "A007", "SOD"},
	{200113, 4000.00, 600.00,  stringToTime("06/10/2008"), "C00022", "A002", "SOD"},
	{200102, 2000.00, 300.00,  stringToTime("05/25/2008"), "C00012", "A012", "SOD"},
	{200114, 3500.00, 2000.00, stringToTime("08/15/2008"), "C00002", "A008", "SOD"},
	{200122, 2500.00, 400.00,  stringToTime("09/16/2008"), "C00003", "A004", "SOD"},
	{200118, 500.00,  100.00,  stringToTime("07/20/2008"), "C00023", "A006", "SOD"},
	{200119, 4000.00, 700.00,  stringToTime("09/16/2008"), "C00007", "A010", "SOD"},
	{200121, 1500.00, 600.00,  stringToTime("09/23/2008"), "C00008", "A004", "SOD"},
	{200130, 2500.00, 400.00,  stringToTime("07/30/2008"), "C00025", "A011", "SOD"},
	{200134, 4200.00, 1800.00, stringToTime("09/25/2008"), "C00004", "A005", "SOD"},
	{200108, 4000.00, 600.00,  stringToTime("02/15/2008"), "C00008", "A004", "SOD"},
	{200103, 1500.00, 700.00,  stringToTime("05/15/2008"), "C00021", "A005", "SOD"},
	{200105, 2500.00, 500.00,  stringToTime("07/18/2008"), "C00025", "A011", "SOD"},
	{200109, 3500.00, 800.00,  stringToTime("07/30/2008"), "C00011", "A010", "SOD"},
	{200101, 3000.00, 1000.00, stringToTime("07/15/2008"), "C00001", "A008", "SOD"},
	{200111, 1000.00, 300.00,  stringToTime("07/10/2008"), "C00020", "A008", "SOD"},
	{200104, 1500.00, 500.00,  stringToTime("03/13/2008"), "C00006", "A004", "SOD"},
	{200106, 2500.00, 700.00,  stringToTime("04/20/2008"), "C00005", "A002", "SOD"},
	{200125, 2000.00, 600.00,  stringToTime("10/10/2008"), "C00018", "A005", "SOD"},
	{200117, 800.00,  200.00,  stringToTime("10/20/2008"), "C00014", "A001", "SOD"},
	{200123, 500.00,  100.00,  stringToTime("09/16/2008"), "C00022", "A002", "SOD"},
	{200120, 500.00,  100.00,  stringToTime("07/20/2008"), "C00009", "A002", "SOD"},
	{200116, 500.00,  100.00,  stringToTime("07/13/2008"), "C00010", "A009", "SOD"},
	{200124, 500.00,  100.00,  stringToTime("06/20/2008"), "C00017", "A007", "SOD"},
	{200126, 500.00,  100.00,  stringToTime("06/24/2008"), "C00022", "A002", "SOD"},
	{200129, 2500.00, 500.00,  stringToTime("07/20/2008"), "C00024", "A006", "SOD"},
	{200127, 2500.00, 400.00,  stringToTime("07/20/2008"), "C00015", "A003", "SOD"},
	{200128, 3500.00, 1500.00, stringToTime("07/20/2008"), "C00009", "A002", "SOD"},
	{200135, 2000.00, 800.00,  stringToTime("09/16/2008"), "C00007", "A010", "SOD"},
	{200131, 900.00,  150.00,  stringToTime("08/26/2008"), "C00012", "A012", "SOD"},
	{200133, 1200.00, 400.00,  stringToTime("06/29/2008"), "C00009", "A002", "SOD"}
};



//*****************************************************************************
class SOCICreateSimpleDBApp: public framework::application::IApp {
public:
	const static int g_sessionPoolSize = 4;

public:

	SOCICreateSimpleDBApp():
		IApp(),
		m_sessionPoolManager(g_sessionPoolSize, true)
	{
	}

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) {
		m_mysqlConfig = optionsManager.add<offcenter::soci::MySQLProgramOptions>();
	}

	void onSetUp() override {
	}

	void onExecute() override {
		std::cout << "OnExecute" << std::endl;

		// Use a session to create a database
		{
			std::cout << "Creating a session to database: '" << m_mysqlConfig->dbname() << "'" << std::endl;

			// If the command line doesn't contain a database name, add one
			if (m_mysqlConfig->dbname().empty()) {
				m_mysqlConfig->dbname = "soci_create_simple_db_test";
			}

			std::cout << "Dropping database: '" << m_mysqlConfig->dbname() << "'" << std::endl;
			m_sessionPoolManager.dropDB(*m_mysqlConfig);

			std::cout << "Creating database: ;" << m_mysqlConfig->dbname() << "'" << std::endl;
			m_sessionPoolManager.createDB(*m_mysqlConfig);
		}

		std::cout << "Creating a session to database: '" << m_mysqlConfig->dbname() << "'" << std::endl;
		m_sessionPoolManager.open(*m_mysqlConfig);

		// Create and initialize data
		initData("AGENTS", g_agentData, g_agentsCreateSQL, g_agentsInsertSQL);
		initData("CUSTOMER", g_customerData, g_customerCreateSQL, g_customerInsertSQL);
		initData("ORDERS", g_orderData, g_ordersCreateSQL, g_ordersInsertSQL);

		// Query #1
		{
			offcenter::soci::Session session(m_sessionPoolManager);
			AgentData agentData;
			::soci::statement agentDataST = (session().prepare << "SELECT * FROM AGENTS ORDER BY AGENT_NAME", ::soci::into(agentData));
			agentDataST.execute();
			while (agentDataST.fetch()) {
				std::cout << agentData << std::endl;

				CustomerData customerData;
				::soci::statement customerDataST = (session().prepare << "SELECT * FROM CUSTOMER WHERE AGENT_CODE = :AGENT_CODE ORDER BY CUST_NAME", ::soci::into(customerData), ::soci::use(agentData.agentCode));
				customerDataST.execute();
				while (customerDataST.fetch()) {
					std::cout << "\t" << customerData << std::endl;

					OrderData orderData;
					::soci::statement orderDataST = (session().prepare << "SELECT * FROM ORDERS WHERE CUST_CODE = :CUST_CODE ORDER BY ORD_DATE", ::soci::into(orderData), ::soci::use(customerData.custCode));
					orderDataST.execute();
					while (orderDataST.fetch()) {
						std::cout << "\t\t" << orderData << std::endl;
					}
				}
			}
		}

		std::cout << "Dropping database: '" << m_mysqlConfig->dbname() << "'" << std::endl;
		m_sessionPoolManager.dropDB(*m_mysqlConfig);
	}

	void onTearDown() override {

	}

	void onHelp(const std::string& help) override {
		std::cout << help << std::endl;
	}

	void onVersion() override {
		std::cout << "Version: " << std::endl;
	}

private:
	offcenter::soci::MySQLProgramOptions::ConfigPtr m_mysqlConfig;
	offcenter::soci::SessionPoolManager m_sessionPoolManager;

	template <class D>
	void initData(const std::string& table, const std::vector<D>& dataSet, const std::string& createTable, const std::string& insertData)
	{
		offcenter::soci::Session session(m_sessionPoolManager);

		std::cout << "Create table: '" << table << "'" << std::endl;
		session().once << createTable;

		std::cout << "Populate table: '" << table << "' ";
		D insertRecord;
		::soci::statement st = (session().prepare << insertData, ::soci::use(insertRecord));
		for (D currentRecord : dataSet) {
			insertRecord = currentRecord;
			st.execute(true);
			std::cout << ".";
		}
		std::cout << std::endl;
	}
};

//*****************************************************************************
int main(int argc, char **argv) {
	START_EASYLOGGINGPP(argc, argv);

	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");

	LOG(INFO) << "Starting basic app thread";

	using App = framework::application::AppManager<SOCICreateSimpleDBApp>;

	std::thread appThread = framework::application::create_basic_app_in_thread<App>(argc, argv);
	appThread.join();

}
