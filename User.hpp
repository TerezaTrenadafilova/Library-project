#ifndef __USER_HPP
#define __USER_HPP

#include<fstream>

class User {
private:
	char* m_username;
	char* m_password;
	//���� �� ������, ��� ���� ������ �����������.

public:
	User();
	User(char*, char*);
	User(const User&);
	User& operator=(const User&);
	~User();

private:
	void copyFrom(const User&);
	void cleanMemory();

public:
	//������
	void setUsername(char*);
	void setPassword(char*);

	//������
	char* getUsername()const;
	char* getPassword() const;//���� ���� ������ � ������� � ������ ��� � ������� private!!!

	//��������� �� ����������� � ������� ����.
	void serializeUser(std::ofstream&) const;

	//������ �� ���������� �� ������� ����.
	void deserializeUser(std::ifstream&);
};

#endif
