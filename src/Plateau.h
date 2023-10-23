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
        void afficherPlateau();
        void ecoute_entree(); 
        bool ajouterPiece(string nom, char couleur);
        //void capturePiece();
};