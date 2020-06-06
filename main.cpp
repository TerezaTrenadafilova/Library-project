#pragma warning(disable:4996) //За да работи правилно strcpy().
#include<iostream>
#include "Book.hpp"
#include"User.hpp"
#include"Tag.hpp"
#include"Manager.hpp"
#include"Tests.hpp"


int main() {

	Book b1("Ivan Vazov", "Pod igoto", "roman", "description", 1892, 123);
	std::ofstream ofs1("Library.bin", std::ios::out | std::ios::binary);
	if (!ofs1.is_open()) {
		return 1;
	}
	unsigned countB = 1;
	unsigned capacity = 2;
	ofs1.write((const char*)& countB, sizeof(countB));
	ofs1.write((const char*)& capacity, sizeof(capacity));
	b1.writeBookToFile(ofs1);
	ofs1.close();
	
	User u1("Ivan", "123");
	User u2("Ani", "7414");
	std::ofstream ofs("Users.bin", std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		return 1;
	}
	unsigned count = 2;
	ofs.write((const char*)& count, sizeof(count));
	u1.serializeUser(ofs);
	u2.serializeUser(ofs);
	ofs.close();
	
	Manager m;
	m.runProgram();

	return 0;
}