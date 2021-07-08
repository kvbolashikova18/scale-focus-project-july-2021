#include <iostream> 
#include <nanodbc.h> 
#include <exception> 
#include <string>
#include <vector>
using namespace std;

// defining colors used for output design
#define RESET   "\033[0m"
#define RED     "\033[1;91m" 
#define YELLOW  "\033[1;93m"  
#define GREEN   "\033[1;92m"
#define BLUE    "\033[0;36m"
#define CYAN    "\033[1;96m"
#define PURPLE  "\033[1;95m"
#define GRAY    "\033[1;90m" 
#define WHITE   "\033[4;37m"

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
	string dateOfCreation;
	int idOfCreator;
	string dateOfLastChange;
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


// reads input and prints an error until the user enters an integer
int cinInt()
{
	int number;

	while (!(cin >> number)) {

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << endl;
		cout << RED << "You have to enter a number. Please, try again: " << RESET;
	}

	return number;
}

// function that asks the user if they want to return to the main menu
bool returnBack()
{
	int choice;

	cout << endl;
	cout << "What would you like to do now?" << endl << endl;
	cout << GREEN << "1)" << RESET << " Stay in this menu" << endl;
	cout << GRAY << "2)" << RESET << " Go back to the main menu" << endl << endl;
	cout << "Enter your choice: ";

	choice = cinInt();

	while (choice > 2 or choice < 1)
	{
		cout << endl;
		cout << RED << "The number you enter has to be either 1 or 2! Please, try again: " RESET;
		choice = cinInt();
	}

	cout << endl;

	system("cls");

	if (choice == 1)
		return true;

	return false;
}



int main()
{
	try {
		nanodbc::string connstr = NANODBC_TEXT("DRIVER={ODBC Driver 17 for SQL Server};SERVER=(localdb)\\MSSQLLocaldb;DATABASE=Team Management;Trusted_Connection=yes;"); // an ODBC connection string to your database

		nanodbc::connection conn(connstr);

		auto result = nanodbc::execute(conn, NANODBC_TEXT(R"( SELECT TOP 3 * FROM [Team Management].dbo.Users )"));

		while (result.next()) {
		 int id = result.get<int>("Id"); 
	     string username = result.get<nanodbc::string>("Username");
		 string password = result.get<nanodbc::string>("Password");
		 string firstName = result.get<nanodbc::string>("First Name");
		 string lastName = result.get<nanodbc::string>("Last Name");
		 string dateOfCreation = result.get<nanodbc::string>("Date of creation");
		 //int idOfCreator = result.get<int>("Id of creator");
		 string dateOfLastChange = result.get<nanodbc::string>("Date of last change");
		 //int idOfChanger = result.get<int>("Id of changer");

		 cout << id << ", " << username << ", "<< password << ", " << firstName << ", " << lastName << ", " << dateOfCreation << ", " << dateOfLastChange << endl;
		} 
		
		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}