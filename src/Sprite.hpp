#ifndef Sprite_hpp
#define Sprite_hpp

#include "raylib.h"
#include <iostream>

using namespace std;
class Sprite{
protected:
    Vector2 pos;
    Vector2 dim;
    Vector2 vel;
    float angle;
    int hitsToDie;
    int earnedPoints;
    bool isFacingRight;
    int maxFrames;
    Texture2D texture;
public:
    Sprite(const string& texturePath, float x, float y);
    virtual ~Sprite();
    virtual void update(float deltaTime);
    virtual void draw() const;
    Vector2 getPos() const;
    void setPos(float x, float y);
    void setVel(float vx, float vy);
    Vector2 getVel() const;
    
};

#endif 
