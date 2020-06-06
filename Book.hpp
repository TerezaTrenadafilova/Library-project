#ifndef __BOOK_HPP
#define __BOOK_HPP

#include<fstream>
#include<cstring>
#include "Tag.hpp"
//Всички за този клас е тествано и работи правилно! :)

class Book {
private:
	char* m_name;
	char* m_title;
	char* m_genre;
	char* m_description;
	unsigned m_yearOfIssue;
	
	Tag* m_tags;
	unsigned m_numberTag;
	unsigned m_capacityTag;

	
	unsigned m_rating;
	//Уникален идентификационен номер на книга.
	unsigned m_bookID;

public:
	static unsigned m_ID;
	static const unsigned startCapacity = 8;



	Book();
	Book(char*, char*);
	Book(char*, char*, char*, char*, unsigned, unsigned, Tag* = nullptr, unsigned = 0, unsigned = 0, unsigned= m_ID);
	Book(char*, char*, char*, char*, unsigned, Tag*,unsigned,unsigned, unsigned); //последната променлива я няма за ID
	Book(const Book&);
	Book& operator=(const Book&);
	~Book();

public:
	//сетъри
	void setAuthor(char*);
	void setTitle(char*);
	void setGenre(char*);
	void setDescription(char*);
	void setYearOfIssue(unsigned);
	
	void setKeywords(Tag*);
	void setNumberTag(unsigned);
	void setCapacityTag(unsigned);
	
	void setRating(unsigned);
	

	//гетъри
	char* getName()const;
	char* getTitle()const;
	char* getGenre()const;
	char* getDescription()const;
	unsigned getYearOfIssue()const;

	Tag* getKeywords()const;
	unsigned getNumberTag() const;
	unsigned getCapacityTag() const;
	
	unsigned getRating()const;
	/*static*/ unsigned getID();

	//print- функция
	void print() const;

	//Извеждане на пълна информация за книгата.
	void printAllInfo() const;

	//записване на книга във файл
	void writeBookToFile( std::ofstream&);

	//четене на информация за дадена книва от файл
	void readBookFromFile( std::ifstream&);

	//Предефиниран оператор ==
	bool operator==(const Book&);

private:
	void copyFrom(const Book&);
	void cleanMemory();

};


#endif