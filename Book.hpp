#ifndef __BOOK_HPP
#define __BOOK_HPP

#include<fstream>
#include<cstring>
#include "Tag.hpp"
//������ �� ���� ���� � �������� � ������ ��������! :)

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
	//�������� ���������������� ����� �� �����.
	unsigned m_bookID;

public:
	static unsigned m_ID;
	static const unsigned startCapacity = 8;



	Book();
	Book(char*, char*);
	Book(char*, char*, char*, char*, unsigned, unsigned, Tag* = nullptr, unsigned = 0, unsigned = 0, unsigned= m_ID);
	Book(char*, char*, char*, char*, unsigned, Tag*,unsigned,unsigned, unsigned); //���������� ���������� � ���� �� ID
	Book(const Book&);
	Book& operator=(const Book&);
	~Book();

public:
	//������
	void setAuthor(char*);
	void setTitle(char*);
	void setGenre(char*);
	void setDescription(char*);
	void setYearOfIssue(unsigned);
	
	void setKeywords(Tag*);
	void setNumberTag(unsigned);
	void setCapacityTag(unsigned);
	
	void setRating(unsigned);
	

	//������
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

	//print- �������
	void print() const;

	//��������� �� ����� ���������� �� �������.
	void printAllInfo() const;

	//��������� �� ����� ��� ����
	void writeBookToFile( std::ofstream&);

	//������ �� ���������� �� ������ ����� �� ����
	void readBookFromFile( std::ifstream&);

	//������������ �������� ==
	bool operator==(const Book&);

private:
	void copyFrom(const Book&);
	void cleanMemory();

};


#endif