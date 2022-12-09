/*
int *ary = new int[sizeX*sizeY];

// ary[i][j] is then rewritten as
ary[i*sizeY+j]
*/

#include "Doodlebug.cpp"
#include <string>

const int ANT_BREED_THRESHOLD = 3;
const int DOODLEBUG_STARVE_THRESHOLD = 3;
const int DOODLEBUG_BREED_THRESHOLD = 8;
const int STARTING_NUMBER_OF_ANTS = 100;
const int STARTING_NUMBER_OF_DOODLEBUGS = 5;
const int WORLD_LENGTH = 20;
const int WORLD_BREADTH = 20;

const char SYMBOL_ANT = 'o';
const char SYMBOL_DOODLEBUG = 'X';
const char SYMBOL_VACANT_SPACE = '-';

//List of functions in this file.
Doodlebug createDoodlebug(int entityNumber, int positionX, int positionY);
Ant createAnt(int entityNumber, int positionX, int positionY);
bool isOccupiedByAnt(char world[], int positionX, int positionY);
bool isOccupiedByDoodleBug(char world[], int positionX, int positionY);
bool isVacant(char world[], int positionX, int positionY);
void findRandomVacantLocation(char world[],int* i, int* j);
void worldBuilder(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants);
void displayWorldInstance(char world[]);
void eat(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants, int i, int positionToEatX, int positionToEatY);
void turnDoodlebug(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants);
void moveDoodlebugRandomly(char world[], vector<Doodlebug>& doodlebugs, int i);
void breedDoodlebugRandomly(char world[], vector<Doodlebug>& doodlebugs, int i);
void turnAnt(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants);
void moveAntRandomly(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ant, int i);
void breedAntRandomly(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants, int i);


int main()
{
    //Seeding random function.
    srand(time(0));

    //the world array will hold and display the current status of the simulation world as it is.
    char* world = new char[WORLD_LENGTH * WORLD_BREADTH];

    //Ant vector will keep track of all the ants in the simulation.
    vector<Ant> ants;

    vector<Doodlebug> doodlebugs;

    worldBuilder(world,doodlebugs, ants);
    cout << "Loading new world..." << endl;
    cout << endl;
    displayWorldInstance(world);
    cout << endl;
    cout << "Press enter to continue, ctrl+C to exit: ";

    cout << endl;
    
    while(cin.get())
    {
        if (doodlebugs.size() == 0)
        {
            cout << "All doodlebugs are dead. Simulation ends." << endl;
            break;
        }
        if (ants.size() == 0)
        {
            cout << "All ants are dead. Simulation ends." <<  endl;
            break;
        }
        cout << endl;

        turnDoodlebug(world,doodlebugs,ants);

        turnAnt(world,doodlebugs,ants);

        displayWorldInstance(world);

        cout << endl;

        //cout << "Number of ants: " << ants.size() << endl;
        //cout << "Number of doodlebugs: " << doodlebugs.size() << endl;

        cout << "Press enter to continue, ctrl+C to exit: " << endl;
    }
}


//Function to create a new doodlebug at a given location.
Doodlebug createDoodlebug(int positionX, int positionY)
{
    int age = 0;
    Doodlebug db(age, positionX, positionY);
    return db;
}

//Function to create a new ant at a given location.
Ant createAnt( int positionX, int positionY)
{
    int age = 0;
    Ant at(age,positionX,positionY);
    return at;
}

//Function to check if a particular location in the world is occupied by an ant.
bool isOccupiedByAnt(char world[], int positionX, int positionY)
{
    if (positionY > WORLD_BREADTH - 1 || positionY < 0 || positionX > WORLD_LENGTH - 1 || positionX < 0)
    {
        return false;
    }
    if (world[positionX * WORLD_BREADTH + positionY] == SYMBOL_ANT)
    {
        return true;
    }
    return false;
}

//Function to check if a particular location in the world is occupied by a doodlebug.
bool isOccupiedByDoodleBug(char world[], int positionX, int positionY)
{
    if (positionY > WORLD_BREADTH - 1 || positionY < 0 || positionX > WORLD_LENGTH - 1 || positionX < 0)
    {
        return false;
    }
    if (world[positionX * WORLD_BREADTH + positionY] == SYMBOL_DOODLEBUG)
    {
        return true;
    }
    return false;
}

//Function to check if a particular location in the world is vacant.
bool isVacant(char world[], int positionX, int positionY)
{
    if (positionY > WORLD_BREADTH - 1 || positionY < 0 || positionX > WORLD_LENGTH - 1 || positionX < 0)
    {
        return false;
    }
    if(world[positionX * WORLD_BREADTH + positionY] == SYMBOL_VACANT_SPACE)
    {
        return true;
    }
    return false;
}

//Function to recursively find a random vacant location in the world and update the reference variables with the coordinates.
void findRandomVacantLocation(char world[],int* i, int* j)
{
    int positionX = (rand() % WORLD_LENGTH);
    int positionY = (rand() % WORLD_BREADTH);

    if(isVacant(world,positionX,positionY))
    {
        *i = positionX;
        *j = positionY;
        return;
    }
    else
    {
        findRandomVacantLocation(world, i,j);
    }
}

//Function to create a world of defined area (using X and Y coordinates) and populate it with initial number of creatures.
void worldBuilder(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants)
{
    //Initializing all squares to  vacant space.
    for(int i = 0; i < WORLD_BREADTH * WORLD_LENGTH; i++)
    {
        world[i] = SYMBOL_VACANT_SPACE;
    }

    for(int i = 1; i <= STARTING_NUMBER_OF_DOODLEBUGS; i++)
    {
        int positionX = 0, positionY = 0;
        findRandomVacantLocation(world, &positionX, &positionY);

        doodlebugs.push_back(createDoodlebug(positionX,positionY));

        world[positionX * WORLD_BREADTH + positionY] = SYMBOL_DOODLEBUG;
    }

    for(int i = 1; i <= STARTING_NUMBER_OF_ANTS; i++)
    {
        int positionX = 0, positionY = 0;
        findRandomVacantLocation(world,&positionX, &positionY);

        ants.push_back(createAnt(positionX, positionY));
        world[positionX * WORLD_BREADTH + positionY] = SYMBOL_ANT;
    }
}

//Function to display the world array in 2D format.
void displayWorldInstance(char world[])
{
    for(int i = 0; i < WORLD_LENGTH; i++)
    {
        for(int j = 0; j < WORLD_BREADTH; j++)
        {
            cout << world[i * WORLD_BREADTH + j] << " ";
        }
        cout << endl;
    }
}

//Function to replace a particular ant with a particular doodlebug at a particular location.
void eat(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants, int i, int positionToEatX, int positionToEatY)
{
    int doodlebugPositionX = doodlebugs[i].getPositionX();
    int doodlebugPositionY = doodlebugs[i].getPositionY();

    //replacing doodlebug's current position with that of vacant space.
    world[doodlebugPositionX * WORLD_BREADTH + doodlebugPositionY] = SYMBOL_VACANT_SPACE;

    //placing the doodlebug at its new location.
    world[positionToEatX * WORLD_BREADTH + positionToEatY] = SYMBOL_DOODLEBUG;

    //updating the doodlebug's parameters in the doodlebugs tracker vector.
    doodlebugs[i].setPositionX(positionToEatX);
    doodlebugs[i].setPositionY(positionToEatY);

    //since the doodlebug has eaten, it's eat counter is reset to 0.
    doodlebugs[i].setStepsSinceLastEaten(0);

    //Modifying the ants vector to remove the ant object that the current doodlebug ate.
    vector<Ant>::iterator it;
    for (it = ants.begin(); it != ants.end(); it++)
    {
        if (it->getPositionX() == positionToEatX && it->getPositionY() == positionToEatY)
        {
            ants.erase(it);
            break;
        }
    }
}

//Function to process doodlebugs' turn.
void turnDoodlebug(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants)
{

    //looping through doodlebugs, one at a time.
    for (int i = 0; i < doodlebugs.size(); i++)
    {
        //increasing age of all doodlebugs by 1.
        doodlebugs[i].setAge(doodlebugs[i].getAge() + 1);

        int doodlebugPositionX = doodlebugs[i].getPositionX(), doodlebugPositionY = doodlebugs[i].getPositionY();

        //Finding and storing the positions of nearby left, right, up and down blocks.
        int positionLeftX = doodlebugPositionX, positionLeftY = doodlebugPositionY - 1;

        int positionRightX = doodlebugPositionX, positionRightY = doodlebugPositionY + 1;

        int positionUpX = doodlebugPositionX - 1, positionUpY = doodlebugPositionY;

        int positionDownX = doodlebugPositionX + 1, positionDownY = doodlebugPositionY;

        //Checking if the adjacent position is valid (ie within the bounds of the world) and is occupied by an ant in the order:
        // up, down, left, right as stated in requirements.
        if (positionUpX >= 0 && isOccupiedByAnt(world, positionUpX, positionUpY))
        {
            eat(world, doodlebugs, ants, i, positionUpX, positionUpY);
        }
        else if (positionDownX < WORLD_LENGTH && isOccupiedByAnt(world,positionDownX,positionDownY))
        {
            eat(world, doodlebugs, ants, i, positionDownX, positionDownY);
        }
		else if (positionLeftY >= 0 && isOccupiedByAnt(world,positionLeftX,positionLeftY))
        {
            eat(world, doodlebugs, ants, i, positionLeftX, positionLeftY);
        }
        else if (positionRightY < WORLD_BREADTH && isOccupiedByAnt(world, positionRightX, positionRightY))
        {
            eat(world, doodlebugs, ants, i, positionRightX, positionRightY);
        }
        else
        {
        	moveDoodlebugRandomly(world, doodlebugs, i);
            int eatenSteps = doodlebugs[i].getStepsSinceLastEaten() + 1;
            doodlebugs[i].setStepsSinceLastEaten(eatenSteps);
        }

        if (doodlebugs[i].getStepsSinceLastEaten() == DOODLEBUG_STARVE_THRESHOLD)
        {
            world[doodlebugs[i].getPositionX() * WORLD_BREADTH + doodlebugs[i].getPositionY()] = SYMBOL_VACANT_SPACE;
            vector<Doodlebug>::iterator it;
            it = doodlebugs.begin();
            for (int j = 0; j < i; j++)
            {
                it++;
            }
            doodlebugs.erase(it);
        }

        if (doodlebugs[i].getAge() == DOODLEBUG_BREED_THRESHOLD)
        {
            breedDoodlebugRandomly(world, doodlebugs, i);
        }
    }
}

void moveDoodlebugRandomly(char world[], vector<Doodlebug>& doodlebugs, int i)
{
    //Making a random choice.
	int choice = (rand() % 4) + 1;
	
	int doodlebugPositionX = doodlebugs[i].getPositionX(), doodlebugPositionY = doodlebugs[i].getPositionY();

	//Finding and storing the positions of nearby left, right, up and down blocks.
    int positionLeftX = doodlebugPositionX, positionLeftY = doodlebugPositionY - 1;

    int positionRightX = doodlebugPositionX, positionRightY = doodlebugPositionY + 1;

    int positionUpX = doodlebugPositionX - 1, positionUpY = doodlebugPositionY;

    int positionDownX = doodlebugPositionX + 1, positionDownY = doodlebugPositionY;

    //Breaking condition for when the doodlebug is surrounded by other doodlebugs and cannot move.
    if (isOccupiedByDoodleBug(world,positionLeftX,positionLeftY) && isOccupiedByDoodleBug(world,positionRightX,positionRightY) && isOccupiedByDoodleBug(world,positionUpX,positionUpY) && isOccupiedByDoodleBug(world,positionDownX,positionDownY))
    {
        return;
    }
    
    if (choice == 1 && positionUpX >= 0)
    {
        //changing the current position of doodlebug to vacant space.
        world[doodlebugPositionX * WORLD_BREADTH + doodlebugPositionY] = SYMBOL_VACANT_SPACE;

        //placing the doodlebug at a new location in the world
        world[positionUpX * WORLD_BREADTH + positionUpY] = SYMBOL_DOODLEBUG;

        //updating the doodlebug tracker
        doodlebugs[i].setPositionX(positionUpX);
        doodlebugs[i].setPositionY(positionUpY);

        return;
    }
    if (choice == 2 && positionDownX < WORLD_LENGTH)
    {
        world[doodlebugPositionX * WORLD_BREADTH + doodlebugPositionY] = SYMBOL_VACANT_SPACE;
        world[positionDownX * WORLD_BREADTH + positionDownY] = SYMBOL_DOODLEBUG;

        doodlebugs[i].setPositionX(positionDownX);
        doodlebugs[i].setPositionY(positionDownY);
        return;
    }
    if (choice == 3 && positionLeftY >= 0)
    {
        world[doodlebugPositionX * WORLD_BREADTH + doodlebugPositionY] = SYMBOL_VACANT_SPACE;
        world[positionLeftX * WORLD_BREADTH + positionLeftY] = SYMBOL_DOODLEBUG;

        doodlebugs[i].setPositionX(positionLeftX);
        doodlebugs[i].setPositionY(positionLeftY);
        return;
    }
    if(choice == 4 && positionRightY < WORLD_BREADTH)
    {
        world[doodlebugPositionX * WORLD_BREADTH + doodlebugPositionY] = SYMBOL_VACANT_SPACE;
        world[positionRightX * WORLD_BREADTH + positionRightY] = SYMBOL_DOODLEBUG;

        doodlebugs[i].setPositionX(positionRightX);
        doodlebugs[i].setPositionY(positionRightY);
        return;
    }
    moveDoodlebugRandomly(world,doodlebugs, i);
}

void breedDoodlebugRandomly(char world[], vector<Doodlebug>& doodlebugs, int i)
{
    //Generating a random choice.
    int choice = (rand() % 4) + 1;

    int doodlebugPositionX = doodlebugs[i].getPositionX(), doodlebugPositionY = doodlebugs[i].getPositionY();

	//Finding and storing the positions of nearby left, right, up and down blocks.
    int positionLeftX = doodlebugPositionX, positionLeftY = doodlebugPositionY - 1;

    int positionRightX = doodlebugPositionX, positionRightY = doodlebugPositionY + 1;

    int positionUpX = doodlebugPositionX - 1, positionUpY = doodlebugPositionY;

    int positionDownX = doodlebugPositionX + 1, positionDownY = doodlebugPositionY;

    //If no position is valid, no breeding occurs.
    if (!(isVacant(world,positionLeftX,positionLeftY)) && !(isVacant(world, positionRightX, positionRightY)) && !(isVacant(world,positionUpX,positionUpY)) && !(isVacant(world, positionDownX, positionDownY)))
    {
        return;
    }

    //Position is valid if it is in the world and is vacant.
    if (choice == 1 && isVacant(world,positionLeftX,positionLeftY) && positionLeftY >= 0)
    {
        world[positionLeftX * WORLD_BREADTH + positionLeftY] = SYMBOL_DOODLEBUG;

        //creating a new doodlebug object and pushing it into the vector.
        doodlebugs.push_back(createDoodlebug(positionLeftX,positionLeftY));

        //Changing the current doodlebug's age to 0 since it has bred already.
        doodlebugs[i].setAge(0);
        return;
    }
    if (choice == 2 && isVacant(world, positionRightX, positionRightY) && positionRightY < WORLD_BREADTH)
    {
        world[positionRightX * WORLD_BREADTH + positionRightY] = SYMBOL_DOODLEBUG;

        //creating a new doodlebug object and pushing it into the vector.
        doodlebugs.push_back(createDoodlebug(positionRightX,positionRightY));

        //Changing the current doodlebug's age to 0 since it has bred already.
        doodlebugs[i].setAge(0);
        return;
    }
    if (choice == 3 && isVacant(world,positionUpX,positionUpY) && positionUpX >= 0)
    {
        world[positionUpX * WORLD_BREADTH + positionUpY] = SYMBOL_DOODLEBUG;

        //creating a new doodlebug object and pushing it into the vector.
        doodlebugs.push_back(createDoodlebug(positionUpX,positionUpY));

        //Changing the current doodlebug's age to 0 since it has bred already.
        doodlebugs[i].setAge(0);
        return;
    }
    if (choice == 4 && isVacant(world, positionDownX, positionDownY) && positionDownX < WORLD_LENGTH)
    {
        doodlebugs.push_back(createDoodlebug(positionDownX,positionDownY));
        world[positionDownX * WORLD_BREADTH + positionDownY] = SYMBOL_DOODLEBUG;
        doodlebugs[i].setAge(0);
        return;
    }

    //if the choice turns out to be invalid, try again.
    breedDoodlebugRandomly(world,doodlebugs,i);
}

void turnAnt(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants)
{
    for (int i = 0; i < ants.size(); i++)
    {
        //increasing the age of current ant by 1.
        ants[i].setAge(ants[i].getAge() + 1);

        int antPositionX = ants[i].getPositionX(), antPositionY = ants[i].getPositionY();
        int leftPositionX = antPositionX, leftPositionY = antPositionY - 1;
        int rightPositionX = antPositionX, rightPositionY = antPositionY + 1;
        int upPositionX = antPositionX - 1, upPositionY = antPositionY;
        int downPositionX = antPositionX + 1, downPositionY = antPositionY;

        moveAntRandomly(world,doodlebugs,ants,i);

        if (ants[i].getAge() == 3)
        {
            breedAntRandomly(world,doodlebugs,ants,i);
            ants[i].setAge(0);
        }
    }
}

void moveAntRandomly(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants, int i)
{
    int choice = (rand() % 4) + 1;

    int antPositionX = ants[i].getPositionX(), antPositionY = ants[i].getPositionY();
    int leftPositionX = antPositionX, leftPositionY = antPositionY - 1;
    int rightPositionX = antPositionX, rightPositionY = antPositionY + 1;
    int upPositionX = antPositionX - 1, upPositionY = antPositionY;
    int downPositionX = antPositionX + 1, downPositionY = antPositionY;

    //breaking condition for when all adjacent positions are occupied.
    if (!(isVacant(world,leftPositionX,leftPositionY)) && !(isVacant(world,rightPositionX,rightPositionY)) && !(isVacant(world,upPositionX,upPositionY)) && !(isVacant(world,downPositionX,downPositionY)))
    {
        return;
    }

    //If choice is left, and left position is valid as well as vacant, move the ant to left.
    if (choice == 1 && leftPositionY >= 0 && isVacant(world,leftPositionX,leftPositionY))
    {
        world[antPositionX * WORLD_BREADTH + antPositionY] = SYMBOL_VACANT_SPACE;
        world[leftPositionX * WORLD_BREADTH + leftPositionY] = SYMBOL_ANT;
        ants[i].setPositionX(leftPositionX);
        ants[i].setPositionY(leftPositionY);
        return;
    }

    if (choice == 2 && rightPositionY < WORLD_BREADTH && isVacant(world, rightPositionX,rightPositionY))
    {
        world[antPositionX * WORLD_BREADTH + antPositionY] = SYMBOL_VACANT_SPACE;
        world[rightPositionX * WORLD_BREADTH + rightPositionY] = SYMBOL_ANT;
        ants[i].setPositionX(rightPositionX);
        ants[i].setPositionY(rightPositionY);
        return;
    }

    if (choice == 3 && upPositionX >= 0 && isVacant(world,upPositionX,upPositionY))
    {
        world[antPositionX * WORLD_BREADTH + antPositionY] = SYMBOL_VACANT_SPACE;
        world[upPositionX * WORLD_BREADTH + upPositionY] = SYMBOL_ANT;
        ants[i].setPositionX(upPositionX);
        ants[i].setPositionY(upPositionY);
        return;
    }

    if (choice == 4 && downPositionX << WORLD_LENGTH && isVacant(world,downPositionX,downPositionY))
    {
        world[antPositionX * WORLD_BREADTH + antPositionY] = SYMBOL_VACANT_SPACE;
        world[downPositionX * WORLD_BREADTH + downPositionY] = SYMBOL_ANT;
        ants[i].setPositionX(downPositionX);
        ants[i].setPositionY(downPositionY);
        return;
    }
    moveAntRandomly(world,doodlebugs,ants,i);
}

void breedAntRandomly(char world[], vector<Doodlebug>& doodlebugs, vector<Ant>& ants, int i)
{
    int choice = (rand() % 4) + 1;
    int antPositionX = ants[i].getPositionX(), antPositionY = ants[i].getPositionY();
    int leftPositionX = antPositionX, leftPositionY = antPositionY - 1;
    int rightPositionX = antPositionX, rightPositionY = antPositionY + 1;
    int upPositionX = antPositionX - 1, upPositionY = antPositionY;
    int downPositionX = antPositionX + 1, downPositionY = antPositionY;

    if (!(isVacant(world,leftPositionX,leftPositionY)) && !(isVacant(world,rightPositionX,rightPositionY)) && !(isVacant(world,upPositionX,upPositionY)) && !(isVacant(world,downPositionX,downPositionY)))
    {
        return;
    }

    //If choice is left, and left position is valid as well as vacant, move the ant to left.
    if (choice == 1 && leftPositionY >= 0 && isVacant(world,leftPositionX,leftPositionY))
    {
        world[leftPositionX * WORLD_BREADTH + leftPositionY] = SYMBOL_ANT;
        ants.push_back(createAnt(leftPositionX,leftPositionY));
        return;
    }

    if (choice == 2 && rightPositionY < WORLD_BREADTH && isVacant(world, rightPositionX,rightPositionY))
    {
        world[rightPositionX * WORLD_BREADTH + rightPositionY] = SYMBOL_ANT;
        ants.push_back(createAnt(rightPositionX,rightPositionY));
        return;
    }

    if (choice == 3 && upPositionX >= 0 && isVacant(world,upPositionX,upPositionY))
    {
        world[upPositionX * WORLD_BREADTH + upPositionY] = SYMBOL_ANT;
        ants.push_back(createAnt(upPositionX,upPositionY));
        return;
    }

    if (choice == 4 && downPositionX << WORLD_LENGTH && isVacant(world,downPositionX,downPositionY))
    {
        world[downPositionX * WORLD_BREADTH + downPositionY] = SYMBOL_ANT;
        ants.push_back(createAnt(downPositionX,downPositionY));
        return;
    }
    breedAntRandomly(world,doodlebugs,ants,i);
}

