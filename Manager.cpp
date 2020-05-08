#include<iostream>
#include<cstring>
#include "Manager.hpp"

unsigned const MAX_LEN_COMMAND = 11;
unsigned const MAX_LEN = 50;

void Manager::closeFile()
{
	if (ptrIfs == nullptr && ptrOfs == nullptr) {
		std::cout << "Unvalid operation!" << std::endl;
		return;
	}

	m_lib.cleanMemory();

	if (ptrIfs != nullptr) {
		ptrIfs->close();
	}
	if (ptrOfs != nullptr) {
		ptrOfs->close();
	}
	std::cout << "Successfully closed file." << std::endl;
}

void Manager::help() const
{
	std::cout << "The following commands are supported:" << std::endl
				<< "open<file> " << '\t' << "opens<file>";
	std::cout << "close" << '\t' << "close currently opened file" << std::endl
			  << "save" << '\t' << "saves the currently opened file" << std::endl
		      << "saveas<file>" << '\t' << "saves the currently open file in <file>" << std::endl
			  << "help" << '\t' << "prints this information" << std::endl
			  << "exit" << '\t' << "exit the program" << std::endl;
}

void Manager::login()
{
	if (isUser == false) {
		char name[MAX_LEN];
		char password[MAX_LEN];
		std::cout << "Username: ";
		std::cin.getline(name, MAX_LEN);

		std::cout << "Password: ";
		std::cin.getline(password, MAX_LEN);

		std::ifstream ifs("Users.bin", std::ios::in | std::ios::binary);
		unsigned count = 0;
		ifs.read((char*)& count, sizeof(count));
		User *usersList = new(std::nothrow) User[count];
		if (usersList == nullptr) {
			std::cout << "Error!" << std::endl;
		}

		for (int i = 0; i < count; ++i) {
			usersList[i].deserializeUser(ifs);
		}

		for (int i = 0; i < count; ++i) {
			if (strcmp(usersList[i].getUsername(), name) == 0 && strcmp(usersList[i].getPassword(), password) == 0) {
				isUser = true;
				std::cout << "Welcome " << name << " !" << std::endl;
			}
		}
		if (isUser == false) {
			std::cout << "Uncorrect username/password." << std::endl;
		}


		ifs.close();

	}
	else {
		std::cout << "You are already logged in!" << std::endl;
	}
	
}

void Manager::exit()
{
	std::cout << "Exit the program. " << std::endl;
}

void Manager::logout()
{
	//Проверка дали вписаният потребител е администратор или обикновен потребител.
	if (isUser == true) {
		isUser = false;
	}

	if(isAdmin==true){
		isAdmin == false;
	}

}

void Manager::booksAll()
{
	m_lib.booksAll();
}

void Manager::booksInfo(unsigned ID)
{
	m_lib.booksInfo(ID);
}

void Manager::booksFind(char * option, char * optionString)
{
	if (strcmp(option, "titile") == 0) {
		m_lib.booksFindTitile(optionString);
	}

	if (strcmp(option, "author") == 0) {
		m_lib.booksFindAuthor(optionString);
	}

	if (strcmp(option, "tag") == 0) {
		m_lib.booksFindTag(optionString);
	}

	else {
		std::cout << "Invalid search option." << std::endl;
	}
}

void Manager::userAdd(char * username, char * password)
{
	std::ifstream ifs("Users.bin", std::ios::in | std::ios::binary);
	unsigned count = 0;

	//Прочитане на броя потребители от базата данни на потребителите.
	ifs.read((char*)& count, sizeof(count));

	User *usersList = new(std::nothrow) User[count];
	if (usersList == nullptr) {
		std::cout << "Error! Not enought memory for usersList." << std::endl;
	}

	for (int i = 0; i < count; ++i) {
		usersList[i].deserializeUser(ifs);
	}

	ifs.close();

	//Проверка дали такъв потребител вече съществува.
	//Проверяваме само за потребителското име, защото не е възможно да има двама потребителя с едно и също име.
	for (int i = 0; i < count; ++i) {
		if (strcmp(usersList[i].getUsername(), username) == 0) {
			std::cout << "There is already one registered user. Try again with another username." << std::endl;
			return;
		}
	}

	//Добавяне на новия потребител.
	for (int i = 0; i < count; ++i) {
		usersList[count] = User(username, password);
	}
	++count;

	//Записване на новият списък с потребители.
	std::ofstream ofs("Users.bin", std::ios::out | std::ios::binary| std::ios::trunc);
	ofs.write((const char*)& count, sizeof(count));

	for (int i = 0; i < count; ++i) {
		usersList[i].serializeUser(ofs);
	}

	ofs.close();
}

void Manager::userRemove(char * username)
{
	std::ifstream ifs("Users.bin", std::ios::in | std::ios::binary);
	unsigned count = 0;

	//Прочитане на броя потребители от базата данни на потребителите.
	ifs.read((char*)& count, sizeof(count));

	User *usersList = new(std::nothrow) User[count];
	if (usersList == nullptr) {
		std::cout << "Error! Not enought memory for usersList." << std::endl;
	}

	for (int i = 0; i < count; ++i) {
		usersList[i].deserializeUser(ifs);
	}

	ifs.close();

	int posOfTheUserToBeDeleted = -1;

	//Намиране на позицията на потребителя, който ще изтрием.
	for (int i = 0; i < count; ++i) {
		if (strcmp(usersList[i].getUsername(), username) == 0) {
			posOfTheUserToBeDeleted = i;
		}
	}

	//Проверка дали потребителят, който трябва да бъде изтрит съществува.
	if (posOfTheUserToBeDeleted == -1) {
		std::cout << "User with username \" " << username << "\" does not exist." << std::endl;
		return;
	}

	//Премахване на потребител, като наредбата на потребителите не е от значение.
	for (int i = 0; i < count; ++i) {
		usersList[posOfTheUserToBeDeleted] = usersList[count - 1];
	}
	--count;
	
	//Записване на новият списък с потребители.
	std::ofstream ofs("Users.bin", std::ios::out | std::ios::binary| std::ios::trunc);
	ofs.write((const char*)& count, sizeof(count));

	for (int i = 0; i < count; ++i) {
		usersList[i].serializeUser(ofs);
	}

	ofs.close();

}

void Manager::booksSort(char * option, char * type)
{
	if (strcmp(option, "title") == 0) {
		if (strcmp(type, "desc") == 0) {
			m_lib.sortBooksOfTitleDesc();
		}
		else {
			m_lib.sortBooksOfTitleAsc();
		}
	}

	if (strcmp(option, "author") == 0) {
		if (strcmp(type, "desc") == 0) {
			m_lib.sortBooksOfAuthorDesc();
		}
		else {
			m_lib.sortBooksOfAuthorAsc();
		}
	}

	if (strcmp(option, "year") == 0) {
		if (strcmp(type, "desc") == 0) {
			m_lib.sortBooksOfYearOfIssueDesc();
		}
		else {
			m_lib.sortBooksOfYearOfIssueAsc();
		}
	}

	if (strcmp(option, "rating") == 0) {
		if (strcmp(type, "desc") == 0) {
			m_lib.sortBooksOfRatingDesc();
		}
		else {
			m_lib.sortBooksOfRatingAsc();
		}
	}
	else {
		std::cout << "Ivalid option/type of sort." << std::endl;
	}
}

void Manager::booksAdd(const Book & book)
{
	m_lib.addBook(book);
}


void Manager::runProgram()
{
	char command[MAX_LEN_COMMAND];
	for (;;) {
		std::cin.getline(command, MAX_LEN_COMMAND);

		//Затваряне на текущо отворения файл.
		if (strcmp(command, "close") == 0) {
			closeFile();
		}

		if (strcmp(command, "help") == 0) {
			help();
		}

		//Вписване на потребител.
		if (strcmp(command, "login") == 0) {
			login();
		}

		//Излизне на потребител.
		if (strcmp(command, "logout") == 0) {
			logout();
		}

		//Прекратяване изпълнението на програмата.
		if (strcmp(command, "exit") == 0) {
			exit();
			break;
			return;
		}

		//Извеждане на информацията за книгите в библиотеката.
		if (strcmp(command, "books all") == 0) {
			if (isUser == true) {
				booksAll();
			}
			else {
				std::cout << "No logged user." << std::endl;
			}	
		}

		//Извеждане на информацията за дадена книга с персонален номер.
		if (strcmp(command, "books info") == 0) {
			unsigned idBook;
			std::cin >> idBook;
			booksInfo(idBook);
		}

		//Търсене на книга по даден критерии.
		if (strcmp(command, "books find") == 0) {
			if (isUser == true) {
				char option[MAX_LEN];
				char optionString[MAX_LEN];

				std::cin.getline(option, MAX_LEN);
				std::cin.getline(optionString, MAX_LEN);

				booksFind(option, optionString);

			}
			else {
				std::cout << "No logged user." << std::endl;
			}
		}

		//Сортиране на книгите.
		if (strcmp(command, "books sort") == 0) {
			if (isUser == true) {
				char option[MAX_LEN];
				char typeSort[MAX_LEN];

				std::cout << "Option sort: ";
				std::cin.getline(option, MAX_LEN);

				std::cout << "Type of sort: ";
				std::cin.getline(typeSort, MAX_LEN);

				booksSort(option, typeSort);

			}
			else {
				std::cout << "No logged user." << std::endl;
			}
		}

		//Добавяне на книга.
		if (strcmp(command, "books add") == 0) {
			if (isUser == true || isUser == true) {
				char author[MAX_LEN];
				char title[MAX_LEN];
				char genre[MAX_LEN];
				char description[MAX_LEN];
				unsigned year;
				unsigned rating;

				std::cout << "You want to add a new book. Please enter the book details first." << std::endl;

				std::cout << "Author: ";
				std::cin.getline(author, MAX_LEN);

				std::cout << "Title: ";
				std::cin.getline(title, MAX_LEN);

				std::cout << "Genre: ";
				std::cin.getline(genre, MAX_LEN);

				std::cout << "Description: ";
				std::cin.getline(description, MAX_LEN);

				std::cout << "Year of issue: ";
				std::cin >> year;

				std::cout << "Rating: ";
				std::cin >> rating;

				Book newBook(author, title, genre, description,year,rating);

				booksAdd(newBook);

			}
			else {
				std::cout << "No logged user/admin." << std::endl;
			}
		}

		//Добавяне на нов потребител.
		if (strcmp(command, "users add") == 0) {
			if (isUser == true || isAdmin == true) {
				char username[MAX_LEN];
				char password[MAX_LEN];

				std::cout << "Username: ";
				std::cin.getline(username, MAX_LEN);

				std::cout << "Password: ";
				std::cin.getline(password, MAX_LEN);

				//Извикване на функцията за добавяне на нов потребител.
				userAdd(username, password);
			}
			else {
				std::cout << "No logged user/admin." << std::endl;
			}
		}

		//Премахване на потребител.
		if (strcmp(command, "user remove") == 0) {
			if (isUser == true || isAdmin == true) {
				char usernameErase[MAX_LEN];
				std::cout << "Enter username: ";
				std::cin.getline(usernameErase, MAX_LEN);

				//Извикване на функцията userRemove().
				userRemove(usernameErase);
			}
			else{
				std::cout << "No logged user/admin." << std::endl;
			}
		}

	}
}


