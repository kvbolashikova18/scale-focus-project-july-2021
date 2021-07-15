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
	int idOfProject = 0;
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

void spaces(int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << " ";
	}
}

void displayWelcome()
{
	spaces(17); cout << " __          __  _                          " << endl;
	spaces(17); cout << " \\ \\        / / | |                         " << endl;
	spaces(17); cout << "  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___ " << endl;
	spaces(17); cout << "   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\" << endl;
	spaces(17); cout << "    \\  /\\  /  __/ | (_| (_) | | | | | |  __/" << endl;
	spaces(17); cout << "     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|" << endl << endl << endl;
}


void displayUser(USER* users, int index, USER currentUser)
{
	if (users[index].isDeleted == false)
	{
		cout << " ________________________________________________" << endl;
		cout << "/                                                \\" << endl;
		cout << GRAY << "  ID: " << RESET << users[index].id << endl;
		cout << GRAY << "  Username: " << RESET << users[index].username << endl;
		if (currentUser.isAdmin == true)
		{
			cout << GRAY << "  Password: " << RESET << users[index].password << endl;
		}
		cout << GRAY << "  First name: " << RESET << users[index].firstName << endl;
		cout << GRAY << "  Last name: " << RESET << users[index].lastName << endl;
		cout << GRAY << "  Date of creation: " << RESET << users[index].dateOfCreation << endl;
		cout << GRAY << "  ID of creator: " << RESET << users[index].idOfCreator << endl;
		cout << GRAY << "  Date of last change: " << RESET << users[index].dateOfLastChange << endl;
		cout << GRAY << "  ID of last changer: " << RESET << users[index].idOfChanger << endl;
		cout << "\\________________________________________________/" << endl;
	}

	cout << endl;
}

void displayTeam(TEAM* teams, int index)
{
	if (teams[index].isDeleted == false)
	{
		cout << " ________________________________________________" << endl;
		cout << "/                                                \\" << endl;
		cout << GRAY << "  ID: " << RESET << teams[index].id << endl;
		cout << GRAY << "  Title: " << RESET << teams[index].title << endl;
		cout << GRAY << "  Date of creation: " << RESET << teams[index].dateOfCreation << endl;
		cout << GRAY << "  ID of creator: " << RESET << teams[index].idOfCreator << endl;
		cout << GRAY << "  Date of last change: " << RESET << teams[index].dateOfLastChange << endl;
		cout << GRAY << "  ID of last changer: " << RESET << teams[index].idOfChanger << endl;
		cout << "\\________________________________________________/" << endl;
	}

	cout << endl;
}

void displayProject(PROJECT* projects, int index)
{
	if (projects[index].isDeleted == false)
	{
		cout << " ________________________________________________" << endl;
		cout << "/                                                \\" << endl;
		cout << GRAY << "  ID: " << RESET << projects[index].id << endl;
		cout << GRAY << "  Title: " << RESET << projects[index].title << endl;
		cout << GRAY << "  Description: " << RESET << projects[index].description << endl;
		cout << GRAY << "  Date of creation: " << RESET << projects[index].dateOfCreation << endl;
		cout << GRAY << "  ID of creator: " << RESET << projects[index].idOfCreator << endl;
		cout << GRAY << "  Date of last change: " << RESET << projects[index].dateOfLastChange << endl;
		cout << GRAY << "  ID of last changer: " << RESET << projects[index].idOfChanger << endl;
		cout << "\\________________________________________________/" << endl;
	}

	cout << endl;
}

void displayTask(TASK* tasks, int index)
{
	if (tasks[index].isDeleted == false)
	{
		cout << " ________________________________________________" << endl;
		cout << "/                                                \\" << endl;
		cout << GRAY << "  ID: " << RESET << tasks[index].id << endl;
		cout << GRAY << "  ID of project: " << RESET << tasks[index].idOfProject << endl;
		cout << GRAY << "  ID of assignee: " << RESET << tasks[index].idOfAssignee << endl;
		cout << GRAY << "  Title: " << RESET << tasks[index].title << endl;
		cout << GRAY << "  Description: " << RESET << tasks[index].description << endl;
		if (tasks[index].status == status::pending)
			cout << GRAY << "  Status: pending" << RESET << endl;
		else if (tasks[index].status == status::inProgress)
			cout << GRAY << "  Status: in progress" << RESET << endl;
		else
			cout << GRAY << "  Status: completed" << RESET << endl;
		cout << GRAY << "  Date of creation: " << RESET << tasks[index].dateOfCreation << endl;
		cout << GRAY << "  ID of creator: " << RESET << tasks[index].idOfCreator << endl;
		cout << GRAY << "  Date of last change: " << RESET << tasks[index].dateOfLastChange << endl;
		cout << GRAY << "  ID of last changer: " << RESET << tasks[index].idOfChanger << endl;
		cout << "\\________________________________________________/" << endl;
	}

	cout << endl;
}

void displayLog(LOG* logs, int index)
{
	if (logs[index].isDeleted == false)
	{
		cout << " __________________________________" << endl;
		cout << "/                                  \\" << endl;
		cout << GRAY << "  ID: " << RESET << logs[index].id << endl;
		cout << GRAY << "  ID of task: " << RESET << logs[index].idOfTask << endl;
		cout << GRAY << "  ID of user: " << RESET << logs[index].idOfUser << endl;
		cout << GRAY << "  Time spent (hours): " << RESET << logs[index].time << endl;
		cout << GRAY << "  Date: " << RESET << logs[index].date << endl;
		cout << "\\__________________________________/" << endl;
	}

	cout << endl;
}


void displayAllUsers(USER* users, int index, USER currentUser)
{
	for (int i = 0; i < index; i++)
	{
		displayUser(users, i, currentUser);
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

void displayAllTasks(TASK* tasks, int index, int projectId)
{
	for (int i = 0; i < index; i++)
	{
		if (tasks[i].idOfProject == projectId)
		{
			displayTask(tasks, i);
		}
	}
}

void displayAllLogs(LOG* logs, int index, int taskId)
{
	for (int i = 0; i < index; i++)
	{
		if (logs[i].idOfTask == taskId)
		{
			displayLog(logs, i);
		}
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
		users[index].isAdmin = result.get<int>("isAdmin");

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


void insertUser(nanodbc::connection conn, USER* users, int& index, USER& currentUser)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Users
    (Username, [Password], [First Name], [Last Name], [Id of creator], [Id of changer], [isAdmin])
    VALUES
    (?, ?, ?, ?, ?, ?, ?)
    )"));

	cout << endl;

	cout << GRAY << " Username: " << RESET;
	users[index].username = cinText();
	statement.bind(0, users[index].username.c_str());

	cout << GRAY << " Password: " << RESET;
	users[index].password = cinText();
	statement.bind(1, users[index].password.c_str());

	cout << GRAY << " First name: " << RESET;
	users[index].firstName = cinText();
	statement.bind(2, users[index].firstName.c_str());

	cout << GRAY << " Last name: " << RESET;
	users[index].lastName = cinText();
	statement.bind(3, users[index].lastName.c_str());

	users[index].idOfCreator = currentUser.id;
	statement.bind(4, &users[index].idOfCreator);

	users[index].idOfChanger = currentUser.id;
	statement.bind(5, &users[index].idOfChanger);

	int a = 0;
	statement.bind(6, &a);

	execute(statement);

	getUserFromDatabase(conn, users, index);

	cout << GREEN << "\n User has been successfully added" <<  RESET << endl << endl;
}

void insertTeam(nanodbc::connection conn, TEAM* teams, int& index, USER& currentUser)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Teams
    (Title, [Id of creator], [Id of changer])
    VALUES
    (?, ?, ?)
    )"));

	cout << endl;

	cout << GRAY << " Title: " << RESET;
	teams[index].title = cinText();
	statement.bind(0, teams[index].title.c_str());

	teams[index].idOfCreator = currentUser.id;
	statement.bind(1, &teams[index].idOfCreator);

	teams[index].idOfChanger = currentUser.id;
	statement.bind(2, &teams[index].idOfChanger);

	execute(statement);

	getTeamFromDatabase(conn, teams, index);

	cout << GREEN << "\n Team has been successfully added" << RESET << endl << endl;
}

void insertProject(nanodbc::connection conn, PROJECT* projects, int& index, USER& currentUser)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Projects
    (Title, Description, [Id of creator], [Id of changer])
    VALUES
    (?, ?, ?, ?)
    )"));

	cout << endl;

	cout << GRAY << " Title: " << RESET;
	projects[index].title = cinText();
	statement.bind(0, projects[index].title.c_str());

	cout << GRAY << " Description: " << RESET;
	projects[index].description = cinText();
	statement.bind(1, projects[index].description.c_str());

	projects[index].idOfCreator = currentUser.id;
	statement.bind(2, &projects[index].idOfCreator);

	projects[index].idOfChanger = currentUser.id;
	statement.bind(3, &projects[index].idOfChanger);

	execute(statement);

	getProjectFromDatabase(conn, projects, index);

	cout << GREEN << "\n Project has been successfully added" << RESET << endl << endl;
}

void insertTask(nanodbc::connection conn, TASK* tasks, int& index, int projectId, USER& currentUser)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Tasks
    ([Id of Project], [Id of Assignee], Title, Description, Status, [Id of creator], [Id of changer])
    VALUES
    (?, ?, ?, ?, ?, ?, ?)
    )"));

	cout << endl;

	cout << GRAY << " Title: " << RESET;
	tasks[index].title = cinText();
	statement.bind(2, tasks[index].title.c_str());

	cout << GRAY << " Description: " << RESET;
	tasks[index].description = cinText();
	statement.bind(3, tasks[index].description.c_str());

	tasks[index].idOfProject = projectId;
	statement.bind(0, &tasks[index].idOfProject);

	cout << GRAY << " Id of assignee: " << RESET;
	tasks[index].idOfAssignee = cinInt();
	statement.bind(1, &tasks[index].idOfAssignee);

	cout << GRAY << " Status (0 - Pending / 1 - In progress / 2 - Completed): " << RESET;
	int status;
	status = cinInt();
	if (status == 0)
		tasks[index].status = status::pending;
	else if (status == 1)
		tasks[index].status = status::inProgress;
	else if (status == 2)
		tasks[index].status = status::completed;
	statement.bind(4, &status);

	tasks[index].idOfCreator = currentUser.id;
	statement.bind(5, &tasks[index].idOfCreator);

	tasks[index].idOfChanger = currentUser.id;
	statement.bind(6, &tasks[index].idOfChanger);

	execute(statement);

	int j = 0;
	getTaskFromDatabase(conn, tasks, j);
	index++;

	cout << GREEN << "\n Task has been successfully added" << RESET << endl << endl;
}

void insertLog(nanodbc::connection conn, LOG* logs, int& index, int taskId, USER& currentUser)
{
	nanodbc::statement statement(conn);
	nanodbc::prepare(statement, NANODBC_TEXT(R"(
    INSERT INTO
    [Team Management].dbo.Logs
    ([Id of Task], [Id of User], Time)
    VALUES
    (?, ?, ?)
    )"));

	cout << endl;

	logs[index].idOfTask = taskId;
	statement.bind(0, &logs[index].idOfTask);

	cout << GRAY << " Id of User: " << RESET;
	logs[index].idOfUser = cinInt();
	statement.bind(1, &logs[index].idOfUser);

	cout << GRAY << " Time spent (in hours): " << RESET;
	logs[index].time = cinInt();
	statement.bind(2, &logs[index].time);

	execute(statement);

	int j = 0;
	getLogFromDatabase(conn, logs, j);
	index++;

	cout << GREEN << "\n Log has been successfully added" << RESET << endl << endl;
}


void editUser(nanodbc::connection conn, USER* users, int& index, USER& currentUser)
{
	nanodbc::statement statement(conn);

	cout << " Enter the ID of the user you want to edit: ";
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

	cout << endl;

	cout << GRAY << " New username: " << RESET;
	users[position].username = cinText();
	statement.bind(0, users[position].username.c_str());

	cout << GRAY << " New password: " << RESET;
	users[position].password = cinText();
	statement.bind(1, users[position].password.c_str());

	cout << GRAY << " New first name: " << RESET;
	users[position].firstName = cinText();
	statement.bind(2, users[position].firstName.c_str());

	cout << GRAY << " New last name: " << RESET;
	users[position].lastName = cinText();
	statement.bind(3, users[position].lastName.c_str());

	users[position].idOfChanger = currentUser.id;
	statement.bind(4, &users[position].idOfChanger);

	statement.bind(5, &id);

	execute(statement);

	cout << GREEN << "\n User has been successfully updated" << RESET << endl << endl;
}

void editTeam(nanodbc::connection conn, TEAM* teams, int& index, USER& currentUser)
{
	nanodbc::statement statement(conn);

	cout << " Enter the ID of the team you want to edit: ";
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

	cout << endl;

	cout << GRAY << " New title: " << RESET;
	teams[position].title = cinText();
	statement.bind(0, teams[position].title.c_str());

	teams[position].idOfChanger = currentUser.id;
	statement.bind(1, &teams[position].idOfChanger);

	statement.bind(2, &id);

	execute(statement);

	cout << GREEN << "\n Team has been successfully updated" << RESET << endl << endl;
}

void editProject(nanodbc::connection conn, PROJECT* projects, int& index, USER& currentUser)
{
	nanodbc::statement statement(conn);

	cout << " Enter the ID of the project you want to edit: ";
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

	cout << endl;

	cout << GRAY << " New title: " << RESET;
	projects[position].title = cinText();
	statement.bind(0, projects[position].title.c_str());

	cout << GRAY << " New description: " << RESET;
	projects[position].description = cinText();
	statement.bind(1, projects[position].description.c_str());

	projects[position].idOfChanger = currentUser.id;
	statement.bind(2, &projects[position].idOfChanger);

	statement.bind(3, &id);

	execute(statement);

	cout << GREEN << "\n Project has been successfully updated" << RESET << endl << endl;
}

void editTask(nanodbc::connection conn, TASK* tasks, int& index, USER& currentUser)
{
	nanodbc::statement statement(conn);

	cout << " Enter the ID of the task you want to edit: ";
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

	cout << endl;

	cout << GRAY << " New title: " << RESET;
	tasks[position].title = cinText();
	statement.bind(1, tasks[position].title.c_str());

	cout << GRAY << " New description: " << RESET;
	tasks[position].description = cinText();
	statement.bind(2, tasks[position].description.c_str());

	cout << GRAY << " New status (0 - Pending / 1 - In progress / 2 - Completed): " << RESET;
	int status;
	status = cinInt();
	if (status == 0)
		tasks[position].status = status::pending;
	else if (status == 1)
		tasks[position].status = status::inProgress;
	else if (status == 2)
		tasks[position].status = status::completed;
	statement.bind(3, &status);

	cout << GRAY << " Id of new assignee: " << RESET;
	tasks[position].idOfAssignee = cinInt();
	statement.bind(0, &tasks[position].idOfAssignee);

	tasks[position].idOfChanger = currentUser.id;
	statement.bind(4, &tasks[position].idOfChanger);

	statement.bind(5, &id);

	execute(statement);

	cout << GREEN << "\n Task has been successfully updated" << RESET << endl << endl;
}

void editLog(nanodbc::connection conn, LOG* logs, int& index, USER& currentUser)
{
	nanodbc::statement statement(conn);

	cout << " Enter the ID of the log you want to edit: ";
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

	cout << endl;

	cout << GRAY << " Id of new task: " << RESET;
	logs[position].idOfTask = cinInt();
	statement.bind(0, &logs[position].idOfTask);

	cout << GRAY << " Id of new user: " << RESET;
	logs[position].idOfUser = cinInt();
	statement.bind(1, &logs[position].idOfUser);

	cout << GRAY << " Time spent (in hours): " << RESET;
	logs[position].time = cinInt();
	statement.bind(2, &logs[position].time);

	statement.bind(3, &id);

	execute(statement);

	cout << GREEN << "\n Log has been successfully updated" << RESET << endl << endl;
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

	cout << GREEN << "\n User has been successfully removed!" << RESET<<endl<<endl;
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

	cout << GREEN << "\n Team has been successfully removed!" << RESET << endl << endl;
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

	cout << GREEN << "\n Project has been successfully removed!" << RESET << endl << endl;
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

	cout << GREEN << "\n Task has been successfully removed!" << RESET << endl << endl;
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

	cout << GREEN << "\n Log has been successfully removed!" << RESET << endl << endl;
}


// function that asks the user if they want to return to the main menu
bool returnBack()
{
	int choice;

	cout << endl;
	cout << "What would you like to do now?" << endl << endl;
	cout << "1)" << GRAY << " Stay in this menu" << RESET << endl;
	cout << "2)" << GRAY << " Go one menu back" << RESET <<endl << endl;
	cout << GRAY << " Enter your choice: " << RESET;

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

string enterHiddenText()
{
	string password = "";
	char symbol = ' ';

	while (symbol != '	')
	{
		symbol = _getch();
		if (symbol != '	')
		{
			cout << GRAY << '*' << RESET;
			password += symbol;
		}
	}

	cout << endl;
  
	return password;
}

bool logIn(string& username, string& password, USER* users, int& userIndex, USER& currentUser)
{
	cout << "                                 | LOG IN |" << endl << endl;

	cout << "                             Username: ";
	getline(cin, username);

	cout << "                             Password: ";
	password = enterHiddenText();

	int usernameMatchIndex = 0;
	int usernameMatchCount = 0;

	for (int i = 0; i < userIndex; i++)
	{
		if (users[i].username == username)
		{
			usernameMatchIndex = i;
			usernameMatchCount++;
		}
	}

	if (usernameMatchCount != 0 and users[usernameMatchIndex].username == username and users[usernameMatchIndex].password == password)
	{
		currentUser = users[usernameMatchIndex];
		return true;
	}

	return false;
}

void displayLogsMenu(LOG* logs, int& logIndex, nanodbc::connection conn, USER& currentUser)
{
	int taskId;
	cout << " Please, enter the ID of the task, the logs of which you want to see: ";
	cin >> taskId;

	system("cls");

	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		spaces(27);  cout << "  _                     " << endl;
		spaces(27);  cout << " | |                    " << endl;
		spaces(27);  cout << " | |     ___   __ _ ___ " << endl;
		spaces(27);  cout << " | |    / _ \\ / _` / __|" << endl;
		spaces(27);  cout << " | |___| (_) | (_| \\__ \\" << endl;
		spaces(27);  cout << " |______\\___/ \\__, |___/" << endl;
		spaces(27);  cout << "               __/ |    " << endl;
		spaces(27);  cout << "              |___/     " << endl << endl;
		spaces(19);  cout << " ________________________________________" << endl;
		spaces(19);  cout << "|                                        |" << endl;
		spaces(19);  cout << "|" << " 1)" << YELLOW << " Show a list of all logs" << RESET << "             |" << endl;
		spaces(19);  cout << "|" << " 2)" << GREEN << " Create a log" << RESET << "                        |" << endl;
		spaces(19);  cout << "|" << " 3)" << CYAN << " Edit a log" << RESET << "                          |" << endl;
		spaces(19);  cout << "|" << " 4)" << RED << " Delete a log" << RESET << "                        |" << endl;
		spaces(19);  cout << "|" << " 5)" << GRAY << " Return back to the Tasks menu" << RESET << "       |" << endl;
		spaces(19);  cout << "|________________________________________|" << endl << endl;

		cout << " Enter your choice: ";
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
			displayAllLogs(logs, logIndex, taskId);
			cont = returnBack();
			break;
		case 2:
			insertLog(conn, logs, logIndex, taskId, currentUser);
			cont = returnBack();
			break;
		case 3:
			editLog(conn, logs, logIndex, currentUser);
			cont = returnBack();
			break;
		case 4:
			int id;
			cout << " Enter the ID of the log you want to remove: ";
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

void displayTasksMenu(TASK* tasks, int& taskIndex, LOG* logs, int& logIndex, nanodbc::connection conn, USER& currentUser)
{
	int projectId;
	cout << "Please, enter the ID of the project, the tasks of which you want to see: ";
	cin >> projectId;

	system("cls");

	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		spaces(26);  cout << "  _______        _        " << endl;
		spaces(26);  cout << " |__   __|      | |       " << endl;
		spaces(26);  cout << "    | | __ _ ___| | _____ " << endl;
		spaces(26);  cout << "    | |/ _` / __| |/ / __|" << endl;
		spaces(26);  cout << "    | | (_| \\__ \\   <\\__ \\" << endl;
		spaces(26);  cout << "    |_|\\__,_|___/_|\\_\\___/" << endl << endl;
		spaces(20);  cout << " ________________________________________" << endl;
		spaces(20);  cout << "|                                        |" << endl;
		spaces(20);  cout << "|" << " 1)" << YELLOW << " Show a list of all tasks" << RESET << "            |" << endl;
		spaces(20);  cout << "|" << " 2)" << GREEN << " Create a task" << RESET << "                       |" << endl;
		spaces(20);  cout << "|" << " 3)" << CYAN << " Edit a task" << RESET << "                         |" << endl;
		spaces(20);  cout << "|" << " 4)" << RED << " Delete a task" << RESET << "                       |" << endl;
		spaces(20);  cout << "|" << " 5)" << BLUE << " View the Logs menu for this task" << RESET << "    |" << endl;
		spaces(20);  cout << "|" << " 6)" << GRAY << " Return back to the Projects menu" << RESET << "    |" << endl;
		spaces(20);  cout << "|________________________________________|" << endl << endl;

		cout << " Enter your choice: ";
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
			displayAllTasks(tasks, taskIndex, projectId);
			cont = returnBack();
			break;
		case 2:
			insertTask(conn, tasks, taskIndex, projectId, currentUser);
			cont = returnBack();
			break;
		case 3:
			editTask(conn, tasks, taskIndex, currentUser);
			cont = returnBack();
			break;
		case 4:
			int id;
			cout << " Enter the ID of the task you want to remove: ";
			cin >> id;
			deleteTask(conn, tasks, id, taskIndex);
			cont = returnBack();
			break;
		case 5:
			displayLogsMenu(logs, logIndex, conn, currentUser);
			break;
		case 6:
			cont = false;
			break;
		}
	}
}

void displayProjectsMenu(PROJECT* projects, int& projectIndex, TASK* tasks, int& taskIndex, LOG* logs, int& logIndex, nanodbc::connection conn, USER& currentUser)
{
	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		spaces(20);  cout << "  _____           _           _       " << endl;
		spaces(20);  cout << " |  __ \\         (_)         | |      " << endl;
		spaces(20);  cout << " | |__) | __ ___  _  ___  ___| |_ ___ " << endl;
		spaces(20);  cout << " |  ___/ '__/ _ \\| |/ _ \\/ __| __/ __|" << endl;
		spaces(20);  cout << " | |   | | | (_) | |  __/ (__| |_\\__ \\" << endl;
		spaces(20);  cout << " |_|   |_|  \\___/| |\\___|\\___|\\__|___/" << endl;
		spaces(20);  cout << "                _/ |                  " << endl;
		spaces(20);  cout << "               |__/                   " << endl << endl;
		spaces(19);  cout << " ________________________________________" << endl;
		spaces(19);  cout << "|                                        |" << endl;
		spaces(19);  cout << "|" << " 1)" << YELLOW << " Show a list of all projects" << RESET << "         |" << endl;
		spaces(19);  cout << "|" << " 2)" << GREEN << " Create a project" << RESET << "                    |" << endl;
		spaces(19);  cout << "|" << " 3)" << CYAN << " Edit a project" << RESET << "                      |" << endl;
		spaces(19);  cout << "|" << " 4)" << RED << " Delete a project" << RESET << "                    |" << endl;
		spaces(19);  cout << "|" << " 5)" << PURPLE << " Assign a team to a project" << RESET << "          |" << endl;
		spaces(19);  cout << "|" << " 6)" << BLUE << " View the Task menu for this project" << RESET << " |" << endl;
		spaces(19);  cout << "|" << " 7)" << GRAY << " Return back to the Main Menu" << RESET << "        |" << endl;
		spaces(19);  cout << "|________________________________________|" << endl << endl;

		cout << " Enter your choice: ";
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
			insertProject(conn, projects, projectIndex, currentUser);
			cont = returnBack();
			break;
		case 3:
			editProject(conn, projects, projectIndex, currentUser);
			cont = returnBack();
			break;
		case 4:
			int id;
			cout << " Enter the ID of the project you want to remove: ";
			cin >> id;
			deleteProject(conn, projects, id, projectIndex);
			cont = returnBack();
			break;
		case 5:
			cout << endl;
			spaces(17);  cout << BLUE << "Sorry, this option is still under development ;(" << RESET << endl;
			cont = returnBack();
			break;
		case 6:
			displayTasksMenu(tasks, taskIndex, logs, logIndex, conn, currentUser);
			break;
		case 7:
			cont = false;
			break;
		}
	}
}

void displayTeamsMenu(TEAM* teams, int& teamIndex, nanodbc::connection conn, USER& currentUser)
{
	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		spaces(23);  cout << "  _______                       " << endl;
		spaces(23);  cout << " |__   __|                      " << endl;
		spaces(23);  cout << "    | | ___  __ _ _ __ ___  ___ " << endl;
		spaces(23);  cout << "    | |/ _ \\/ _` | '_ ` _ \\/ __|" << endl;
		spaces(23);  cout << "    | |  __/ (_| | | | | | \\__ \\" << endl;
		spaces(23);  cout << "    |_|\\___|\\__,_|_| |_| |_|___/" << endl << endl;
		spaces(20);  cout << " _______________________________________" << endl;
		spaces(20);  cout << "|                                       |" << endl;
		spaces(20);  cout << "|" << " 1)" << YELLOW << " Show a list of all teams" << RESET << "           |" << endl;
		spaces(20);  cout << "|" << " 2)" << GREEN << " Create a team" << RESET << "                      |" << endl;
		spaces(20);  cout << "|" << " 3)" << CYAN << " Edit a team" << RESET << "                        |" << endl;
		spaces(20);  cout << "|" << " 4)" << RED << " Delete a team" << RESET << "                      |" << endl;
		spaces(20);  cout << "|" << " 5)" << PURPLE << " Assign a user to a team" << RESET << "            |" << endl;
		spaces(20);  cout << "|" << " 6)" << GRAY << " Return back to the Main Menu" << RESET << "       |" << endl;
		spaces(20);  cout << "|_______________________________________|" << endl << endl;

		cout << " Enter your choice: ";
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
			if (currentUser.isAdmin == true)
				insertTeam(conn, teams, teamIndex, currentUser);
			else
			{
				cout << endl;
				spaces(17);  cout << RED << "You don't have permission for this operation" << RESET << endl;
			}
			cont = returnBack();
			break;
		case 3:
			if (currentUser.isAdmin == true)
				editTeam(conn, teams, teamIndex, currentUser);
			else
			{
				cout << endl;
				spaces(17);  cout << RED << "You don't have permission for this operation" << RESET << endl;
			}
			cont = returnBack();
			break;
		case 4:
			if (currentUser.isAdmin == true)
			{
				int id;
				cout << " Enter the ID of the team you want to remove: ";
				cin >> id;
				deleteTeam(conn, teams, id, teamIndex);
			}
			else
			{
				cout << endl;
				spaces(17);  cout << RED << "You don't have permission for this operation" << RESET << endl;
			}
			cont = returnBack();
			break;
		case 5:
			cout << endl;
			spaces(17);  cout << BLUE << "Sorry, this option is still under development ;(" << RESET << endl;
			cont = returnBack();
			break;
		case 6:
			cont = false;
			break;
		}
	}
}

void displayUsersMenu(USER* users, int& userIndex, nanodbc::connection conn, USER& currentUser)
{
	bool cont = true;

	while (cont == true)
	{
		int choice = 0;

		cout << endl;
		spaces(26); cout << "  _    _                   " << endl;
		spaces(26); cout << " | |  | |                  " << endl;
		spaces(26); cout << " | |  | |___  ___ _ __ ___ " << endl;
		spaces(26); cout << " | |  | / __|/ _ \\ '__/ __|" << endl;
		spaces(26); cout << " | |__| \\__ \\  __/ |  \\__ \\" << endl;
		spaces(26); cout << "  \\____/|___/\\___|_|  |___/" << endl << endl << endl;
		spaces(20); cout << " _______________________________________" << endl;
		spaces(20); cout << "|                                       |" << endl;
		spaces(20); cout << "|" << " 1)" << YELLOW << " Show a list of all users" << RESET << "           |" << endl;
		spaces(20); cout << "|" << " 2)" << GREEN << " Create a user" << RESET << "                      |" << endl;
		spaces(20); cout << "|" << " 3)" << CYAN << " Edit a user" << RESET << "                        |" << endl;
		spaces(20); cout << "|" << " 4)" << RED << " Delete a user" << RESET << "                      |" << endl;
		spaces(20); cout << "|" << " 5)" << GRAY << " Return back to the Main Menu" << RESET << "       |" << endl;
		spaces(20); cout << "|_______________________________________|" << endl << endl;

		cout << " Enter your choice: ";
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
			displayAllUsers(users, userIndex, currentUser);
			cont = returnBack();
			break;
		case 2:
			if (currentUser.isAdmin == true)
				insertUser(conn, users, userIndex, currentUser);
			else
			{
				cout << endl;
				spaces(17);  cout << RED << "You don't have permission for this operation" << RESET << endl;
			}
			cont = returnBack();
			break;
		case 3:
			if (currentUser.isAdmin == true)
				editUser(conn, users, userIndex, currentUser);
			else
			{
				cout << endl;
				spaces(17);  cout << RED << "You don't have permission for this operation" << RESET << endl;
			}
			cont = returnBack();
			break;
		case 4:
			if (currentUser.isAdmin == true)
			{
				int id;
				cout << " Enter the ID of the user you want to remove: ";
				cin >> id;
				deleteUser(conn, users, id, userIndex);
			}
			else
			{
				cout << endl;
				spaces(17);  cout << RED << "You don't have permission for this operation" << RESET << endl;
			}
			cont = returnBack();
			break;
		case 5:
			cont = false;
			break;
		}
	}
}

void displayMainMenu(USER* users, int& userIndex, TEAM* teams, int& teamIndex, PROJECT* projects, int& projectIndex, TASK* tasks, int& taskIndex, LOG* logs, int& logIndex, nanodbc::connection conn, USER& currentUser)
{

	int choice = 0;

	while (choice != 4)
	{
		cout << endl;

		spaces(17);  cout << " __  __       _          __  __                      " << endl;
		spaces(17);  cout << "|  \\/  |     (_)        |  \\/  |                   " << endl;
		spaces(17);  cout << "| \\  / | __ _ _ _ __    | \\  / | ___ _ __  _   _   " << endl;
		spaces(17);  cout << "| |\\/| |/ _` | | '_ \\   | |\\/| |/ _ \\ '_ \\| | | |" << endl;
		spaces(17);  cout << "| |  | | (_| | | | | |  | |  | |  __/ | | | |_| |    " << endl;
		spaces(17);  cout << "|_|  |_|\\__,_|_|_| |_|  |_|  |_|\\___|_| |_|\\__,_| " << endl;

		cout << endl;
		cout << endl;

		spaces(19);  cout << "Which set of data would you like to work with?" << endl << endl;
		spaces(29);  cout << " =====================" << endl;
		spaces(29);  cout << "|" << " 1)" << YELLOW << " Users" << RESET << "            |" << endl;
		spaces(29);  cout << "|" << " 2)" << GREEN << " Teams" << RESET << "            |" << endl;
		spaces(29);  cout << "|" << " 3)" << CYAN << " Projects" << RESET << "         |" << endl;
		spaces(29);  cout << "|" << " 4)" << GRAY << " Exit" << RESET << "             |" << endl;
		spaces(29);  cout << " =====================" << endl;
		cout << endl;
		cout << " Enter your choice: ";
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
			displayUsersMenu(users, userIndex, conn, currentUser);
			break;
		case 2:
			displayTeamsMenu(teams, teamIndex, conn, currentUser);
			break;
		case 3:
			displayProjectsMenu(projects, projectIndex, tasks, taskIndex, logs, logIndex, conn, currentUser);
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
	TEAM* teams = new TEAM[50];
	PROJECT* projects = new PROJECT[50];
	TASK* tasks = new TASK[50];
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

		displayWelcome();
		
		bool success = false;

		while (success == false)
		{
			success = logIn(currentUser.username, currentUser.password, users, userIndex, currentUser);

			if (success == false)
			{
				system("cls");
				cout << endl;
				spaces(18);  cout << RED << "Incorrect username or password! Try again: " << RESET << endl << endl;
			}
		}

		system("cls");
		
		displayMainMenu(users, userIndex, teams, teamIndex, projects, projectIndex, tasks, taskIndex, logs, logIndex, conn, currentUser);

		return EXIT_SUCCESS;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}