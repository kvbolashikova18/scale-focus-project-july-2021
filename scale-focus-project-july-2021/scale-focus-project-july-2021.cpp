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

enum class status
{
	pending,
	inProgress,
	completed
};

struct USER
{
	int id = 0;
	string username = "";
	string password = "";
	string firstName = "";
	string lastName = "";
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateOfLastChange = "";
	int idOfChanger = 0;
	bool isAdmin = 0;
};

struct TEAM
{
	int id = 0;
	string title = "";
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateOfLastChange = "";
	int idOfChanger = 0;
};

struct PROJECT
{
	int id = 0;
	string title = "";
	string description = "";
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateOfLastChange = "";
	int idOfChanger = 0;
};

struct TASK
{
	int id = 0;
	int idOfProject = 0;
	int idOfAssignee = 0;
	string title = "";
	string description = "";
	status status = status::pending;
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateOfLastChange = "";
	int idOfChanger = 0;
};

struct LOG
{
	int id = 0;
	int idOfTask = 0;
	int idOfUser = 0;
	int time = 0;
	string date = "";
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


void displayUser(USER* users, int index)
{
	cout << GRAY << "ID: " << RESET << users[index].id << endl;
	cout << "Username: " << users[index].username << endl;
	cout << "Password: " << users[index].password << endl;
	cout << "First name: " << users[index].firstName << endl;
	cout << "Last name: " << users[index].lastName << endl;
	cout << "Date of creation: " << users[index].dateOfCreation << endl;
	cout << "ID of creator: " << users[index].idOfCreator << endl;
	cout << "Date of last change: " << users[index].dateOfLastChange << endl;
	cout << "ID of last changer: " << users[index].idOfChanger << endl;
}

void displayTeam(TEAM* teams, int index)
{
	cout << GRAY << "ID: " << RESET << teams[index].id << endl;
	cout << "Title: " << teams[index].title << endl;
	cout << "Date of creation: " << teams[index].dateOfCreation << endl;
	cout << "ID of creator: " << teams[index].idOfCreator << endl;
	cout << "Date of last change: " << teams[index].dateOfLastChange << endl;
	cout << "ID of last changer: " << teams[index].idOfChanger << endl;
}

void displayProject(PROJECT* projects, int index)
{
	cout << GRAY << "ID: " << RESET << projects[index].id << endl;
	cout << "Title: " << projects[index].title << endl;
	cout << "Description: " << projects[index].description << endl;
	cout << "Date of creation: " << projects[index].dateOfCreation << endl;
	cout << "ID of creator: " << projects[index].idOfCreator << endl;
	cout << "Date of last change: " << projects[index].dateOfLastChange << endl;
	cout << "ID of last changer: " << projects[index].idOfChanger << endl;
}

void displayTask(TASK* tasks, int index)
{
	cout << GRAY << "ID: " << RESET << tasks[index].id << endl;
	cout << "ID of project: " << tasks[index].idOfProject << endl;
	cout << "ID of assignee: " << tasks[index].idOfAssignee << endl;
	cout << "Title: " << tasks[index].title << endl;
	cout << "Description: " << tasks[index].description << endl;
	if (tasks[index].status == status::pending)
		cout << "Status: pending" << endl;
	else if (tasks[index].status == status::inProgress)
		cout << "Status: in progress" << endl;
	else
		cout << "Status: completed" << endl;
	cout << "Date of creation: " << tasks[index].dateOfCreation << endl;
	cout << "ID of creator: " << tasks[index].idOfCreator << endl;
	cout << "Date of last change: " << tasks[index].dateOfLastChange << endl;
	cout << "ID of last changer: " << tasks[index].idOfChanger << endl;
}

void displayLog(LOG* logs, int index)
{
	cout << GRAY << "ID: " << RESET << logs[index].id << endl;
	cout << "ID of task: " << logs[index].idOfTask << endl;
	cout << "ID of user: " << logs[index].idOfUser << endl;
	cout << "Time spent (hours): " << logs[index].time << endl;
	cout << "Date: " << logs[index].date << endl;
}


void getUserFromDatabase(nanodbc::connection conn, USER* users, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    SELECT *
    FROM [Team Management].dbo.Users
    )"));

	auto result = execute(statement);

	while (result.next()) {
		users[index].id = result.get<int>("Id");
		users[index].username = result.get<nanodbc::string>("Username");
		users[index].password = result.get<nanodbc::string>("Password");
		users[index].firstName = result.get<nanodbc::string>("First Name");
		users[index].lastName = result.get<nanodbc::string>("Last Name");
		users[index].dateOfCreation = result.get<nanodbc::string>("Date of creation");
		//users[index].idOfCreator = result.get<int>("Id of creator");
		users[index].dateOfLastChange = result.get<nanodbc::string>("Date of last change");
		//users[index].idOfChanger = result.get<int>("Id of changer");
	}

	index++;
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
	USER* users = new USER[100];
	TEAM* teams = new TEAM[20];
	PROJECT* projects = new PROJECT[20];
	TASK* tasks = new TASK[20];
	LOG* logs = new LOG[100];

	int userIndex = 0, teamIndex = 0, projectIndex = 0, taskIndex = 0, logIndex = 0;

	

	try {
		nanodbc::string connstr = NANODBC_TEXT("DRIVER={ODBC Driver 17 for SQL Server};SERVER=(localdb)\\MSSQLLocaldb;DATABASE=Team Management;Trusted_Connection=yes;"); // an ODBC connection string to your database

		nanodbc::connection conn(connstr);

		//auto result = nanodbc::execute(conn, NANODBC_TEXT(R"( SELECT TOP 3 * FROM [Team Management].dbo.Users )"));


		getUserFromDatabase(conn, users, userIndex);
		displayUser(users, 0);

		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	
}