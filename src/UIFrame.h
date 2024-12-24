#ifndef UIFRAME_H
#define UIFRAME_H

#include "IDrawable.h"
#include "TextureBackground.h"
#include <vector>

class UIFrame : public IDrawable
{
private:
    TextureBackground* background{};
    std::vector<IDrawable*> elements;

public:
    UIFrame(const char* backgroundPath);
    UIFrame();
    ~UIFrame() override;

    void addElement(IDrawable* element);
    void draw() override;
    TextureBackground* getBackground();
    void changeBackground(const char* backgroundPath);
    void clearElements();
    void updateHoverStatus();
};

#endif