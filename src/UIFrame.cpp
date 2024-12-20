#include "UIFrame.h"
#include "UIText.h"

UIFrame::UIFrame(const char* backgroundPath) : background(new TextureBackground(backgroundPath))
{
}

UIFrame::UIFrame() = default;

UIFrame::~UIFrame()
{
    delete background;
    for (auto element : elements)
    {
        delete element;
    }
    elements.clear();
}

void UIFrame::addElement(IDrawable* element)
{
    elements.push_back(element);
}
void UIFrame::draw()
{
    float scaleX = (float)GetScreenWidth() / (float)background->originalWidth;
    float scaleY = (float)GetScreenHeight() / (float)background->originalHeight;

    for (auto element : elements)
    {
        UIText* uiText = dynamic_cast<UIText*>(element);
        if(uiText != nullptr)
        {
            uiText->setScale(scaleX, scaleY);
        }
    }
    updateHoverStatus();
    background->draw();
    for (auto element : elements)
    {
        element->draw();
    }
}
TextureBackground* UIFrame::getBackground()
{
    return background;
}
void UIFrame::changeBackground(const char* backgroundPath)
{
    background->changeTexture(backgroundPath);
}
void UIFrame::clearElements()
{
    for (auto element : elements)
    {
        delete element;
    }
    elements.clear();
}

void UIFrame::updateHoverStatus()
{
    for(auto element : elements)
    {
        UIText* uiText = dynamic_cast<UIText*>(element);
        if(uiText != nullptr)
        {
            uiText->setHover(uiText->isMouseOver());
        }
    }
}