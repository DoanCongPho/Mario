#include "UIFrame.h"

#include <iostream>

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
    const float scaleX = static_cast<float>(GetScreenWidth()) / static_cast<float>(background->originalWidth);
    const float scaleY = static_cast<float>(GetScreenHeight()) / static_cast<float>(background->originalHeight);

    for (auto element : elements)
    {
        if(auto* uiText = dynamic_cast<UIText*>(element); uiText != nullptr)
        {
            uiText->setScale(scaleX, scaleY);
        }
    }

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
TextureBackground* UIFrame::getBackgroundByPath(const std::string& path)
{
    if (background != nullptr && background->getTexturePath() == path) return background;
    return nullptr;
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
        if(auto* uiText = dynamic_cast<UIText*>(element); uiText != nullptr)
        {
            uiText->setHover(uiText->isMouseOver() && uiText->isClickedOn());
        }
    }
}

IDrawable* UIFrame::getElementByName(const std::string& name)
{
    for (auto element : elements)
        if(auto* uiText = dynamic_cast<UIText*>(element); uiText != nullptr)
        {
            if (uiText->getText() == name) return element;
        }
    return nullptr;
}
