#pragma once
#include <iostream>
#include <vector>

enum CardType { Armes, Permanantes, Action };
enum ChrType { Actif, Passif };

#ifndef CARTES_H_INCLUDED
#define CARTES_H_INCLUDED

class Cardorig
{
    private:
        CardType type;
        std::string name;
        int attack;
        int portee;
        int NbCartes;
    
    public:
        Cardorig(CardType cardType, const std::string& nomcarte, int Portee, int Degats, int NbCartes)
            : type(cardType), name(nomcarte), portee(Portee), attack(Degats),  NbCartes(NbCartes) {}

        CardType getType() const { return type; }
        std::string getName() const { return name; }
        int getAttack() const { return attack; }
        int getPortee() const { return portee; }
        int getNbCartes() const { return NbCartes; }
};

class Cardtot
{
    private:
        CardType type;
        std::string name;
        int attack;
        int portee;
    
    public:
        Cardtot(CardType cardType, const std::string& nomcarte, int Portee, int Degats)
            : type(cardType), name(nomcarte), portee(Portee), attack(Degats) {}

        CardType getType() const { return type; }
        std::string getName() const { return name; }
        int getAttack() const { return attack; }
        int getPortee() const { return portee; }
};

class Cardrolles
{
    public:
        std::vector<std::string> roles;
};

class Cardchar
{
    private:
        ChrType type;
        std::string name;
        int hp;

    public:
        Cardchar(ChrType chartype, const std::string& nomcarte, int vie)
            : type (chartype), name(nomcarte), hp(vie) {}

        bool operator==(const Cardchar& other) const {
            return (type == other.type && name == other.name && hp == other.hp);
        }

        ChrType getType() const { return type; }
        std::string getName() const { return name; }
        int getHp() const { return hp; }
};

extern std::vector<Cardtot> totCards;

extern std::vector<Cardorig> allCards;

extern Cardrolles roles;

extern std::vector<Cardchar> charCards;

extern std::vector<Cardtot> defausse;

void cartes();

#endif
