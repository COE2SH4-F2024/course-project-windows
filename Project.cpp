#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000 // Delay constant for game loop

// Global variables
bool exitFlag; // Indicates if the game should exit
GameMechs* mainGame; // Pointer to the game mechanics object
Player* player; // Pointer to the player object
objPosArrayList* snake; // Pointer to the snake's position list

// Function prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Main function: Implements the game loop
int main(void) {
    Initialize(); // Initialize game components

    // Game loop: Runs until exit flag is set
    while(exitFlag == false) {
        GetInput(); // Process user input
        RunLogic(); // Update game logic
        DrawScreen(); // Render the game state
        LoopDelay(); // Pause briefly
    }

    CleanUp(); // Clean up resources
}

// Initializes game components and settings
void Initialize(void) {
    srand(time(0)); // Seed random number generator

    MacUILib_init(); // Initialize the graphics library
    MacUILib_clearScreen();

    exitFlag = false; // Intialize exitFlag

    mainGame = new GameMechs(); // Create game mechanics object
    player = new Player(mainGame); // Create player object

    mainGame->generateFood(player->getPlayerPos()); // Generate initial food
}

// Processes input from the user
void GetInput(void) {
    if (MacUILib_hasChar()) {
        mainGame->setInput(MacUILib_getChar());
    }
}

// Updates game logic, including player movement and collision detection
void RunLogic(void) {
    player->updatePlayerDir(); // Update player direction
    player->movePlayer(); // Move the player

    snake = player->getPlayerPos(); // Update snake position

    exitFlag = mainGame->getExitFlagStatus(); // Check exit condition
}

// Renders the current game state to the screen
void DrawScreen(void) {
    MacUILib_clearScreen();
    int width = mainGame->getBoardSizeX();
    int height = mainGame->getBoardSizeY();
    int snakePrintCount = 0; // Tracks number of snake parts printed
    
    if(!mainGame->getExitFlagStatus()) {
        // Loop through the board grid
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if(i == 0 || i == (width-1) || j == 0 || j == (height-1)) {
                    MacUILib_printf("#"); // Print board border
                    continue; 
                }
                
                bool printed = false; 

                // Check if snake occupies the current position
                for (int k = 0; k < player->getPlayerPos()->getSize() && !printed; k++) { 
                    int posX = player->getPlayerPos()->getElement(k).getObjPos().getPosX();
                    int posY = player->getPlayerPos()->getElement(k).getObjPos().getPosY();
                    if ((i == posX) && (j == posY)) {
                        MacUILib_printf("%c", player->getPlayerPos()->getElement(k).getSymbol());
                        snakePrintCount++;
                        printed = true;
                    }
                }

                // Check if the current board position matches the position of the generated food
                if (!printed) {
                    if (i == mainGame->getFoodPos().pos->x && j == mainGame->getFoodPos().pos->y) {
                        MacUILib_printf("%c", mainGame->getFoodPos().symbol);
                    } else
                        MacUILib_printf(" ");
                } 
            }
            MacUILib_printf("\n");
        }    
        
        // Display score and controls
        MacUILib_printf("Score: %d\n", mainGame->getScore());
        MacUILib_printf("\nControls: W = Up, S = Down, A = Left, D = Right, / = Exit\n");

    } else if(mainGame->getLoseFlagStatus() && mainGame->getExitFlagStatus()) 
        MacUILib_printf("Collision Detected! You lose!\n"); // Self collision message

    else if(mainGame->getExitFlagStatus())
        MacUILib_printf("Forced Exit!\n"); // Forced exit message
}

void LoopDelay(void) {
    if(!mainGame->getLoseFlagStatus() && !mainGame->getExitFlagStatus())
        MacUILib_Delay(DELAY_CONST); // 0.1s delay
    else
        MacUILib_Delay(DELAY_CONST*30); // Delay for message displayed during exit
}

void CleanUp(void) {
    MacUILib_clearScreen();    

    delete player; // Free player
    player = nullptr;

    delete mainGame; // Free mainGame
    mainGame = nullptr;

    MacUILib_uninit();
}



