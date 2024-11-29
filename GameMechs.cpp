#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;
    score = 0;
    exitFlag = false;
    loseFlag = false;

    bitVectorSize = ((boardSizeX * boardSizeY) / 32) + 1;
    bitVector = new int[bitVectorSize]();

    srand(time(nullptr));
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
    score = 0;
    exitFlag = false;
    loseFlag = false;

    bitVectorSize = ((boardSizeX * boardSizeY) / 32) + 1;
    bitVector = new int[bitVectorSize]();

    srand(time(nullptr));
}

GameMechs::~GameMechs()
{
    delete[] bitVector;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    if (MacUILib_hasChar()){
        return MacUILib_getChar();
    }
    return NULL; //PETER: return null if no new character
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

void GameMechs::generateFood(objPos blockOff) {
    int i, j, randX, randY, index;;

    int playerIndex = blockOff.getObjPos().pos->y * getBoardSizeX() + blockOff.getObjPos().pos->x;
    bitVector[playerIndex / 32] |= (1 << (playerIndex % 32));

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
