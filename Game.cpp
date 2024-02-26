
#include "Game.h"
#include"Joueur.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <conio.h>
#include <random>



void Game::jeu() {
    while (Jeu) {
        tour();
    }
    std::vector<int> totPoints;
    for (Joueur& joueur : ListeJoueur) {
        if (ListeJoueur.size() == 3) {
            if (joueur.getRole() == "shogun") {
                totPoints.push_back(joueur.getHoneur()*2);
            }
            else {
                totPoints.push_back(joueur.getHoneur());
            }
        }
        else if (ListeJoueur.size() == 4) {
            if (joueur.getRole() == "samurai") {
                totPoints.push_back(joueur.getHoneur() * 2);
            }
            else {
                totPoints.push_back(joueur.getHoneur());
            }
        }
        else if (ListeJoueur.size() == 5) {
            if (joueur.getRole() == "ronin") {
                totPoints.push_back(joueur.getHoneur() * 2);
            }
            else {
                totPoints.push_back(joueur.getHoneur());
            }
        }
        else if (ListeJoueur.size() == 6) {
            if (joueur.getRole() == "ronin") {
                totPoints.push_back(joueur.getHoneur() * 3);
            }
            else if (joueur.getRole() == "samurai") {
                totPoints.push_back(joueur.getHoneur() * 2);
            }
            else {
                totPoints.push_back(joueur.getHoneur());
            }
        }
        else if (ListeJoueur.size() == 7) {
            if (joueur.getRole() == "ronin") {
                totPoints.push_back(joueur.getHoneur() * 3);
            }
            else {
                totPoints.push_back(joueur.getHoneur());
            }
        }
    }
    std::cout << "Les points sont: " << std::endl;
    int i = 0;
    int max = 0;
    int maxIndex;
    for (int& points : totPoints) {
        std::cout << ListeJoueur[i].getName() << " posede: " << points << " points" << std::endl;
        if (points > max) {
            max = points;
            maxIndex = i;
        }
    }
    std::cout << "Le Gagnant est: " << ListeJoueur[maxIndex].getName();
}

void Game::tour() {
    for (Joueur& joueur : ListeJoueur) {
        std::cout << "Joueur " << joueur.getName() << " Appuyez pour commencez votre tour..." << std::endl;
        _getch();
        system("cls");
        Pioche(joueur);
        verifIncapacite(joueur);
        afficherStats(joueur);
        selectionCarte(joueur);
        setJeu(verifHonneur());
        verifSurplus(joueur);
        Sleep(1500);
        system("cls");
        if (!joueur.getPerm().empty()) {
            std::cout << "Carte Permanantes du joueur (" << joueur.getName() << " ) : ";
            for (int i = 0; i < joueur.getPerm().size(); i++) {
                std::cout << joueur.getPerm()[i].getName() << " ";
            }
            std::cout << " Appuyez pour avancer au prochain joueur" << std::endl;
            _getch();
            system("cls");
        }
    }
}

void Game::afficherStats(Joueur& joueur) {
    std::cout << "Nom: " << joueur.getName() << std::endl;
    std::cout << "Role: " << joueur.getRole() << std::endl;
    std::cout << "Personnage: " << joueur.getCharacter()[0].getName() << std::endl;
    std::cout << "Vie: " << joueur.getVie() << std::endl;
    std::cout << "Honneur: " << joueur.getHoneur() << std::endl;
    std::cout << "Main: " << std::endl;
}

void Game::afficherMain(Joueur& joueur) {
    int j = 0;
    while (j < joueur.getMain().size()) {
        if (joueur.getMain()[j].getType() == Armes) {
            std::cout << "[" << j << "] " << joueur.getMain()[j].getName() << " ";
            std::cout << " Degats: " << joueur.getMain()[j].getAttack() << " ";
            std::cout << " Portee: " << joueur.getMain()[j].getPortee() << " " << std::endl;
        }
        else {
            std::cout << "[" << j << "] " << joueur.getMain()[j].getName() << std::endl;
        }
        j++;
    }
    if (joueur.getCharacter()[0].getType() == Actif) {
        std::cout << "[" << j + 1 << "] " << "Utiliser effet character: " << joueur.getCharacter()[0].getName() << std::endl;
    }
}

void Game::selectionCarte(Joueur& joueur) {
    int cible = 0;
    bool btmp = true;
    while (btmp) {
        int i = 0;
        afficherMain(joueur);
        std::cout << "Choisissez une carte a jouer (-1 si vous voulez passer le tour): ";
        std::cin >> i;
        if (i >= 0 && i < joueur.getMain().size()) {
            std::cout << "Vous avez choisi: " << joueur.getMain()[i].getName() << std::endl;
            if (joueur.getMain()[i].getType() == Armes && joueur.getAttaqueJoue() != 0) {
                cible = selectionCible(joueur);
                attaque(joueur, cible, joueur.getMain()[i].getAttack(), joueur.getVie(), joueur.getMain()[i].getPortee());
                defausse.push_back(joueur.getMain()[i]);
                joueur.setAttaqueJoue(joueur.getAttaqueJoue() - 1);
                joueur.getMain().erase(joueur.getMain().begin() + i);
            }
            else if (joueur.getMain()[i].getType() == Permanantes) {
                joueur.getPerm().push_back(joueur.getMain()[i]);
                joueur.getMain().erase(joueur.getMain().begin() + i);
            }
            else if (joueur.getMain()[i].getType() == Action) {
                FunctionCartes functcartes;
                defausse.push_back(joueur.getMain()[i]);
                auto ctmp = joueur.getMain()[i];
                joueur.getMain().erase(joueur.getMain().begin() + i);
                functcartes.CartesAction(ctmp.getName(), joueur.getName());
            }
            else {
                std::cout << "Vous avez deja joue une carte arme cet tour, choisisee une autre carte" << std::endl;
            }
        }
        else if (i == -1) {
            joueur.setAttaqueJoue(1);
            btmp = false;
        }
        else {
            FunctionCartes functcartes;
            functcartes.CharactereActif(joueur.getCharacter()[0].getName(), joueur.getName());
        }
    }
}

int Game::selectionCible(Joueur& joueur) {
    int index = 0;
    int selection = 0;
    int displayedIndex = 0;

    for (const Joueur& tmpjoueur : ListeJoueur) {
        if (tmpjoueur.getName() != joueur.getName() && !tmpjoueur.getIncapacite()) {
            std::cout << "[" << displayedIndex << "] Choisir joueur " << tmpjoueur.getName() << std::endl;
            displayedIndex++;
        }
        if (tmpjoueur.getName() != joueur.getName()) {
            index++;
        }
    }

    std::cin >> selection;

    int adjustedSelection = -1;
    displayedIndex = 0; // Reset displayed index for reiteration
    for (const Joueur& tmpjoueur : ListeJoueur) {
        if (tmpjoueur.getName() != joueur.getName() && !tmpjoueur.getIncapacite()) {
            if (selection == displayedIndex) {
                adjustedSelection = index;
                break;
            }
            displayedIndex++;
        }
        if (tmpjoueur.getName() != joueur.getName()) {
            index++;
        }
    }
    return adjustedSelection;
}

void Game::afficherAttaque(Joueur& joueur, int cible, int degats) {
    system("cls");
    std::cout << "Attaque effectuee par le joueur " << joueur.getName() << " sur le joueur " << ListeJoueur[cible].getName() << " Avec degats: " << degats << std::endl;
    _getch();
}

int Game::difficulte(Joueur& joueur, int cible, int porte) {
    int indice_joueur = joueur.trouverIndice(ListeJoueur, joueur.getName());
    int max = ListeJoueur.size() / 2;
    int difficulte = std::abs(indice_joueur - cible);
    if (difficulte > max) {
        difficulte = difficulte - max;
        return difficulte;
    }
    else {
        return difficulte;
    }
}

void Game::subirDegats(Joueur& joueur, int cible, int degats, int hp) {
    int tmp = 0;
    for (int i = 0; i < joueur.getPerm().size(); i++) {
        if (joueur.getPerm()[i].getName() == "attaque_rapide") {
            std::cout << "Au cause de la carte permanantes attaque rapide les degats augmentent de 1" << std::endl;
            tmp++;
        }
    }
    degats = degats + tmp;
    if (ListeJoueur[cible].getCharacter()[0].getName() == "Ginchiyo" && degats != 1) {
        std::cout << "Le charactere Ginchiyo ( " << ListeJoueur[cible].getName() << " ) prend un point de degats en moin" << std::endl;
        degats--;
    }
    if (hp - degats > 0) {
        ListeJoueur[cible].setVie(hp - degats);
        if (ListeJoueur[cible].getCharacter()[0].getName() == "Ushiwaka") {
            std::cout << "Le charactere Ushiwaka ( " << ListeJoueur[cible].getName() << " ) pioche une carte pour chaque point de vie perdue" << std::endl;
            int vtmp = 0;
            if (totCards.size() >= degats) {
                for (vtmp < degats; vtmp++;) {
                    ListeJoueur[cible].getMain().push_back(totCards[0]);
                    totCards.erase(totCards.begin());
                }
            }
            else {
                totCards.insert(totCards.end(), defausse.begin(), defausse.end());

                defausse.clear();

                std::random_device rd;
                std::mt19937 g(rd());
                std::shuffle(totCards.begin(), totCards.end(), g);
                std::cout << "Forment une nouvelle pioche en melangent la defausse et chaque joueur perd un point d'honneur";
                for (Joueur& jtmp : ListeJoueur) {
                    jtmp.setHoneur(jtmp.getHoneur() - 1);
                }
                for (vtmp < degats; vtmp++;) {
                    ListeJoueur[cible].getMain().push_back(totCards[0]);
                    totCards.erase(totCards.begin());
                }
            }
        }
    }
    else {
        if (ListeJoueur[cible].getCharacter()[0].getName() == "Ushiwaka") {
            std::cout << "Le charactere Ushiwaka ( " << ListeJoueur[cible].getName() << " ) pioche une carte pour chaque point de vie perdue" << std::endl;
            int vtmp = 0;
            if (totCards.size() >= hp) {
                for (vtmp < hp; vtmp++;) {
                    ListeJoueur[cible].getMain().push_back(totCards[0]);
                    totCards.erase(totCards.begin());
                }
            }
            else {
                totCards.insert(totCards.end(), defausse.begin(), defausse.end());

                defausse.clear();

                std::random_device rd;
                std::mt19937 g(rd());
                std::shuffle(totCards.begin(), totCards.end(), g);
                std::cout << "Forment une nouvelle pioche en melangent la defausse et chaque joueur perd un point d'honneur";
                for (Joueur& jtmp : ListeJoueur) {
                    jtmp.setHoneur(jtmp.getHoneur() - 1);
                }
                for (vtmp < hp; vtmp++;) {
                    ListeJoueur[cible].getMain().push_back(totCards[0]);
                    totCards.erase(totCards.begin());
                }
            }
        }
        ListeJoueur[cible].setVie(0);
        ListeJoueur[cible].setIncapacite(true);
        ListeJoueur[cible].setHoneur(ListeJoueur[cible].getHoneur() - 1);
        joueur.setHoneur(joueur.getHoneur() + 1);
    }
    if (joueur.getCharacter()[0].getName() == "Tomoe") {
        std::cout << "Le charactere Ginchiyo ( " << joueur.getName() << " ) pioche une carte au cause du effet special" << std::endl;
        if (totCards.size() >= 1) {
            joueur.getMain().push_back(totCards[0]);
            totCards.erase(totCards.begin());
        }
        else {
            totCards.insert(totCards.end(), defausse.begin(), defausse.end());

            defausse.clear();

            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(totCards.begin(), totCards.end(), g);
            std::cout << "Forment une nouvelle pioche en melangent la defausse et chaque joueur perd un point d'honneur";
            for (Joueur& jtmp : ListeJoueur) {
                jtmp.setHoneur(jtmp.getHoneur() - 1);
            }
            joueur.getMain().push_back(totCards[0]);
            totCards.erase(totCards.begin());
        }
        int hp_restant = ListeJoueur[cible].getVie();
        if (hp_restant > 0) {
            std::cout << "Joueur :" << ListeJoueur[cible].getName() << " a subit " << degats << " degats, il lui reste donc : " << hp_restant << " Points de vie" << std::endl;
        }
        else {
            std::cout << "Joueur :" << ListeJoueur[cible].getName() << " a subit " << degats << " degats, il lui reste : " << hp_restant << " Points de vie" << std::endl;
            std::cout << "Il est mis a terre et perd un point d'honneur, " << joueur.getName() << " gagne 1 point d'honeur" << std::endl;
        }
    }
}

bool Game::verifParade(int cible) {
    for (int i = 0; i < ListeJoueur[cible].getMain().size(); i++) {
        if (ListeJoueur[cible].getMain()[i].getName() == "parade") {
            defausse.push_back(ListeJoueur[cible].getMain()[i]);
            ListeJoueur[cible].getMain().erase(ListeJoueur[cible].getMain().begin() + i);
            return true;
        }
        else {
            return false;
        }
    }
}

void Game::attaque(Joueur& joueur, int cible, int degats, int hp, int porte) {
    int tmp = 1;
    for (int i = 0; i < ListeJoueur[cible].getPerm().size(); i++) {
        if (ListeJoueur[cible].getPerm()[i].getName() == "concentration") {
            tmp++;
            std::cout << "Au cause de la carte permanante concentration, apres cette carte armes vous pouvez jouer une autre." << std::endl;
        }
    }
    joueur.setAttaqueJoue(tmp);
    int demande;
    afficherAttaque(joueur, cible, degats);
    int difficulter = difficulte(joueur, cible, porte);
    tmp = 0;
    for (int i = 0; i < ListeJoueur[cible].getPerm().size(); i++) {
        if (ListeJoueur[cible].getPerm()[i].getName() == "armure") {
            tmp++;
            std::cout << "Au cause de la carte permanante armure, la difficultee pour attaquer le joueur " << ListeJoueur[cible].getName() << "augmente de 1." << std::endl;
        }
    }
    if (ListeJoueur[cible].getCharacter()[0].getName() == "Benkei") {
        tmp++;
        std::cout << "Le charactere Benkei ( " << ListeJoueur[cible].getName() << " ) augmente la difficulte de 1" << std::endl;
    }
    difficulter = difficulter + tmp;
    std::cout << "Difficulte finale: " << difficulter << std::endl;
    if (difficulter < porte) {
        std::cout << ListeJoueur[cible].getName() << " Avez vous une carte parade et voulez vous la utilise?" << std::endl << "- '0' pour oui " << std::endl << "- '1' pour non " << std::endl;
        std::cin >> demande;
        if (demande == 1) {
            subirDegats(joueur, cible, degats, hp);
        }
        else {
            if (!verifParade(cible)) {
                std::cout << "Pas de carte parade, degats vont passee" << std::endl;
                subirDegats(joueur, cible, degats, hp);
            }
        }
    }
    else {
        std::cout << "Difficultee trop grande pour cette carte, le joueur cible ne recoit pas de degats" << std::endl;
        Sleep(1000);
    }
}

void Game::verifIncapacite(Joueur& joueur) {
    if (joueur.getIncapacite() == true) {
        std::cout << "Joueur a terre, reprend toute vie et continue a jouer." << std::endl;
        joueur.setVie(joueur.getCharacter()[0].getHp());
        joueur.setIncapacite(false);
        Sleep(1000);
    }
}

bool Game::verifHonneur() {
    for (Joueur& joueur : ListeJoueur) {
        if (joueur.getHoneur() <= 0) {
            return false;
        }
    }
    return true;
}

void Game::Pioche(Joueur& joueur) {
    if (totCards.size() >= 3) {
        joueur.getMain().push_back(totCards[0]);
        totCards.erase(totCards.begin());
        joueur.getMain().push_back(totCards[0]);
        totCards.erase(totCards.begin());
        if (joueur.getCharacter()[0].getName() == "Hideyoshi") {
            std::cout << "Le charactere Hideyoshi ( " << joueur.getName() << " ) pioche une carte supplemantaire" << std::endl;
            joueur.getMain().push_back(totCards[0]);
            totCards.erase(totCards.begin());
        }
    }
    else {
        totCards.insert(totCards.end(), defausse.begin(), defausse.end());

        defausse.clear();

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(totCards.begin(), totCards.end(), g);
        std::cout << "Forment une nouvelle pioche en melangent la defausse et chaque joueur perd un point d'honneur";
        for (Joueur& jtmp : ListeJoueur) {
            jtmp.setHoneur(jtmp.getHoneur() - 1);
        }
        Pioche(joueur);
    }
}

void Game::verifSurplus(Joueur& joueur) {
    int tmp;
    if (joueur.getMain().size() > 7) {
        for (int i = joueur.getMain().size(); i > 7; i--) {
            afficherMain(joueur);
            std::cout << "Choisissez une carte a defauser car surplus de 7 cartes: ";
            std::cin >> tmp;
            defausse.push_back(joueur.getMain()[i]);
            joueur.getMain().erase(joueur.getMain().begin() + i);
        }
    }
}