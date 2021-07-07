#include <iostream> 
#include <nanodbc.h> 
#include <exception> 
using namespace std;



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