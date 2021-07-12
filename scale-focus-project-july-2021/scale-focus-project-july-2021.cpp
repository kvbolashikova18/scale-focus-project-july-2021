#include <iostream> 
#include <nanodbc.h> 
#include <exception> 
#include <string>
#include <vector>
#include <conio.h>
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

	cout << endl;
}

void displayTeam(TEAM* teams, int index)
{
	cout << GRAY << "ID: " << RESET << teams[index].id << endl;
	cout << "Title: " << teams[index].title << endl;
	cout << "Date of creation: " << teams[index].dateOfCreation << endl;
	cout << "ID of creator: " << teams[index].idOfCreator << endl;
	cout << "Date of last change: " << teams[index].dateOfLastChange << endl;
	cout << "ID of last changer: " << teams[index].idOfChanger << endl;

	cout << endl;
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

	cout << endl;
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

	cout << endl;
}

void displayLog(LOG* logs, int index)
{
	cout << GRAY << "ID: " << RESET << logs[index].id << endl;
	cout << "ID of task: " << logs[index].idOfTask << endl;
	cout << "ID of user: " << logs[index].idOfUser << endl;
	cout << "Time spent (hours): " << logs[index].time << endl;
	cout << "Date: " << logs[index].date << endl;

	cout << endl;
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

		index++;
	}
}

void getTeamFromDatabase(nanodbc::connection conn, TEAM* teams, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    SELECT * 
    FROM [Team Management].dbo.Teams
    )"));

	auto result = execute(statement);

	while (result.next()) {
		teams[index].id = result.get<int>("Id");
		teams[index].title = result.get<nanodbc::string>("Title");
		teams[index].dateOfCreation = result.get<nanodbc::string>("Date of creation");
		teams[index].idOfCreator = result.get<int>("Id of creator");
		teams[index].dateOfLastChange = result.get<nanodbc::string>("Date of last change");
		teams[index].idOfChanger = result.get<int>("Id of changer");

		index++;
	}
}

void getProjectFromDatabase(nanodbc::connection conn, PROJECT* projects, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    SELECT * 
    FROM [Team Management].dbo.Projects
    )"));

	auto result = execute(statement);

	while (result.next()) {
		projects[index].id = result.get<int>("Id");
		projects[index].title = result.get<nanodbc::string>("Title");
		projects[index].description = result.get<nanodbc::string>("Description");
		projects[index].dateOfCreation = result.get<nanodbc::string>("Date of creation");
		projects[index].idOfCreator = result.get<int>("Id of creator");
		projects[index].dateOfLastChange = result.get<nanodbc::string>("Date of last change");
		projects[index].idOfChanger = result.get<int>("Id of changer");

		index++;
	}
}

void getTaskFromDatabase(nanodbc::connection conn, TASK* tasks, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    SELECT * 
    FROM [Team Management].dbo.Tasks
    )"));

	auto result = execute(statement);

	while (result.next()) {
		tasks[index].id = result.get<int>("Id");
		tasks[index].idOfProject = result.get<int>("Id of Project");
		tasks[index].idOfAssignee = result.get<int>("Id of Assignee");
		tasks[index].title = result.get<nanodbc::string>("Title");
		tasks[index].description = result.get<nanodbc::string>("Description");
		//tasks[index].status = result.get<status>("Status");
		tasks[index].dateOfCreation = result.get<nanodbc::string>("Date of creation");
	    tasks[index].idOfCreator = result.get<int>("Id of creator");
		tasks[index].dateOfLastChange = result.get<nanodbc::string>("Date of last change");
		tasks[index].idOfChanger = result.get<int>("Id of changer");

		index++;
	}
}

void getLogFromDatabase(nanodbc::connection conn, LOG* logs, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    SELECT * 
    FROM [Team Management].dbo.Logs
    )"));

	auto result = execute(statement);

	while (result.next()) {
		logs[index].id = result.get<int>("Id");
		logs[index].idOfTask = result.get<int>("Id of Task");
		logs[index].idOfUser = result.get<int>("Id of User");
		logs[index].time = result.get<int>("Time");
		logs[index].date = result.get<nanodbc::string>("Date");

		index++;
	}
}


void editUser()
{

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

/*string enterHiddenText()
{
	string password = "";
	char symbol = ' ';

	while (symbol!='	')
	{
		symbol = _getch();
		if (symbol != '	')
		 cout << YELLOW << '*' << RESET;

		password += symbol;
	}
	cout << endl;
  
	return password;
}*/

void displayProjectsMenu(PROJECT* projects, int& projectIndex, nanodbc::connection conn)
{
	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		cout << "  _____           _           _       " << endl;
		cout << " |  __ \\         (_)         | |      " << endl;
		cout << " | |__) | __ ___  _  ___  ___| |_ ___ " << endl;
		cout << " |  ___/ '__/ _ \\| |/ _ \\/ __| __/ __|" << endl;
		cout << " | |   | | | (_) | |  __/ (__| |_\\__ \\" << endl;
		cout << " |_|   |_|  \\___/| |\\___|\\___|\\__|___/" << endl;
		cout << "                _/ |                  " << endl;
		cout << "               |__/                   " << endl << endl;
		cout << " =======================================" << endl;
		cout << "|" << " 1)" << YELLOW << " Show a list of all projects" << RESET << "        |" << endl;
		cout << "|" << " 2)" << GREEN << " Create a project" << RESET << "                   |" << endl;
		cout << "|" << " 3)" << CYAN << " Edit a project" << RESET << "                     |" << endl;
		cout << "|" << " 4)" << RED << " Delete a project" << RESET << "                   |" << endl;
		cout << "|" << " 5)" << PURPLE << " Assign a team to a project" << RESET << "         |" << endl;
		cout << "|" << " 6)" << GRAY << " Return back to the Main Menu" << RESET << "       |" << endl;
		cout << " =======================================" << endl << endl;

		cout << "Enter your choice: ";
		choice = cinInt();

		while (choice > 6 or choice < 1)
		{
			cout << endl;
			cout << RED << "The number you enter has to be between 1 and 6! Please, try again: " << RESET;
			choice = cinInt();
		}

		system("cls");

		switch (choice)
		{
		case 1:
			for (int i = 0; i < projectIndex; i++)
			{
				displayProject(projects, i);
			}
			cont = returnBack();
			break;
		case 2:
			//
			cont = returnBack();
			break;
		case 3:
			//
			cont = returnBack();
			break;
		case 4:
			//
			cont = returnBack();
			break;
		case 5:
			//
			cont = returnBack();
			break;
		case 6:
			cont = false;
			break;
		}
	}
}

void displayTeamsMenu(TEAM* teams, int& teamIndex, nanodbc::connection conn)
{
	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		cout << "  _______                       " << endl;
		cout << " |__   __|                      " << endl;
		cout << "    | | ___  __ _ _ __ ___  ___ " << endl;
		cout << "    | |/ _ \\/ _` | '_ ` _ \\/ __|" << endl;
		cout << "    | |  __/ (_| | | | | | \\__ \\" << endl;
		cout << "    |_|\\___|\\__,_|_| |_| |_|___/" << endl << endl;
		cout << " =======================================" << endl;
		cout << "|" << " 1)" << YELLOW << " Show a list of all teams" << RESET << "           |" << endl;
		cout << "|" << " 2)" << GREEN << " Create a team" << RESET << "                      |" << endl;
		cout << "|" << " 3)" << CYAN << " Edit a team" << RESET << "                        |" << endl;
		cout << "|" << " 4)" << RED << " Delete a team" << RESET << "                      |" << endl;
		cout << "|" << " 5)" << PURPLE << " Assign a user to a team" << RESET << "            |" << endl;
		cout << "|" << " 6)" << GRAY << " Return back to the Main Menu" << RESET << "       |" << endl;
		cout << " =======================================" << endl << endl;

		cout << "Enter your choice: ";
		choice = cinInt();

		while (choice > 6 or choice < 1)
		{
			cout << endl;
			cout << RED << "The number you enter has to be between 1 and 6! Please, try again: " << RESET;
			choice = cinInt();
		}

		system("cls");

		switch (choice)
		{
		case 1:
			for (int i = 0; i < teamIndex; i++)
			{
				displayTeam(teams, i);
			}
			cont = returnBack();
			break;
		case 2:
			//
			cont = returnBack();
			break;
		case 3:
			//
			cont = returnBack();
			break;
		case 4:
			//
			cont = returnBack();
			break;
		case 5:
			//
			cont = returnBack();
			break;
		case 6:
			cont = false;
			break;
		}
	}
}

void displayUsersMenu(USER* users, int& userIndex, nanodbc::connection conn)
{
	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		cout << "  _    _                   " << endl;
		cout << " | |  | |                  " << endl;
		cout << " | |  | |___  ___ _ __ ___ " << endl;
		cout << " | |  | / __|/ _ \\ '__/ __|" << endl;
		cout << " | |__| \\__ \\  __/ |  \\__ \\" << endl;
		cout << "  \\____/|___/\\___|_|  |___/" << endl << endl;
		cout << " =======================================" << endl;
		cout << "|" << " 1)" << YELLOW << " Show a list of all users" << RESET << "           |" << endl;
		cout << "|" << " 2)" << GREEN << " Create a user" << RESET << "                      |" << endl;
		cout << "|" << " 3)" << CYAN << " Edit a user" << RESET << "                        |" << endl;
		cout << "|" << " 4)" << RED << " Delete a user" << RESET << "                      |" << endl;
		cout << "|" << " 5)" << GRAY << " Return back to the Main Menu" << RESET << "       |" << endl;
		cout << " =======================================" << endl << endl;

		cout << "Enter your choice: ";
		choice = cinInt();

		while (choice > 5 or choice < 1)
		{
			cout << endl;
			cout << RED << "The number you enter has to be between 1 and 5! Please, try again: " << RESET;
			choice = cinInt();
		}

		system("cls");

		switch (choice)
		{
		case 1:
			for (int i = 0; i < userIndex; i++)
			{
				displayUser(users, i);
			}
			cont = returnBack();
			break;
		case 2:
		    //
			cont = returnBack();
			break;
		case 3:
			//
			cont = returnBack();
			break;
		case 4:
			//
			cont = returnBack();
			break;
		case 5:
			cont = false;
			break;
		}
	}
}

void displayMainMenu(USER* users, int& userIndex, TEAM* teams, int& teamIndex, PROJECT* projects, int& projectIndex, TASK* tasks, int& taskIndex, LOG* logs, int& logIndex, nanodbc::connection conn)
{
	int choice = 0;

	while (choice != 4)
	{
		cout << endl;

		cout << " __  __       _         __  __                      " << endl;
		cout << "|  \\/  |     (_)       |  \\/  |                   " << endl;
		cout << "| \\  / | __ _ _ _ __   | \\  / | ___ _ __  _   _   " << endl;
		cout << "| |\\/| |/ _` | | '_ \\  | |\\/| |/ _ \\ '_ \\| | | |" << endl;
		cout << "| |  | | (_| | | | | | | |  | |  __/ | | | |_| |    " << endl;
		cout << "|_|  |_|\\__,_|_|_| |_| |_|  |_|\\___|_| |_|\\__,_| " << endl;

		cout << endl;
		cout << endl;

		cout << "Which set of data would you like to work with?" << endl << endl;
		cout << " =====================" << endl;
		cout << "|" << " 1)" << YELLOW << " Users" << RESET << "            |" << endl;
		cout << "|" << " 2)" << GREEN << " Teams" << RESET << "            |" << endl;
		cout << "|" << " 3)" << CYAN << " Projects" << RESET << "         |" << endl;
		cout << "|" << " 4)" << GRAY << " Exit" << RESET << "             |" << endl;
		cout << " =====================" << endl;
		cout << endl;
		cout << "Enter your choice: ";
		choice = cinInt();

		while (choice > 4 or choice < 1)
		{
			cout << endl;
			cout << RED << "The number you enter has to be between 1 and 4! Please, try again: " << RESET;
			choice = cinInt();
		}

		system("cls");

		switch (choice)
		{
		case 1:
			displayUsersMenu(users, userIndex, conn);
			break;
		case 2:
			displayTeamsMenu(teams, teamIndex, conn);
			break;
		case 3:
			displayProjectsMenu(projects, projectIndex, conn);
			break;
		case 4:
			exit(0);
			break;
		}
	}

}

int main()
{
	USER* users = new USER[100];
	TEAM* teams = new TEAM[20];
	PROJECT* projects = new PROJECT[20];
	TASK* tasks = new TASK[20];
	LOG* logs = new LOG[100];

	int userIndex = 4, teamIndex = 3, projectIndex = 3, taskIndex = 2, logIndex = 2;
	USER currentUser;
	

	try {
		nanodbc::string connstr = NANODBC_TEXT("DRIVER={ODBC Driver 17 for SQL Server};SERVER=(localdb)\\MSSQLLocaldb;DATABASE=Team Management;Trusted_Connection=yes;"); // an ODBC connection string to your database

		nanodbc::connection conn(connstr);

		//auto result = nanodbc::execute(conn, NANODBC_TEXT(R"( SELECT TOP 3 * FROM [Team Management].dbo.Users )"));

		for (int i = 0; i < userIndex; i++)
		{
			getUserFromDatabase(conn, users, i);
		}

		for (int i = 0; i < teamIndex; i++)
		{
			getTeamFromDatabase(conn, teams, i);
		}

		for (int i = 0; i < projectIndex; i++)
		{
			getProjectFromDatabase(conn, projects, i);
		}

		for (int i = 0; i < taskIndex; i++)
		{
			getTaskFromDatabase(conn, tasks, i);
		}

		for (int i = 0; i < logIndex; i++)
		{
			getLogFromDatabase(conn, logs, i);
		}


		displayMainMenu(users, userIndex, teams, teamIndex, projects, projectIndex, tasks, taskIndex, logs, logIndex, conn);

		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

}