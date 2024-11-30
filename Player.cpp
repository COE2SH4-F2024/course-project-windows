#include "Player.h"
#include "objPos.h"
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;   
    myDir = STOP;
    playerPosList = new objPosArrayList;
    foodPos = thisGMRef->getFoodPos();
    
    //setting head of snake
    objPos part = {5, 9, '*'};
    playerPosList->insertHead(part);
    head = playerPosList->getHeadElement();
    // more actions to be included
}

Player::~Player()
{
    delete[] playerPosList;
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    if(mainGameMechsRef->getInput() != '\0') {
        switch(mainGameMechsRef->getInput()) {                      
            case '/':  
                mainGameMechsRef->setExitTrue(); 
                break;
            case 'a':  
                if(myDir != RIGHT) 
                    myDir = LEFT; 
                break;
            case 'd':  
                if(myDir != LEFT) 
                    myDir = RIGHT; 
                break;
            case 'w':  
                if(myDir != DOWN) 
                    myDir = UP; 
                break;
            case 's':  
                if(myDir != UP) 
                    myDir = DOWN; 
                break;
            default:   
                break;
        }
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    // movement implementation
    switch(myDir) {
        case LEFT: 
            (head.pos->y)--; 
            break;
        case RIGHT: 
            (head.pos->y)++; 
            break;
        case UP: 
            (head.pos->x)--; 
            break;
        case DOWN: 
            (head.pos->x)++;
            break;
        default: 
            break;
    }

    // wrap around implementation
    if(head.pos->x == 0) 
        head.pos->x = mainGameMechsRef->getBoardSizeX()-2;
    else if (head.pos->x == (mainGameMechsRef->getBoardSizeX()-1))
        head.pos->x = 1;
    else if (head.pos->y == 0) 
        head.pos->y = mainGameMechsRef->getBoardSizeY()-2;
    else if (head.pos->y == (mainGameMechsRef->getBoardSizeY()-1)) 
        head.pos->y = 1;
    
    //insertion of head and removal of tail
    foodPos = mainGameMechsRef->getFoodPos();
    if(checkFoodConsumption()) {
        mainGameMechsRef->generateFood(head);
        playerPosList->insertHead(head);
    } else {
        playerPosList->insertHead(head);
        playerPosList->removeTail();
    }
}

bool Player::checkFoodConsumption() {
    return(head.getPosX() == foodPos.getPosX() && head.getPosY() == foodPos.getPosY());
}

// More methods to be added
