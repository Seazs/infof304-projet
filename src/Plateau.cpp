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
}

bool Plateau::ajouterPiece(string nom, char couleur)
{
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    itr = cases.find(nom); //recherche la case dans la map
    if (itr != cases.end()) //si la case existe
    {
        if (itr->second->getCouleur() == '.') //si la case est vide
        {
            if(capturePieces(itr->second) == true){
                itr->second->setCouleur(couleur); //on ajoute la pièce
                cout << "Pièce a été capturée" << endl;
                return true;
            }
            else{
                cout << "Pas de pièce n'a pas été capturée" << endl;
                return false;
            }
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

bool Plateau::verifie_la_prise_Up(Case* c){
    if(c->getUp() != NULL){
        if(c->getUp()->getCouleur() != '.'){
            if(c->getUp()->getCouleur() != couleur_joueur){
                if(c->getUp()->getUp() != NULL){
                    if(c->getUp()->getUp()->getCouleur() != '.'){
                        if(c->getUp()->getUp()->getCouleur() == couleur_joueur){
                            return true;
                        }
                        else{
                            return verifie_la_prise_Up(c->getUp());
                        }
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Plateau::verifie_la_prise_Down(Case* c){
    if(c->getDown() != NULL){
        if(c->getDown()->getCouleur() != '.'){
            if(c->getDown()->getCouleur() != couleur_joueur){
                if(c->getDown()->getDown() != NULL){
                    if(c->getDown()->getDown()->getCouleur() != '.'){
                        if(c->getDown()->getDown()->getCouleur() == couleur_joueur){
                            return true;
                        }
                        else{
                            return verifie_la_prise_Down(c->getDown());
                        }
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Plateau::verifie_la_prise_Left(Case* c){
    if(c->getLeft() != NULL){
        if(c->getLeft()->getCouleur() != '.'){
            if(c->getLeft()->getCouleur() != couleur_joueur){
                if(c->getLeft()->getLeft() != NULL){
                    if(c->getLeft()->getLeft()->getCouleur() != '.'){
                        if(c->getLeft()->getLeft()->getCouleur() == couleur_joueur){
                            return true;
                        }
                        else{
                            return verifie_la_prise_Left(c->getLeft());
                        }
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Plateau::verifie_la_prise_Right(Case* c){
    if(c->getRight() != NULL){
        if(c->getRight()->getCouleur() != '.'){
            if(c->getRight()->getCouleur() != couleur_joueur){
                if(c->getRight()->getRight() != NULL){
                    if(c->getRight()->getRight()->getCouleur() != '.'){
                        if(c->getRight()->getRight()->getCouleur() == couleur_joueur){
                            return true;
                        }
                        else{
                            return verifie_la_prise_Right(c->getRight());
                        }
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Plateau::verifie_la_prise_UpLeft(Case* c){
    if(c->getUpLeft() != NULL){
        if(c->getUpLeft()->getCouleur() != '.'){
            if(c->getUpLeft()->getCouleur() != couleur_joueur){
                if(c->getUpLeft()->getUpLeft() != NULL){
                    if(c->getUpLeft()->getUpLeft()->getCouleur() != '.'){
                        if(c->getUpLeft()->getUpLeft()->getCouleur() == couleur_joueur){
                            return true;
                        }
                        else{
                            return verifie_la_prise_UpLeft(c->getUpLeft());
                        }
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Plateau::verifie_la_prise_UpRight(Case* c){
    if(c->getUpRight() != NULL){
        if(c->getUpRight()->getCouleur() != '.'){
            if(c->getUpRight()->getCouleur() != couleur_joueur){
                if(c->getUpRight()->getUpRight() != NULL){
                    if(c->getUpRight()->getUpRight()->getCouleur() != '.'){
                        if(c->getUpRight()->getUpRight()->getCouleur() == couleur_joueur){
                            return true;
                        }
                        else{
                            return verifie_la_prise_UpRight(c->getUpRight());
                        }
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Plateau::verifie_la_prise_DownLeft(Case* c){
    if(c->getDownLeft() != NULL){
        if(c->getDownLeft()->getCouleur() != '.'){
            if(c->getDownLeft()->getCouleur() != couleur_joueur){
                if(c->getDownLeft()->getDownLeft() != NULL){
                    if(c->getDownLeft()->getDownLeft()->getCouleur() != '.'){
                        if(c->getDownLeft()->getDownLeft()->getCouleur() == couleur_joueur){
                            return true;
                        }
                        else{
                            return verifie_la_prise_DownLeft(c->getDownLeft());
                        }
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool Plateau::verifie_la_prise_DownRight(Case* c){
    if(c->getDownRight() != NULL){
        if(c->getDownRight()->getCouleur() != '.'){
            if(c->getDownRight()->getCouleur() != couleur_joueur){
                if(c->getDownRight()->getDownRight() != NULL){
                    if(c->getDownRight()->getDownRight()->getCouleur() != '.'){
                        if(c->getDownRight()->getDownRight()->getCouleur() == couleur_joueur){
                            return true;
                        }
                        else{
                            return verifie_la_prise_DownRight(c->getDownRight());
                        }
                    }
                    else{
                        return false;
                    }
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

void Plateau::capturePieceUp(Case* c){
    while (c->getUp()->getCouleur() != couleur_joueur)
    {
        c->getUp()->setCouleur(couleur_joueur);
        c = c->getUp();
    }
}

void Plateau::capturePieceDown(Case* c){
    while (c->getDown()->getCouleur() != couleur_joueur)
    {
        c->getDown()->setCouleur(couleur_joueur);
        c = c->getDown();
    }
}

void Plateau::capturePieceLeft(Case* c){
    while (c->getLeft()->getCouleur() != couleur_joueur)
    {
        c->getLeft()->setCouleur(couleur_joueur);
        c = c->getLeft();
    }
}

void Plateau::capturePieceRight(Case* c){
    while (c->getRight()->getCouleur() != couleur_joueur)
    {
        c->getRight()->setCouleur(couleur_joueur);
        c = c->getRight();
    }
}

void Plateau::capturePieceUpLeft(Case* c){
    while (c->getUpLeft()->getCouleur() != couleur_joueur)
    {
        c->getUpLeft()->setCouleur(couleur_joueur);
        c = c->getUpLeft();
    }
}

void Plateau::capturePieceUpRight(Case* c){
    while (c->getUpRight()->getCouleur() != couleur_joueur)
    {
        c->getUpRight()->setCouleur(couleur_joueur);
        c = c->getUpRight();
    }
}

void Plateau::capturePieceDownLeft(Case* c){
    while (c->getDownLeft()->getCouleur() != couleur_joueur)
    {
        c->getDownLeft()->setCouleur(couleur_joueur);
        c = c->getDownLeft();
    }
}

void Plateau::capturePieceDownRight(Case* c){
    while (c->getDownRight()->getCouleur() != couleur_joueur)
    {
        c->getDownRight()->setCouleur(couleur_joueur);
        c = c->getDownRight();
    }
}

bool Plateau::capturePieces(Case* c){
    int i = 0;
    if(verifie_la_prise_Up(c)){
        capturePieceUp(c);
        i++;
    }
    if (verifie_la_prise_Down(c)){
        capturePieceDown(c);
        i++;
    }
    if (verifie_la_prise_Left(c)){
        capturePieceLeft(c);
        i++;
    }
    if (verifie_la_prise_Right(c)){
        capturePieceRight(c);
        i++;
    }
    if (verifie_la_prise_UpLeft(c)){
        capturePieceUpLeft(c);
        i++;
    }
    if (verifie_la_prise_UpRight(c)){
        capturePieceUpRight(c);
        i++;
    }
    if (verifie_la_prise_DownLeft(c)){
        capturePieceDownLeft(c);
        i++;
    }
    if (verifie_la_prise_DownRight(c)){
        capturePieceDownRight(c);
        i++;
    }
    if(i == 0){
        return false;
    }
    return true;
}