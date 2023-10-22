#include "File.h"


void File::copySelectionInBuffer()
{
	if (m_sizeOfSelection != 0)
    	m_buffer = m_text.substr(m_cursor, m_sizeOfSelection);// Wee add into the buffer the string which start at index and finish at index  sizeOfSelection
}


void File::setSizeOfSelection(int newSize)
{
	if (newSize >= 0 && m_cursor + newSize <= m_text.size())
    	this->m_sizeOfSelection = newSize;// Set the size of the selection
}

void File::setCursor(int number)
{
	if (number >= 0 && number <= m_text.size())
    	m_cursor = number;
	if (m_sizeOfSelection + m_cursor > m_text.size())//To prevent being off page
    	m_sizeOfSelection = m_text.size() - m_cursor;
}



void File::deletion()
{
	if (m_sizeOfSelection > 0)
	{
	//then we extract the string, erase the selection, and set the selection to 0
    	std::string temp = m_text.substr(m_cursor, m_sizeOfSelection);

    	// Efface la partie sélectionnée du texte
    	m_text.erase(m_cursor, m_sizeOfSelection);
    	m_sizeOfSelection = 0;
	}
	else if (m_cursor > 0)
	{
    	m_text.erase(m_cursor - 1, 1); // The case we have no selection : we remove a character
    	m_cursor--;
	}
}


void File::pasteBuffer()
{
	m_text.insert(m_cursor, m_buffer);
}


void File::writeContent(const char& content)
{
	m_text.insert(m_text.begin() + m_cursor, content);
	m_cursor++;
}
