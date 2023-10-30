#include <iostream>
#include "Plateau.h"
using std::cout;
using std::endl;
using std::cin;

int main()
{
    cout << "Bienvenue au jeu de reversi" << endl;
    cout << "Choisissez le type du joueur 1 (humain (H), intelligence artificielle (A) ou fichier (F)) : ";
    char joueur1;
    cin >> joueur1;
    cout << "Choisissez le type du joueur 2 (humain (H), intelligence artificielle (A) ou fichier (F)) : ";
    char joueur2;
    cin >> joueur2;
    if(joueur1 != 'H' && joueur1 != 'A' && joueur1 != 'F' && joueur2 != 'H' && joueur2 != 'A' && joueur2 != 'F'){
        cout << "Vous avez choisi un type de joueur invalide" << endl;
        return 0;
    }
    char type_du_joueur_qui_joue = joueur1;
    Plateau p;
    p.afficherPlateau();
    while (true)
    {
        if(p.fin_de_partie()){
            p.affiche_score();
            break;
        }
        
        if(type_du_joueur_qui_joue == 'H'){
            p.ecoute_entree();
        }
        else if(type_du_joueur_qui_joue == 'A'){
            p.regarde_le_futur(p, p.getCouleurJoueur(),2);
            //boucle qui parcourt les branches du plateau et qui affiche le score de chaque branche
            for (list<Plateau*>::iterator it = p.getBranches().begin(); it != p.getBranches().end(); it++)
            {
                cout << "score de la branche : " << (*it)->getevaluation_score() << endl;
            }
        }
        else if(type_du_joueur_qui_joue == 'F'){
            p.ecoute_entree();
        }
        cout << "vrai plateau" << endl;
        p.afficherPlateau();
        if(type_du_joueur_qui_joue == joueur1){
            type_du_joueur_qui_joue = joueur2;
        }
        else{
            type_du_joueur_qui_joue = joueur1;
        }
    }
    return 0;
}
