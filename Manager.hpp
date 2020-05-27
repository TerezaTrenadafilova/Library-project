#ifndef __MANAGER_HPP
#define __MANAGER_HPP

#include<fstream>
#include "Library.hpp"
#include "User.hpp"

class Manager {
private:
	Library m_lib;

public:
	//Променлива, която пази името на файла, с който е работено, за да изпилъни след това save() на същия файл.
	char* m_nameFile = nullptr;

	//Дали има успешно отворен файл.
	bool isSuccessfullyOpenFile = false;
	bool isUser =false;
	bool isAdmin = true;//Защото винаги има регистриран по подразбиране администратор.
	

	std::ifstream* ptrIfs = nullptr;
	std::ofstream* ptrOfs = nullptr;
	

	void open(char *);
	void closeFile();
	void save();
	void saveAs(char*);
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

	void booksRemove(const Book&);

	//Не са тествани сортировките.
	void booksSort(char* option, char*type = "asc");

	//Добавяне на книга.
	void booksAdd(const Book&);

	//Не е тествана.
	void runProgram();
};


#endif
