#pragma once


#include "File.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL.H>




class System;


// The abstract class to launch a command
class Command
{
public:
	Command()//Constructor of Command
    	: m_preconditions()
	{}




	virtual ~Command() {}




	virtual bool checkPreconditions();// Check if the execute method //can be launched
	virtual void execute() = 0;// Execute the command




	static void linkFile(File* file)//To link a file and an history //to our commands.
	{
    	m_file = file;
	}




protected:
	static File* m_file; // the file which contains the text
	std::vector<SDL_KeyCode> m_preconditions;// conditions 
};


//The Write class let us writing letters
class Write : public Command
{
public:
	Write()// Initialize preconditions of Write
	{
    	// The following SDL_KeyCodes should NOT be detected to activate this event
    	m_preconditions.push_back(SDL_KeyCode::SDLK_LCTRL);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_RIGHT);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_LEFT);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_UP);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_DOWN);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_BACKSPACE);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_KP_PLUS);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_KP_MINUS);
	}




	virtual bool checkPreconditions();// A special verification for 
// Write: Except these conditions
	void execute() override; // Write something if checkPreconditions // returns true
};


//The class to increment the selection 
class SelectMore : public Command
{
public:
	SelectMore()//Preconditions are initialized
	{
    	m_preconditions.push_back(SDL_KeyCode::SDLK_LCTRL);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_RIGHT);
	}
	void execute() override;// Execute the command




};
//The class to decrement the selection 
class SelectLess : public Command
{
public:
	SelectLess()//Preconditions are initialized
	{
    	m_preconditions.push_back(SDL_KeyCode::SDLK_LCTRL);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_LEFT);
	}
	void execute() override;// Execute the command




};


// The class to copy the string in the selection
class Copy : public Command
{
public:
	Copy()//Preconditions are initialized
	{
    	m_preconditions.push_back(SDL_KeyCode::SDLK_c);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_LCTRL);
	}
	void execute() override;// Execute the command
};


// The class to paste the buffer on the text
class Paste : public Command
{
public:
	Paste()//Preconditions are initialized
	{
    	m_preconditions.push_back(SDL_KeyCode::SDLK_v);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_LCTRL);
	}
	void execute() override;// Execute the command
};
//The class for cutting the string within the selection
class Cut : public Command
{
public:
	Cut()//Preconditions are initialized
	{
    	m_preconditions.push_back(SDL_KeyCode::SDLK_x);
    	m_preconditions.push_back(SDL_KeyCode::SDLK_LCTRL);
	}
	void execute() override;// Execute the command
};


//The class to increment the cursor
class MoveRight : public Command
{
public:
	MoveRight()//Preconditions are initialized
	{
    	m_preconditions.push_back(SDL_KeyCode::SDLK_RIGHT);
	}
	void execute() override;// Execute the command
};


//The class to decrement the cursor
class MoveLeft : public Command
{
public:
	MoveLeft()//Preconditions are initialized
	{
    	m_preconditions.push_back(SDL_KeyCode::SDLK_LEFT);
	}
	void execute() override;// Execute the command
};


//The class to remove: the string withing the selection or a letter
class Remove : public Command
{
public:
	Remove()//Preconditions are initialized
	{
    	m_preconditions.push_back(SDL_KeyCode::SDLK_BACKSPACE);
	}
	void execute() override;// Execute the command
};


