#include "Joueur.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>

#include <conio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::vector<Joueur> ListeJoueur;

Joueur::Joueur() : shuffledCharacters() {
    for (const auto& card : charCards) {
        shuffledCharacters.push_back(card.getName());
    }
}

void Joueur::mainjoueurs(int nombreJoueurs) {

    initializeRoles(nombreJoueurs);
    // Input player names
    for (int i = 0; i < nombreJoueurs; ++i) {
        std::string playerName;
        std::vector<Cardchar> character;
        int hp;

        std::cout << "Enter the name of Player " << i + 1 << ": ";
        std::cin >> playerName;

        std::string role = Rndrole();
        std::tie(character, hp) = Rndcharacter();

        // Create a player and add to the vector
        ListeJoueur.push_back(Joueur(playerName, role, character, hp, false, 1, Honeurpoints(role, nombreJoueurs), {}, {}));
    }
};

void Joueur::initializeRoles(int nombreJoueurs) {
    shuffledRoles.clear();

    // Duplicate roles based on the number of players
    for (int i = 0; i < nombreJoueurs; ++i) {
        shuffledRoles.push_back(roles.roles[i]);
    }

    // Shuffle roles only once
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffledRoles.begin(), shuffledRoles.end(), g);
}

std::string Joueur::Rndrole() {
    std::string tmp = shuffledRoles[0];
    shuffledRoles.erase(shuffledRoles.begin());
    return tmp;
};

std::tuple<std::vector<Cardchar>, int> Joueur::Rndcharacter() {

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(shuffledCharacters.begin(), shuffledCharacters.end(), g);

    std::string tmp = shuffledCharacters[0];
    shuffledCharacters.erase(shuffledCharacters.begin());

    int hp = 0;
    std::vector<Cardchar> name;
    for (Cardchar& card : charCards) {
        if (card.getName() == tmp) {
            hp = card.getHp();
            name.push_back(card);
            break;
        }
    }

    return std::make_tuple(name, hp);
};

int Joueur::Honeurpoints(std::string role, int nombreJoueurs) {
    if (nombreJoueurs != 3) {
        if (role == "shogun") {
            return 5;
        }
        else if (nombreJoueurs > 5) {
            return 3;
        }
        else if (nombreJoueurs <= 5) {
            return 4;
        }
    } else {
        if (role == "shogun") {
            return 6;
        }
        else {
            return 3;
        }
    };
};

void Joueur::distribcartes() {

    // Find shogun dans le vecteur players
    auto shogun = std::find_if(ListeJoueur.begin(), ListeJoueur.end(), [](const Joueur& joueur) {
        return joueur.role == "shogun";
        });

    // Si Shogun est trouver mettre tout les joueurs apres lui en debut de liste
    if (shogun != ListeJoueur.end()) {
        std::rotate(ListeJoueur.begin(), shogun, ListeJoueur.end());
    }

    // Shuffle deck
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(totCards.begin(), totCards.end(), g);

    // Number of cards to distribute to each player
    std::vector<int> cardsPerPlayer = { 4, 5, 5, 6, 6, 7, 7 };
    int f = -1;

    // Distribute cards to each player's hand
    for (Joueur& joueur : ListeJoueur) {
        f++;
        for (int j = 0; j < cardsPerPlayer[f]; j++) {
            joueur.main.push_back(totCards[0]);
            totCards.erase(totCards.begin());
        }
    }
    std::cout << "Changement du passage des joueurs, Le Shogun: " << ListeJoueur[0].getName() << " Devien premier a passee" << std::endl;
    Sleep(2000);
    std::cout << "Repartition des cartes..." << std::endl;
    Sleep(2000);
    system("cls");
    for (Joueur& main : ListeJoueur) {
        std::cout << main.getName() << " Appuyez sur une touche pour consulter vos cartes !" << std::endl;
        _getch();
        std::cout << "Les cartes s'affiche dans 2 secondes !" << std::endl;
        Sleep(1500);
        int j = 0;
        while (j < main.getMain().size()) {
            if (main.getMain()[j].getType() == Armes) {
                std::cout << "[" << j << "] " << main.getMain()[j].getName() << " ";
                std::cout << " Degats: " << main.getMain()[j].getAttack() << " ";
                std::cout << " Portee: " << main.getMain()[j].getPortee() << " " << std::endl;
            }
            else {
                std::cout << "[" << j << "] " << main.getMain()[j].getName() << std::endl;
            }
            j++;
        }
        std::cout << "Appuyez sur une touche une fois que vous avez vu votre cartes !";
        _getch();
        system("cls");
    }
}