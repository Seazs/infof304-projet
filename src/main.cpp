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
    char type_du_joueur_qui_joue = joueur1; //le joueur 1 commence toujours
    Plateau p; //initialise le plateau
    while (true)  //boucle de jeu
    {
        p.afficherPlateau(); // le plateau est affiché au debut de chaque tour
        if(p.passe_le_tour()){  //verifie si le joueur peut jouer
            p.changeCouleurJoueur(); //le joueur doit passé son tour -> change la couleur et le type du joueur qui joue
            if(type_du_joueur_qui_joue == joueur1){
                type_du_joueur_qui_joue = joueur2;
            }
            else{
                type_du_joueur_qui_joue = joueur1;
            }
            if(p.passe_le_tour()){ //verifie si le deuxieme joueur peut jouer
                p.affiche_score(); //finalise la partir
                break; // sort de la boucle de jeu
            }
        }
        if(type_du_joueur_qui_joue == 'H'){ //si le type de joueur qui joue est humain
            p.ecoute_entree();//l'humain joue
            p.changeCouleurJoueur(); //fin de tour -> change la couleur et le type du joueur qui joue
        }
        else if(type_du_joueur_qui_joue == 'A'){ //si le type de joueur qui joue est une intelligence artificielle
            cout << "L'ordinateur de couleur " << p.getCouleurJoueur() << " joue" << endl;
            p.tour_ia(7); //l'ia joue
        }
        else if(type_du_joueur_qui_joue == 'F'){ //si le type de joueur qui joue est un fichier
            p.ecoute_entree(); //le fichier joue
        }
        if(type_du_joueur_qui_joue == joueur1){
            type_du_joueur_qui_joue = joueur2;
        }
        else{
            type_du_joueur_qui_joue = joueur1;
        }
    }
    return 0; //fin du programme si on sort de la boucle de jeu
}
