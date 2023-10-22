#pragma once




#include <iostream>
#include <string>
#include <vector>




class File
{
public:
	File()
    	: m_cursor(0), m_sizeOfSelection(0), m_text(""), m_buffer("")
	{
	}
//To copy the selection into the buffer
	void copySelectionInBuffer();
//A method to write a character on the text at the index position
	void writeContent(const char& content);
// A method to return the text
	const std::string& getText() { return m_text; }
// To modify the size of the cursor
	void setCursor(int number);
//A method to get the current position of the cursor
	inline int getCursor() { return m_cursor; }
// To modify the size of the current selection
	void setSizeOfSelection(int newSize);
	inline int getSizeOfSelection() { return m_sizeOfSelection; }


	std::string getSelection() { return m_text.substr(m_cursor, m_sizeOfSelection); }
// To remove a character or the string contained in the selection
	void deletion();
//The method to paste the buffer on the text
	void pasteBuffer();
	int sizeOfBuffer() { return m_buffer.size(); }


private:
	int m_cursor;
	std::string m_text;
	std::string m_buffer;
	int m_sizeOfSelection;
};
