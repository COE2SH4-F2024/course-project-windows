#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

/*
Player: Represents the player (snake) and manages its behavior, including movement and collision detection.
*/

class Player {
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP}; // Direction enum to define possible movement directions

        Player(GameMechs* thisGMRef); // Constructor with reference to game mechanics
        ~Player(); // Destructor to clean up resources

        objPosArrayList* getPlayerPos() const; // Get the player's position list

        void updatePlayerDir(); // Update the player's direction
        void movePlayer(); // Move the player based on direction

        bool checkFoodConsumption(); // Check if the player consumes food
        void increasePlayerLength(); // Increase the player's length
        void checkPlayerCollision(); // Check for collisions with itself
        void checkWin(); // Check if snake length equals size of the board

    private:
        objPosArrayList* playerPosList; // List of positions occupied by the player
        enum Dir myDir; // Current movement direction
        objPos foodPos; // Position of the food
        objPos head; // Position of the snake's head

        GameMechs* mainGameMechsRef; // Reference to GameMechs to obtain information about food position
};

#endif
