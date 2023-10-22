#pragma once

#include "File.h"
#include <string>
#include <iostream>
// The class memento is a class which contains an index where his implementations are going to do an action
class Memento {
protected:
	int m_index;
public:
	Memento(int index) :m_index(index)
	{}
	virtual ~Memento() {}
	virtual Memento* execute(File* file) = 0;
	int getIndex() { return m_index; };




};


//The class Deletion contains an index, but also a size of a selection that he has to remove at the index position if it is executed
class Deletion : public Memento {
private:
	int m_sizeToRemove;
public:
	Deletion(int index, int sizeToRemove)
    	:Memento(index)
    	, m_sizeToRemove(sizeToRemove)
	{
	}
	~Deletion() {};
	//The method to delete at index a selection of size sizeToRemove
	Memento* execute(File* file);
};
//The class Insertion contains an index, but also a string that he has to write at the index position if it is executed
class Insertion : public Memento {
private:
	std::string m_removed;
public:
	Insertion(int index, std::string removed)
    	:Memento(index), m_removed(removed)
	{
    	std::cout << "Insertion existe : " << index << " : " << m_removed << std::endl;
	}
	~Insertion() {};
//The method to insert the string at the index position
	Memento* execute(File* file);
};

