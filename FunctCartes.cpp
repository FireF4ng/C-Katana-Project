#include "FunctCartes.h"
#include "Game.h"
#include <map>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <conio.h>
#include <random>


void FunctionCartes::CartesAction(std::string NomCarte, std::string NomJoueur) {
	if (NomCarte == "cri_de_guerre") {
		cri_de_guerre(NomJoueur);
	}
	else if (NomCarte == "daimyo") {
		daimyo(NomJoueur);
	}
	else if (NomCarte == "diversion") {
		diversion(NomJoueur);
	}
	else if (NomCarte == "meditation") {
		meditation(NomJoueur);
	}
	else if (NomCarte == "ceremonie_du_the") {
		ceremonie_du_the(NomJoueur);
	}
	else if (NomCarte == "jujitsu") {
		jujitsu(NomJoueur);
	}
	else if (NomCarte == "parade") {
		std::cout << "Carte Parade ne peut pas etre utilisee, choisisee une autre carte" << std::endl;
		Game game;
		Joueur joueur;
		int tmp = joueur.trouverIndice(ListeJoueur, NomJoueur);
		game.selectionCarte(ListeJoueur[tmp]);
	}
	else if (NomCarte == "geisha") {
		geisha(NomJoueur);
	}
	else {
		std::cout << "Cette carte n'est pas dans la liste" << std::endl;
	}
}

void FunctionCartes::CharactereActif(std::string NomCarte, std::string NomJoueur) {
	if (NomCarte == "Hanzo") {
		Hanzo(NomJoueur);
	}
	else if (NomCarte == "Ieyasu") {
		Ieyasu(NomJoueur);
	}
	else if (NomCarte == "Nobunaga") {
		Nobunaga(NomJoueur);
	}
	else {
		std::cout << "Cette carte n'est pas dans la liste" << std::endl;
	}
}


// Cartes Action
void cri_de_guerre(std::string nomJoueur) {
	for (Joueur& joueur : ListeJoueur) {
		int tmp;
		bool btmp = true;
		if (joueur.getIncapacite() == false && joueur.getName() != nomJoueur && joueur.getCharacter()[0].getName() != "Chiyome") {
			while (btmp) {
				std::cout << joueur.getName() << "Voulez vous défausser une carte parade pour ne pas perdre un point de vie?" << std::endl;
				std::cout << "[1] Oui" << std::endl << "[2] Non" << std::endl;
				std::cin >> tmp;
				switch (tmp) 
				{
				case 1:
					if (joueur.getCharacter()[0].getName() != "Hanzo") {
						for (auto it = joueur.getMain().begin(); it != joueur.getMain().end(); ++it) {
							if (it->getName() == "parade") {
								std::cout << "Carte Parades défausser, passage au prochain joueur" << std::endl;
								defausse.push_back(*it);
								it = joueur.getMain().erase(it);
								btmp = false;
								break;
							}
						}
						if (btmp) {
							std::cout << "Vous n'avez pas de Parades, soustraction d'un point de vie" << std::endl;
							std::cout << joueur.getName() << " passe de " << joueur.getVie() << " points de vie";
							joueur.setVie(joueur.getVie() - 1);
							std::cout << " à " << joueur.getVie() << " points de vie" << std::endl;
							btmp = false;
						}
						break;
					}
					else {
						std::cout << "Le personage Hanzo" << joueur.getName() << "peut utiliser sa capacite" << std::endl;
						std::cout << "[1] Oui" << std::endl << "[2] Non" << std::endl;
						int i;
						std::cin >> i;
						switch (i)
						{
							case 1:
								Hanzo(joueur.getName());
								btmp = false;
								break;
							case 2:
								for (auto it = joueur.getMain().begin(); it != joueur.getMain().end(); ++it) {
									if (it->getName() == "parade") {
										std::cout << "Carte Parades défausser, passage au prochain joueur" << std::endl;
										defausse.push_back(*it);
										it = joueur.getMain().erase(it);
										btmp = false;
										break;
									}
								}
								if (btmp) {
									std::cout << "Vous n'avez pas de Parades, soustraction d'un point de vie" << std::endl;
									std::cout << joueur.getName() << " passe de " << joueur.getVie() << " points de vie";
									joueur.setVie(joueur.getVie() - 1);
									std::cout << " à " << joueur.getVie() << " points de vie" << std::endl;
									btmp = false;
								}
								break;
						default:
							break;
						}
						Hanzo(joueur.getName());
						btmp = false;
					}
				case 2:
					std::cout << "Soustraction du point de vie" << std::endl;
					std::cout << joueur.getName() << "passe de " << joueur.getVie() << "points de vies";
					joueur.setVie(joueur.getVie() - 1);
					std::cout << "a" << joueur.getVie() << "points de vie" << std::endl;
					btmp = false;
				default:
					std::cout << "Option incorecte, revient au choix" << std::endl;
					continue;
				}
			}
		}
		else if (joueur.getCharacter()[0].getName() == "Chiyome") {
			std::cout << "Le charactere Chiyome ( " << joueur.getName() << " ) n'est pas affectee par cette carte au cause de son pouvoir" << std::endl;
		}
		Sleep(1000);
	}
	Sleep(1000);
	system("cls");
}

void daimyo(std::string nomJoueur) {
	Joueur joueur;
	int tmp = joueur.trouverIndice(ListeJoueur, nomJoueur);
	if (totCards.size() >= 2) {
		for (int j = 0; j < 2; j++) {
			ListeJoueur[tmp].getMain().push_back(totCards[0]);
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
		daimyo(nomJoueur);
	}
}

void diversion(std::string nomJoueur) {
	int i = 0;
	std::cout << "Choisir un joueur cible" << std::endl;
	for (const Joueur& joueur : ListeJoueur) {
		if (joueur.getName() != nomJoueur) {
			std::cout << "[" << i << "] Joueur " << joueur.getName() << std::endl;
			i++;
		}
	}

	int tmp;
	std::cin >> tmp;
	if (tmp < 0 || tmp >= ListeJoueur.size() || ListeJoueur[tmp].getName() == nomJoueur) {
		std::cerr << "Choix invalide." << std::endl;
		return;
	}

	Joueur joueur;
	int jtmp = joueur.trouverIndice(ListeJoueur, nomJoueur);

	std::cout << "Choisir un nombre de 0 a" << ListeJoueur[tmp].getMain().size()-1 << std::endl;
	std::cin >> i;

	ListeJoueur[jtmp].getMain().push_back(ListeJoueur[tmp].getMain()[i]);
	defausse.push_back(ListeJoueur[tmp].getMain()[i]);
	ListeJoueur[tmp].getMain().erase(ListeJoueur[tmp].getMain().begin() + i - 1);
}

void geisha(std::string nomJoueur) {
	int tmp;
	std::cout << "Chosir diffuser" << std::endl << "[1] 1 carte permanente en jeu" << std::endl << "[2] 1 carte au hasard dans la main d’un autre joueur" << std::endl;
	std::cin >> tmp;
	int i = 0;
	switch (tmp)
	{
	case 1:
		std::cout << "Voulez Vous diffuzer une carte permanante de quel joueur?" << std::endl;
		for (const Joueur& joueur : ListeJoueur) {
			std::cout << "[" << i << "] Joueur " << joueur.getName() << std::endl;
			i++;
		}
		std::cin >> tmp;
		if (tmp < 0 || tmp >= ListeJoueur.size() || ListeJoueur[tmp].getPerm().size() == 0) {
			std::cerr << "Choix invalide." << std::endl;
			geisha(nomJoueur);
		}
		std::cout << "Chosir quelle carte eliminer: " << std::endl;
		for (int i = 0; i < ListeJoueur[tmp].getPerm().size() -1; i++) {
			std::cout << "[" << i << "] Carte " << ListeJoueur[tmp].getPerm()[i].getName() << std::endl;
		}
		std::cin >> i;
		std::cout << "Carte " << ListeJoueur[tmp].getPerm()[i].getName() << "Eliminee" << std::endl;
		defausse.push_back(ListeJoueur[tmp].getPerm()[i]);
		ListeJoueur[tmp].getPerm().erase(ListeJoueur[tmp].getPerm().begin() + i -1);

	case 2:
		diversion(nomJoueur);
	default:
		std::cout << "Choix non existant" << std::endl;
		geisha(nomJoueur);
	}
}

void meditation(std::string nomJoueur) {
	std::cout << "Vous recevez toutes vos vies" << std::endl;
	Joueur joueur;
	int tmp = joueur.trouverIndice(ListeJoueur, nomJoueur);
	int ctmp = -1;
	for (size_t i = 0; i < charCards.size(); ++i) {
		if (charCards[i].getName() == ListeJoueur[tmp].getCharacter()[0].getName()) {
			ctmp = static_cast<int>(i);
			break;
		}
	}
	ListeJoueur[tmp].setVie(charCards[ctmp].getHp());
	int i = 0;

	std::cout << "Choisir un joueur cible" << std::endl;
	for (const Joueur& joueur : ListeJoueur) {
		if (joueur.getName() != nomJoueur) {
			std::cout << "[" << i << "] Joueur " << joueur.getName() << std::endl;
			i++;
		}
	}
	int jtmp;
	std::cin >> jtmp;
	if (jtmp < 0 || jtmp >= ListeJoueur.size() || ListeJoueur[jtmp].getName() == nomJoueur) {
		std::cerr << "Choix invalide." << std::endl;
		return;
	}
	if (totCards.size() >= 1) {
		ListeJoueur[jtmp].getMain().push_back(totCards[0]);
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
		ListeJoueur[jtmp].getMain().push_back(totCards[0]);
		totCards.erase(totCards.begin());
	}
}

void ceremonie_du_the(std::string nomJoueur) {
	if (totCards.size() >= 10) {
		for (Joueur& joueur : ListeJoueur) {
			if (joueur.getName() != nomJoueur) {
				joueur.getMain().push_back(totCards[0]);
				totCards.erase(totCards.begin());
				std::cout << joueur.getName() << "A pioche une carte" << std::endl;
			}
			else {
				for (int i = 0; i < 3; i++) {
					joueur.getMain().push_back(totCards[0]);
					totCards.erase(totCards.begin());
				}
				std::cout << joueur.getName() << "A pioche trois carte" << std::endl;
			}
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
		ceremonie_du_the(nomJoueur);
	}
}

void jujitsu(std::string nomJoueur) {
	for (Joueur& joueur : ListeJoueur) {
		int tmp;
		bool btmp = true;
		if (joueur.getIncapacite() == false && joueur.getName() != nomJoueur && joueur.getCharacter()[0].getName() != "Chiyome") {
			while (btmp) {
				std::cout << joueur.getName() << "Voulez vous défausser une carte arme pour ne pas perdre un point de vie?" << std::endl;
				std::cout << "[1] Oui" << std::endl << "[2] Non" << std::endl;
				std::cin >> tmp;
				switch (tmp)
				{
				case 1:
					for (auto it = joueur.getMain().begin(); it != joueur.getMain().end(); ++it) {
						if (it->getType() == Armes) {
							std::cout << "Carte Armes défausser, passage au prochain joueur" << std::endl;
							defausse.push_back(*it);
							it = joueur.getMain().erase(it);
							btmp = false;
							break;
						}
					}
					if (btmp) {
						std::cout << "Vous n'avez pas de Armes, soustraction d'un point de vie" << std::endl;
						std::cout << joueur.getName() << " passe de " << joueur.getVie() << " points de vie";
						joueur.setVie(joueur.getVie() - 1);
						std::cout << " à " << joueur.getVie() << " points de vie" << std::endl;
						btmp = false;
					}
					break;
				case 2:
					std::cout << "Soustraction du point de vie" << std::endl;
					std::cout << joueur.getName() << "passe de " << joueur.getVie() << "points de vies";
					joueur.setVie(joueur.getVie() - 1);
					std::cout << "a" << joueur.getVie() << "points de vie" << std::endl;
					btmp = false;
				default:
					std::cout << "Option incorecte, revient au choix" << std::endl;
					continue;
				}
			}
		}
		else if (joueur.getCharacter()[0].getName() == "Chiyome") {
			std::cout << "Le charactere Chiyome ( " << joueur.getName() << " ) n'est pas affectee par cette carte au cause de son pouvoir" << std::endl;
		}
		Sleep(1000);
	}
	Sleep(1000);
	system("cls");
}



// Cartes Charactere Actifs
void Hanzo(std::string NomJoueur) {
	Joueur joueur;
	int jtmp = joueur.trouverIndice(ListeJoueur, NomJoueur);
	bool btmp = true;

	for (auto it = ListeJoueur[jtmp].getMain().begin(); it != ListeJoueur[jtmp].getMain().end(); ++it) {
		if (it->getType() == Armes) {
			std::cout << "Carte Armes défausser, passage au prochain joueur" << std::endl;
			defausse.push_back(*it);
			it = ListeJoueur[jtmp].getMain().erase(it);
			btmp = false;
			break;
		}
	}
	if (btmp) {
		std::cout << "Vous n'avez pas de Armes, soustraction d'un point de vie" << std::endl;
		std::cout << ListeJoueur[jtmp].getName() << " passe de " << ListeJoueur[jtmp].getVie() << " points de vie";
		ListeJoueur[jtmp].setVie(ListeJoueur[jtmp].getVie() - 1);
		std::cout << " à " << ListeJoueur[jtmp].getVie() << " points de vie" << std::endl;
	}
}

void Ieyasu(std::string NomJoueur) {
	Joueur joueur;
	int jtmp = joueur.trouverIndice(ListeJoueur, NomJoueur);

	ListeJoueur[jtmp].getMain().push_back(defausse[0]);
	defausse.erase(defausse.begin());
	std::cout << ListeJoueur[jtmp].getName() << "A pioche une carte de la defausse" << std::endl;
}

void Nobunaga(std::string NomJoueur) {
	Joueur joueur;
	int jtmp = joueur.trouverIndice(ListeJoueur, NomJoueur);

	std::cout << "En utilisant la capacite de Nobunaga:" << std::endl;
	std::cout << ListeJoueur[jtmp].getName() << " passe de " << ListeJoueur[jtmp].getVie() << " points de vie";
	ListeJoueur[jtmp].setVie(ListeJoueur[jtmp].getVie() - 1);
	std::cout << " à " << ListeJoueur[jtmp].getVie() << " points de vie" << std::endl;
	std::cout << "En plus il pioche une carte" << std::endl;
	ListeJoueur[jtmp].getMain().push_back(totCards[0]);
	totCards.erase(totCards.begin());
}
