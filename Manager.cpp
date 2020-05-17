#pragma warning(disable:4996)//За да работи правилно strcpy()
#include<iostream>
#include<cstring>
#include "Manager.hpp"

unsigned const MAX_LEN_COMMAND = 11;
unsigned const MAX_LEN = 50;

void Manager::open(char * fileName) 
{
	std::cout << "open fuction" << std::endl;
	//Потребителят има достъп само до файла на библиотеката с книгите.
	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		std::cout << "File is not open." << std::endl;
		return;
	}
	

	ptrIfs = &ifs;
	isSuccessfullyOpenFile = true;

	//Прочитане даннитеза книгите от файла в бибилиотека, в която се намира.
	m_lib.readBooksFromFile(ifs);

	if (ifs.good()) {
		std::cout << "Successfully opened file " << fileName << std::endl;
	}
	else {
		std::cout << "File is not readen." << std::endl;
	}
	

	ifs.close();

}

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

void Manager::save()
{
	std::ofstream ofs(m_nameFile, std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "The file is not saved." << std::endl;
		return;
	}
	m_lib.writeBooksToFile(ofs);
	if (ofs.good()) {
		std::cout << "Successfully saved " << m_nameFile << std::endl;
	}
	else {
		std::cout << "Save has failed. " << std::endl;
	}
}

void Manager::saveAs(char * newFileName)
{
	std::ofstream ofs(newFileName, std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		std::cout << "File is not open! Error";
		return;
	}

	m_lib.writeBooksToFile(ofs);

	if (ofs.good()) {
		std::cout << "Successfully saved another file " << newFileName << std::endl;
	}
	else {
		std::cout << "Unsuccessfully saved another file " << newFileName << std::endl;
	}
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

		std::ifstream ifs("User1.bin", std::ios::in | std::ios::binary);
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
	std::cout << "in user add" << std::endl;
	std::ifstream ifs("User1.bin", std::ios::in | std::ios::binary);

	
	if (!ifs.is_open()) {
		std::cout << "File is not open." << std::endl;
		return;
	}

	unsigned count = 0;

	//Прочитане на броя потребители от базата данни на потребителите.
	ifs.read((char*)& count, sizeof(count));
	
	User *usersList = new(std::nothrow) User[count+1];
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
	
	User newUser(username, password);

	//Добавяне на новия потребител.
	usersList[count] = newUser;
	
	++count;

	//Записване на новият списък с потребители.
	std::ofstream ofs("User1.bin", std::ios::out | std::ios::binary| std::ios::trunc);
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

void Manager::booksRemove(const Book & book)
{
	m_lib.removeBook(book);
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
		std::cout << "Enter command: ";
		std::cin.getline(command, MAX_LEN_COMMAND);

		//Отваряне на файл.
		if (strcmp(command, "open") == 0) {
			char fileName[MAX_LEN];
			std::cout << "file name: ";
			std::cin.getline(fileName, MAX_LEN);
			std::cout << "File name in function open is: " << fileName << std::endl;

			m_nameFile = new(std::nothrow) char[strlen(fileName) + 1];
			if (m_nameFile == nullptr) {
				std::cout << "Not enought memory for m_nameFile in open()." << std::endl;
			}
			strcpy(m_nameFile, fileName);

			open(fileName);

		}

		//Затваряне на текущо отворения файл.
		if (strcmp(command, "close") == 0) {
			if (isSuccessfullyOpenFile == true) {
				closeFile();
			}
			else {
				std::cout << "There is an unsuccessfully opened file." << std::endl;
			}
			
		}

		if (strcmp(command, "save") == 0) {
			if (isSuccessfullyOpenFile == true) {
				save();
			}
			else {
				std::cout << "There is an unsuccessfully opened file." << std::endl;
			}
		}

		if (strcmp(command, "saveas") == 0) {
			if (isSuccessfullyOpenFile == true) {
				char newNameFile[MAX_LEN];
				std::cin.getline(newNameFile, MAX_LEN);
				saveAs(newNameFile);
			}
			else {
				std::cout << "There is an unsuccessfully opened file." << std::endl;
			}
		}

		if (strcmp(command, "help") == 0) {
			if (isSuccessfullyOpenFile == true) {
				help();
			}
			else {
				std::cout << "There is an unsuccessfully opened file." << std::endl;
			}
		}

		//Вписване на потребител.
		if (strcmp(command, "login") == 0) {
			if (isSuccessfullyOpenFile == true) {
				login();
			}
			else {
				std::cout << "There is an unsuccessfully opened file." << std::endl;
			}
		}

		//Излизне на потребител.
		if (strcmp(command, "logout") == 0) {
			if (isSuccessfullyOpenFile == true) {
				logout();
			}
			else {
				std::cout << "There is an unsuccessfully opened file." << std::endl;
			}
			
		}

		//Прекратяване изпълнението на програмата.
		if (strcmp(command, "exit") == 0) {
			exit();
			break;
			return;
		}

		//Извеждане на информацията за книгите в библиотеката.
		if (strcmp(command, "books all") == 0) {
			if (isUser == true && isSuccessfullyOpenFile==true) {
				booksAll();
			}
			else {
				std::cout << "No logged user or there is an unsuccessfully opened file ." << std::endl;
			}	
		}

		//Извеждане на информацията за дадена книга с персонален номер.
		if (strcmp(command, "books info") == 0) {
			if (isSuccessfullyOpenFile == true) {
				unsigned idBook;
				std::cin >> idBook;
				booksInfo(idBook);
			}
			else {
				std::cout << "There is an unsuccessfully opened file." << std::endl;
			}
			
		}

		//Търсене на книга по даден критерии.
		if (strcmp(command, "books find") == 0) {
			if (isUser == true && isSuccessfullyOpenFile==true) {
				char option[MAX_LEN];
				char optionString[MAX_LEN];

				std::cin.getline(option, MAX_LEN);
				std::cin.getline(optionString, MAX_LEN);

				booksFind(option, optionString);

			}
			else {
				std::cout << "No logged user or there is an unsuccessfully opened file." << std::endl;
			}
		}

		//Сортиране на книгите.
		if (strcmp(command, "books sort") == 0) {
			if (isUser == true && isSuccessfullyOpenFile==true) {
				char option[MAX_LEN];
				char typeSort[MAX_LEN];

				std::cout << "Option sort: ";
				std::cin.getline(option, MAX_LEN);

				std::cout << "Type of sort: ";
				std::cin.getline(typeSort, MAX_LEN);

				booksSort(option, typeSort);

			}
			else {
				std::cout << "No logged user or there is an unsuccessfully opened file." << std::endl;
			}
		}

		//Добавяне на книга.
		if (strcmp(command, "books add") == 0) {
			if ((isUser == true || isUser == true) && isSuccessfullyOpenFile==true) {
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
				std::cout << "No logged user/admin or there is an unsuccessfully opened file." << std::endl;
			}
		}

		//Добавяне на нов потребител.
		if (strcmp(command, "users add") == 0) {
			if ((isUser == true || isAdmin == true) && isSuccessfullyOpenFile==true) {
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
				std::cout << "No logged user/admin or there is an unsuccessfully opened file." << std::endl;
			}
		}

		//Премахване на потребител.
		if (strcmp(command, "user remove") == 0) {
			if ((isUser == true || isAdmin == true) && isSuccessfullyOpenFile==true) {
				char usernameErase[MAX_LEN];
				std::cout << "Enter username: ";
				std::cin.getline(usernameErase, MAX_LEN);

				//Извикване на функцията userRemove().
				userRemove(usernameErase);
			}
			else{
				std::cout << "No logged user/admin or there is an unsuccessfully opened file." << std::endl;
			}
		}

		//Премахване на книга
		if (strcmp(command, "books remove") == 0) {
			if ((isUser == true || isAdmin == true) && isSuccessfullyOpenFile == true) {
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

				Book newBook(author, title, genre, description, year, rating);

				booksRemove(newBook);
			}
			else {
				std::cout << "No logged user/admin or there is an unsuccessfully opened file." << std::endl;
			}
		}

	}
}


