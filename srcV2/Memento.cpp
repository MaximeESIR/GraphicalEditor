#include "Memento.h"
//The method execute adds the element stocked at the index stocked. Then, it creates a new memento which is a deletion to cancel this execution if the user wants. It also update the current position of the cursor , and returns the memento
Memento* Insertion::execute(File* file)
{
    file->setCursor(m_index);

    for (char c : m_removed)
    {
   	 file->writeContent(c);
    }

    Deletion* newMemento = new Deletion(m_index, m_removed.size());
    return newMemento;
}
//The execute method removes the element at the index position with a size of m_sizeTo_Remove. Then, it creates a new Memo which is an Insertion, to cancel this execute if the user wants, and returns it. It also update the current position of the cursor
Memento* Deletion::execute(File* file)
{
    std::string temp = file->getText().substr(m_index, m_sizeToRemove);
    Insertion* newMemento = new Insertion(m_index, temp);

    file->setCursor(m_index);
    file->setSizeOfSelection(m_sizeToRemove);
    file->deletion();
    return newMemento;
}
