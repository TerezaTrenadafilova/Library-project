#ifndef __MANAGER_HPP
#define __MANAGER_HPP

#include<fstream>
#include "Library.hpp"
#include "User.hpp"

class Manager {
private:
	Library m_lib;

public:
	bool isUser =false;
	bool isAdmin = false;

	std::ifstream* ptrIfs = nullptr;
	std::ofstream* ptrOfs = nullptr;

	void closeFile();
	void help() const;

	//Не са тествани функциите.
	void login();
	void exit();
	void logout();
	void booksAll();
	void booksInfo(unsigned ID);

	//Тествай я отделно.
	void booksFind(char* option, char* optionString);

	void userAdd(char* username, char* password);
	void userRemove(char* username);

	//Не са тествани сортировките.
	void booksSort(char* option, char*type = "asc");

	//Добавяне на книга.
	void booksAdd(const Book&);

	//Не е тествана.
	void runProgram();
};


#endif
