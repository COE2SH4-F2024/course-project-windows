#include "Player.h"
#include "objPos.h"
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;   
    myDir = STOP;
    playerPosList = new objPosArrayList;
    foodPos = thisGMRef->getFoodPos();
    
    objPos part = {7, 15, '*'};
    playerPosList->insertHead(part);

    head = playerPosList->getHeadElement();
}

Player::~Player() {
    delete[] playerPosList;
    delete[] mainGameMechsRef;
}

objPosArrayList* Player::getPlayerPos() const {
    return playerPosList;
}

void Player::updatePlayerDir()
{
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

void Player::movePlayer() {
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

    if(head.pos->x == 0) 
        head.pos->x = mainGameMechsRef->getBoardSizeX()-2;
    else if (head.pos->x == (mainGameMechsRef->getBoardSizeX()-1))
        head.pos->x = 1;
    else if (head.pos->y == 0) 
        head.pos->y = mainGameMechsRef->getBoardSizeY()-2;
    else if (head.pos->y == (mainGameMechsRef->getBoardSizeY()-1)) 
        head.pos->y = 1;
    
    checkPlayerCollision();

    foodPos = mainGameMechsRef->getFoodPos();
    
    if(checkFoodConsumption()) {
        increasePlayerLength();
        mainGameMechsRef->incrementScore();
        mainGameMechsRef->generateFood(playerPosList);
    } else {
        playerPosList->insertHead(head);
        playerPosList->removeTail();
    }
}

bool Player::checkFoodConsumption() {
    return(head.getPosX() == foodPos.getPosX() && head.getPosY() == foodPos.getPosY());
}

void Player::increasePlayerLength() {
    playerPosList->insertHead(head);
}

void Player::checkPlayerCollision() {
    int i;
    for (i = 1; i < playerPosList->getSize(); i++) {
        int snakeX = playerPosList->getElement(i).getObjPos().getPosX();
        int snakeY = playerPosList->getElement(i).getObjPos().getPosY();

        if (head.getPosX() == snakeX && head.getPosY() == snakeY) {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
        }
    }
}