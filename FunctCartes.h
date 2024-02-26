#pragma once
#include "Joueur.h"


#ifndef FUNCTCARTES_H_INCLUDED
#define FUNCTCARTES_H_INCLUDED

class FunctionCartes
{
	public:

		void CartesAction(std::string NomCarte, std::string NomJoueur); // Cartes Action

		void CharactereActif(std::string NomChr, std::string NomJoueur); // Cartes Charactere Actif

};
// Cartes Action
void cri_de_guerre(std::string NomJoueur);

void daimyo(std::string NomJoueur);

void diversion(std::string NomJoueur);

void geisha(std::string NomJoueur);

void meditation(std::string NomJoueur);

void ceremonie_du_the(std::string NomJoueur);

void jujitsu(std::string NomJoueur);


// Cartes Charactere Actif
void Hanzo(std::string NomJoueur);

void Ieyasu(std::string NomJoueur);

void Nobunaga(std::string NomJoueur);

#endif