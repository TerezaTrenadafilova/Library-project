#pragma warning(disable:4996)
#include<iostream>
#include<cstring>
#include"User.hpp"

User::User()
	:m_username(nullptr),m_password(nullptr)
{
	//Не знам дали тук трябва да напарвя потребителя по подразбиране. Помисли!
	setUsername("admin");
	setPassword("i<3c++");
}

User::User(char *name, char * password)
	:m_username(nullptr),m_password(nullptr)
{
	setUsername(name);
	setPassword(password);
}

User::User(const User & other)
{
	if (this != &other) {
		copyFrom(other);
	}
}

User & User::operator=(const User & other)
{
	if (this!= &other) {
		cleanMemory();
		copyFrom(other);
	}
	return *this;
}

User::~User()
{
	cleanMemory();
}

void User::copyFrom(const User &other)
{
	setUsername(other.m_username);
	setPassword(other.m_password);
}

void User::cleanMemory()
{
	delete[] m_username;
	delete[] m_password;
}

void User::setUsername(char * name)
{
	m_username = new(std::nothrow) char[strlen(name) + 1];
	if (m_username == nullptr) {
		std::cout << "Not enought memory for username! Error!" << std:: endl;
		return;
	}
	strcpy(m_username, name);
}

void User::setPassword(char * password)
{
	m_password = new(std::nothrow) char[strlen(password) + 1];
	if (m_password == nullptr) {
		std::cout << "Not enought memory fo password! Error!" << std::endl;
		return;
	}
	strcpy(m_password, password);
}

char * User::getUsername() const
{
	return m_username;
}

char * User::getPassword() const
{
	return m_password;
}

void User::serializeUser(std::ofstream & ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	unsigned lenName = strlen(m_username);
	ofs.write((const char*)& lenName, sizeof(lenName));
	ofs.write(m_username, lenName);

	unsigned lenPassword = strlen(m_password);
	ofs.write((const char*)& lenPassword, sizeof(lenPassword));
	ofs.write(m_password, lenPassword);
}

void User::deserializeUser(std::ifstream & ifs)
{
	if (!ifs.is_open()) {
		std::cout << "File is not open." << std::endl;
		return;
	}
	unsigned lenName = 0;
	ifs.read((char*)& lenName, sizeof(lenName));
	m_username = new(std::nothrow) char[lenName + 1];
	if (m_username) {
		ifs.read(m_username, lenName);
		m_username[lenName] = '\0';
	}
	else {
		std::cout << "Not enought memory for username in deserialize!" << std::endl;
	}

	unsigned lenPassword = 0;
	ifs.read((char*)& lenPassword, sizeof(lenPassword));
	m_password = new(std::nothrow) char[lenPassword + 1];
	if (m_password) {
		ifs.read(m_password, lenPassword);
		m_password[lenPassword] = '\0';
	}
	else {
		std::cout << "Not enought memory for password in deserialize." << std::endl;
	}

}
