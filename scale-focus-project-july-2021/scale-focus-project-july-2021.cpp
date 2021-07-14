#include <iostream> 
#include <nanodbc.h> 
#include <exception> 
#include <string>
#include <vector>
#include <conio.h>
#include <ios>
#include <limits>
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
	bool isDeleted = 0;
};

struct TEAM
{
	int id = 0;
	string title = "";
	string dateOfCreation = "";
	int idOfCreator = 0;
	string dateOfLastChange = "";
	int idOfChanger = 0;
	bool isDeleted = 0;
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
	bool isDeleted = 0;
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
	bool isDeleted = 0;
};

struct LOG
{
	int id = 0;
	int idOfTask = 0;
	int idOfUser = 0;
	int time = 0;
	string date = "";
	bool isDeleted = 0;
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

string cinText()
{
	cin.ignore(0, '\n');
	string text;
	getline(cin, text);

	return text;
}


void displayUser(USER* users, int index)
{
	if (users[index].isDeleted == false)
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

	cout << endl;
}

void displayTeam(TEAM* teams, int index)
{
	if (teams[index].isDeleted == false)
	{
		cout << GRAY << "ID: " << RESET << teams[index].id << endl;
		cout << "Title: " << teams[index].title << endl;
		cout << "Date of creation: " << teams[index].dateOfCreation << endl;
		cout << "ID of creator: " << teams[index].idOfCreator << endl;
		cout << "Date of last change: " << teams[index].dateOfLastChange << endl;
		cout << "ID of last changer: " << teams[index].idOfChanger << endl;
	}

	cout << endl;
}

void displayProject(PROJECT* projects, int index)
{
	if (projects[index].isDeleted == false)
	{
		cout << GRAY << "ID: " << RESET << projects[index].id << endl;
		cout << "Title: " << projects[index].title << endl;
		cout << "Description: " << projects[index].description << endl;
		cout << "Date of creation: " << projects[index].dateOfCreation << endl;
		cout << "ID of creator: " << projects[index].idOfCreator << endl;
		cout << "Date of last change: " << projects[index].dateOfLastChange << endl;
		cout << "ID of last changer: " << projects[index].idOfChanger << endl;
	}

	cout << endl;
}

void displayTask(TASK* tasks, int index)
{
	if (tasks[index].isDeleted == false)
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

	cout << endl;
}

void displayLog(LOG* logs, int index)
{
	if (logs[index].isDeleted == false)
	{
		cout << GRAY << "ID: " << RESET << logs[index].id << endl;
		cout << "ID of task: " << logs[index].idOfTask << endl;
		cout << "ID of user: " << logs[index].idOfUser << endl;
		cout << "Time spent (hours): " << logs[index].time << endl;
		cout << "Date: " << logs[index].date << endl;
	}

	cout << endl;
}


void displayAllUsers(USER* users, int index)
{
	for (int i = 0; i < index; i++)
	{
		displayUser(users, i);
	}
}

void displayAllTeams(TEAM* teams, int index)
{
	for (int i = 0; i < index; i++)
	{
		displayTeam(teams, i);
	}
}

void displayAllProjects(PROJECT* projects, int index)
{
	for (int i = 0; i < index; i++)
	{
		displayProject(projects, i);
	}
}

void displayAllTasks(TASK* tasks, int index)
{
	for (int i = 0; i < index; i++)
	{
		displayTask(tasks, i);
	}
}

void displayAllLogs(LOG* logs, int index)
{
	for (int i = 0; i < index; i++)
	{
		displayLog(logs, i);
	}
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
		users[index].idOfCreator = result.get<int>("Id of creator");
		users[index].dateOfLastChange = result.get<nanodbc::string>("Date of last change");
		users[index].idOfChanger = result.get<int>("Id of changer");

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
		tasks[index].status = (status)result.get<int>("Status");
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


void insertUser(nanodbc::connection conn, USER* users, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Users
    (Username, [Password], [First Name], [Last Name], [Id of creator], [Id of changer], [isAdmin])
    VALUES
    (?, ?, ?, ?, ?, ?, ?)
    )"));

	cout << "Username: ";
	users[index].username = cinText();
	statement.bind(0, users[index].username.c_str());

	cout << "Password: ";
	users[index].password = cinText();
	statement.bind(1, users[index].password.c_str());

	cout << "First name: ";
	users[index].firstName = cinText();
	statement.bind(2, users[index].firstName.c_str());

	cout << "Last name: ";
	users[index].lastName = cinText();
	statement.bind(3, users[index].lastName.c_str());

	cout << "Id of creator: ";
	users[index].idOfCreator = cinInt();
	statement.bind(4, &users[index].idOfCreator);

	cout << "Id of last changer: ";
	users[index].idOfChanger = cinInt();
	statement.bind(5, &users[index].idOfChanger);

	int a = 0;
	statement.bind(6, &a);

	execute(statement);

	getUserFromDatabase(conn, users, index);

	cout << GREEN << "User has been successfully added" <<  RESET << endl;
}

void insertTeam(nanodbc::connection conn, TEAM* teams, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Teams
    (Title, [Id of creator], [Id of changer])
    VALUES
    (?, ?, ?)
    )"));

	cout << "Title: ";
	teams[index].title = cinText();
	statement.bind(0, teams[index].title.c_str());

	cout << "Id of creator: ";
	teams[index].idOfCreator = cinInt();
	statement.bind(1, &teams[index].idOfCreator);

	cout << "Id of last changer: ";
	teams[index].idOfChanger = cinInt();
	statement.bind(2, &teams[index].idOfChanger);

	execute(statement);

	getTeamFromDatabase(conn, teams, index);

	cout << GREEN << "Team has been successfully added" << RESET << endl;
}

void insertProject(nanodbc::connection conn, PROJECT* projects, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Projects
    (Title, Description, [Id of creator], [Id of changer])
    VALUES
    (?, ?, ?, ?)
    )"));

	cout << "Title: ";
	projects[index].title = cinText();
	statement.bind(0, projects[index].title.c_str());

	cout << "Description: ";
	projects[index].description = cinText();
	statement.bind(1, projects[index].description.c_str());

	cout << "Id of creator: ";
	projects[index].idOfCreator = cinInt();
	statement.bind(2, &projects[index].idOfCreator);

	cout << "Id of last changer: ";
	projects[index].idOfChanger = cinInt();
	statement.bind(3, &projects[index].idOfChanger);

	execute(statement);

	getProjectFromDatabase(conn, projects, index);

	cout << GREEN << "Project has been successfully added" << RESET << endl;
}

void insertTask(nanodbc::connection conn, TASK* tasks, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Tasks
    ([Id of Project], [Id of Assignee], Title, Description, Status, [Id of creator], [Id of changer])
    VALUES
    (?, ?, ?, ?, ?, ?, ?)
    )"));


	cout << "Title: ";
	tasks[index].title = cinText();
	statement.bind(2, tasks[index].title.c_str());

	cout << "Description: ";
	tasks[index].description = cinText();
	statement.bind(3, tasks[index].description.c_str());

	cout << "Id of project: ";
	tasks[index].idOfProject = cinInt();
	statement.bind(0, &tasks[index].idOfProject);

	cout << "Id of assignee: ";
	tasks[index].idOfAssignee = cinInt();
	statement.bind(1, &tasks[index].idOfAssignee);

	cout << "Status (0 - Pending / 1 - In progress / 2 - Completed): ";
	int status;
	status = cinInt();
	if (status == 0)
		tasks[index].status = status::pending;
	else if (status == 1)
		tasks[index].status = status::inProgress;
	else if (status == 2)
		tasks[index].status = status::completed;
	statement.bind(4, &status);

	cout << "Id of creator: ";
	tasks[index].idOfCreator = cinInt();
	statement.bind(5, &tasks[index].idOfCreator);

	cout << "Id of last changer: ";
	tasks[index].idOfChanger = cinInt();
	statement.bind(6, &tasks[index].idOfChanger);

	execute(statement);

	getTaskFromDatabase(conn, tasks, index);

	cout << GREEN << "Task has been successfully added" << RESET << endl;
}

void insertLog(nanodbc::connection conn, LOG* logs, int& index)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Logs
    ([Id of Task], [Id of User], Time)
    VALUES
    (?, ?, ?)
    )"));

	cout << "Id of Task: ";
	logs[index].idOfTask = cinInt();
	statement.bind(0, &logs[index].idOfTask);

	cout << "Id of User: ";
	logs[index].idOfUser = cinInt();
	statement.bind(1, &logs[index].idOfUser);

	cout << "Time spent (in hours): ";
	logs[index].time = cinInt();
	statement.bind(2, &logs[index].time);

	execute(statement);

	getLogFromDatabase(conn, logs, index);

	cout << GREEN << "Log has been successfully added" << RESET << endl;
}


void editUser(nanodbc::connection conn, USER* users, int& index)
{
	nanodbc::statement statement(conn);

	cout << "Enter the ID of the user you want to edit: ";
	int id = cinInt();

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (users[i].id == id)
		{
			position = i;
		}
	}

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Users
    SET
     Username = ?
    ,Password = ?
    ,[First Name] = ?
    ,[Last Name] = ?
    ,[Date of last change] = GETDATE()
    ,[Id of changer] = ?
     WHERE Id = ?;
    )"));

	cout << "New username: ";
	users[position].username = cinText();
	statement.bind(0, users[position].username.c_str());

	cout << "New password: ";
	users[position].password = cinText();
	statement.bind(1, users[position].password.c_str());

	cout << "New first name: ";
	users[position].firstName = cinText();
	statement.bind(2, users[position].firstName.c_str());

	cout << "New last name: ";
	users[position].lastName = cinText();
	statement.bind(3, users[position].lastName.c_str());

	cout << "Id of last changer: ";
	users[position].idOfChanger = cinInt();
	statement.bind(4, &users[position].idOfChanger);

	statement.bind(5, &id);

	execute(statement);

	cout << GREEN << "User has been successfully updated" << RESET << endl;
}

void editTeam(nanodbc::connection conn, TEAM* teams, int& index)
{
	nanodbc::statement statement(conn);

	cout << "Enter the ID of the team you want to edit: ";
	int id = cinInt();

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (teams[i].id == id)
		{
			position = i;
		}
	}

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Teams
    SET
     Title = ?
    ,[Date of last change] = GETDATE()
    ,[Id of changer] = ?
     WHERE Id = ?;
    )"));

	cout << "New title: ";
	teams[position].title = cinText();
	statement.bind(0, teams[position].title.c_str());

	cout << "Id of last changer: ";
	teams[position].idOfChanger = cinInt();
	statement.bind(1, &teams[position].idOfChanger);

	statement.bind(2, &id);

	execute(statement);

	cout << GREEN << "Team has been successfully updated" << RESET << endl;
}

void editProject(nanodbc::connection conn, PROJECT* projects, int& index)
{
	nanodbc::statement statement(conn);

	cout << "Enter the ID of the project you want to edit: ";
	int id = cinInt();

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (projects[i].id == id)
		{
			position = i;
		}
	}

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Projects
    SET
     Title = ?
    ,Description = ?
    ,[Date of last change] = GETDATE()
    ,[Id of changer] = ?
     WHERE Id = ?;
    )"));

	cout << "New title: ";
	projects[position].title = cinText();
	statement.bind(0, projects[position].title.c_str());

	cout << "New description: ";
	projects[position].description = cinText();
	statement.bind(1, projects[position].description.c_str());

	cout << "Id of last changer: ";
	projects[position].idOfChanger = cinInt();
	statement.bind(2, &projects[position].idOfChanger);

	statement.bind(3, &id);

	execute(statement);

	cout << GREEN << "Project has been successfully updated" << RESET << endl;
}

void editTask(nanodbc::connection conn, TASK* tasks, int& index)
{
	nanodbc::statement statement(conn);

	cout << "Enter the ID of the task you want to edit: ";
	int id = cinInt();

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (tasks[i].id == id)
		{
			position = i;
		}
	}

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Tasks
    SET
    [Id of Assignee] = ?
    ,Title = ?
    ,Description = ?
    ,Status = ?
    ,[Date of last change] = GETDATE()
    ,[Id of changer] = ?
     WHERE Id = ?;
    )"));

	cout << "New title: ";
	tasks[position].title = cinText();
	statement.bind(1, tasks[position].title.c_str());

	cout << "New description: ";
	tasks[position].description = cinText();
	statement.bind(2, tasks[position].description.c_str());

	cout << "New status (0 - Pending / 1 - In progress / 2 - Completed): ";
	int status;
	status = cinInt();
	if (status == 0)
		tasks[position].status = status::pending;
	else if (status == 1)
		tasks[position].status = status::inProgress;
	else if (status == 2)
		tasks[position].status = status::completed;
	statement.bind(3, &status);

	cout << "Id of new assignee: ";
	tasks[position].idOfAssignee = cinInt();
	statement.bind(0, &tasks[position].idOfAssignee);

	cout << "Id of last changer: ";
	tasks[position].idOfChanger = cinInt();
	statement.bind(4, &tasks[position].idOfChanger);

	statement.bind(5, &id);

	execute(statement);

	cout << GREEN << "Task has been successfully updated" << RESET << endl;
}

void editLog(nanodbc::connection conn, LOG* logs, int& index)
{
	nanodbc::statement statement(conn);

	cout << "Enter the ID of the log you want to edit: ";
	int id = cinInt();

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (logs[i].id == id)
		{
			position = i;
		}
	}

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Logs
    SET
     [Id of Task] = ?
    ,[Id of User] = ?
    ,Time = ?
    ,Date = GETDATE()
     WHERE Id = ?;
    )"));


	cout << "Id of new task: ";
	logs[position].idOfTask = cinInt();
	statement.bind(0, &logs[position].idOfTask);

	cout << "Id of new user: ";
	logs[position].idOfUser = cinInt();
	statement.bind(1, &logs[position].idOfUser);

	cout << "Time spent (in hours): ";
	logs[position].time = cinInt();
	statement.bind(2, &logs[position].time);

	statement.bind(3, &id);

	execute(statement);

	cout << GREEN << "Log has been successfully updated" << RESET << endl;
}


void deleteUser(nanodbc::connection conn, USER* users, int id, int& index)
{
	nanodbc::statement statement(conn);

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Users
     SET [isDeleted] = 'True'
     WHERE Id = ?
    )"));

	statement.bind(0, &id);

	execute(statement);

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (users[i].id == id)
		{
			position = i;
		}
	}

	users[position].isDeleted = true;

	cout << GREEN << "User has been successfully removed!" << RESET<<endl;
}

void deleteTeam(nanodbc::connection conn, TEAM* teams, int id, int& index)
{
	nanodbc::statement statement(conn);

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Teams
     SET [isDeleted] = 'True'
     WHERE Id = ?
    )"));

	statement.bind(0, &id);

	execute(statement);

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (teams[i].id == id)
		{
			position = i;
		}
	}

	teams[position].isDeleted = true;

	cout << GREEN << "Team has been successfully removed!" << RESET << endl;
}

void deleteProject(nanodbc::connection conn, PROJECT* projects, int id, int& index)
{
	nanodbc::statement statement(conn);

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Projects
     SET [isDeleted] = 'True'
     WHERE Id = ?
    )"));

	statement.bind(0, &id);

	execute(statement);

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (projects[i].id == id)
		{
			position = i;
		}
	}

	projects[position].isDeleted = true;

	cout << GREEN << "Project has been successfully removed!" << RESET << endl;
}

void deleteTask(nanodbc::connection conn, TASK* tasks, int id, int& index)
{
	nanodbc::statement statement(conn);

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Tasks
     SET [isDeleted] = 'True'
     WHERE Id = ?
    )"));

	statement.bind(0, &id);

	execute(statement);

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (tasks[i].id == id)
		{
			position = i;
		}
	}

	tasks[position].isDeleted = true;

	cout << GREEN << "Task has been successfully removed!" << RESET << endl;
}

void deleteLog(nanodbc::connection conn, LOG* logs, int id, int& index)
{
	nanodbc::statement statement(conn);

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    UPDATE [Team Management].dbo.Logs
     SET [isDeleted] = 'True'
     WHERE Id = ?
    )"));

	statement.bind(0, &id);

	execute(statement);

	int position = 0;

	for (int i = 0; i < index; i++)
	{
		if (logs[i].id == id)
		{
			position = i;
		}
	}

	logs[position].isDeleted = true;

	cout << GREEN << "Log has been successfully removed!" << RESET << endl;
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

void displayLogsMenu(LOG* logs, int& logIndex, nanodbc::connection conn)
{
	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		cout << "  _                     " << endl;
		cout << " | |                    " << endl;
		cout << " | |     ___   __ _ ___ " << endl;
		cout << " | |    / _ \\ / _` / __|" << endl;
		cout << " | |___| (_) | (_| \\__ \\" << endl;
		cout << " |______\\___/ \\__, |___/" << endl;
		cout << "               __/ |    " << endl;
		cout << "              |___/     " << endl << endl;
		cout << " ========================================" << endl;
		cout << "|" << " 1)" << YELLOW << " Show a list of all logs" << RESET << "             |" << endl;
		cout << "|" << " 2)" << GREEN << " Create a log" << RESET << "                        |" << endl;
		cout << "|" << " 3)" << CYAN << " Edit a log" << RESET << "                          |" << endl;
		cout << "|" << " 4)" << RED << " Delete a log" << RESET << "                        |" << endl;
		cout << "|" << " 5)" << GRAY << " Return back to the Tasks menu" << RESET << "       |" << endl;
		cout << " ========================================" << endl << endl;

		cout << "Enter your choice: ";
		choice = cinInt();

		while (choice > 5 or choice < 1)
		{
			cout << endl;
			cout << RED << "The number you enter has to be between 1 and 5! Please, try again: " << RESET;
			choice = cinInt();
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("cls");

		switch (choice)
		{
		case 1:
			//
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
			int id;
			cout << "Enter the ID of the log you want to remove: ";
			cin >> id;
			deleteLog(conn, logs, id, logIndex);
			cont = returnBack();
			break;
		case 5:
			cont = false;
			break;
		}
	}
}

void displayTasksMenu(TASK* tasks, int& taskIndex, LOG* logs, int& logIndex, nanodbc::connection conn)
{
	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		cout << "  _______        _        " << endl;
		cout << " |__   __|      | |       " << endl;
		cout << "    | | __ _ ___| | _____ " << endl;
		cout << "    | |/ _` / __| |/ / __|" << endl;
		cout << "    | | (_| \\__ \\   <\\__ \\" << endl;
		cout << "    |_|\\__,_|___/_|\\_\\___/" << endl << endl;
		cout << " ========================================" << endl;
		cout << "|" << " 1)" << YELLOW << " Show a list of all tasks" << RESET << "            |" << endl;
		cout << "|" << " 2)" << GREEN << " Create a task" << RESET << "                       |" << endl;
		cout << "|" << " 3)" << CYAN << " Edit a task" << RESET << "                         |" << endl;
		cout << "|" << " 4)" << RED << " Delete a task" << RESET << "                       |" << endl;
		cout << "|" << " 5)" << BLUE << " View the Logs menu for this task" << RESET << "    |" << endl;
		cout << "|" << " 6)" << GRAY << " Return back to the Projects menu" << RESET << "    |" << endl;
		cout << " ========================================" << endl << endl;

		cout << "Enter your choice: ";
		choice = cinInt();

		while (choice > 6 or choice < 1)
		{
			cout << endl;
			cout << RED << "The number you enter has to be between 1 and 6! Please, try again: " << RESET;
			choice = cinInt();
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("cls");

		switch (choice)
		{
		case 1:
			//
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
			int id;
			cout << "Enter the ID of the task you want to remove: ";
			cin >> id;
			deleteTask(conn, tasks, id, taskIndex);
			cont = returnBack();
			break;
		case 5:
			displayLogsMenu(logs, logIndex, conn);
			break;
		case 6:
			cont = false;
			break;
		}
	}
}

void displayProjectsMenu(PROJECT* projects, int& projectIndex, TASK* tasks, int& taskIndex, LOG* logs, int& logIndex, nanodbc::connection conn)
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
		cout << " ========================================" << endl;
		cout << "|" << " 1)" << YELLOW << " Show a list of all projects" << RESET << "         |" << endl;
		cout << "|" << " 2)" << GREEN << " Create a project" << RESET << "                    |" << endl;
		cout << "|" << " 3)" << CYAN << " Edit a project" << RESET << "                      |" << endl;
		cout << "|" << " 4)" << RED << " Delete a project" << RESET << "                    |" << endl;
		cout << "|" << " 5)" << PURPLE << " Assign a team to a project" << RESET << "          |" << endl;
		cout << "|" << " 6)" << BLUE << " View the Task menu for this project" << RESET << " |" << endl;
		cout << "|" << " 7)" << GRAY << " Return back to the Main Menu" << RESET << "        |" << endl;
		cout << " ========================================" << endl << endl;

		cout << "Enter your choice: ";
		choice = cinInt();

		while (choice > 7 or choice < 1)
		{
			cout << endl;
			cout << RED << "The number you enter has to be between 1 and 7! Please, try again: " << RESET;
			choice = cinInt();
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("cls");

		switch (choice)
		{
		case 1:
			displayAllProjects(projects, projectIndex);
			cont = returnBack();
			break;
		case 2:
			insertProject(conn, projects, projectIndex);
			cont = returnBack();
			break;
		case 3:
			editProject(conn, projects, projectIndex);
			cont = returnBack();
			break;
		case 4:
			int id;
			cout << "Enter the ID of the project you want to remove: ";
			cin >> id;
			deleteProject(conn, projects, id, projectIndex);
			cont = returnBack();
			break;
		case 5:
			//
			cont = returnBack();
			break;
		case 6:
			displayTasksMenu(tasks, taskIndex, logs, logIndex, conn);
			break;
		case 7:
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

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("cls");

		switch (choice)
		{
		case 1:
			displayAllTeams(teams, teamIndex);
			cont = returnBack();
			break;
		case 2:
			insertTeam(conn, teams, teamIndex);
			cont = returnBack();
			break;
		case 3:
			editTeam(conn, teams, teamIndex);
			cont = returnBack();
			break;
		case 4:
			int id;
			cout << "Enter the ID of the team you want to remove: ";
			cin >> id;
			deleteTeam(conn, teams, id, teamIndex);
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

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		system("cls");

		switch (choice)
		{
		case 1:
			displayAllUsers(users, userIndex);
			cont = returnBack();
			break;
		case 2:
			insertUser(conn, users, userIndex);
			cont = returnBack();
			break;
		case 3:
			editUser(conn, users, userIndex);
			cont = returnBack();
			break;
		case 4:
			int id;
			cout << "Enter the ID of the user you want to remove: ";
			cin >> id;
			deleteUser(conn, users, id, userIndex);
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
			displayProjectsMenu(projects, projectIndex, tasks, taskIndex, logs, logIndex, conn);
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

	int userIndex = 5, teamIndex = 3, projectIndex = 3, taskIndex = 2, logIndex = 2;
	USER currentUser;
	

	try {
		nanodbc::string connstr = NANODBC_TEXT("DRIVER={ODBC Driver 17 for SQL Server};SERVER=(localdb)\\MSSQLLocaldb;DATABASE=Team Management;Trusted_Connection=yes;");
		nanodbc::connection conn(connstr);

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