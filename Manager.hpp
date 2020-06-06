#ifndef __MANAGER_HPP
#define __MANAGER_HPP

#include<fstream>
#include "Library.hpp"
#include "User.hpp"

class Manager {
private:
	Library m_lib;

public:
	static unsigned const MAX_LEN_COMMAND = 20;//Константа за максимална дължина на команда.
	static unsigned const MAX_LEN = 50;

	//Променлива, която пази името на файла, с който е работено, за да изпилъни след това save() на същия файл.
	char* m_nameFile = nullptr;

	//Дали има успешно отворен файл.
	bool isSuccessfullyOpenFile = false;

	//Променлива, която пази дали има упсешно влязъл потребител.
	bool isUser =false;
	bool isAdmin = true;//Защото винаги има регистриран по подразбиране администратор.
	

	std::ifstream* ptrIfs = nullptr;
	std::ofstream* ptrOfs = nullptr;
	

	void open(char *);
	void closeFile();
	void save();
	void saveAs(char*);
	void help() const;

	void login();
	void exit();
	void logout();
	void booksAll();

	//Извеждане на информацията за книга с даден номер.
	void booksInfo(unsigned ID);

	//Търсене на книга по определен критерии и стойност на критерия.
	void booksFind(char* option, char* optionString);

	//Добавяне на потребител.
	void userAdd(char* username, char* password);

	//Премахване на потребител.
	void userRemove(char* username);

	//Прамахване на книга.
	void booksRemove(const Book&);

	//Сортиране на книгите по даден критерии. По подразбиране сортирането ще е във възходящ ред.
	void booksSort(char* option, char*type = "asc");

	//Добавяне на книга.
	void booksAdd(const Book&);

	//Стартиране на програмата. 
	void runProgram();
};


#endif
