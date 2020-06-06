#ifndef __MANAGER_HPP
#define __MANAGER_HPP

#include<fstream>
#include "Library.hpp"
#include "User.hpp"

class Manager {
private:
	Library m_lib;

public:
	static unsigned const MAX_LEN_COMMAND = 20;//��������� �� ���������� ������� �� �������.
	static unsigned const MAX_LEN = 50;

	//����������, ����� ���� ����� �� �����, � ����� � ��������, �� �� �������� ���� ���� save() �� ����� ����.
	char* m_nameFile = nullptr;

	//���� ��� ������� ������� ����.
	bool isSuccessfullyOpenFile = false;

	//����������, ����� ���� ���� ��� ������� ������ ����������.
	bool isUser =false;
	bool isAdmin = true;//������ ������ ��� ����������� �� ������������ �������������.
	

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

	//��������� �� ������������ �� ����� � ����� �����.
	void booksInfo(unsigned ID);

	//������� �� ����� �� ��������� �������� � �������� �� ��������.
	void booksFind(char* option, char* optionString);

	//�������� �� ����������.
	void userAdd(char* username, char* password);

	//���������� �� ����������.
	void userRemove(char* username);

	//���������� �� �����.
	void booksRemove(const Book&);

	//��������� �� ������� �� ����� ��������. �� ������������ ����������� �� � ��� �������� ���.
	void booksSort(char* option, char*type = "asc");

	//�������� �� �����.
	void booksAdd(const Book&);

	//���������� �� ����������. 
	void runProgram();
};


#endif
