class Case
{
private:
    Case* up;
    Case* down;
    Case* left;
    Case* right;
    Case* upLeft;
    Case* upRight;
    Case* downLeft;
    Case* downRight;
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
