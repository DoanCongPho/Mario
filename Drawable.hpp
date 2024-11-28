
#ifndef Drawable_hpp
#define Drawable_hpp

#include <stdio.h>


class Drawable {

public:
    virtual ~Drawable() = default;
    virtual void draw() = 0;
};


#endif


