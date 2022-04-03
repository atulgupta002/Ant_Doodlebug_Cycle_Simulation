#include "Organism.cpp"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

class Ant: public Organism
{
    public:
    Ant(int age, int positionX, int positionY):Organism(age, positionX, positionY){}
    void move();
    void breed();
    bool isOccupiedByAnt(char world[], int positionX, int positionY);
};

void Ant::move()
{
}

void Ant::breed()
{
}