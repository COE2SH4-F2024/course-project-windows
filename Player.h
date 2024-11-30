#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player {
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos() const;
        void updatePlayerDir();
        void movePlayer();

        bool checkFoodConsumption();
        void increasePlayerLength();
        void checkPlayerCollision();

    private:
        objPosArrayList* playerPosList; 
        enum Dir myDir;
        objPos foodPos;
        objPos head;

        GameMechs* mainGameMechsRef;
};

#endif