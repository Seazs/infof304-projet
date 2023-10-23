#include "Case.h"

Case::Case(string nom)
{
    this->nom = nom;
    // initialise les cases voisines
    up = NULL;
    down = NULL;
    left = NULL;
    right = NULL;
    upLeft = NULL;
    upRight = NULL;
    downLeft = NULL;
    downRight = NULL;
    couleur = '.';
}

Case::~Case()
{
    //dtor
}

void Case::setVoisins(Case* up, Case* down, Case* left, Case* right, Case* upLeft, Case* upRight, Case* downLeft, Case* downRight)
{
    // defini les cases voisines
    this->up = up;
    this->down = down;
    this->left = left;
    this->right = right;
    this->upLeft = upLeft;
    this->upRight = upRight;
    this->downLeft = downLeft;
    this->downRight = downRight;
}

string Case::getNom()
{
    return nom;
}

Case* Case::getUp()
{
    return up;
}

Case* Case::getDown()
{
    return down;
}

Case* Case::getLeft()
{
    return left;
}

Case* Case::getRight()
{
    return right;
}

Case* Case::getUpLeft()
{
    return upLeft;
}

Case* Case::getUpRight()
{
    return  upRight;
}

Case* Case::getDownLeft()
{
    return  downLeft;
}

Case* Case::getDownRight()
{
    return  downRight;
}

void Case::setCouleur(char couleur)
{
    this->couleur = couleur;
}

char Case::getCouleur()
{
    return couleur;
}



