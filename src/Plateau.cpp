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

/*
    cases["a1"]->setCouleur('O');
    cases["a2"]->setCouleur('X');
    cases["a3"]->setCouleur('X');
    cases["a4"]->setCouleur('X');
    cases["a5"]->setCouleur('X');
    cases["a6"]->setCouleur('X');
    cases["a7"]->setCouleur('X');
    cases["a8"]->setCouleur('X');
    cases["b1"]->setCouleur('X');
    cases["b2"]->setCouleur('X');
    cases["b3"]->setCouleur('X');
    cases["b4"]->setCouleur('X');
    cases["b5"]->setCouleur('X');
    cases["b6"]->setCouleur('X');
    cases["b7"]->setCouleur('X');
    cases["b8"]->setCouleur('X');
    cases["c1"]->setCouleur('X');
    cases["c2"]->setCouleur('X');
    cases["c3"]->setCouleur('X');
    cases["c4"]->setCouleur('X');
    cases["c5"]->setCouleur('X');
    cases["c6"]->setCouleur('X');
    cases["c7"]->setCouleur('X');
    cases["c8"]->setCouleur('X');
    cases["d1"]->setCouleur('X');
    cases["d2"]->setCouleur('X');
    cases["d3"]->setCouleur('X');
    cases["d4"]->setCouleur('X');
    cases["d5"]->setCouleur('X');
    cases["d6"]->setCouleur('X');
    cases["d7"]->setCouleur('X');
    cases["d8"]->setCouleur('X');
    cases["e1"]->setCouleur('X');
    cases["e2"]->setCouleur('X');
    cases["e3"]->setCouleur('X');
    cases["e4"]->setCouleur('X');
    cases["e5"]->setCouleur('X');
    cases["e6"]->setCouleur('X');
    cases["e7"]->setCouleur('X');
    cases["e8"]->setCouleur('X');
    cases["f1"]->setCouleur('X');
    cases["f2"]->setCouleur('X');
    cases["f3"]->setCouleur('X');
    cases["f4"]->setCouleur('X');
    cases["f5"]->setCouleur('X');
    cases["f6"]->setCouleur('X');
    cases["f7"]->setCouleur('X');
    cases["f8"]->setCouleur('X');
    cases["g1"]->setCouleur('X');
    cases["g2"]->setCouleur('X');
    cases["g3"]->setCouleur('X');
    cases["g4"]->setCouleur('X');
    cases["g5"]->setCouleur('X');
    cases["g6"]->setCouleur('X');
    cases["g7"]->setCouleur('X');
    cases["g8"]->setCouleur('X');
    cases["h1"]->setCouleur('X');
    cases["h2"]->setCouleur('X');
    cases["h3"]->setCouleur('X');
    cases["h4"]->setCouleur('X');
*/

    //couleur du joueur qui commence
    setCouleurJoueur('X');
    initalise_voisin_cases();
    
}

/*
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
}*/
void Plateau::initialise_voisin_cases()
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
            
            // check les voisins dans toutes les directions
            setVoisins(itr, j, i-1, &Case::setUp);
            setVoisins(itr, j, i+1, &Case::setDown);
            setVoisins(itr, j-1, i, &Case::setLeft);
            setVoisins(itr, j+1, i, &Case::setRight);
            setVoisins(itr, j-1, i-1, &Case::setUpLeft);
            setVoisins(itr, j+1, i-1, &Case::setUpRight);
            setVoisins(itr, j-1, i+1, &Case::setDownLeft);
            setVoisins(itr, j+1, i+1, &Case::setDownRight);
        }
    }
}

void Plateau::setVoisins(map<string, Case*>::iterator itr, char j, char i, void (Case::*setNeighbor)(Case*))
{
    string nom = "";
    nom += j;
    nom += i;
    if (cases.find(nom) != cases.end())
    {
        (itr->second->*setNeighbor)(cases[nom]);
    }
}


Plateau::~Plateau()
{
    //dtor
}

void Plateau::setCouleurJoueur(char couleur){
    couleur_joueur = couleur;
}

char Plateau::getCouleurJoueur(){
    return couleur_joueur;
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
                cout << "Pas de pièce n'a pu être capturée" << endl;
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

bool Plateau::ajouterPieceVirtuelle(string nom, char couleur)
{
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    itr = cases.find(nom); //recherche la case dans la map
    if (itr != cases.end()) //si la case existe
    {
        if (itr->second->getCouleur() == '.') //si la case est vide
        {
            if(capturePiecesVirtuelle(itr->second) == true){
                /*itr->second->setCouleur(couleur); //on ajoute la pièce*/
                return true;
            }
            else{
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
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

bool Plateau::capturePiecesVirtuelle(Case* c){
    int i = 0;
    if(verifie_la_prise_Up(c)){
        i++;
    }
    if (verifie_la_prise_Down(c)){
        i++;
    }
    if (verifie_la_prise_Left(c)){
        i++;
    }
    if (verifie_la_prise_Right(c)){
        i++;
    }
    if (verifie_la_prise_UpLeft(c)){
        i++;
    }
    if (verifie_la_prise_UpRight(c)){
        i++;
    }
    if (verifie_la_prise_DownLeft(c)){
        i++;
    }
    if (verifie_la_prise_DownRight(c)){
        i++;
    }
    if(i == 0){
        return false;
    }
    return true;
}

bool Plateau::verifie_si_le_joueur_peut_jouer(char couleur){
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    for (int i=1; i<9; i++)
    {
        for(int j=1; j<9; j++)
        {
            string nom = "";
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = cases.find(nom); //recherche la case dans la map
            if(ajouterPieceVirtuelle(nom, couleur)){
                return true;   
            }
        }
    }
    return false;
}

bool Plateau::passe_le_tour(){
    if(verifie_si_le_joueur_peut_jouer(getCouleurJoueur())){
        return false;
    }
    else{
        cout << "Le joueur " << getCouleurJoueur() << " ne peut pas jouer, il passe son tour" << endl;
        if (couleur_joueur == 'X')
        {
            couleur_joueur = 'O';
        }
        else
        {
            couleur_joueur = 'X';
        }
        return true;
    }
}

bool Plateau::fin_de_partie(){
    if(passe_le_tour()==true){
        if(passe_le_tour()==true){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

int Plateau::score_joueur(char couleur){
    int score = 0;
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    for (int i=1; i<9; i++)
    {
        for(int j=1; j<9; j++)
        {
            string nom = "";
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = cases.find(nom); //recherche la case dans la map
            if(itr->second->getCouleur() == couleur){
                score++;
            }
        }
    }
    return score;
}

void Plateau::affiche_score(){
    cout << "Fin de partie" << endl;
    cout << "Score du joueur noir : " << score_joueur('O') << endl;
    cout << "Score du joueur blanc : " << score_joueur('X') << endl;
    if(score_joueur('O') > score_joueur('X')){
        cout << "Le joueur noir a gagné" << endl;
    }
    else if(score_joueur('O') < score_joueur('X')){
        cout << "Le joueur blanc a gagné" << endl;
    }
    else{
        cout << "Egalité" << endl;
    }
}