#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs* mainGame;
Player* player;
objPosArrayList* snake;

int main(void) {
    Initialize();

    while(exitFlag == false) {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void) {
    srand(time(0));

    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;

    mainGame = new GameMechs();
    player = new Player(mainGame);

    mainGame->generateFood(player->getPlayerPos());
}

void GetInput(void) {
    if (MacUILib_hasChar()) {
        mainGame->setInput(MacUILib_getChar());
    }
}

void RunLogic(void) {
    player->updatePlayerDir();
    player->movePlayer();

    snake = player->getPlayerPos();

    exitFlag = mainGame->getExitFlagStatus();
}

void DrawScreen(void) {
    MacUILib_clearScreen();
    int width = mainGame->getBoardSizeX();
    int height = mainGame->getBoardSizeY();
    int snakePrintCount = 0; //to count 
    
    if(!mainGame->getExitFlagStatus()) {
        for (int i = 0; i < width; i++){
            for (int j = 0; j < height; j++){
                if(i == 0 || i == (width-1) || j == 0 || j == (height-1)) {
                    MacUILib_printf("#");
                    continue; 
                }
                
                bool printed = false; 

                for (int k = 0; (k < player->getPlayerPos()->getSize()) && (snakePrintCount < player->getPlayerPos()->getSize()) && (!printed); k++) { 
                    int posX = player->getPlayerPos()->getElement(k).getObjPos().getPosX();
                    int posY = player->getPlayerPos()->getElement(k).getObjPos().getPosY();
                    if ((i == posX) && (j == posY)) {
                        MacUILib_printf("%c", (player->getPlayerPos()->getElement(k).getSymbol()));
                        snakePrintCount++;
                        printed = true;
                    }
                }

                if (!printed) {
                    if (i == mainGame->getFoodPos().pos->x && j == mainGame->getFoodPos().pos->y) {
                        MacUILib_printf("%c", mainGame->getFoodPos().symbol);
                    } else
                        MacUILib_printf(" ");
                } 
            }
            MacUILib_printf("\n");
        }    
        
        MacUILib_printf("Score: %d\n", mainGame->getScore());
        MacUILib_printf("\nControls: W = Up, S = Down, A = Left, D = Right, / = Exit\n");
    } else if(mainGame->getLoseFlagStatus() && mainGame->getExitFlagStatus()) 
        MacUILib_printf("Collision Detected! You lose!\n");
    else if(mainGame->getExitFlagStatus())
        MacUILib_printf("Forced Exit!\n");
}

void LoopDelay(void) {
    if(!mainGame->getLoseFlagStatus() && !mainGame->getExitFlagStatus())
        MacUILib_Delay(DELAY_CONST); // 0.1s delay
    else
        MacUILib_Delay(DELAY_CONST*30);
}

void CleanUp(void) {
    MacUILib_clearScreen();    

    delete player;
    player = nullptr;

    delete mainGame;
    mainGame = nullptr;

    MacUILib_uninit();
}



