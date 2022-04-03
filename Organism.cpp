
class Organism
{
    private:
        int entityNumber;
        int age;
        int positionX;
        int positionY;

    public:
        Organism(){}
    
        Organism(int age, int positionX, int positionY)
        {
            this->age = age;
            this->positionX = positionX;
            this->positionY = positionY;
        }

        int getAge();
        void setAge(int newAge);

        int getPositionX();
        void setPositionX(int positionX);

        int getPositionY();
        void setPositionY(int positionY);

        virtual void move();
        virtual void breed();
};

void Organism::move()
{
}

void Organism::breed()
{
    
}

int Organism::getAge()
{
    return this->age;
}

void Organism::setAge(int newAge)
{
    this->age = newAge;
}

int Organism::getPositionX()
{
    return this->positionX;
}

void Organism::setPositionX(int positionX)
{
    this->positionX = positionX;
}

int Organism::getPositionY()
{
    return this->positionY;
}

void Organism::setPositionY(int positionY)
{
    this->positionY = positionY;
}