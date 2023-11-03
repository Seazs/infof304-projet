#include <iostream>
#include "Plateau.h"
using std::cout;
using std::endl;

int main()
{
    Plateau p = Plateau();
    p.afficherPlateau();
    while (true)
    {
        if(p.fin_de_partie()){
            p.affiche_score();
            break;
        }
        p.ecoute_entree();
        p.afficherPlateau();
    }
    return 0;
}
