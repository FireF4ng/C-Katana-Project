#include "UserInterface.h"
#include "Joueur.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <conio.h>
using namespace std;


void UserInterface::messageBienvenu(){
    cout << "Bienvenu dans le jeu KATANA" << endl;
    cout << "Choisissez un nombre de joueurs de 3 a 7 ! : " ; cin >> nombreJoueurs; cout << endl;
    while (nombreJoueurs < 3 || nombreJoueurs > 7) {
        cout << "Choisissez un nombre de joueurs de 3 a 7 ! : ";
        cin >> nombreJoueurs;
        cout << endl;
        cout << "C'est l'heure de l'attribution des roles, ne regardez que votre role ! ";
    }}

void UserInterface::affichageRoles() {
    for (const Joueur& main : ListeJoueur) {
        cout << main.getName() << " Appuyez sur une touche pour consulter votre role !"<< endl;
        _getch();
        cout << "Le role s'affiche dans 2 secondes !";
        Sleep(1500);
        system("cls");
        cout << "Nom Joueur: " << main.getName() << endl;
        cout << "Role: " << main.getRole() << endl;
        cout << "Personnage: " << main.getCharacter()[0].getName() << endl;
        cout << "Appuyez sur une touche une fois que vous avez vu votre role !";
        _getch();
        Sleep(1500);
        system("cls");
    }
}

void UserInterface::affichageASCII() {
    cout << R"(

                            /|
                          /'||
                         |  ||
                         |  ||
                         |  ||
                         |  ||
                         |  ||
                         |  ||         __.--._
                         |  ||      /~~   __.-~\ _
                         |  ||  _.-~ / _---._ ~-\/~\
                         |  || // /  /~/  .-  \  /~-\
                         |  ||((( /(/_(.-(-~~~~~-)_/ |
                         |  || ) (( |_.----~~~~~-._\ /
                         |  ||    ) |              \_|
                         |  ||     (| =-_   _.-=-  |~)        ,
                         |  ||      | `~~ |   ~~'  |/~-._-'/'/_,
                         |  ||       \    |        /~-.__---~ , ,
                         |  ||       |   ~-''     || `\_~~~----~
                         |  ||_.ssSS$$\ -====-   / )\_  ~~--~
                 ___.----|~~~|%$$$$$$/ \_    _.-~ /' )$s._
        __---~-~~        |   |%%$$$$/ /  ~~~~   /'  /$$$$$$$s__
      /~       ~\    ============$$/ /        /'  /$$$$$$$$$$$SS-.
    /'      ./\\\\\\_( ~---._(_))$/ /       /'  /$$$$%$$$$$~      \
    (      //////////(~-(..___)/$/ /      /'  /$$%$$%$$$$'         \
     \    |||||||||||(~-(..___)$/ /  /  /'  /$$$%$$$%$$$            |
      `-__ \\\\\\\\\\\(-.(_____) /  / /'  /$$$$%$$$$$%$             |
          ~~""""""""""-\.(____) /   /'  /$$$$$%%$$$$$$\_            /
                        $|===|||  /'  /$$$$$$$%%%$$$$$( ~         ,'|
                    __  $|===|%\/'  /$$$$$$$$$$$%%%%$$|        ,''  |
                   ///\ $|===|/'  /$$$$$$%$$$$$$$%%%%$(            /'
                    \///\|===|  /$$$$$$$$$%%$$$$$$%%%%$\_-._       |
                     `\//|===| /$$$$$$$$$$$%%%$$$$$$-~~~    ~      /
                       `\|-~~(~~-`$$$$$$$$$%%%///////._       ._  |
                       (__--~(     ~\\\\\\\\\\\\\\\\\\\\        \ \
                       (__--~~(       \\\\\\\\\\\\\\\\\\|        \/
                        (__--~(       ||||||||||||||||||/       _/
                         (__.--._____//////////////////__..---~~
                         |   """"'''''           ___,,,,ss$$$%
                        ,%\__      __,,,\sssSS$$$$$$$$$$$$$$%%
                      ,%%%%$$$$$$$$$$\;;;;\$$$$$$$$$$$$$$$$%%%$.
                     ,%%%%%%$$$$$$$$$$%\;;;;\$$$$$$$$$$$$%%%$$$$
                    %%%%%%%%%%%%$$$$$$$$$$$$$$$$$$\;;;$$$$$$$$$$
                   ""==%%%%%%%$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
                               $$$$$$$$$$$$$$$$$$$$====""""
                                 """""""""~~~~


)" << endl;

};

