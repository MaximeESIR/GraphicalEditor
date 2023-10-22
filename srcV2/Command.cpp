#include "Command.h"
#include "System.h"




File* Command::m_file = nullptr;


History Command::m_history;


//We check all information to see if yes or no we can act
bool Command::checkPreconditions()
{
	if (m_preconditions.size() != System::m_events.size() || System::m_events.size() == 0)
    	return false;


	for (SDL_KeyCode precondition : m_preconditions)
	{
    	bool foundPrecondition = false;
    	for (SDL_KeyCode keyCode : System::m_events)
    	{
        	if (keyCode == precondition) {
            	foundPrecondition = true;
            	break;
        	}
    	}
    	if (!foundPrecondition) {
        	return false;
    	}
	}
	return true;
}
//write a letter on the text (after a verification), create a Deletion
//Memo
void Write::execute()
{
	if (!checkPreconditions()) return;




	if (m_file->getSizeOfSelection() != 0) {
    	m_history.addMemento(new Insertion(m_file->getCursor(), m_file->getSelection()));
    	m_file->deletion();
	}




	SDL_KeyCode input = System::m_events.front();
	System::m_events.remove(input);


	char toWrite = -1;
	if (input == SDLK_RETURN)
	{
    	toWrite = '\n';
	}
	else
    	if ((int)input < 127)
    	{
        	toWrite = (char)input;
    	}
	// Cas ou l’on utilise le clavier numérique de droite
    	else if (input >= SDLK_KP_1 && input <= SDLK_KP_9)
    	{
        	toWrite = (char)(input - SDLK_KP_1 + SDLK_1);
    	}
    	else if (input == SDLK_KP_0)
    	{
        	toWrite = '0';
    	}


	if (toWrite != -1)
	{
    	m_history.addMemento(new Deletion(m_file->getCursor(), 1));
    	m_file->writeContent(toWrite);
	}
}


// A special check for write : if not the preconditions : it’s ok
bool Write::checkPreconditions() {
	if (System::m_events.size() == 0) return false;
	for (SDL_KeyCode precondition : m_preconditions)
	{
    	for (SDL_KeyCode keyCode : System::m_events)
    	{
        	if (keyCode == precondition) {
            	return false;
        	}
    	}
	}
	return true;
}
// Remove the selection or a character. Create an Insertion Memo
void Remove::execute()
{
	if (checkPreconditions()) {
    	std::string toDelete = m_file->getSelection();
    	if (toDelete.size() != 0)
    	{
        	m_history.addMemento(new Insertion(m_file->getCursor(), toDelete));
        	m_file->deletion();
    	}
    	else if (m_file->getCursor() != 0)
    	{
        	toDelete = m_file->getText().substr(m_file->getCursor() - 1, 1);
        	m_history.addMemento(new Insertion(m_file->getCursor() - 1, toDelete));
        	m_file->deletion();
    	}


    	System::m_events.pop_front();
	}
}
// Copy the string within the selection into the buffer
void Copy::execute()
{
	if (checkPreconditions()) {
    	if (m_file->getSizeOfSelection() != 0)
    	{
        	m_file->copySelectionInBuffer();
    	}
    	System::m_events.remove(SDLK_c);
	}
}
// Paste the buffer on the text. create a Deletion Memo
void Paste::execute()
{
	if (checkPreconditions() && m_file->sizeOfBuffer() != 0) {


    	if (m_file->getSizeOfSelection() != 0)
    	{
        	std::string toDelete = m_file->getSelection();
        	m_history.addMemento(new Insertion(m_file->getCursor(), toDelete));
        	m_file->deletion();
    	}


    	m_history.addMemento(new Deletion(m_file->getCursor(), m_file->sizeOfBuffer()));
    	m_file->pasteBuffer();
    	System::m_events.remove(SDLK_v);
	}


}


//Delete and copy a string into the buffer. Create an Insertion Memo
void Cut::execute()
{
	if (checkPreconditions()) {
    	m_file->copySelectionInBuffer();


    	std::string toDelete = m_file->getSelection();
    	if (toDelete.size() != 0)
    	{
        	m_history.addMemento(new Insertion(m_file->getCursor(), toDelete));
        	m_file->deletion();
    	}




    	System::m_events.remove(SDLK_x);
	}
}
// Increment the cursor
void MoveRight::execute()
{
	if (!checkPreconditions()) return;
	m_file->setCursor(m_file->getCursor() + 1);
	System::m_events.remove(SDLK_RIGHT);
}
//Decrement the cursor
void MoveLeft::execute()
{
	if (!checkPreconditions()) return;
	m_file->setCursor(m_file->getCursor() - 1);
	System::m_events.remove(SDLK_LEFT);
}


//Increment the size of the selection
void SelectMore::execute()
{
	if (!checkPreconditions()) return;
	m_file->setSizeOfSelection(m_file->getSizeOfSelection() + 1);
	System::m_events.remove(SDLK_RIGHT);
}
//Decrement the size of the selection
void SelectLess::execute() {
	if (!checkPreconditions()) return;
	m_file->setSizeOfSelection(m_file->getSizeOfSelection() - 1);
	System::m_events.remove(SDLK_LEFT);
}
// Cancel an action: ctrl + z
void Cancel::execute() // ctrl + z
{
	if (checkPreconditions()) {
    	m_history.cancel();
    	System::m_events.remove(SDLK_z);
	}
}
// Restore the text: ctrl+y
void Restore::execute()// ctrl + y
{
	if (checkPreconditions()) {
    	std::cout << "DeCancel" << std::endl;
    	m_history.restore();
    	System::m_events.remove(SDLK_y);
	}
}

