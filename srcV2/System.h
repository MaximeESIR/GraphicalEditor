#pragma once


#include "File.h"
#include <string>
#include <vector>
#include <list>
#include <SDL_ttf.h>
#include <unordered_map>


class Command;
//The class which launches the graphical editor. System uses a loop which updates all events, and executes all commands.
class System
{
public:
    System();
    ~System();


    void loop(); // Boucle principale
    void updateEvents(); // Gestion des évènements clavier
    void printDocument(); // Affichage du document dans la fenêtre
    void executeAllCommands(); // Appel des commandes


    static std::list<SDL_KeyCode> m_events; // Contient les SDL_KeyCodes des touches pressées


private:
    File m_file;
    std::vector<Command *> m_commands;


    // Attributs relatifs au contrôle de la fenêtre graphique
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    int m_winWidth;
    int m_winHeight;
    bool m_demandToQuit; // Vérifie si l’on veut quitter ou non l’application
    static bool m_hasToPrint; // Vérifie si l’on a besoin de rafraichir la fenêtre


    TTF_Font *m_font; // Police et taille
    SDL_Color m_color;// Couleur
    std::vector<SDL_Texture *> m_alphabet;// correspondance entre caractère ASCII et texture
};



