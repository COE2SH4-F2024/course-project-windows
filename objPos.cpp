#include "objPos.h"

// Initializes position to (0,0) and symbol to null character
objPos::objPos() {
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0;
}

// Initializes position and symbol to given values
objPos::objPos(int xPos, int yPos, char sym) {
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Frees memory allocated for position
objPos::~objPos() {
    delete pos;
}

// Copies position and symbol from another objPos object
objPos::objPos(const objPos &o) {
    pos = new Pos;
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// Assigns values from another objPos object
objPos& objPos::operator=(const objPos &o) {
    if(this != nullptr) {
        pos->x = o.pos->x;
        pos->y = o.pos->y;
        symbol = o.symbol;
    }
    return *this;
}

// Updates position using another objPos object
void objPos::setObjPos(objPos o) {
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// Updates position and symbol with given values
void objPos::setObjPos(int xPos, int yPos, char sym) {
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Returns a copy of the current objPos
objPos objPos::getObjPos() const {
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    return returnPos;
}

// Retrieves the symbol of the object
char objPos::getSymbol() const {
    return symbol;
}

// Checks if the current position is equal to the given reference position
bool objPos::isPosEqual(const objPos* refPos) const {
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// Returns the symbol if the position matches the given reference position
char objPos::getSymbolIfPosEqual(const objPos* refPos) const {
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}

// Retrieves the x-coordinate of the position
int objPos::getPosX() const {
    return pos->x;
}

// Retrieves the y-coordinate of the position
int objPos::getPosY() const {
    return pos->y;
}
