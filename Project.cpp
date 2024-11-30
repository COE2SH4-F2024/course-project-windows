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

int main(void)
{

    Initialize();

    while(exitFlag == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    srand(time(0));

    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;

    if (!mainGame) {
        mainGame = new GameMechs();  // Create GameMechs only once
    }
    if (!player) {
        player = new Player(mainGame);
    }
    if (!snake) {
        snake = new objPosArrayList();
    }


    mainGame->generateFood(snake->getHeadElement(), snake);
}

void GetInput(void)
{
   if (MacUILib_hasChar()){
        mainGame->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();

    snake = player->getPlayerPos();

    exitFlag = mainGame->getExitFlagStatus();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    int width = mainGame->getBoardSizeX();
    int height = mainGame->getBoardSizeY();
    int snakePrintCount = 0; //to count 
    
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            if(i == 0 || i == (width-1) || j == 0 || j == (height-1)){ // border creation
                MacUILib_printf("#");
                continue; //to go back to printing
            }
            
            bool printed = false; //to hold value if a snake part is printed

            for (int k = 0; (k < snake->getSize()) && (snakePrintCount < snake->getSize()) && (!printed) ; k++){ 
                //only runs when snake is not fully printed
                int posX = snake->getElement(k).getObjPos().getPosX();
                int posY = snake->getElement(k).getObjPos().getPosY();
                if ((i == posX) && (j == posY))
                {
                    MacUILib_printf("%c", (snake->getElement(k).getSymbol()));
                    snakePrintCount++;
                    printed = true;
                }
            }

            if (!printed){
                if (i == mainGame->getFoodPos().pos->x && j == mainGame->getFoodPos().pos->y) {
                    MacUILib_printf("%c", mainGame->getFoodPos().symbol);
                }
                else
                    MacUILib_printf(" "); // runs if none of the items in the bin are printed
            } 
        }
        MacUILib_printf("\n");
    }    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    delete player;
    delete mainGame;
    delete snake;
    MacUILib_uninit();
}



