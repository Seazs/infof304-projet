#include <string>
using std::string;

class Case
{
private:
    string nom;
    Case* up;
    Case* down;
    Case* left;
    Case* right;
    Case* upLeft;
    Case* upRight;
    Case* downLeft;
    Case* downRight;
    char couleur;
public:
    Case(string nom);
    ~Case();
    void setCouleur(char couleur);
    char getCouleur();

    void setUp(Case* up);
    void setDown(Case* down);
    void setLeft(Case* left);
    void setRight(Case* right);
    void setUpLeft(Case* upLeft);
    void setUpRight(Case* upRight);
    void setDownLeft(Case* downLeft);
    void setDownRight(Case* downRight);
    

    string getNom();
    Case* getUp();
    Case* getDown();
    Case* getLeft();
    Case* getRight();
    Case* getUpLeft();
    Case* getUpRight();
    Case* getDownLeft();
    Case* getDownRight();
};
