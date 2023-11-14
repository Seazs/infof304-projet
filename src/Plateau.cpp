#include "Plateau.h"
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::map;
using std::list;

//méthodes de création, de copie et de destruction

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
    for(auto& case_a_supprimer : cases) {
        delete case_a_supprimer.second;
    }
    cases.clear();
    branches.clear();
    //vide la root
    root = NULL;

}


//méthodes d'initialisation

void Plateau::setCouleurJoueur(char couleur){
    couleur_joueur = couleur;
}

void Plateau::setCases(map<string, Case*> cases){
    this->cases = cases;
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

void Plateau::setevaluation_score(int score){
    evaluation_score = score;
}


//méthodes d'accès

char Plateau::getCouleurJoueur(){
    return couleur_joueur;
}

map<string, Case*> Plateau::getCases(){
    return cases;
}

list<Plateau*> Plateau::getBranches(){
    return branches;
}

int Plateau::getevaluation_score(){
    return evaluation_score;
}


//méthodes de modification

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

void Plateau::ajoute_branche(Plateau* branche){
    branches.push_back(branche);
}


//méthodes d'affichage

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


//méthodes de jeu

void Plateau::ecoute_entree() //demande le nom de la case à modifier à l'humain et appelle "ajouterPiece"
{
    string nom_case; //initialise le nom de la case à modifier entrée par l'humain
    cout << "Entrez le nom de la case à modifier du joueur " << couleur_joueur << " : " ;
    cin >> nom_case; //demande le nom de la case à modifier
    while(ajouterPiece(nom_case, couleur_joueur) == false) //tant que la case n'existe pas ou qu'elle est déjà occupée, on redemande le nom de la case
    {
        cout << "Entrez le nom de la case à modifier du joueur " << couleur_joueur << " : " ;
        cin >> nom_case;
    }
}

void Plateau::tour_ia(int profondeur)//Appelle la fonction qui regarde le futur pour créer l'arbres des possibilités, puis remplace le plateau par la branche avec le meilleur score
{
    /*
    //si le plateau à des branches, on trouve celle dont les cases sont identiques au plateau actuel en comparent chaaque case et le plateau devient cette branche
    if(getBranches().size() > 0){
        for (Plateau* branche : getBranches()){
            bool identique = true;
            //on compare chaque case du plateau avec la case correspondante de la branche avec leur noms
            for(int i=1; i<9; i++){
                for(int j=1; j<9; j++){
                    string nom = "";
                    nom += (char)(j + 96);
                    nom += (char)(i + 48);
                    if(cases[nom]->getCouleur() != branche->getCases()[nom]->getCouleur()){
                        identique = false;
                        break;
                    }
                }
                if(identique == false){
                    break;
                }
            }
            if(identique){
                //on supprime toutes les branches sauf celle qui est identique au plateau actuel
                for (Plateau* branche_plus_utile : getBranches()){
                    if (branche_plus_utile != branche){
                        branche_plus_utile->supresseur_d_arbre();
                        delete branche_plus_utile;
                    }
                }
                *this = *branche;
                for(Plateau* branche : getBranches()){
                    branche->supresseur_d_arbre();
                    branches.clear();
                }
                break;
            }
            else{//si aucune branche n'est identique au plateau actuel, on supprime toutes les branches
                for (Plateau* branche : getBranches()){
                    branche->supresseur_d_arbre();
                    branches.clear();
                }
            }
        }
    }
    */
    //regarde_le_futur(getCouleurJoueur(), profondeur); //crée l'arbre des possibilités
    creer_arbre(profondeur);//crée l'arbre des possibilités
    Plateau* meilleur_branche = NULL; //initialise la branche avec le meilleur score et le meilleur score
    int meilleur_score = 0;
    cout << "nombre de branches du joueur " << getCouleurJoueur() << " : " << getBranches().size() << endl;
    for (Plateau* branche : getBranches()){ //On parcourt les branches directes du plateau
        cout << "score de la branche : " << branche->getevaluation_score() << endl;
        if(meilleur_branche == NULL){ //si c'est la première branche, on l'initialise comme la meilleure
            meilleur_score = branche->getevaluation_score();
            meilleur_branche = branche;
        }
        else if(getCouleurJoueur() == 'X' && branche->getevaluation_score() > meilleur_score){//le joueur X cherche le meilleur score positif
            meilleur_score = branche->getevaluation_score();
            meilleur_branche = branche;
            //cout << "nouveau meilleur score : " << meilleur_score << endl;
        }
        else if(getCouleurJoueur() == 'O' && branche->getevaluation_score() < meilleur_score){//le joueur O cherche le meilleur score négatif
            meilleur_score = branche->getevaluation_score();
            meilleur_branche = branche;
            //cout << "nouveau meilleur score : " << meilleur_score << endl;
        }
    }
    cout << "meilleur score : " << meilleur_score << endl;
    if(getBranches().size() > 0){//si le plateau a des branches, on les supprime toutes sauf la meilleure
        for (Plateau* branche : getBranches()){
            if (branche != meilleur_branche){
                branche->supresseur_d_arbre();
                delete branche;
            }
        }
    }
    *this = *meilleur_branche; //remplace le plateau par la branche avec le meilleur score
    //supprime toutes les branches du plateau
    for (Plateau* branche : getBranches()){
        branche->supresseur_d_arbre();
        branches.clear();
    }
}


//fonctions de jeu

bool Plateau::ajouterPiece(string nom, char couleur)//trouve la case dans la map et appelle "capturePieces" si la case est vide. La couleur de la case est changée si "capturePieces" renvoie true et la fonction renvoie true. Sinon, la fonction renvoie false
{
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    itr = cases.find(nom); //recherche la case dans la map
    if (itr != cases.end()) //si la case existe
    {
        if (itr->second->getCouleur() == '.') //si la case est vide
        {
            if(capturePieces(itr->second) == true){//si au moins une pièce a été capturée
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

bool Plateau::ajouterPiece_silencieux(string nom, char couleur)//meme chose que "ajouterPiece" mais sans afficher de message pour pouvoir créer des branches silencieusement
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

bool Plateau::capturePieces(Case* c)//vérifie si la pièce peut être capturée dans toutes les directions avec "verifie_la_prise" et appelle "capturePiece" si c'est le cas. La fonction renvoie true si au moins une pièce a été capturée et false sinon
{
    int i = 0;//compteur de pièces capturées
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

bool Plateau::verifie_la_prise(Case* c, Case* (Case::*getNeighbor)())//regarde dans la direction donnée si une pièce peut être capturée et renvoie true si c'est le cas
{
    while ((c->*getNeighbor)() != NULL && ((c->*getNeighbor)())->getCouleur() != '.' && ((c->*getNeighbor)())->getCouleur() != getCouleurJoueur() && ((c->*getNeighbor)()->*getNeighbor)() != NULL) 
    {//tant que la case suivante existe, qu'elle n'est pas vide, qu'elle n'est pas de la couleur du joueur qui joue et d'apres existe aussi
        c = (c->*getNeighbor)(); //on continue dans la direction à regarder plus loin
        if ((c->*getNeighbor)()->getCouleur() == couleur_joueur) {//si la case suivante est de la couleur du joueur qui joue->Il y a un encadrement de pièces->il y a prise
            //cout << "La pièce " << couleur_joueur << " peut être capturée en " << c->getNom() << endl;
            return true;
        }
    }
    return false;
}

void Plateau::capturePiece(Case* c, Case* (Case::*getNeighbor)())//capture les pièces dans la direction donnée jusqu'à rencontré une pièce de la couleur du joueur qui joue
{
    while ((c->*getNeighbor)()->getCouleur() != couleur_joueur)//tant que la case suivante n'est pas de la couleur du joueur qui joue
    {
        (c->*getNeighbor)()->setCouleur(couleur_joueur);//change la couleur de la pièce
        c = (c->*getNeighbor)();//on continue dans la direction à regarder plus loin
    }
}



//fonctions d'arret de jeu

bool Plateau::passe_le_tour()//appelle "verifie_si_le_joueur_peut_jouer" et renvoie true si le joueur ne peut pas jouer.
{
    if(verifie_si_le_joueur_peut_jouer(getCouleurJoueur())){
        return false;
    }
    else{
        cout << "Le joueur " << getCouleurJoueur() << " ne peut pas jouer, il passe son tour" << endl;
        return true;
    }
}

bool Plateau::verifie_si_le_joueur_peut_jouer(char couleur)//appelle "ajouterPieceVirtuelle" pour toutes les cases du plateau et renvoie true si au moins une pièce peut être ajoutée. La fonction renvoie false si aucune pièce ne peut être ajoutée
{
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    for (int i=1; i<9; i++)
    {
        for(int j=1; j<9; j++)
        {
            string nom = "";
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = cases.find(nom); //recherche la case dans la map
            if(ajouterPieceVirtuelle(nom, couleur)){//si au moins une pièce peut être ajoutée
                return true;   //s'arrete des qu'une pièce peut être ajoutée
            }
        }
    }
    return false;
}

bool Plateau::ajouterPieceVirtuelle(string nom, char couleur)//meme chose que "ajouterPiece" mais sans afficher de message et appelle "capturePiecesVirtuelle" au lieu de "capturePieces". La fonction renvoie true si au moins une pièce peut être capturée
{
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    itr = cases.find(nom); //recherche la case dans la map
    //print l'iterateur de la case
    if (itr->second->getCouleur() == '.') //si la case est vide
    {
        if(capturePiecesVirtuelle(itr->second) == true){
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

bool Plateau::capturePiecesVirtuelle(Case* c)//meme chose que "capturePieces" mais sans appeler "capturePiece" pour ne pas changer la couleur des pièces. La fonction renvoie true si au moins une pièce peut être capturée
{
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


void Plateau::affiche_score()//appelle "score_joueur" pour les deux joueurs et affiche le score et le gagnant
{
    int score_joueur_X = score_joueur('X');
    int score_joueur_O = score_joueur('O');
    cout << "Fin de partie" << endl;
    cout << "Score du joueur blanc : " << score_joueur_O << endl;
    cout << "Score du joueur noir : " << score_joueur_X << endl;
    if(score_joueur_X > score_joueur_O){
        cout << "Le joueur noir a gagné (X)" << endl;
    }
    else if(score_joueur_X < score_joueur_O){
        cout << "Le joueur blanc a gagné (O)" << endl;
    }
    else{
        cout << "Egalité" << endl;
    }
}

int Plateau::score_joueur(char couleur)//compte le nombre de pièces de la couleur donnée et renvoie le score
{
    int score = 0;//initialise le score
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
                score++;//ajoute 1 au score pour chaque pièce de la couleur du joueur
            }
        }
    }
    return score;
}


//fonctions d'intelligence artificielle

void Plateau::regarde_le_futur(char couleur, int profondeur)//crée l'arbre des possibilités pour les branches du plateau actuel tout en suivant un algo minimax avec élagage alpha beta
{
    char couleur_joueur_virtuel = couleur;
    if(couleur_joueur_virtuel == 'X'){
        setevaluation_score(-100000);//initialise le score à -100000 pour le joueur X
    }
    else{
        setevaluation_score(100000);//initialise le score à 100000 pour le joueur O
    }
    map<string, Case*>::iterator itr; //itérateur pour parcourir la map
    for(int i=1; i<9; i++){
        for(int j=1; j<9; j++){
            string nom = "";    
            nom += (char)(j + 96);
            nom += (char)(i + 48);
            itr = cases.find(nom); //recherche la case dans la map
            if(ajouterPieceVirtuelle(nom, couleur) == true)//si une pièce peut être ajoutée sur cette case
            {
                Plateau* p_virtuel = new Plateau(*this);//crée un plateau virtuel copie du plateau actuel
                p_virtuel->ajouterPiece_silencieux(nom, couleur);//ajoute une pièce sur la case du plateau virtuel
                ajoute_branche(p_virtuel);//ajoute le plateau virtuel comme branche du plateau actuel
                p_virtuel->root = this;//donne le plateau actuel comme racine du plateau virtuel
                //p_virtuel->afficherPlateau();//affiche le plateau virtuel
                if(profondeur > 0)//si la profondeur n'est pas atteinte, on continue de créer l'arbre des possibilités
                {
                    //le prochain joueur est le joueur adverse, on change donc la couleur du joueur virtuel pour la prochaine branche
                    if (couleur_joueur_virtuel == 'X')
                    {
                        couleur_joueur_virtuel = 'O';
                    }
                    else
                    {
                        couleur_joueur_virtuel = 'X';
                    }
                    p_virtuel->setCouleurJoueur(couleur_joueur_virtuel);//change la couleur du joueur virtuel pour la prochaine branche
                    p_virtuel->regarde_le_futur(couleur_joueur_virtuel, profondeur-1);//crée l'arbre des possibilités pour les branches du plateau actuel
                    //on revient sur le plateau actuel donc on récupère la couleur du joueur actuel
                    if (couleur_joueur_virtuel == 'X')
                    {
                        couleur_joueur_virtuel = 'O';
                    }
                    else
                    {
                        couleur_joueur_virtuel = 'X';
                    }
                    p_virtuel->setCouleurJoueur(couleur_joueur_virtuel);//récupère la couleur du joueur actuel
                }
                else{//si la profondeur est atteinte
                    p_virtuel->setevaluation_score(p_virtuel->evaluation());//évalue le plateau virtuel
                    //cout << "score du plateau virtuel : " << p_virtuel->getevaluation_score() << endl;
                }
                
                //elagage alpha beta
                if(root != NULL)//si le père du plateau virtuel existe et a un score d'évaluation différent de 0 (il a reçu son score d'évaluation d'un autre fils)
                {
                    //cout << root->getBranches().size() << endl;
                    for(Plateau* frere : root->getBranches()){//pour chaque frere du plateau actuel
                        if(frere != this){//si le frere est différent du plateau actuel
                            if(couleur_joueur_virtuel == 'X'){
                                if(frere->getevaluation_score() < p_virtuel->getevaluation_score()){//si le score du frere est supérieur au score du fils
                                    //cout << "élagage alpha" << endl;
                                    //cout << "score du frere : " << frere->getevaluation_score() << endl;
                                    //cout << "score du fils : " << p_virtuel->getevaluation_score() << endl;
                                    setevaluation_score(p_virtuel->getevaluation_score());//le score du plateau actuel est le score du frere avec le meilleur score
                                    return;//on arrête de créer des branches pour le plateau actuel
                                }
                            }
                            else{
                                if(frere->getevaluation_score() > p_virtuel->getevaluation_score()){//si le score du frere est inférieur au score du fils
                                    //cout << "élagage beta" << endl;
                                    setevaluation_score(p_virtuel->getevaluation_score());//le score du plateau actuel est le score du frere avec le meilleur score
                                    return;//on arrête de créer des branches pour le plateau actuel
                                }
                            }
                        }
                    }
                }
                
            }
        }
    }
    //le plateau actuel est évalué en fonction des scores de ses branches
    if(couleur_joueur_virtuel == 'X'){
        for(Plateau* branche : getBranches()){
            if(branche->getevaluation_score() > getevaluation_score()){
                setevaluation_score(branche->getevaluation_score());//le score du plateau actuel est le score de la branche avec le meilleur score
            }
        }
    }
    else{
        for(Plateau* branche : branches){
            if(branche->getevaluation_score() < getevaluation_score()){
                setevaluation_score(branche->getevaluation_score());//le score du plateau actuel est le score de la branche avec le meilleur score
            }
        }
    }
}

int Plateau::evaluation()//évalue le plateau en fonction du nombre de pièces de chaque joueur et de leur position sur le plateau. Renvoie le score.
{
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
                score++;//ajoute 1 au score pour chaque pièce de la couleur du joueur
                if(i == 1 || i == 8 || j == 1 || j == 8){//ajoute 10 au score pour chaque pièce sur un bord
                score += 10;
                }
                if((j == 1 && j == 8) || (i == 1 && i == 8) || (j == 1 && i == 1) || (j == 8 && i == 8)){//ajoute 100 au score pour chaque pièce dans un coin
                score += 100;
                }
            }
            if(itr->second->getCouleur() == 'O'){
                score--;//ajoute 1 au score pour chaque pièce de la couleur du joueur
                if(i == 1 || i == 8 || j == 1 || j == 8){//ajoute 10 au score pour chaque pièce sur un bord
                score -= 10;
                }
                if((j == 1 && j == 8) || (i == 1 && i == 8) || (j == 1 && i == 1) || (j == 8 && i == 8)){//ajoute 100 au score pour chaque pièce dans un coin
                score -= 100;
                }
            }
        }
    }
    return score;
}

void Plateau::supresseur_d_arbre()//s'appelle récursivement pour supprimer toutes les branches du plateau
{
    if(getBranches().size() > 0){//si le plateau a des branches
        for(Plateau* branche : getBranches()){//appelle chaque branche
            branche->supresseur_d_arbre();//supprime les branches de la branche
            delete branche;//supprime la branche
        }
    }
    branches.clear();//vide la liste des branches
}


void Plateau::creer_arbre(int profondeur)//nouvelle version de "regarde_le_futur"
{
    if(profondeur > 0)//si la profondeur n'est pas atteinte, on continue de créer l'arbre des possibilités
    {
        if(getBranches().size() > 0){//si le plateau a des branches
            for(Plateau* branche : getBranches()){//appelle chaque branche
                branche->creer_arbre(profondeur-1);//crée l'arbre des possibilités pour les branches du plateau actuel
            }
        }
        else{
            map<string, Case*>::iterator itr; //itérateur pour parcourir la map
            for(int i=1; i<9; i++){
                for(int j=1; j<9; j++){
                    string nom = "";    
                    nom += (char)(j + 96);
                    nom += (char)(i + 48);
                    itr = cases.find(nom); //recherche la case dans la map
                    if(ajouterPieceVirtuelle(nom, getCouleurJoueur()) == true)//si une pièce peut être ajoutée sur cette case
                    {
                        Plateau* p_virtuel = new Plateau(*this);//crée un plateau virtuel copie du plateau actuel
                        p_virtuel->ajouterPiece_silencieux(nom, getCouleurJoueur());//ajoute une pièce sur la case du plateau virtuel
                        ajoute_branche(p_virtuel);//ajoute le plateau virtuel comme branche du plateau actuel
                        p_virtuel->root = this;//donne le plateau actuel comme racine du plateau virtuel
                        //p_virtuel->afficherPlateau();//affiche le plateau virtuel
                        p_virtuel->changeCouleurJoueur();//on a ajouter une piece donc la couleur du plateau change
                        p_virtuel->evaluation_initiale();//initialise le score du plateau virtuel
                        p_virtuel->creer_arbre(profondeur-1);//crée l'arbre des possibilités pour les branches du plateau actuel
                        if(elagage_alpha_beta()){//si l'élagage alpha beta a été fait, on arrête de créer des branches pour le plateau actuel
                            return;
                        }
                    }
                }
            }
        }
    }
    else{//si la profondeur est atteinte
        setevaluation_score(evaluation());//évalue le plateau feuille
    }
    minimax();//appelle la fonction minimax pour le plateau actuel
}

void Plateau::evaluation_initiale()//donne une evaluation initiale en fonction de la couleur du plateau
{
    if(getCouleurJoueur() == 'X'){
        setevaluation_score(-100000);//initialise le score à -100000 pour le joueur X
    }
    else{
        setevaluation_score(100000);//initialise le score à 100000 pour le joueur O
    }
}

void Plateau::minimax()
{
    if(getCouleurJoueur()=='X'){
        for(Plateau* branche : getBranches()){
            if(branche->getevaluation_score() > getevaluation_score()){
                setevaluation_score(branche->getevaluation_score());//le score du plateau actuel est le score de la branche avec le meilleur score
            }
        }
    }
    else{
        for(Plateau* branche : branches){
            if(branche->getevaluation_score() < getevaluation_score()){
                setevaluation_score(branche->getevaluation_score());//le score du plateau actuel est le score de la branche avec le meilleur score
            }
        }
    }
}

bool Plateau::elagage_alpha_beta()
{
    if(root != NULL)//si le père du plateau virtuel existe et a un score d'évaluation différent de 0 (il a reçu son score d'évaluation d'un autre fils)
    {
        //cout << root->getBranches().size() << endl;
        for(Plateau* frere : root->getBranches()){//pour chaque frere du plateau actuel
            if(frere != this){//si le frere est différent du plateau actuel
                if(getCouleurJoueur() == 'X'){
                    for(Plateau* fils : getBranches()){
                        if(fils->getevaluation_score() > frere->getevaluation_score()){
                            setevaluation_score(fils->getevaluation_score());//le score du plateau actuel est le score de la branche avec le meilleur score
                            return true;//on arrête de créer des branches pour le plateau actuel
                        }
                    }
                }
                else{
                    for(Plateau* fils : getBranches()){
                        if(fils->getevaluation_score() < frere->getevaluation_score()){
                            setevaluation_score(fils->getevaluation_score());//le score du plateau actuel est le score de la branche avec le meilleur score
                            return true;//on arrête de créer des branches pour le plateau actuel
                        }
                    }
                }
            }
        }
    }
    return false;
}
