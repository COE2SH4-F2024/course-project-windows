#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

/*
GameMechs: Handles the core game logic and mechanics, including board configuration, score tracking, input handling, and food generation.
*/

class GameMechs {
    private:
        char input; // Stores the current input character

        bool exitFlag; // Flag to determine if the game should exit
        bool loseFlag; // Flag to determine if the player has lost
        bool winFlag; // Flag to determine if the player has won

        int score; // Current game score

        int *bitArray; // Bit array for efficient collision detection
        int bitArraySize; // Size of the bit array

        int boardSizeX; // Width of the game board
        int boardSizeY; // Height of the game board

        objPos food; // Position of the food on the board

    public:
        // Constructors and Destructor
        GameMechs(); // Default constructor
        GameMechs(int boardX, int boardY); // Parameterized constructor
        ~GameMechs(); // Destructor to clean up resources
        
        // Accessors and Mutators
        bool getExitFlagStatus() const; // Check if exit flag is set
        void setExitTrue(); // Set exit flag
        bool getLoseFlagStatus() const; // Check if lose flag is set
        void setLoseFlag(); // Set lose flag
        bool getWinFlagStatus() const; // Check if win flag is set
        void setWinFlag(); // Set win flag

        char getInput() const; // Get the current input
        void setInput(char this_input); // Set the current input
        void clearInput(); // Clear the input

        int getBoardSizeX() const; // Get board width
        int getBoardSizeY() const; // Get board height
        
        int getScore() const; // Get current score
        void incrementScore(); // Increment the score

        // Food management within GameMechs
        void generateFood(objPosArrayList* snakeBody); // Generate a new food position
        objPos getFoodPos() const; // Get the current food position
};

#endif
