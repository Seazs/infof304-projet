#include "Plateau.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::map;
using std::list;


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
    setevaluation_score(0);
}

Plateau::Plateau(Plateau& plateau){
    //deep Copy the content of the Plateau pointed to by p to this Plateau object
    for(auto& case_originale : plateau.cases) {
        // Vous devez cloner chaque élément de la map en profondeur
    Case* nouvelle_case = new Case(*(case_originale.second)); // Supposons que Case a un constructeur de copie approprié
    cases[case_originale.first] = nouvelle_case;
    }
    couleur_joueur = plateau.couleur_joueur;
    initialise_voisin_cases();
    setevaluation_score(0);
}

Plateau::~Plateau()
{
    //supprime les cases
    for(auto& case_a_supprimer : cases) {
        delete case_a_supprimer.second;
    }
    cases.clear();
    //si elles existent, supprime les branches avec le suprrimeur de plateau ~Plateau()
    if(branches.size() > 0){
        cout << "nombre de branches à supprimer : " << branches.size() << endl;
        for(Plateau* branche : branches){
            delete branche;
        }
    }
    branches.clear();
    //vide la root
    root = NULL;

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
            itr = cases.find(nom); //recherche la case dans la map
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
            itr = cases.find(nom); //recherche la case dans la map
            
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
    if (cases.find(nom) != cases.end())
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
            //cout << "La pièce " << couleur_joueur << " peut être capturée en " << c->getNom() << endl;
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
            itr = cases.find(nom); //recherche la case dans la map
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
    itr = cases.find(nom); //recherche la case dans la map
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
        cout << "Le joueur O a gagné" << endl;
    }
    else if(score_joueur('O') < score_joueur('X')){
        cout << "Le joueur X a gagné" << endl;
    }
    else{
        cout << "Egalité" << endl;
    }
}

void Plateau::ajoute_branche(Plateau* branche){
    branches.push_back(branche);
}

void Plateau::regarde_le_futur(char couleur, int profondeur){
    char couleur_joueur_virtuel = couleur;
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            string nom = "";    
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = cases.find(nom); //recherche la case dans la map
            if(ajouterPieceVirtuelle(nom, couleur) == true){
                Plateau* p_virtuel = new Plateau(*this);
                p_virtuel->ajouterPiece_silencieux(nom, couleur);
                ajoute_branche(p_virtuel);
                p_virtuel->root = this;
                if(profondeur > 0){
                    if (couleur_joueur_virtuel == 'X')
                    {
                        couleur_joueur_virtuel = 'O';
                    }
                    else
                    {
                        couleur_joueur_virtuel = 'X';
                    }
                    p_virtuel->setCouleurJoueur(couleur_joueur_virtuel);
                    p_virtuel->regarde_le_futur(couleur_joueur_virtuel, profondeur-1);
                    if (couleur_joueur_virtuel == 'X')
                    {
                        couleur_joueur_virtuel = 'O';
                    }
                    else
                    {
                        couleur_joueur_virtuel = 'X';
                    }
                    p_virtuel->setCouleurJoueur(couleur_joueur_virtuel);   
                }
                else{
                    p_virtuel->setevaluation_score(p_virtuel->evaluation());
                    //elagation alpha beta
                    if(root != NULL && root->getevaluation_score() != 0){
                        if(couleur_joueur_virtuel == 'X'){
                            if(p_virtuel->getevaluation_score() >= root->getevaluation_score()){
                                cout << "élagage alpha beta" << endl;
                                setevaluation_score(p_virtuel->getevaluation_score());
                                return;
                            }
                        }
                        else{
                            if(p_virtuel->getevaluation_score() <= root->getevaluation_score()){
                                cout << "élagage alpha beta 2" << endl;
                                setevaluation_score(p_virtuel->getevaluation_score());
                                return;
                            }
                        }

                    }
                    
                }
            }
        }
    }
    if(couleur_joueur_virtuel == 'X'){
        setevaluation_score(-10000);
        for(Plateau* branche : getBranches()){
            if(branche->getevaluation_score() > getevaluation_score()){
                setevaluation_score(branche->getevaluation_score());
            }
        }
        //donne le score à la racine pour élagage alpha beta
        if(root != NULL){
            root->setevaluation_score(getevaluation_score());
        }
    }
    else{
        setevaluation_score(10000);
        for(Plateau* branche : branches){
            if(branche->getevaluation_score() < getevaluation_score()){
                setevaluation_score(branche->getevaluation_score());
            }
        }
        //donne le score à la racine pour élagage alpha beta
        if(root != NULL){
            root->setevaluation_score(getevaluation_score());
        }
    }
    //si les branches ont des branches, on les supprime
    /*
    for(Plateau* branche : branches){
        if(branche->getBranches().size() > 0){
            for(Plateau* branche2 : branche->getBranches()){
                delete branche2;
            }
            branche->getBranches().clear();
        }
    }
    */
}

list<Plateau*> Plateau::getBranches(){
    return branches;
}

bool Plateau::ajouterPiece_silencieux(string nom, char couleur)
{
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    itr = cases.find(nom); //recherche la case dans la map
    if (itr != cases.end()) //si la case existe
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

int Plateau::evaluation(){
    int score = 0;
    //boucle qui passe sur toutes les cases du plateau
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    for (int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            string nom = "";
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = cases.find(nom); //recherche la case dans la map
            if(itr->second->getCouleur() == 'X'){
                score++;
                if(i == 1 || i == 8 || j == 1 || j == 8){
                score += 10;
                }
                if((j == 1 && j == 8) || (i == 1 && i == 8) || (j == 1 && i == 1) || (j == 8 && i == 8)){
                score += 100;
                }
            }
            if(itr->second->getCouleur() == 'O'){
                score--;
                if(i == 1 || i == 8 || j == 1 || j == 8){
                score -= 10;
                }
                if((j == 1 && j == 8) || (i == 1 && i == 8) || (j == 1 && i == 1) || (j == 8 && i == 8)){
                score -= 100;
                }
            }
        }
    }
    return score;
}

void Plateau::setevaluation_score(int score){
    evaluation_score = score;
}

int Plateau::getevaluation_score(){
    return evaluation_score;
}

void Plateau::changeCouleurJoueur(){
    if (couleur_joueur == 'X')
    {
        couleur_joueur = 'O';
    }
    else
    {
        couleur_joueur = 'X';
    }
}

void Plateau::tour_ia(int profondeur){
    regarde_le_futur(getCouleurJoueur(), profondeur);
    //trouve la branche avec le meilleur score et remplace le plateau par cette branche
    int meilleur_score = 0;
    Plateau* meilleur_branche = NULL;
    //ecrit la taille de la liste de branches
    //cout << "score du plateau " << getevaluation_score() << endl;
    cout << "nombre de branches du joueur " << getCouleurJoueur() << " : " << getBranches().size() << endl;
    for (Plateau* branche : getBranches()){
        cout << "score de la branche : " << branche->getevaluation_score() << endl;
        if(meilleur_branche == NULL){
            meilleur_score = branche->getevaluation_score();
            meilleur_branche = branche;
        }
        else if(getCouleurJoueur() == 'X' && branche->getevaluation_score() > meilleur_score){
            meilleur_score = branche->getevaluation_score();
            meilleur_branche = branche;
            //cout << "nouveau meilleur score : " << meilleur_score << endl;
        }
        else if(getCouleurJoueur() == 'O' && branche->getevaluation_score() < meilleur_score){
            meilleur_score = branche->getevaluation_score();
            meilleur_branche = branche;
            //cout << "nouveau meilleur score : " << meilleur_score << endl;
        }
    }
    cout << "meilleur score : " << meilleur_score << endl;
    //supprime les branches
    if(getBranches().size() > 0){
        for(Plateau* branche : getBranches()){
            if (branche != meilleur_branche){
                cout << "suppression d'une branche" << endl;
                delete branche;
                cout << "branche supprimée" << endl;
            }
        }
    }
    branches.clear();
    //remplace le plateau par la branche
    *this = *meilleur_branche;
    //supprime les branches du nouveau plateau
    if(getBranches().size() > 0){
        for(Plateau* branche : getBranches()){
            delete branche;
        }
    }
    
}