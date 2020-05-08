#include<iostream>
#include"Library.hpp"

unsigned Library::START_CAPACITY = 16;
const unsigned MAX_CMD_LEN = 7;
const unsigned MAX_FILE_LEN = 100;


Library::Library()
	:m_countBook(0), m_capacity(START_CAPACITY),m_books(nullptr)
{
}

Library::Library(unsigned count, unsigned capacity, Book * book)
	:m_countBook(count),m_capacity(capacity), m_books(nullptr)
{
	m_books = new (std::nothrow) Book[count];
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


//Как да направим файла да се отваря за четене и писане?
//bool Library::open(const char * fileName)
//{
//	std::cout << "How you want the file to be opened. Enter 'r' for reading or 'w' for writing." << std::endl;
//	char typeFile;
//	std::cin >> typeFile;
//	if (typeFile == 'r') {
//		std::ifstream ifs;
//		ifs.open(fileName, std::ios::binary);
//
//		//Проверка дали файлът е отворен успешно.
//		if (!ifs.is_open()) {
//			std::cout << "Failed to open!";
//			return false;
//		}
//		ptrIfs = &ifs;
//		readBooksFromFile(ifs);
//		//Ако файлът е отворен успешно.
//		std::cout << "Succesffully opened " << fileName << std::endl;
//		return true;
//	}
//	else if (typeFile == 'w') {
//		std::ofstream ofs;
//		ofs.open(fileName, std::ios::binary);
//
//		//Проверка дали файлът е отворен успешно.
//		if (!ofs.is_open()) {
//			std::cout << "Failed to open!";
//			return false;
//		}
//		ptrOfs = &ofs;
//
//		//Ако файлът е отворен успешно.
//		std::cout << "Succesffully opened " << fileName << std::endl;
//		return true;
//	}
//
//}
//
//void Library::closeFile()
//{
//	
//	cleanMemory();
//	if (ptrIfs == nullptr && ptrOfs == nullptr) {
//		std::cout << "Unvalid operation!" << std::endl;
//	}
//	if (ptrIfs != nullptr) {
//		ptrIfs->close();
//	}
//	if (ptrOfs != nullptr) {
//		ptrOfs->close();
//	}
//	std::cout << "Successfully closed file." << std::endl;
//	
//}
//
//void Library::save()
//{
//	//Щом сме извикали функцията save, дначи сме променяли файла. Затова използвам ptrOfs.
//	if (ptrOfs != nullptr) {
//		writeBooksToFile(*ptrOfs);
//	
//		std::cout << "Successfully saved." << std::endl;
//	}
//	std::cout << "You are trying to save a file that has not been modified" << std::endl;
//	
//}
//
//void Library::saveas(const char * name) {
//	std::ofstream ofs(name, std::ios::binary);
//
//	if (!ofs.is_open()) {
//		std::cout << "Not save " << name << " as file.";
//		return;
//	}
//	writeBooksToFile(ofs);
//
//	//затваряне на файла, след като сме писали в него.
//	ofs.close();
//
//}
//
//void Library::help() const
//{
//	std::cout << "The following commands are supported:" << std::endl
//		<< "open<file> " << '\t' << "opens<file>";
//	std::cout << "close" << '\t' << "close currently opened file" << std::endl
//		<< "save" << '\t' << "saves the currently opened file" << std::endl
//		<< "saveas<file>" << '\t' << "saves the currently open file in <file>" << std::endl
//		<< "help" << '\t' << "prints this information" << std::endl
//		<< "exit" << '\t' << "exit the program" << std::endl;
//}
//
//void Library::exit() const
//{
//	std::cout << "Exit the program!" << std::endl;
//	
//}

void Library::addBook(const Book & newBook)
{
	if (m_countBook >= m_capacity) {
		resizeLib();
	}
	m_books[m_countBook++] = newBook;
}

void Library::removeBook(const Book & book)
{
	//TODO: make it work
}

void Library::booksAll()
{
	for (int i = 0; i < m_countBook; ++i) {
		m_books[i].print();
	}
}

void Library::booksInfo(unsigned id)
{
	for (int i = 0; i < m_countBook; ++i) {
		if (m_books[i].getID() == id) {
			std::cout << "Author: " << m_books[i].getName() << std::endl
				<< "Title: " << m_books[i].getTitle() << std::endl
				<< "Genre: " << m_books[i].getGenre() << std::endl
				<< "Description: " << m_books[i].getDescription() << std::endl
				<< "Year of issue: " << m_books[i].getYearOfIssue() << std::endl
				<< "Rating: " << m_books[i].getRating() << std::endl
				<< "ID: " << m_books[i].getID() << std::endl;
		}
	}
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

			////Връщане на книгата като резултат, защото потребителят може да иска да я вземе.
			//return m_books[i];
			
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
	for (int i = 0; i < m_countBook - 1; ++i) {
		for (int j = i + 1; j < m_countBook; ++j) {
			if (strcmp(m_books[i].getTitle(), m_books[j].getTitle()) > 0) {
				/*char tempTitle[MAX_FILE_LEN];
				strcpy(tempTitle, m_books[i].getTitle());
				strcpy(m_books[i].getTitle(), m_books[j].getTitle());
				strcpy(m_books[j].getTitle(), tempTitle);*/

				unsigned lenTemp = strlen(m_books[i].getTitle());
				char* tempTitle = new(std::nothrow) char[lenTemp+1];
				if (tempTitle == nullptr) {
					std::cout << "Not enought memory in sortBooksOfTitleAsc(). Error! " << std::endl;
					return;
				}
				strcpy(tempTitle, m_books[i].getTitle());
				m_books[i].setTitle(m_books[j].getTitle());
				m_books[j].setTitle(tempTitle);

				delete[] tempTitle;
			}
		}
	}
}

void Library::sortBooksOfTitleDesc()
{
	for (int i = 0; i < m_countBook - 1; ++i) {
		for (int j = i + 1; j < m_countBook; ++j) {
			if (strcmp(m_books[i].getTitle(), m_books[j].getTitle()) < 0) {

				unsigned lenTemp = strlen(m_books[i].getTitle());

				char* tempTitle = new(std::nothrow) char[lenTemp + 1];
				if (tempTitle == nullptr) {
					std::cout << "Not enought memory in sortBooksOfTitleDesc(). Error! " << std::endl;
					return;
				}

				strcpy(tempTitle, m_books[i].getTitle());
				m_books[i].setTitle(m_books[j].getTitle());
				m_books[j].setTitle(tempTitle);

				delete[] tempTitle;
			}
		}
	}
}

void Library::sortBooksOfAuthorAsc()
{
	for (int i = 0; i < m_countBook - 1; ++i) {
		for (int j = i + 1; j < m_countBook; ++j) {
			if (strcmp(m_books[i].getName(), m_books[j].getName()) > 0) {
				

				unsigned lenTemp= strlen(m_books[i].getTitle());
				char* tempAuthor = new(std::nothrow) char[lenTemp + 1];
				if (tempAuthor == nullptr) {
					std::cout << "Not enought memory in sortBooksOfTitleAsc(). Error! " << std::endl;
					return;
				}
				strcpy(tempAuthor, m_books[i].getTitle());
				m_books[i].setTitle(m_books[j].getTitle());
				m_books[j].setTitle(tempAuthor);

				delete[] tempAuthor;
			}
		}
	}
}

void Library::sortBooksOfAuthorDesc()
{
	for (int i = 0; i < m_countBook - 1; ++i) {
		for (int j = i + 1; j < m_countBook; ++j) {
			if (strcmp(m_books[i].getName(), m_books[j].getName()) < 0) {

				unsigned lenTemp = strlen(m_books[i].getTitle());
				char* tempAuthor = new(std::nothrow) char[lenTemp + 1];
				if (tempAuthor == nullptr) {
					std::cout << "Not enought memory in sortBooksOfTitleAsc(). Error! " << std::endl;
					return;
				}
				strcpy(tempAuthor, m_books[i].getTitle());
				m_books[i].setTitle(m_books[j].getTitle());
				m_books[j].setTitle(tempAuthor);

				delete[] tempAuthor;
			}
		}
	}
}

//void Library::runProgram()
//{
//	/*char input[MAX_CMD_LEN];
//	char fileName[MAX_FILE_LEN];
//
//	bool isOpenedFile = false;
//	for (;;) {//безкраен цикъл
//		std::cin >> input;
//		if (my_strcmp(input, "open") == 0) {
//			std::cin >> fileName;
//			isOpenedFile=open(fileName);
//		}
//		if (isOpenedFile == true) {
//			if (my_strcmp(input, "close")==0) {
//				close();
//			}
//			else if (my_strcmp(input, "save")==0) {
//				save();
//			}
//			else if (my_strcmp(input, "saveas")==0) {
//				std::cin >> fileName;
//				saveas(fileName);
//			}
//			else if (my_strcmp(input, "help") == 0) {
//				help();
//			}
//			else if (my_strcmp(input, "exit") == 0) {
//				exit();
//			}
//			else {
//				std::cout << "Unknown command! Command 'hepl' will help you." << std::endl;
//			}
//		}
//		std::cout < "Try again to open file." << std::endl;
//	}*/
//
//	std::cout << "do to work!" << std::endl;
//}

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

	cleanMemory();

	m_books = new(std::nothrow) Book[m_capacity];
	if (m_books == nullptr) {
		std::cout << "Error!" << std::endl;
	}

	for (unsigned i = 0; i < m_countBook; ++i) {
		m_books[i].readBookFromFile(ifs);
	}
}

