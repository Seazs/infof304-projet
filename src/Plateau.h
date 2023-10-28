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
        map<string, Case*> cases;
        char couleur_joueur;
        Plateau* root = NULL;
        list <Plateau*> branches;

    public:
        Plateau();
        Plateau(Plateau& plateau);
        ~Plateau();
        void setCouleurJoueur(char couleur);
        char getCouleurJoueur();
        void setCases(map<string, Case*> cases);
        map<string, Case*> getCases();
        void afficherPlateau();
        void ecoute_entree(); 
        void initialise_voisin_cases();
        void setVoisins(map<string, Case*>::iterator itr, char j, char i, void (Case::*setNeighbor)(Case*));

        //fonctions de jeu
        bool ajouterPiece(string nom, char couleur);
        bool ajouterPiece_silencieux(string nom, char couleur);
        bool ajouterPieceVirtuelle(string nom, char couleur);
        bool verifie_la_prise(Case* c, Case* (Case::*setNeighbor)());

        void capturePiece(Case* c, Case* (Case::*getNeighbor)());
        bool capturePieces(Case* c);
        bool capturePiecesVirtuelle(Case* c);

        //fonctions d'arret de jeu
        bool verifie_si_le_joueur_peut_jouer(char couleur);
        bool passe_le_tour();
        bool fin_de_partie();
        int score_joueur(char couleur);
        void affiche_score();

        //fonctions d'intelligence artificielle
        void regarde_le_futur(Plateau plateau, char couleur, int profondeur);

};