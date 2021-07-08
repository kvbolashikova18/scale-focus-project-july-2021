#include <iostream> 
#include <nanodbc.h> 
#include <exception> 
#include <string>
using namespace std;

enum status
{
	pending,
	inProgress,
	completed
};

struct USER
{
	int id;
	string username;
	string password;
	string firstName;
	string lastName;
	//date dateOfCreation;
	int idOfCreator;
	//date dateOfLastChange;
	int idOfChanger;
	bool isAdmin;
};

struct TEAM
{
	int id;
	string title;
	//date dateOfCreation;
	int idOfCreator;
	//date dateOfLastChange;
	int idOfChanger;
};

struct PROJECT
{
	int id;
	string title;
	string description;
	//date dateOfCreation;
	int idOfCreator;
	//date dateOfLastChange;
	int idOfChanger;
};

struct TASK
{
	int id;
	int idOfProject;
	int idOfAssignee;
	string title;
	string description;
	status status;
	//date dateOfCreation;
	int idOfCreator;
	//date dateOfLastChange;
	int idOfChanger;
};

struct LOG
{
	int id;
	int idOfTask;
	int idOfUser;
	int time;
	//date date;
};

int main()
{
	try {
		auto const connstr = NANODBC_TEXT("DRIVER={ODBC Driver 17 for SQL Server};SERVER=(localdb)\\MSSQLLocaldb;DATABASE=BikeStores;Trusted_Connection=yes;"); // an ODBC connection string to your database nanodbc::connection conn(connstr);

		nanodbc::connection conn(connstr);

		auto result = nanodbc::execute(conn, NANODBC_TEXT(R"( SELECT TOP 2 * FROM BikeStores.sales.customers )"));

		while (result.next()) {
			auto i = result.get<int>(0); auto firstName = result.get<nanodbc::string>(1, "NULL FIELD");

			cout << i << ", " << firstName << endl;
		} return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl; return EXIT_FAILURE;
	}
}