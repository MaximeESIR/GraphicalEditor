#include "History.h"


History::History() :m_past(), m_future() {}
//This method cancel the last action the user did. and add the new memento in the m_future list if the user want to restore the text
void History::cancel() {
	if (m_past.size() != 0) {
    	Memento* lastMemento = m_past.back();
    	m_past.pop_back();




    	Memento* newMemento = lastMemento->execute(m_file);
    	m_future.push_front(newMemento);
    	std::cout << "future : " << m_future.size() << " elements\n";
    	delete lastMemento;
	}
};


//This method restore the file after the user canceled something. Then, a new memento is created and added in m_future if someone want to cancel the action.
void History::restore() {
	if (m_future.size() != 0)
	{
    	Memento* lastMemento = m_future.front();
    	m_future.pop_front();
    	// Editer texte
    	Memento* newMemento = lastMemento->execute(m_file);
    	m_past.push_back(newMemento);
    	delete lastMemento;
	}
};
void History::addMemento(Memento* memento) {
	if (m_future.size() != 0) {
    	m_future.clear();
    	std::cout << "future : " << m_future.size() << " elements\n";
	}
	m_past.push_back(memento);
};

