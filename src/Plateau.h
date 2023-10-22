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

    public:
        Plateau();
        ~Plateau();
        void afficherPlateau();
        //void ajouterPiece();
        //void capturePiece();
};