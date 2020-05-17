#ifndef __TAG_HPP
#define __TAG_HPP

#include<cstring>
#include<fstream>

class Tag {
private:
	char* m_name;

public:
	//Голяма четворка.
	Tag();
	Tag(char*);
	Tag(const Tag&);
	Tag& operator=(const Tag&);
	~Tag();

	//Сетъри и гетъри
	void setTag(char*);

	char* getTag() const;

	//Записване в бинарен файл.
	void serializeTag(std::ofstream&) const ;
	
	//Четене от бинарен файл.
	void deserializeTag(std::ifstream&);

private:
	void copyFrom(const Tag&);

};

#endif
