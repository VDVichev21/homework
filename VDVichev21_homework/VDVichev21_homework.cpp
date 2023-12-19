#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;
const string server = "tcp://sqlvicho.mysql.database.azure.com:3306";
const string username = "mysqladmin";
const string password = "Homework!";

int main()
{
	
	

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("vichodb");

	char answer;
	string username, password, email;
	std::cout << "Log in or Register?" << std::endl;
	std::cout << "L/R ";
	std::cin >> answer;
	if (answer == 'L')
	{
		std::cout << "Username: ";
		std::cin >> username;
		std::cout << std::endl;
		std::cout << "Password: ";
		std::cin >> password;

		pstmt = con->prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
		pstmt->setString(1, username);
		pstmt->setString(2, password);
		if (pstmt->execute())
		{
			cout << "Logged in." << endl;
		}
		else
		{
			cout << "Wrong password or username";
		}
		
	}
	else if (answer == 'R')
	{
		std::cout << "Email: ";
		std::cin >> email;
		std::cout << std::endl;
		std::cout << "Username: ";
		std::cin >> username;
		std::cout << std::endl;
		std::cout << "Password: ";
		std::cin >> password;

		pstmt = con->prepareStatement("INSERT INTO users(email, username, password) VALUES(?,?,?)");
		pstmt->setString(1, email);
		pstmt->setString(2, username);
		pstmt->setString(3, password);
		pstmt->execute();
		cout << "Account registered." << endl;
	}
	
}