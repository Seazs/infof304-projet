#include <iostream>
#include "Plateau.h"

int main()
{
    Plateau p = Plateau();
    p.afficherPlateau();
    while (true)
    {
        p.ecoute_entree();
        p.afficherPlateau();
    }
    return 0;
}
