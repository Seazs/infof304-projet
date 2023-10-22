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
    string couleur;
public:
    Case();
    ~Case();
    void setCase(Case* up, Case* down, Case* left, Case* right, Case* upLeft, Case* upRight, Case* downLeft, Case* downRight);
    Case* getUp();
    Case* getDown();
    Case* getLeft();
    Case* getRight();
    Case* getUpLeft();
    Case* getUpRight();
    Case* getDownLeft();
    Case* getDownRight();
    
}
