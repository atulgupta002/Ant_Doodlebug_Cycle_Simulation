#include "Ant.cpp"

class Doodlebug: public Organism
{
    public:
    Doodlebug( int age, int positionX, int positionY):Organism(age, positionX,positionY){
        this->stepsSinceLastEaten = 0;
    }
    void move(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants, int i);
    void breed();
    int getStepsSinceLastEaten();
    void setStepsSinceLastEaten(int newSteps);

    private:
    int stepsSinceLastEaten;

};

int Doodlebug::getStepsSinceLastEaten()
{
    return this->stepsSinceLastEaten;
}

void Doodlebug::setStepsSinceLastEaten(int newSteps)
{
    this->stepsSinceLastEaten = newSteps;
}

void Doodlebug::move(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants, int i)
{
}

void Doodlebug::breed()
{
}

