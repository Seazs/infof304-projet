#include "Plateau.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;

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
            Case* c = new Case(nom);
            cases.insert(std::pair<string, Case*>(nom, c));
        }
    }
    //crée les 4 pions centraux
    cases["d4"]->setCouleur('O');
    cases["e4"]->setCouleur('X');
    cases["d5"]->setCouleur('X');
    cases["e5"]->setCouleur('O');

    //couleur du joueur qui commence
    couleur_joueur = 'X';

    initalise_voisin_cases();
    
}

void Plateau::initalise_voisin_cases()
{
    for (char i='1'; i<'9'; i++)
    {
        for(char j='a'; j<'i'; j++)
        {
            string nom = "";
            nom += j;
            nom += i;
            cout << nom << endl;
            map<string, Case*>::iterator itr; //itérateur pour parcourir la map
            itr = cases.find(nom); //recherche la case dans la map
            string nomUp = "";
            nomUp += j;
            nomUp += (i-1);
            string nomDown = "";
            nomDown += j;
            nomDown += (i+1);
            string nomLeft = "";
            nomLeft += (j-1);
            nomLeft += i;
            string nomRight = "";
            nomRight += (j+1);
            nomRight += i;
            string nomUpLeft = "";
            nomUpLeft += (j-1);
            nomUpLeft += (i-1);
            string nomUpRight = "";
            nomUpRight += (j+1);
            nomUpRight += (i-1);
            string nomDownLeft = "";
            nomDownLeft += (j-1);
            nomDownLeft += (i+1);
            string nomDownRight = "";
            nomDownRight += (j+1);
            nomDownRight += (i+1);
            
            //si la case existe
            if (cases.find(nomUp) != cases.end())
            {
                itr->second->setUp(cases[nomUp]);
            }
            if (cases.find(nomDown) != cases.end())
            {
                itr->second->setDown(cases[nomDown]);
            }
            if (cases.find(nomLeft) != cases.end())
            {
                itr->second->setLeft(cases[nomLeft]);
            }
            if (cases.find(nomRight) != cases.end())
            {
                itr->second->setRight(cases[nomRight]);
            }
            if (cases.find(nomUpLeft) != cases.end())
            {
                itr->second->setUpLeft(cases[nomUpLeft]);
            }
            if (cases.find(nomUpRight) != cases.end())
            {
                itr->second->setUpRight(cases[nomUpRight]);
            }
            if (cases.find(nomDownLeft) != cases.end())
            {
                itr->second->setDownLeft(cases[nomDownLeft]);
            }
            if (cases.find(nomDownRight) != cases.end())
            {
                itr->second->setDownRight(cases[nomDownRight]);
            }
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

void Plateau::ecoute_entree()
{
    string nom_case;
    cout << "Entrez le nom de la case à modifier du joueur " << couleur_joueur << " : " ;
    cin >> nom_case;
    while(ajouterPiece(nom_case, couleur_joueur) == false)
    {
        cout << "Entrez le nom de la case à modifier du joueur " << couleur_joueur << " : " ;
        cin >> nom_case;
    }
    if (couleur_joueur == 'X')
    {
        couleur_joueur = 'O';
    }
    else
    {
        couleur_joueur = 'X';
    }
    map<string, Case*>::iterator itr;
    cout << "voisins de la case jouée : " << endl;
    itr = cases.find(nom_case);
    cout << "up : " << ((itr->second->getUp())->getNom()) << endl;
    cout << "down : " << ((itr->second->getDown())->getNom()) << endl;
    cout << "left : " << ((itr->second->getLeft())->getNom()) << endl;
    cout << "right : " << ((itr->second->getRight())->getNom()) << endl;
    cout << "upLeft : " << ((itr->second->getUpLeft())->getNom()) << endl;
    cout << "upRight : " << ((itr->second->getUpRight())->getNom()) << endl;
    cout << "downLeft : " << ((itr->second->getDownLeft())->getNom()) << endl;
    cout << "downRight : " << ((itr->second->getDownRight())->getNom()) << endl;
}

bool Plateau::ajouterPiece(string nom, char couleur)
{
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    itr = cases.find(nom); //recherche la case dans la map
    if (itr != cases.end()) //si la case existe
    {
        if (itr->second->getCouleur() == '.') //si la case est vide
        {
            itr->second->setCouleur(couleur); //on ajoute la pièce
            return true;
        }
        else
        {
            cout << "La case est déjà occupée" << endl;
            return false;
        }
    }
    else
    {
        cout << "La case n'existe pas" << endl;
        return false;
    }
}