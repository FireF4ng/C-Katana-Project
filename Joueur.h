#pragma once
#include <iostream>
#include <vector>
#include "Cartes.h"



#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

class Joueur
{
	private:
		std::string name;
		std::string role;
		std::vector<Cardchar> character;
		int vie;
		bool incapacite;
		int attaquejoue;
		int honeur;
		std::vector<Cardtot> main;
		std::vector<std::string> shuffledCharacters;
		std::vector<std::string> shuffledRoles;
		std::vector<Cardtot> carteperm;

	public:

		Joueur();

		Joueur(std::string names, std::string roles, std::vector<Cardchar> chr, int vies, bool incapacite, int attaque, int honeurs, std::vector<Cardtot> cardes, std::vector<Cardtot> cartesperm)
			: name(names), role(roles), character(chr), vie(vies), incapacite(incapacite), attaquejoue(attaque), honeur(honeurs), main(cardes), carteperm(cartesperm) {}

		bool operator==(const std::string& playerName) const {
			return name == playerName;
		}

		// (Getter) Prendre les valeurs
		std::string getName() const { return name; }
		std::string getRole() const { return role; }
		std::vector<Cardchar> getCharacter() const { return character; }
		int getVie() const { return vie; }
		bool getIncapacite() const { return incapacite; }
		int getAttaqueJoue() const { return attaquejoue; }
		int getHoneur() const { return honeur; }
		std::vector<Cardtot>& getMain() { return main; }
		std::vector<Cardtot>& getPerm() { return carteperm; }

		// (Setter) changer des valeurs
		void setVie(int newVie) { vie = newVie; }
		void setHoneur(int newHoneur) { honeur = newHoneur; }
		void setIncapacite(bool newIncapacite) { incapacite = newIncapacite; }
		void setAttaqueJoue(int newAttaqueJoue) { attaquejoue = newAttaqueJoue; }


		void mainjoueurs(int nombreJoueurs);

		void initializeRoles(int nombreJoueurs);

		std::string Rndrole();

		std::tuple<std::vector<Cardchar>, int> Rndcharacter();

		int Honeurpoints(std::string role, int nombreJoueurs);

		void distribcartes();

		int trouverIndice(const std::vector<Joueur>& ListeJoueur, std::string nomJoueur) {
			for (size_t i = 0; i < ListeJoueur.size(); ++i) {
				if (ListeJoueur[i].getName() == nomJoueur) {
					return static_cast<int>(i);
				}
			}
			return -1; // If not found
		}
};

extern std::vector<Joueur> ListeJoueur;

#endif
