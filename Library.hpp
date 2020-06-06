#ifndef __LIBRARY_HPP
#define __LIBRARY_HPP

#include<fstream>
#include "Book.hpp"


class Library {
private:
	unsigned m_countBook;
	unsigned m_capacity;
	Book* m_books;

public:
	static unsigned START_CAPACITY;

	Library();
	Library(unsigned, unsigned, Book*);
	Library(const Library& );
	Library& operator = (const Library& );
	~Library();

	//std::ifstream* ptrIfs=nullptr;
	//std::ofstream* ptrOfs= nullptr;
	//bool isIfstream = false;

private:
	
	void resizeLib();
	void copyFrom(const Library&);

public:
	void cleanMemory();//Публична функиция, за да се извиква при въвеждане на команда close.

	//Гетъри.
	unsigned getCountBook()const;
	unsigned getCapacityOfLibary()const;

	//Добавяне на нова книга.
	void addBook(const Book&);

	//Изтриване на книга.
	void removeBook(const Book&);

	//Извеждане на информацията за всяка книга от библиотеката.
	void booksAll();

	//Извеждане на подробна информация за книга с персонален номер
	void booksInfo(unsigned);

	//Търсене на книга по заглавие. 
	void booksFindTitile(char* title);

	//Търсене на книга по автор. Типът на функцията е void, защото може да има няколко различни книги от един автор.
	void booksFindAuthor(char* author);

	//Търсене на книга по ключова дума. Типът на функцията е void, защото може да има няколко книги с такава ключова дума.
	void booksFindTag(char* tag);

	//Сортиране на книгите във възходящ ред по година на производство.
	void sortBooksOfYearOfIssueAsc();

	//Сортиране на книгите в низходящ  ред по година на производство.
	void sortBooksOfYearOfIssueDesc();

	//Сортиране на книгите във възходящ ред по рейтинг.
	void sortBooksOfRatingAsc();

	//Сортиране на книгите в низходящ ред по рейтинг.
	void sortBooksOfRatingDesc();

	//Сортиране на книгите във възходящ ред по заглавие.
	void sortBooksOfTitleAsc();

	//Сортиране на книгите в низходящ ред по заглавие.
	void sortBooksOfTitleDesc();

	//Сортиране на книгите във възходящ ред по име на автора.
	void sortBooksOfAuthorAsc();

	//Сортиране на книгите в низходящ ред по име на автора.
	void sortBooksOfAuthorDesc();

	//void runProgram();

	void writeBooksToFile( std::ofstream&);
	void readBooksFromFile(std::ifstream&);
};

#endif
