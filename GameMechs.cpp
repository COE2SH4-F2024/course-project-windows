#include "GameMechs.h"
#include "MacUILib.h"

// Initializes default game board dimensions and game state variables
GameMechs::GameMechs() {
    boardSizeX = 15;
    boardSizeY = 30;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    input = '\0';

    // Calculate bitArray size for collision detection and initialize
    bitArraySize = ((boardSizeX * boardSizeY) / 32) + 1;
    bitArray = new int[bitArraySize]();
}

// Allows custom board dimensions
GameMechs::GameMechs(int boardX, int boardY) {
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
    exitFlag = false;
    loseFlag = false;
    winFlag = false;
    input = '\0';

    bitArraySize = ((boardSizeX * boardSizeY) / 32) + 1;
    bitArray = new int[bitArraySize]();
}

// Frees memory allocated for bitArray
GameMechs::~GameMechs() {
    delete[] bitArray;
}

// Checks if the game exit flag is set
bool GameMechs::getExitFlagStatus() const {
    return exitFlag;
}

// Checks if the player has lost
bool GameMechs::getLoseFlagStatus() const {
    return loseFlag;
}

// Checks if the player has lost
bool GameMechs::getWinFlagStatus() const {
    return winFlag;
}

// Retrieves current input character
char GameMechs::getInput() const {
    return input;
}

// Returns current score
int GameMechs::getScore() const {
    return score;
}

// Returns board width
int GameMechs::getBoardSizeX() const {
    return boardSizeX;
}

// Returns board height
int GameMechs::getBoardSizeY() const {
    return boardSizeY;
}

// Increments the player's score
void GameMechs::incrementScore() {
    score++;
}

// Sets exit flag to true
void GameMechs::setExitTrue() {
    exitFlag = true;
}

// Sets lose flag to true
void GameMechs::setLoseFlag() {
    loseFlag = true;
}

// Sets win flag to true
void GameMechs::setWinFlag() {
    winFlag = true;
}

// Updates input with a given character
void GameMechs::setInput(char this_input) {
    input = this_input;
}

// Clears the input character
void GameMechs::clearInput() {
    input = '\0';
}

// Generates a food position on the board, avoiding the snake's current position
void GameMechs::generateFood(objPosArrayList* snakeBody) {
    // Logic for generating food in a valid location using bit arrays
    int randX, randY, snakeX, snakeY, snakeIndex, index, i;

    // Populate bitArray with snake body positions
    for (i = 0; i < snakeBody->getSize(); i++) {
        snakeX = snakeBody->getElement(i).getObjPos().getPosX();
        snakeY = snakeBody->getElement(i).getObjPos().getPosY();
        snakeIndex = snakeY * getBoardSizeX() + snakeX;

        if (snakeIndex >= 0 && snakeIndex < boardSizeX * boardSizeY) {
            bitArray[snakeIndex / 32] |= (1 << (snakeIndex % 32));
        }
    }

    // Generate random position until valid food location is found
    do {
        randX = rand() % (getBoardSizeX() - 2) + 1;
        randY = rand() % (getBoardSizeY() - 2) + 1;
        index = randY * getBoardSizeX() + randX;
    } while ((bitArray[index / 32] & (1 << (index % 32))) != 0);

    food.setObjPos(randX, randY, '=');
}

// Retrieves the current position of the food
objPos GameMechs::getFoodPos() const {
    return food;
}

