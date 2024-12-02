#include "Player.h"
#include "objPos.h"
#include "MacUILib.h"

// Initializes the Player object with a reference to the game mechanics
Player::Player(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;   
    myDir = STOP; // Default direction is stopped
    playerPosList = new objPosArrayList; // Initializes the player's position list
    foodPos = thisGMRef->getFoodPos(); // Retrieves initial food position
    
    objPos part = {7, 15, '*'}; // Sets the initial position and symbol of the player
    playerPosList->insertHead(part);

    head = playerPosList->getHeadElement(); // Retrieves head position
}

// Frees memory allocated for the player's position list
Player::~Player() {
    delete playerPosList;
}

// Retrieves the current position list of the player
objPosArrayList* Player::getPlayerPos() const {
    return playerPosList;
}

// Updates the player's direction based on the input character
void Player::updatePlayerDir() {
    if(mainGameMechsRef->getInput() != '\0') {
        switch(mainGameMechsRef->getInput()) {                      
            case '/': // Exit command
                mainGameMechsRef->setExitTrue(); 
                break;
            case 'a':  // Move left, if not moving right
                if(myDir != RIGHT) 
                    myDir = LEFT; 
                break;
            case 'd': // Move right, if not moving left
                if(myDir != LEFT) 
                    myDir = RIGHT; 
                break;
            case 'w': // Move up, if not moving down
                if(myDir != DOWN) 
                    myDir = UP; 
                break;
            case 's': // Move down, if not moving up
                if(myDir != UP) 
                    myDir = DOWN; 
                break;
            default: // Ignore invalid input
                break;
        }
    }
}

// Moves the player in the current direction and handles boundary wrapping
void Player::movePlayer() {
    // Update head position based on direction
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

    // Wrap around the board edges
    if(head.getPosX() == 0) 
        head.pos->x = mainGameMechsRef->getBoardSizeX()-2;
    else if (head.getPosX() == (mainGameMechsRef->getBoardSizeX()-1))
        head.pos->x = 1;
    else if (head.getPosY() == 0) 
        head.pos->y = mainGameMechsRef->getBoardSizeY()-2;
    else if (head.getPosY() == (mainGameMechsRef->getBoardSizeY()-1)) 
        head.pos->y = 1;
    
    checkPlayerCollision(); // Check if the player collides with itself

    checkWin(); // Check if the length of the snake equals the size of the playable space in the board

    foodPos = mainGameMechsRef->getFoodPos(); // Get the current food position
    
    if(checkFoodConsumption()) { // If food is consumed
        increasePlayerLength(); // Increase player's length
        mainGameMechsRef->incrementScore(); // Increment the score
        mainGameMechsRef->generateFood(playerPosList); // Generate new food
    } else {
        playerPosList->insertHead(head); // Move the head
        playerPosList->removeTail(); // Remove the tail to simulate movement
    }
}

// Checks if the player's head position matches the food position
bool Player::checkFoodConsumption() {
    return(head.getPosX() == foodPos.getPosX() && head.getPosY() == foodPos.getPosY());
}

// Increases the player's length by adding a new head element
void Player::increasePlayerLength() {
    playerPosList->insertHead(head);
}

// Checks if the player's head collides with its body
void Player::checkPlayerCollision() {
    for (int i = 1; i < playerPosList->getSize(); i++) { // iterates through each element of the snake's tail
        int snakeX = playerPosList->getElement(i).getObjPos().getPosX();
        int snakeY = playerPosList->getElement(i).getObjPos().getPosY();

        if (head.getPosX() == snakeX && head.getPosY() == snakeY) {
            mainGameMechsRef->setLoseFlag(); // Mark the game as lost
            mainGameMechsRef->setExitTrue(); // Trigger game exit
        }
    }
}

void Player::checkWin() {
    if(playerPosList->getSize() == (mainGameMechsRef->getBoardSizeX() - 2) * (mainGameMechsRef->getBoardSizeY() - 2)) { // Check if snake length is equal to the area excluding the borders
        mainGameMechsRef->setWinFlag(); // Mark the game as won
        mainGameMechsRef->setExitTrue(); // Trigger game exit
    }
}
