#pragma once
#include "Memento.h"
#include <string>
#include <iostream>
#include <list>
// A class to stock two lists of Memento. We use memento form m_past when we want to cancel an action. After we have canceled an action, we can use restore to restore the text.
class History {
private:	
	std::list<Memento*> m_past;// Memento that are used to cancel
	std::list<Memento*> m_future;// Memento that are used to restore
	File* m_file; // Contains the file that has to be modified
public:
	History();
//A method to cancel the last action
	void cancel();
// A method to restore what the cancel method to
	void restore();
//A method to add a Memento
	void addMemento(Memento* memento);
//A method to link the file to our history
	void linkFile(File* file) { m_file = file; }
};

