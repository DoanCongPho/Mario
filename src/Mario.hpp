
#ifndef Mario_hpp
#define Mario_hpp

#include "Sprite.hpp"


enum MarioType {
    MARIO_TYPE_SMALL,
    MARIO_TYPE_SUPER,
    MARIO_TYPE_FLOWER
};

class Mario: public Sprite{
private:
    MarioType type;
    bool isWalking;
    bool isRunning;
public:
    void draw();
    void changeToSmall();
    void changeToSuper();
    void changeToFlower();
    void marioRun();
    void marioJump();
    void marioWalk();
};

#endif
