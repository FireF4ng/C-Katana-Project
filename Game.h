#ifndef PROJET_COURS_GAME_H
#define PROJET_COURS_GAME_H

#include <vector>
#include <string>
#include "Joueur.h"
#include "FunctCartes.h"


class Game {
private:
    bool Jeu = true;
public:

    bool verifHonneur();
    void jeu();
    void tour();
    void selectionCarte(Joueur& joueur);
    int selectionCible(Joueur& joueur);
    void afficherStats(Joueur& joueur);
    void afficherMain(Joueur& joueur);
    void afficherAttaque(Joueur& joueur, int cible, int degats);
    void subirDegats(Joueur& joueur, int cible, int degats, int hp);
    int difficulte(Joueur& joueur, int cible, int porte);
    bool verifParade(int cible);
    void attaque(Joueur& joueur, int cible, int degats, int hp, int porte);
    void Pioche(Joueur& joueur);
    void verifSurplus(Joueur& joueur);
    void verifIncapacite(Joueur& joueur);

    void setJeu(bool newJeu) { Jeu = newJeu; }
};




#endif // PROJET_COURS_GAME_H