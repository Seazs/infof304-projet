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
    getCases()["d4"]->setCouleur('O');
    getCases()["e4"]->setCouleur('X');
    getCases()["d5"]->setCouleur('X');
    getCases()["e5"]->setCouleur('O');

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
    cases["h4"]->setCouleur('X');*/


    //couleur du joueur qui commence
    setCouleurJoueur('X');
    initialise_voisin_cases();
}

Plateau::Plateau(const Plateau& plateau){
    //deep Copy the content of the Plateau pointed to by p to this Plateau object
    for (const auto& paire : plateau.cases) {
        // Vous devez cloner chaque élément de la map en profondeur
    Case* nouvelle_case = new Case(*(paire.second)); // Supposons que Case a un constructeur de copie approprié
    cases[paire.first] = nouvelle_case;
    }
    setCouleurJoueur(this->couleur_joueur);
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

void Plateau::setCases(map<string, Case*> cases){
    this->cases = cases;
}

map<string, Case*> Plateau::getCases(){
    return cases;
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
            itr = this->cases.find(nom); //recherche la case dans la map
            cout << itr->second->getCouleur() << " "; //affiche la couleur de la case
        }
        cout << i << endl;
    }
    cout << "  a b c d e f g h" << endl;
}   

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
            itr = this->cases.find(nom); //recherche la case dans la map
            
            // set les voisins dans toutes les directions
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
    if (this->cases.find(nom) != this->cases.end())
    {
        (itr->second->*setNeighbor)(cases[nom]);
    }
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
    itr = this->cases.find(nom); //recherche la case dans la map
    if (itr != this->cases.end()) //si la case existe
    {
        if (itr->second->getCouleur() == '.') //si la case est vide
        {
            if(capturePieces(itr->second) == true){
                itr->second->setCouleur(couleur); //on ajoute la pièce
                cout << "Pièce " << couleur_joueur << " posée en " << nom << endl;
                return true;
            }
            else{
                cout << "Pas de pièce n'a pu être capturée en " << nom << endl;
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

bool Plateau::capturePieces(Case* c){
    int i = 0;
    if(verifie_la_prise(c, &Case::getUp)){
        capturePiece(c, &Case::getUp);
        i++;
    }
    if (verifie_la_prise(c, &Case::getDown)){
        capturePiece(c, &Case::getDown);
        i++;
    }
    if (verifie_la_prise(c, &Case::getLeft)){
        capturePiece(c, &Case::getLeft);
        i++;
    }
    if (verifie_la_prise(c, &Case::getRight)){
        capturePiece(c, &Case::getRight);
        i++;
    }
    if (verifie_la_prise(c, &Case::getUpLeft)){
        capturePiece(c, &Case::getUpLeft);
        i++;
    }
    if (verifie_la_prise(c, &Case::getUpRight)){
        capturePiece(c, &Case::getUpRight);
        i++;
    }
    if (verifie_la_prise(c, &Case::getDownLeft)){
        capturePiece(c, &Case::getDownLeft);
        i++;
    }
    if (verifie_la_prise(c, &Case::getDownRight)){
        capturePiece(c, &Case::getDownRight);
        i++;
    }
    if(i == 0){
        return false;
    }
    return true;
}

bool Plateau::verifie_la_prise(Case* c, Case* (Case::*getNeighbor)()){
    while ((c->*getNeighbor)() != NULL && ((c->*getNeighbor)())->getCouleur() != '.' && ((c->*getNeighbor)())->getCouleur() != getCouleurJoueur() && ((c->*getNeighbor)()->*getNeighbor)() != NULL) {
        c = (c->*getNeighbor)();
        if ((c->*getNeighbor)()->getCouleur() == couleur_joueur) {
            cout << c->getNom() << " est mangeable" << endl;
            return true;
        }
    }
    return false;
}

void Plateau::capturePiece(Case* c, Case* (Case::*getNeighbor)()){
    while ((c->*getNeighbor)()->getCouleur() != couleur_joueur)
    {
        (c->*getNeighbor)()->setCouleur(couleur_joueur);
        c = (c->*getNeighbor)();
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

bool Plateau::verifie_si_le_joueur_peut_jouer(char couleur){
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    for (int i=1; i<9; i++)
    {
        for(int j=1; j<9; j++)
        {
            string nom = "";
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = this->cases.find(nom); //recherche la case dans la map
            if(ajouterPieceVirtuelle(nom, couleur)){
                return true;   
            }
        }
    }
    return false;
}

bool Plateau::ajouterPieceVirtuelle(string nom, char couleur)
{
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    itr = this->cases.find(nom); //recherche la case dans la map
    //print l'iterateur de la case
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

bool Plateau::capturePiecesVirtuelle(Case* c){
    int i = 0;
    if(verifie_la_prise(c, &Case::getUp)){
        i++;
    }
    if (verifie_la_prise(c, &Case::getDown)){
        i++;
    }
    if (verifie_la_prise(c, &Case::getLeft)){
        i++;
    }
    if (verifie_la_prise(c, &Case::getRight)){
        i++;
    }
    if (verifie_la_prise(c, &Case::getUpLeft)){
        i++;
    }
    if (verifie_la_prise(c, &Case::getUpRight)){
        i++;
    }
    if (verifie_la_prise(c, &Case::getDownLeft)){
        i++;
    }
    if (verifie_la_prise(c, &Case::getDownRight)){
        i++;
    }
    if(i == 0){
        return false;
    }
    return true;
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
            itr = this->cases.find(nom); //recherche la case dans la map
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



void Plateau::regarde_le_futur(Plateau plateau, char couleur, int profondeur){
    char couleur_joueur_virtuel = couleur;
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            string nom = "";    
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = this->cases.find(nom); //recherche la case dans la map
            if(ajouterPieceVirtuelle(nom, couleur) == true){
                cout << nom << endl;
                Plateau p_virtuel(plateau);
                p_virtuel.ajouterPiece(nom, couleur);
                //p_virtuel.afficherPlateau();
                plateau.branches.push_back(&p_virtuel);
                if(profondeur > 0){
                    p_virtuel.regarde_le_futur(p_virtuel, couleur_joueur_virtuel, profondeur-1);
                    
                }
            }
        }
    }
}

bool Plateau::ajouterPiece_silencieux(string nom, char couleur)
{
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    itr = this->cases.find(nom); //recherche la case dans la map
    if (itr != this->cases.end()) //si la case existe
    {
        if (itr->second->getCouleur() == '.') //si la case est vide
        {
            if(capturePieces(itr->second) == true){
                itr->second->setCouleur(couleur); //on ajoute la pièce
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

