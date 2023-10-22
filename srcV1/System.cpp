#include "System.h"
#include "Command.h"
#include "File.h"
#include <iostream>
#include <list>
#include <assert.h>
#include <algorithm>






// Stocke les événements en temps réel
std::list<SDL_KeyCode> System::m_events;
bool System::m_hasToPrint; // Vérifie si l’on a besoin de rafraichir la fenêtre




System::System()
	: m_file()
	, m_commands()
	, m_window(nullptr)
	, m_renderer(nullptr)
	, m_demandToQuit(false)
	, m_winWidth(1000)
	, m_winHeight(700)
	, m_font(nullptr)
	, m_color()
	, m_alphabet(127 - 31, nullptr) // Caractères ASCII imprimables : de 32 à 127
{
	// Accès des commandes au fichier
	Command::linkFile(&m_file);
	// Ajout des commandes
	m_commands.push_back(new Write());
	m_commands.push_back(new SelectMore());
	m_commands.push_back(new SelectLess());
	m_commands.push_back(new Copy());
	m_commands.push_back(new Paste());
	m_commands.push_back(new Cut());
	m_commands.push_back(new MoveRight());
	m_commands.push_back(new MoveLeft());
	m_commands.push_back(new Remove());



//Initialisation du rendu
	// SDL INIT
	SDL_Init(SDL_INIT_VIDEO);
	//TTF Init
	TTF_Init();
	m_font = TTF_OpenFont("arial.ttf", 25);// Police d’écriture
	assert(m_font != NULL);
	m_color = { 255, 255, 255 };// Couleur d’écriture








	// 2 - Create the window
	m_window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_winWidth, m_winHeight, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
    	SDL_Log("Failed to create window: %s", SDL_GetError());
    	SDL_Quit();
    	exit(3);
	}
	// 3 - Create the renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
    	SDL_Log("Failed to create renderer: %s", SDL_GetError());
	}








	// Creating SDL_Textures for every char








	SDL_Surface* tempSurface(nullptr);
	for (char c = 32; c < 127; c++)
	{
    	const char letter[]{ c, 0 };
    	std::string test;
    	test += c;
    	tempSurface = TTF_RenderText_Solid(m_font, test.c_str(), m_color);
    	assert(tempSurface != NULL);
    	m_alphabet[(int)c - 32] = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
    	assert(m_alphabet[(int)c - 32] != NULL);
    	SDL_FreeSurface(tempSurface);
	}
}
















System::~System() //Utilisé dans handleEvents()
{
	SDL_DestroyRenderer(m_renderer); // Détruire le renderer
	SDL_DestroyWindow(m_window);	// Détruire la fenêtre
	TTF_CloseFont(m_font);
	TTF_Quit();//TTF
	SDL_Quit();
}














//actualise l’affichage si une action a été prise. 
void System::printDocument()
{
	if (m_hasToPrint) {
    	m_hasToPrint = false;
    	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    	SDL_RenderClear(m_renderer);
    	//std::cout << "<content>" << m_file.m_text << "<end content>\n";




    	int xPrint = 0;
    	int yPrint = 0;
    	SDL_Texture* currentTexture(nullptr);
    	int index = 0;
    	for (char c : m_file.getText())
    	{
        	if (c == '\n')
        	{
            	xPrint = 0;
            	yPrint += 30;
        	}
        	else
        	{
            	currentTexture = m_alphabet[c - 32];
            	int texW = 0;
            	int texH = 0;
            	//std::cout << "x print : " << xPrint << ", width : " << texW << ", window width : " << m_winWidth << "\n";
            	SDL_QueryTexture(currentTexture, NULL, NULL, &texW, &texH);
            	if ((xPrint + texW) > m_winWidth)
            	{
                	xPrint = 0;
                	yPrint += 30;
            	}
            	SDL_Rect dstrect = { xPrint, yPrint, texW, texH };
            	SDL_RenderCopy(m_renderer, currentTexture, NULL, &dstrect);








            	xPrint += texW;
        	}
        	if (index + 1 == m_file.getCursor())
        	{
            	if (m_file.getSizeOfSelection() == 0)
                	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
            	else
                	SDL_SetRenderDrawColor(m_renderer, 255, 150, 0, 255);
            	SDL_RenderDrawLine(m_renderer, xPrint, yPrint, xPrint, yPrint + 30);
        	}


        	if (m_file.getSizeOfSelection() != 0 && index + 1 == m_file.getCursor() + m_file.getSizeOfSelection())
        	{
            	SDL_SetRenderDrawColor(m_renderer, 255, 150, 0, 255);
            	SDL_RenderDrawLine(m_renderer, xPrint, yPrint, xPrint, yPrint + 30);
        	}
        	index++;
    	}
    	SDL_RenderPresent(m_renderer);
	}
}


//Boucle principale: demander événements -> exécuter commandes -> imprimer
void System::loop()
{
	while (!m_demandToQuit)
	{
    	updateEvents();
    	executeAllCommands();
    	printDocument();
	}
}














//Executer toutes les commandes
void System::executeAllCommands()
{
	for (int i = 0; i < m_commands.size(); i++)
	{
    	m_commands[i]->execute(); 	}
}














//Boucle de capture des Events
void System::updateEvents()
{
	SDL_Event event;
	SDL_KeyCode keyCode;
	SDL_KeyCode keyCodetoRemove;
	while (SDL_PollEvent(&event))
	{
    	switch (event.type)
    	{
    	case SDL_QUIT:
        	m_demandToQuit = true;
        	break;
    	case SDL_KEYDOWN:
        	keyCode = static_cast<SDL_KeyCode>(event.key.keysym.sym);
        	//Si la touche n’est pas resté appuyée:
if (std::find(m_events.begin(), m_events.end(), keyCode) == m_events.end()) {
            	m_events.push_back(keyCode);
            	m_hasToPrint = true;
        	}
        	break;
    	case SDL_KEYUP:
        	keyCodetoRemove = static_cast<SDL_KeyCode>(event.key.keysym.sym);
        	m_events.remove(keyCodetoRemove);
        	break;
    	}
	}
}





