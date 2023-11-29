//plateau du jeu de reversi
#include <map>
#include <string>
#include "Case.h"
#include <list>
using std::list;
using std::map;
using std::string;

class Plateau 
{
    private:
        map<string, Case*> cases; //map de toutes les cases du plateau
        char couleur_joueur; //couleur du joueur qui doit jouer
        Plateau* root = NULL; //pointeur vers la racine/père du plateau
        list<Plateau*> branches ; //liste des pointeurs des branches/fils du plateau
        int evaluation_score; //score d'évaluation du plateau (ou celui recu de ses fils)
        string NomJoueur1; 
        string NomJoueur2;
        char lettre_joueur1; 
        char lettre_joueur2;

    public:
        //méthodes de création, de copie et de destruction
        Plateau();//constructeur par défaut
        Plateau(Plateau& plateau);//constructeur de copie
        ~Plateau();//destructeur
        //méthodes d'initialisation
        void setCouleurJoueur(char couleur);
        void setCases(map<string, Case*> cases);
        void initialise_voisin_cases();
        void setVoisins(map<string, Case*>::iterator itr, char j, char i, void (Case::*setNeighbor)(Case*));
        void setevaluation_score(int score);
        //méthodes d'accès
        void demande_nom_joueur1(char nom_joueur);
        void demande_nom_joueur2(char nom_joueur);
        char getCouleurJoueur();
        map<string, Case*> getCases();
        list<Plateau*> getBranches();
        int getevaluation_score();
        //méthodes de modification
        void changeCouleurJoueur();
        void ajoute_branche(Plateau* branche);
        //méthodes d'affichage
        void afficherPlateau();
        //méthodes de jeu
        void ecoute_entree(); 
        void tour_ia(int profondeur);


        //fonctions de jeu
        bool ajouterPiece(string nom, char couleur);
        bool ajouterPiece_silencieux(string nom, char couleur);
        bool capturePieces(Case* c);
        bool verifie_la_prise(Case* c, Case* (Case::*setNeighbor)());
        void capturePiece(Case* c, Case* (Case::*getNeighbor)());
        

        //fonctions d'arret de jeu
        bool passe_le_tour();
        bool verifie_si_le_joueur_peut_jouer(char couleur);
        bool ajouterPieceVirtuelle(string nom, char couleur);
        bool capturePiecesVirtuelle(Case* c);
        void affiche_score();
        int score_joueur(char couleur);
        

        //fonctions d'intelligence artificielle
        void regarde_le_futur(char couleur, int profondeur);
        int evaluation();
        void supresseur_d_arbre();

        void creer_arbre(int profondeur); 
        void nouvelles_branches();  
        void evaluation_initiale();
        void minimax();
        bool elagage_alpha_beta();

};