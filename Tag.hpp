#ifndef __TAG_HPP
#define __TAG_HPP

#include<cstring>
#include<fstream>

class Tag {
private:
	char* m_name;

public:
	//������ ��������.
	Tag();
	Tag(char*);
	Tag(const Tag&);
	Tag& operator=(const Tag&);
	~Tag();

	//������ � ������
	void setTag(char*);

	char* getTag() const;

	//��������� � ������� ����.
	void serializeTag(std::ofstream&) const ;
	
	//������ �� ������� ����.
	void deserializeTag(std::ifstream&);

private:
	void copyFrom(const Tag&);

};

#endif
