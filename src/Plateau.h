//plateau du jeu de reversi
#include <map>
#include <string>

#include "Case.h"

using std::map;
using std::string;
class Plateau 
{
    private:
        map<string, Case*> cases;
        char couleur_joueur;

    public:
        Plateau();
        ~Plateau();
        char getCouleurJoueur();
        void setCouleurJoueur(char couleur);
        void afficherPlateau();
        void ecoute_entree(); 
        void initialise_voisin_cases();
        void setVoisins(map<string, Case*>::iterator itr, char j, char i, void (Case::*setNeighbor)(Case*));

        bool ajouterPiece(string nom, char couleur);
        bool ajouterPieceVirtuelle(string nom, char couleur);
        bool verifie_la_prise(Case* c, Case* (Case::*setNeighbor)());
        bool verifie_la_prise_Up(Case* c);
        bool verifie_la_prise_Down(Case* c);
        bool verifie_la_prise_Left(Case* c);
        bool verifie_la_prise_Right(Case* c);
        bool verifie_la_prise_UpLeft(Case* c);
        bool verifie_la_prise_UpRight(Case* c);
        bool verifie_la_prise_DownLeft(Case* c);
        bool verifie_la_prise_DownRight(Case* c);

        void capturePiece(Case* c, Case* (Case::*getNeighbor)());
        bool capturePieces(Case* c);
        bool capturePiecesVirtuelle(Case* c);
        void capturePieceUp(Case* c);
        void capturePieceDown(Case* c);
        void capturePieceLeft(Case* c);
        void capturePieceRight(Case* c);
        void capturePieceUpLeft(Case* c);
        void capturePieceUpRight(Case* c);
        void capturePieceDownLeft(Case* c);
        void capturePieceDownRight(Case* c);
        bool verifie_si_le_joueur_peut_jouer(char couleur);
        bool passe_le_tour();
        bool fin_de_partie();
        int score_joueur(char couleur);
        void affiche_score();

};