#pragma warning(disable:4996)//За да работи правилно strcpy()
#include <iostream>
#include<fstream>
#include "Book.hpp"

unsigned Book::m_ID = 0;

Book::Book()
	:m_name(nullptr)
	, m_title(nullptr)
	, m_genre(nullptr)
	, m_description(nullptr)
	, m_yearOfIssue(0)
	, m_tags(nullptr)
	, m_numberTag(0)
	, m_capacityTag(startCapacity)
	,m_rating(0)
	//,m_bookID(m_ID)
{
	m_tags = new(std::nothrow) Tag[m_capacityTag];
	if (m_tags == nullptr) {
		std::cout << "Not enought memory for tags. Error!" << std::endl << std::endl;
		return;
	}
	/*m_bookID = m_ID;
	++m_ID;*/ //Този конструктор го използваме при създване на tempBook при сортировките и затова не увеличаваме id.
}

//Този конструщтор го използвам, когато искам една книга да бъде изтрита.
//За това няма ++m_ID.
Book::Book(char *name, char * title)
	:m_name(nullptr)
	,m_title(nullptr)
	, m_genre(nullptr)
	, m_description(nullptr)
	, m_yearOfIssue(0)
	, m_tags(nullptr)
	, m_numberTag(0)
	, m_capacityTag(startCapacity)
	, m_rating(0)
	//,m_bookID(m_ID)
{
	m_tags = new(std::nothrow) Tag[m_capacityTag];
	if (m_tags == nullptr) {
		std::cout << "Not enought memory for tags. Error!" << std::endl << std::endl;
		return;
	}
	setAuthor(name);
	setTitle(title);
	m_bookID = m_ID;
	++m_ID;
}

//Не знам дали ще работи правилно. По-скоро дали е написано провилно.
Book::Book(char * name, char * title, char * genre, char * description, unsigned year, unsigned rating, Tag *, unsigned, unsigned, unsigned)
	:m_name(nullptr)
	, m_title(nullptr)
	, m_genre(nullptr)
	, m_description(nullptr)
	, m_yearOfIssue(year)
	, m_rating(rating)
{
	setAuthor(name);
	setTitle(title);
	setGenre(genre);
	setDescription(description);
	setYearOfIssue(year);
	setRating(rating);

	m_tags = new(std::nothrow) Tag[m_capacityTag];
	if (m_tags == nullptr) {
		std::cout << "Not enought memory for tags. Error!" << std::endl << std::endl;
		return;
	}

	m_bookID = m_ID;
	//Увеличаваме броя ID.
	++m_ID;
}

Book::Book(char *name, char * title, char * genre, char * dеscpription,unsigned year, Tag* tags, unsigned numberTag, unsigned capacity, unsigned rating)
	:m_name(nullptr)
	,m_title(nullptr)
	, m_genre(nullptr)
	, m_description(nullptr)
	, m_yearOfIssue(year)
	, m_tags(nullptr)
	, m_numberTag(numberTag)
	, m_capacityTag(capacity)
	, m_rating(rating)

{
	this->setAuthor(name);
	this->setTitle(title);
	this->setGenre(genre);
	this->setDescription(dеscpription);
	//инициялизация на ключовите думи
	m_tags = new(std::nothrow) Tag[m_capacityTag];
	if (m_tags == nullptr) {
		std::cout << "not enought memory to set tags." << std::endl;
		return;
	}
	for (int i = 0; i < m_numberTag; ++i) {
		m_tags[i] = tags[i];
	}
	m_bookID = m_ID;
	++m_ID;

}

Book::Book(const Book & other)
{
	if (this != &other) {
		copyFrom(other);
	}
}

Book & Book::operator=(const Book & other)
{
	if (this != &other) {
	//	cleanMemory();
		copyFrom(other);
	}
	return *this;
}

Book::~Book()
{
	cleanMemory();
}

void Book::setAuthor(char * name)
{
	//delete[] m_name;

	m_name = new(std::nothrow)char[strlen(name) + 1];
	if (m_name == nullptr) {
		std::cout << "Not enought memory for author's name! Error!" << std::endl;
		return;
	}
	strcpy(m_name, name);
}

void Book::setTitle(char * title)
{
//	delete[] m_title;

	m_title = new(std::nothrow) char[strlen(title) + 1];
	if (m_title == nullptr) {
		std::cout << "Not enought memory for title of the book! Error!" << std::endl;
		return;
	}
	strcpy(m_title, title);
}

void Book::setGenre(char * genre)
{
	//delete[] m_genre;
	m_genre = new(std::nothrow) char[strlen(genre) + 1];
	if (m_genre == nullptr) {
		std::cout << "Not enought memory for genre of the book! Error!" << std::endl;
		return;
	}
	strcpy(m_genre, genre);
}

void Book::setDescription(char * description)
{
	//delete[] m_description;

	m_description = new(std::nothrow) char[strlen(description) + 1];
	if (m_description == nullptr) {
		std::cout << "Not enought memory for discription of the book! Error!" << std::endl;
		return;
	}
	strcpy(m_description, description);

}

void Book::setYearOfIssue(unsigned year)
{
	m_yearOfIssue = year;
}

void Book::setKeywords( Tag* tag)
{
	m_tags = new(std::nothrow) Tag[m_capacityTag];
	if (m_tags == nullptr) {
		std::cout << "not enought memory to set tags." << std::endl;
		return;
	}
	for (int i = 0; i < m_numberTag; ++i) {
		m_tags[i] = tag[i];
	}
}

void Book::setNumberTag(unsigned number)
{
	m_numberTag = number;
}

void Book::setCapacityTag(unsigned capacity)
{
	m_capacityTag = capacity;
}

void Book::setRating(unsigned rating)
{
	m_rating = rating;
}

char * Book::getName() const
{
	return m_name;
}

char * Book::getTitle() const
{
	return m_title;
}

char * Book::getGenre() const
{
	return m_genre;
}

char * Book::getDescription() const
{
	return m_description;
}

unsigned Book::getYearOfIssue() const
{
	return m_yearOfIssue;
}

Tag * Book::getKeywords() const
{
	return m_tags;
}

unsigned Book::getNumberTag() const
{
	return m_numberTag;
}

unsigned Book::getCapacityTag() const
{
	return m_capacityTag;
}

unsigned Book::getRating() const
{
	return m_rating;
}

unsigned Book::getID()
{
	return m_bookID;
}

void Book::print() const
{
	std::cout <<std::endl<< "Book information: " << std::endl;
	std::cout << "Author: " << m_name << std::endl
		<< "Titile: " << m_title << std::endl
		<< "Genre: " << m_genre << std::endl
		<< "ID: " << m_bookID << std::endl << std::endl;
}

void Book::printAllInfo() const
{
	std::cout << "Author: " << m_name << std::endl
		<< "Title: " << m_title << std::endl
		<< "Genre: " << m_genre << std::endl
		<< "Description: " << m_description << std::endl
		<< "Year of issue: " << m_yearOfIssue << std::endl
		<< "Rating: " << m_rating << std::endl
		<< "ID: " << m_bookID << std::endl << std::endl;
}

void Book::writeBookToFile(/*const Book & book,*/ std::ofstream & ofs)
{
	if (!ofs.is_open())
	{
		return;
	}

	unsigned lenName = strlen(m_name);
	ofs.write((const char*)&lenName, sizeof(lenName));

	ofs.write(m_name, lenName);

	unsigned lenTitle = strlen(m_title);
	ofs.write((const char*)&lenTitle, sizeof(unsigned));

	ofs.write(m_title, lenTitle);

	unsigned lenGenre = strlen(m_genre);
	ofs.write((const char*)&lenGenre, sizeof(unsigned));

	ofs.write(m_genre, lenGenre);

	unsigned lenDis = strlen(m_description);
	ofs.write((const char*)& lenDis, sizeof(lenDis));

	ofs.write(m_description, lenDis);

	ofs.write((const char*)& m_yearOfIssue, sizeof(unsigned));

	//ключовите думи. Трябва да ги промуниш да са масив от думи
	ofs.write((const char*)& m_numberTag, sizeof(m_numberTag));
	ofs.write((const char*)& m_capacityTag, sizeof(m_capacityTag));
	
	for (int i = 0; i < m_numberTag; ++i) {
		m_tags[i].serializeTag(ofs);
	}

	ofs.write((const char*)& m_rating, sizeof(unsigned));

	ofs.write((const char*)& m_bookID, sizeof(m_bookID));

	/*if (ofs.good()) {
		std::cout << "Siccessfully serialize!" << std::endl;
	}
	else {
		std::cout << "Serialize failed!" << std::endl;
	}*/
}

void Book::readBookFromFile( std::ifstream & ifs)
{
	if (!ifs.is_open())
	{
		return;
	}

	unsigned lenName = 0;
	ifs.read((char*)&lenName, sizeof(unsigned));
	m_name = new(std::nothrow) char[lenName + 1];
	if (m_name) {
		ifs.read(m_name, lenName);
		m_name[lenName] = '\0';
	}
	else {
		std::cout << "Not enought memory for name in deserialize method." << std::endl;
		return;
	}

	unsigned lenTitle = 0;
	ifs.read((char*)&lenTitle, sizeof(unsigned));
	m_title = new(std::nothrow) char[lenTitle + 1];
	if (m_title) {
		ifs.read(m_title, lenTitle);
		m_title[lenTitle] = '\0';
	}
	else {
		std::cout << "Not enought memory for title in deserialize method." << std::endl;
		return;
	}

	unsigned lenGenre = 0;
	ifs.read((char*)&lenGenre, sizeof(unsigned));
	m_genre = new(std::nothrow) char[lenGenre + 1];
	if (m_genre) {
		ifs.read(m_genre, lenGenre);
		m_genre[lenGenre] = '\0';
	}
	else {
		std::cout << "Not enought memory for genre in deserialize method." << std::endl;
		return;
	}

	unsigned lenDis = 0;
	ifs.read((char*)&lenDis, sizeof(unsigned));
	m_description = new(std::nothrow) char[lenDis + 1];
	if (m_description) {
		ifs.read(m_description, lenDis);
		m_description[lenDis] = '\0';
	}
	else {
		std::cout << "Not enought memory for discription in deserialize method." << std::endl;
		return;
	}

	ifs.read((char*)& m_yearOfIssue, sizeof(unsigned));

	/*unsigned lenKey = 0;
	ifs.read((char*)&lenKey, sizeof(unsigned));
	m_keywords = new(std::nothrow) char[lenKey + 1];
	if (m_keywords) {
		ifs.read(m_keywords, lenKey);
		m_keywords[lenKey] = '\0';
	}*/

	ifs.read((char*)& m_numberTag, sizeof(m_numberTag));
	ifs.read((char*)& m_capacityTag, sizeof(m_capacityTag));

	m_tags = new(std::nothrow) Tag[m_capacityTag];
	if (m_tags == nullptr) {
		std::cout << "Not enought memory for tags in deserialize book." << std::endl;
		return;
	}
	for (int i = 0; i < m_numberTag; ++i) {
		m_tags[i].deserializeTag(ifs);
	}

	ifs.read((char*)& m_rating, sizeof(unsigned));

	ifs.read((char*)& m_bookID, sizeof(m_bookID));

	/*if (ifs.good()) {
		std::cout << "Successfully deserialize!" << std::endl;
	}
	else {
		std::cout << "Deserialize failed!" << std::endl;
	}*/
}

bool Book::operator==(const Book & book)
{
	if (strcmp(m_name, book.m_name) == 0 && strcmp(m_title, book.m_title) == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Book::copyFrom(const Book & other)
{
	setAuthor(other.m_name);
	setTitle(other.m_title);
	setGenre(other.m_genre);
	setDescription(other.m_description);
	setYearOfIssue(other.m_yearOfIssue);
	setKeywords(other.m_tags);
	setRating(other.m_rating);
	m_bookID = other.m_bookID;
}

void Book::cleanMemory()
{
	delete[] m_name;	
	m_name = nullptr;
	
	delete[] m_title;
	m_title = nullptr;

	delete[] m_genre;
	m_genre = nullptr;

	delete[] m_description;
	m_description = nullptr;

	delete[] m_tags;
	m_tags = nullptr;
}


