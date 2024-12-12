#include "Mario.hpp"



void Mario::changeToSmall() {
    type = MARIO_TYPE_SMALL;
    pos.y = pos.y + 12;
    dim.y = 40;
    maxFrames = 2;
}

void Mario::changeToSuper() {
    type = MARIO_TYPE_SUPER;
    dim.y = 56;
    maxFrames = 3;
}

void Mario::changeToFlower() {
    type = MARIO_TYPE_FLOWER;
    dim.y = 56;
    maxFrames = 3;
}



