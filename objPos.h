#ifndef OBJPOS_H
#define OBJPOS_H

// A struct to represent a 2D position on the board with x and y coordinates.
typedef struct {
    int x;  // X-coordinate
    int y;  // Y-coordinate
} Pos;

/*
objPos: Represents an object with a position (x, y) and a symbol on the game board.
*/

class objPos {
    public:
        Pos* pos; // Pointer to the position struct
        char symbol; // Symbol representing the object

        // Constructors and Destructor
        objPos(); // Default constructor
        objPos(int xPos, int yPos, char sym); // Parameterized constructor
        ~objPos(); // Destructor to clean up resources
        objPos(const objPos &o); // Copy constructor
        objPos& operator=(const objPos &o); // Assignment operator
        
        // Mutators
        void setObjPos(objPos o); // Set position using another objPos
        void setObjPos(int xPos, int yPos, char sym); // Set position and symbol

        // Accessors
        objPos getObjPos() const; // Get the current position
        char getSymbol() const; // Get the object's symbol
        char getSymbolIfPosEqual(const objPos* refPos) const; // Get symbol if positions match

        // Position Comparisons
        bool isPosEqual(const objPos* refPos) const; // Check if positions are equal

        // Get individual coordinates
        int getPosX() const; // Get x-coordinate
        int getPosY() const; // Get y-coordinate
};

#endif
