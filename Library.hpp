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

	std::ifstream* ptrIfs=nullptr;
	std::ofstream* ptrOfs= nullptr;
	bool isIfstream = false;

private:
	
	void resizeLib();
	void copyFrom(const Library&);

public:
	//��������� �� addBook() �� �� ��������.
	//bool open(const char*/*, std::ifstream&*/);
	//void closeFile();
	//void save();
	////���� ������ �� ����� ���� ��� ������ �� �� ������ � ���?! �������!!
	//void saveas(const char*/*, std::ofstream&*/);
	//void help()const;
	//void exit()const;

	void cleanMemory();

	//������.
	unsigned getCountBook()const;
	unsigned getCapacityOfLibary()const;

	//������.������ �� ��� �� ���������.


	//�������� �� ���� �����.
	void addBook(const Book&);

	//��������� �� �����.
	void removeBook(const Book&);

	//��������� �� ������������ �� ����� ����� �� ������������.
	void booksAll();

	//��������� �� �������� ���������� �� ����� � ���������� �����
	void booksInfo(unsigned);

	//������� �� ����� �� ��������. 
	void booksFindTitile(char* title);

	//������� �� ����� �� �����. ����� �� ��������� � void, ������ ���� �� ��� ������� �������� ����� �� ���� �����.
	void booksFindAuthor(char* author);

	//������� �� ����� �� ������� ����. ����� �� ��������� � void, ������ ���� �� ��� ������� ����� � ������ ������� ����.
	void booksFindTag(char* tag);

	//��������� �� ������� ��� �������� ��� �� ������ �� ������������.
	void sortBooksOfYearOfIssueAsc();

	//��������� �� ������� � ��������  ��� �� ������ �� ������������.
	void sortBooksOfYearOfIssueDesc();

	//��������� �� ������� ��� �������� ��� �� �������.
	void sortBooksOfRatingAsc();

	//��������� �� ������� � �������� ��� �� �������.
	void sortBooksOfRatingDesc();

	//��������� �� ������� ��� �������� ��� �� ��������.
	void sortBooksOfTitleAsc();

	//��������� �� ������� � �������� ��� �� ��������.
	void sortBooksOfTitleDesc();

	//��������� �� ������� ��� �������� ��� �� ��� �� ������.
	void sortBooksOfAuthorAsc();

	//��������� �� ������� � �������� ��� �� ��� �� ������.
	void sortBooksOfAuthorDesc();

	//void runProgram();

	void writeBooksToFile( std::ofstream&);
	void readBooksFromFile(std::ifstream&);
};

#endif
