#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;   
    myDir = STOP;
    playerPos = {4, 9, '*'}; 
    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos array list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    if(mainGameMechsRef->getInput() != 0) {
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
    mainGameMechsRef->setInput(0);
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    // movement implementation
    switch(myDir) {
        case LEFT: 
            playerPos.pos->y--; 
            break;
        case RIGHT: 
            playerPos.pos->y++; 
            break;
        case UP: 
            playerPos.pos->x--; 
            break;
        case DOWN: 
            playerPos.pos->x++;
            break;
        default: 
            break;
    }

    // wrap around implementation
    if(playerPos.pos->x == 0) 
        playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 1;
    else if (playerPos.pos->x == mainGameMechsRef->getBoardSizeX())
        playerPos.pos->x = 1;
    else if (playerPos.pos->y == 0) 
        playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 1;
    else if (playerPos.pos->y == mainGameMechsRef->getBoardSizeY()) 
        playerPos.pos->y = 1;
}

// More methods to be added