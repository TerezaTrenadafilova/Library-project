#pragma warning(disable:4996)
#include<iostream>
#include"Library.hpp"

unsigned Library::START_CAPACITY = 16;
//const unsigned MAX_CMD_LEN = 7;
//const unsigned MAX_FILE_LEN = 100;


Library::Library()
	:m_countBook(0), m_capacity(START_CAPACITY),m_books(nullptr)
{
	m_books = new(std::nothrow) Book[m_capacity];
	if (m_books == nullptr) {
		std::cout << "Not enought memory for books is library constructor. Error!" << std::endl;
	}

}

Library::Library(unsigned count, unsigned capacity, Book * book)
	:m_countBook(count),m_capacity(capacity), m_books(nullptr)
{
	m_books = new (std::nothrow) Book[m_capacity];
	if (m_books = nullptr) {
		std::cout << "Not enought memory for books! Error!" << std::endl;
		return;
	}
	for (unsigned i = 0; i < m_countBook; ++i) {
		m_books[i] = book[i];
	}
}

Library::Library(const Library & other)
{
	if (this != &other) {
		copyFrom(other);
	}
}

Library & Library::operator=(const Library &other)
{
	if (this != &other) {
		cleanMemory();
		copyFrom(other);
	}
	return *this;
}

Library::~Library()
{
	cleanMemory();
}

void Library::cleanMemory()
{
	delete[] m_books;
}

unsigned Library::getCountBook() const
{
	return m_countBook;
}

unsigned Library::getCapacityOfLibary() const
{
	return m_capacity;
}

void Library::resizeLib()
{
	unsigned newCapacity = m_capacity * 2;
	Book* newBooks = new (std::nothrow) Book[newCapacity];

	if (newBooks == nullptr) {
		std::cout << "Not enought memory for resize! Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_capacity; ++i) {
		newBooks[i] = m_books[i];
	}
	m_capacity = newCapacity;
	delete[] m_books;
	m_books = newBooks;
}

void Library::copyFrom(const Library & other)
{
	m_countBook = other.m_countBook;
	m_capacity = other.m_capacity;
	for (unsigned i = 0; i < m_countBook; ++i) {
		m_books[i] = other.m_books[i];
	}
}

void Library::addBook(const Book & newBook)
{
	
	if (m_countBook >= m_capacity) {
		resizeLib();
	}
	
	m_books[m_countBook] = newBook;
	++m_countBook;
	
}

void Library::removeBook(const Book & book)
{
	int posBook = -1;
	for (int i = 0; i < m_countBook; ++i) {
		if (m_books[i] == book) {
			posBook = i;
			break;
		}
	}

	//Проверка дали книгата, която искаме да бъде премахната съществува в библиотеката.
	if (posBook == -1) {
		std::cout << "The book \"" << book.getTitle() << "\" is not exist in library. " << std::endl;
		return;
	}

	std::cout << std::endl << "The book \"" << m_books[posBook].getTitle() << "\" has been removed." << std::endl << std::endl;
	//Премахване на книгата, като наредбавата на книгите не е от значение.
	m_books[posBook] = m_books[m_countBook - 1];
	--m_countBook;

}

void Library::booksAll()
{
	for (int i = 0; i < m_countBook; ++i) {
		m_books[i].print();
	}
}

void Library::booksInfo(unsigned id)
{
	int posOfBook = -1;

	//Проверка дали съществува книга с въведеното id.
	for (int i = 0; i < m_countBook; ++i) {
		if (m_books[i].getID() == id) {
			posOfBook = i;
			break; //Прекъсваме цикъла, защото всяка книга има уникален идентификационен номер.
		}
	}
	if (posOfBook == -1) {
		std::cout << std::endl << "The book with id " << id << " is not exist." << std::endl << std::endl;
		return;
	}

	/*for (int i = 0; i < m_countBook; ++i) {
		if (m_books[i].getID() == id) {
			std::cout << "Author: " << m_books[i].getName() << std::endl
				<< "Title: " << m_books[i].getTitle() << std::endl
				<< "Genre: " << m_books[i].getGenre() << std::endl
				<< "Description: " << m_books[i].getDescription() << std::endl
				<< "Year of issue: " << m_books[i].getYearOfIssue() << std::endl
				<< "Rating: " << m_books[i].getRating() << std::endl
				<< "ID: " << m_books[i].getID() << std::endl << std::endl;
		}
	}*/

	//Извеждане на пълната информация за книгата с id.
	m_books[posOfBook].printAllInfo();
}

void Library::booksFindTitile(char * title)
{
	bool isFind = false;
	for (int i = 0; i < m_countBook; ++i) {
		if (strcmp(title, m_books[i].getTitle()) == 0) {
			isFind = true;

			//Извеждане на информацията за книгата
			m_books[i].print();
			std::cout << std::endl;
		}
	}

	//Извеждане на съобщение, ако не е намерена книга
	if (isFind == false) {
		std::cout << "The book entitled \"" << title << "\" was not found." << std::endl;
	}
}

void Library::booksFindAuthor(char * author)
{
	bool isFind = false;

	for (int i = 0; i < m_countBook; ++i) {
		if (strcmp(author, m_books[i].getName()) == 0) {
			isFind = true;
			
			//Извеждане на информацията за намерената книга.
			m_books[i].print();
			std::cout << std::endl;
		}
	}

	//Извеждане на съобщение, ако не е намерена книга.
	if (isFind == false) {
		std::cout << "There are no books by the author " << author << " in the library." << std::endl;
	}
}

void Library::booksFindTag(char * tag)
{
	bool isFind = false;
	for (int i = 0; i < m_countBook; ++i) {
		for (int j = 0; j < m_books[i].getNumberTag(); ++i) {	

			Tag* tags = new(std::nothrow) Tag[m_books[i].getNumberTag()];
			if (tags == nullptr) {
				std::cout << "Not enought memory for tags in booksFindTag. Error!" << std::endl;
				return;
			}
			tags = m_books[i].getKeywords();

			//Преминаваме през всички ключови думи на поредната книга и ги сверяваме дали са като tag.
			if (strcmp(tag, tags[j].getTag()) == 0) {
				isFind = true;
				m_books[i].print();
				break;
			}
		}
	}

	//Ако не е намерена книга с исканата ключова дума.
	if (isFind == false) {
		std::cout << "No books found." << std::endl;
	}
}

void Library::sortBooksOfYearOfIssueAsc()
{
	for (int i = 0; i <m_countBook; ++i) {
		for (int j = 0; j < m_countBook - i - 1; ++j) {
			if (m_books[j].getYearOfIssue() > m_books[j + 1].getYearOfIssue()) {
				Book tempBook = m_books[j];
				m_books[j] = m_books[j + 1];
				m_books[j + 1] = tempBook;
			}
		}
	}
}

void Library::sortBooksOfYearOfIssueDesc()
{
	for (int i = 0; i <m_countBook; ++i) {
		for (int j = 0; j < m_countBook - i - 1; ++j) {
			if (m_books[j].getYearOfIssue() < m_books[j + 1].getYearOfIssue()) {
				Book tempBook = m_books[j];
				m_books[j] = m_books[j + 1];
				m_books[j + 1] = tempBook;
			}
		}
	}
}

void Library::sortBooksOfRatingAsc()
{
	for (int i = 0; i <m_countBook; ++i) {
		for (int j = 0; j < m_countBook - i - 1; ++j) {
			if (m_books[j].getRating() > m_books[j + 1].getRating()) {
				Book tempBook = m_books[j];
				m_books[j] = m_books[j + 1];
				m_books[j + 1] = tempBook;
			}
		}
	}
}

void Library::sortBooksOfRatingDesc()
{
	for (int i = 0; i <m_countBook; ++i) {
		for (int j = 0; j < m_countBook - i - 1; ++j) {
			if (m_books[j].getRating() < m_books[j + 1].getRating()) {
				Book tempBook = m_books[j];
				m_books[j] = m_books[j + 1];
				m_books[j + 1] = tempBook;
			}
		}
	}
}

void Library::sortBooksOfTitleAsc()
{
	for (int i = 0; i < m_countBook; ++i) {
		for (int j = i + 1; j < m_countBook; ++j) {
			if (strcmp(m_books[i].getTitle(), m_books[j].getTitle()) > 0) {
				

				/*unsigned lenTemp = strlen(m_books[i].getTitle());
				char* tempTitle = new(std::nothrow) char[lenTemp+1];
				if (tempTitle == nullptr) {
					std::cout << "Not enought memory in sortBooksOfTitleAsc(). Error! " << std::endl;
					return;
				}
				strcpy(tempTitle, m_books[i].getTitle());
				m_books[i].setTitle(m_books[j].getTitle());
				m_books[j].setTitle(tempTitle);

				delete[] tempTitle;*/

				Book tempBook;
				tempBook = m_books[i];
				m_books[i] = m_books[j];
				m_books[j] = tempBook;
			}
		}
	}
}

void Library::sortBooksOfTitleDesc()
{
	for (int i = 0; i < m_countBook; ++i) {
		for (int j = i + 1; j < m_countBook; ++j) {
			if (strcmp(m_books[i].getTitle(), m_books[j].getTitle()) < 0) {
				Book tempBook;
				tempBook = m_books[i];
				m_books[i] = m_books[j];
				m_books[j] = tempBook;
				
			}
		}
	}
}

void Library::sortBooksOfAuthorAsc()
{
	for (int i = 0; i < m_countBook - 1; ++i) {
		for (int j = i + 1; j < m_countBook; ++j) {
			if (strcmp(m_books[i].getName(), m_books[j].getName()) > 0) {
				Book tempBook;
				tempBook = m_books[i];
				m_books[i] = m_books[j];
				m_books[j] = tempBook;
			}
		}
	}
}

void Library::sortBooksOfAuthorDesc()
{
	for (int i = 0; i < m_countBook - 1; ++i) {
		for (int j = i + 1; j < m_countBook; ++j) {
			if (strcmp(m_books[i].getName(), m_books[j].getName()) < 0) {

				Book tempBook;
				tempBook = m_books[i];
				m_books[i] = m_books[j];
				m_books[j] = tempBook;
			}
		}
	}
}


void Library::writeBooksToFile( std::ofstream & ofs)
{
	if (!ofs.is_open())
	{
		return;
	}

	ofs.write((const char*)& m_countBook, sizeof(m_countBook));
	ofs.write((const char*)& m_capacity, sizeof(m_capacity));

	for (unsigned i = 0; i < m_countBook; ++i) {
		m_books[i].writeBookToFile(ofs);
	}

	/*if (ofs.good()) {
		std::cout << "Successfully serialize!" << std::endl;
	}
	else {
		std::cout << "Serialize failed!" << std::endl;
	}*/
}

void Library::readBooksFromFile(std::ifstream & ifs)
{
	if (!ifs.is_open())
	{
		return;
	}

	ifs.read((char*)& m_countBook, sizeof(m_countBook));
	ifs.read((char*)& m_capacity, sizeof(m_capacity));

	//cleanMemory();

	m_books = new(std::nothrow) Book[m_capacity];
	if (m_books == nullptr) {
		std::cout << "Error!" << std::endl;
	}

	for (unsigned i = 0; i < m_countBook; ++i) {
		m_books[i].readBookFromFile(ifs);
	}
}

