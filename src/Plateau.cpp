#include "Plateau.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;

Plateau::Plateau()
{
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
}

Plateau::~Plateau()
{
    //dtor
}

void Plateau::afficherPlateau()
{
    cout << "  a b c d e f g h" << endl;
    map<string, Case*>::iterator itr;
    

    for (int i=1; i<9; i++)
    {
        cout << i << " ";
        for(int j=1; j<9; j++)
        {
            string nom = "";
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = cases.find(nom);
            cout << itr->second->getCouleur() << " ";
        }
        cout << i << endl;
    }
    cout << "  a b c d e f g h" << endl;
}

