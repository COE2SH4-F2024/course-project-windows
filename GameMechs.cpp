#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs() {
    boardSizeX = 15;
    boardSizeY = 30;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    input = '\0';

    bitVectorSize = ((boardSizeX * boardSizeY) / 32) + 1;
    bitVector = new int[bitVectorSize]();
}

GameMechs::GameMechs(int boardX, int boardY) {
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    input = '\0';

    bitVectorSize = ((boardSizeX * boardSizeY) / 32) + 1;
    bitVector = new int[bitVectorSize]();
}

GameMechs::~GameMechs() {
    delete[] bitVector;
}

bool GameMechs::getExitFlagStatus() const {
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const {
    return loseFlag;
}
    
char GameMechs::getInput() const {
    return input;
}

int GameMechs::getScore() const {
    return score;
}

void GameMechs::incrementScore() {
    score++;
}

int GameMechs::getBoardSizeX() const {
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const {
    return boardSizeY;
}

void GameMechs::setExitTrue() {
    exitFlag = true;
}

void GameMechs::setLoseFlag() {
    loseFlag = true;
}

void GameMechs::setInput(char this_input) {
    input = this_input;
}

void GameMechs::clearInput() {
    input = '\0';
}

void GameMechs::generateFood(objPosArrayList* snakeBody) {
    int randX, randY, snakeX, snakeY, snakeIndex, index, i;

    for (i = 0; i < snakeBody->getSize(); i++) {
        snakeX = snakeBody->getElement(i).getObjPos().getPosX();
        snakeY = snakeBody->getElement(i).getObjPos().getPosY();
        snakeIndex = snakeY * getBoardSizeX() + snakeX;

        if (snakeIndex >= 0 && snakeIndex < boardSizeX * boardSizeY) {
            bitVector[snakeIndex / 32] |= (1 << (snakeIndex % 32));
        }
    }

    do {
        randX = rand() % (getBoardSizeX() - 2) + 1;
        randY = rand() % (getBoardSizeY() - 2) + 1;
        index = randY * getBoardSizeX() + randX;
    } while ((bitVector[index / 32] & (1 << (index % 32))) != 0);

    food.setObjPos(randX, randY, '=');
}

objPos GameMechs::getFoodPos() const {
    return food;
}