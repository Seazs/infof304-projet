#include "Plateau.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;

Plateau::Plateau()
{
    //initialise les 64 cases du plateau avec leur nom en clé
    for (int j = 1; j < 9; j++)
    {
        for (int i = 1; i < 9; i++)
        {
            string nom = "";
            nom += (char)(i + 96);
            nom += (char)(j + 48);
            Case* c = new Case();
            cases.insert(std::pair<string, Case*>(nom, c));
        }
    }
    //crée les 4 pions centraux
    cases["d4"]->setCouleur('X');
    cases["e4"]->setCouleur('O');
    cases["d5"]->setCouleur('X');
    cases["e5"]->setCouleur('O');
}

Plateau::~Plateau()
{
    //dtor
}

void Plateau::afficherPlateau()
{
    cout << "  a b c d e f g h" << endl;

    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    for (int i=1; i<9; i++)
    {
        cout << i << " ";
        for(int j=1; j<9; j++)
        {
            string nom = "";
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = cases.find(nom); //recherche la case dans la map
            cout << itr->second->getCouleur() << " "; //affiche la couleur de la case
        }
        cout << i << endl;
    }
    cout << "  a b c d e f g h" << endl;
}

