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

	//�� �� �������� ���������.
	void login();
	void exit();
	void logout();
	void booksAll();
	void booksInfo(unsigned ID);

	//������� � �������.
	void booksFind(char* option, char* optionString);

	void userAdd(char* username, char* password);
	void userRemove(char* username);

	//�� �� �������� ������������.
	void booksSort(char* option, char*type = "asc");

	//�������� �� �����.
	void booksAdd(const Book&);

	//�� � ��������.
	void runProgram();
};


#endif
