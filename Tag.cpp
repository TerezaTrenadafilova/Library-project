#pragma warning(disable:4996)
#include<iostream>

#include "Tag.hpp"

Tag::Tag()
	:m_name(nullptr)
{
}

Tag::Tag(char * name)
	:m_name(nullptr)
{
	setTag(name);
}

Tag::Tag(const Tag & other)
{
	if (this != &other) {
		copyFrom(other);
	}
}

Tag & Tag::operator=(const Tag & other)
{
	if (this != &other) {
		delete[] m_name;
		copyFrom(other.m_name);
	}
	return *this;
}

Tag::~Tag()
{
	delete[] m_name;
}

void Tag::setTag(char * name)
{
	m_name = new(std::nothrow) char[strlen(name) + 1];
	if (m_name == nullptr) {
		std::cout << "Not enought memory for set tag." << std::endl;
		return;
	}
	strcpy(m_name, name);
}

char * Tag::getTag() const
{
	return m_name;
}

void Tag::serializeTag(std::ofstream & ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	unsigned lenTag = strlen(m_name);
	ofs.write((const char*)& lenTag, sizeof(lenTag));
	ofs.write(m_name, lenTag);

	/*if (ofs.good()) {
		std::cout << "Successffuly serialize tag." << std::endl;
	}
	else {
		std::cout << "Serialize of tag failed!" << std::endl;
	}*/
}

void Tag::deserializeTag(std::ifstream & ifs)
{
	if (!ifs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	unsigned lenTag = 0;
	ifs.read((char*)& lenTag, sizeof(lenTag));
	m_name = new(std::nothrow) char[lenTag + 1];
	if (m_name) {
		ifs.read(m_name, lenTag);
		m_name[lenTag] = '\0';

	}
	else {
		std::cout << "Not enought memory for deserialize tag." << std::endl;
		return;
	}

	/*if (ifs.good()) {
		std::cout << "Successffuly deserialize of tag." << std::endl;
	}
	else {
		std::cout << "desrialize of tag failed." << std::endl;
	}*/
}

void Tag::copyFrom(const Tag & other)
{
	setTag(other.m_name);
}
