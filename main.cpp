#pragma warning(disable:4996) //За да работи правилно strcpy().
#include<iostream>
#include "Book.hpp"
#include"User.hpp"
#include"Tag.hpp"
#include"Manager.hpp"

void testLibraryClass() {

	Book b1("Ivan Vazov", "Nemili nedragi", "povest", "za osvoboditelnoto dvijenie", 1884, 2);
	Book b2("Ivan Vazov", "Pod igoto", "roman", "za osvoboditelnoto dvijenie", 1894, 3);
	Book b3("Aleko Konstantinov", "BAy Ganyo", "roman", "Balgarska prosottia", 1906, 1);
	//b1.print();

	Library lib;
	std::cout << lib.getCountBook() << std::endl;
	lib.addBook(b1);
	lib.addBook(b2);
	lib.addBook(b3);

	/*lib.booksAll();
	std::cout << lib.getCountBook() << std::endl;*/
	lib.sortBooksOfAuthorDesc();//Тестване на всички въмжони сортировки.
	lib.booksAll();
	lib.removeBook(b1);
	std::cout << "After remove" << std::endl;
	lib.booksAll();
}

void testBookClass() {
	Book b1 = Book();
	b1.setAuthor("Aleko");
	std::cout << b1.getName() << "  year::" << b1.getYearOfIssue() << "  id::" << b1.getID() << std::endl;

	unsigned countTag = 2;
	
	Tag* tag = new(std::nothrow) Tag[countTag];
	if (tag == nullptr) {
		std::cout << "Not enought memory for tags." << std::endl;
		return;
	}
	
	tag[0].setTag("bulgari");
	tag[1].setTag("osvobojdenie");

	
	Book b2 ("Ivan Vazov", "Pod igoto", "roman", "za osvoboditelnoto dvijenie", 1894, tag, countTag,countTag, 1000000);
	std::cout << "print book info: " << std::endl;
	b2.print();

	std::ofstream ofs("Book.bin", std::ios::out | std::ios::binary);
	b2.writeBookToFile(ofs);
	ofs.close();

	b2.setTitle("Neili nedragi");
	std::cout << b2.getTitle() << std::endl;
	std::cout << "Book 1 id: " << b1.getID() << std::endl;
	std::cout << "Book 2 id: " << b2.getID() << std::endl;

	Book b3;
	std::cout << "Book 3 id: " << b3.getID() << std::endl;
	b3 = b2;

	std::ifstream ifs("Book.bin", std::ios::in | std::ios::binary);
	Book b4;
	b4.readBookFromFile(ifs);
	std::cout << "After deserialize b4:" << std::endl;
	b4.print();

	std::cout << "Book 3 info:" << std::endl;
	b3.print();
	std::cout << std::endl;
	//b1 = b2;
	//std::cout << "Book 1";
	//b1.print();
	//std::cout << "Book 2";
	//b2.print();

	
	delete[] tag;

}

void testUserClass() {
	User u1;
	u1.setUsername("ani123");
	u1.setPassword("123456789987654321");
	std::cout << "Username: " << u1.getUsername() << std::endl
		<< "Password: " << u1.getPassword() << std::endl;

	//Конструкторът без параметри - работи
	//Сетъри -работят
	//Гетъри - работят
	//Конструктор с параметри - работи
	//Коснтруктор за копиране- работи
	//Оператор = - работи


	User u2 = u1;
	std::cout << std::endl;
	std::cout << " User 2 username: " << u2.getUsername() << std::endl
		<< "User 2 password: " << u2.getPassword() << std::endl;

	User u3("User", "MyPassword123");
	std::cout << "User 3 username: " << u3.getUsername() << std::endl
		<< "User 3 password: " << u3.getPassword() << std::endl;

	User u4;
	u4 = u3;
	std::cout << "User 4 username: " << u4.getUsername() << std::endl
		<< "User 4 password: " << u4.getPassword() << std::endl;

}

void testTagClass() {
	Tag tag("super hero");
	std::cout << "Tag: " << tag.getTag() << std::endl;

	std::ofstream ofs("Tag.bin", std::ios::out | std::ios::binary);
	tag.serializeTag(ofs);
	ofs.close();

	std::ifstream ifs("Tag.bin", std::ios::in | std::ios::binary);
	Tag tag1;
	tag1.deserializeTag(ifs);
	ifs.close();
	std::cout << "Tag2: " << tag.getTag() << std::endl;
}

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