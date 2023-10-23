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

void Case::setUp(Case* up)
{
    this->up = up;
}

void Case::setDown(Case* down)
{
    this->down = down;
}

void Case::setLeft(Case* left)
{
    this->left = left;
}

void Case::setRight(Case* right)
{
    this->right = right;
}

void Case::setUpLeft(Case* upLeft)
{
    this->upLeft = upLeft;
}

void Case::setUpRight(Case* upRight)
{
    this->upRight = upRight;
}

void Case::setDownLeft(Case* downLeft)
{
    this->downLeft = downLeft;
}

void Case::setDownRight(Case* downRight)
{
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



