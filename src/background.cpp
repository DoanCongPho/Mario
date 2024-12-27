#include "background.h"
#include "app_config.h"
#include "raylib.h"

void HandleButtonClicks(std::vector<Button>& buttons, Texture2D& currentBackground, Texture2D background1, Texture2D background2, const Config& config)
{
    for (auto& button : buttons)
    {
        if(button.IsClicked())
        {
            if (button.GetText() == "OPTION")
            {
                currentBackground = background2;
                CreateButtons(buttons, config, currentBackground);
            }
            if (button.GetText() == "RETURN")
            {
                currentBackground = background1;
                CreateButtons(buttons, config, currentBackground);
            }
            else if (button.GetText() == "PLAY GAME")
            {

            }
            TraceLog(LOG_INFO, "Button text = ", button.GetText().c_str());
            button.setClicked(false);
        }
    }
}
void CreateButtons(std::vector<Button>& buttons, const Config& config, Texture2D currentBackground)
{
    buttons.clear();
    if (currentBackground.id == 3)
    {
        buttons.push_back(Button("PLAY GAME", { 270, 285 }));
        buttons.push_back(Button("OPTION", { 270, 315 }));
        buttons.push_back(Button("EXIT",{270, 345}));
        buttons.push_back(Button("x 00", { 240, 30 },false));
        buttons.push_back(Button("000000", { 55, 30 },false));
        buttons.push_back(Button("1 - 1", { 390, 30 },false));
        buttons.push_back(Button("MARIO", { 55, 10 },false));
        buttons.push_back(Button("WORLD", { 365, 10 },false));
        buttons.push_back(Button("TIME", { 505, 10 },false));
    }
    else
    {
        buttons.push_back(Button("RETURN", { 135, 135 }));
        buttons.push_back(Button("MUTE", { 135, 165 }));
        buttons.push_back(Button("x 00", { 240, 30 },false));
        buttons.push_back(Button("000000", { 55, 30 },false));
        buttons.push_back(Button("1 - 1", { 390, 30 },false));
        buttons.push_back(Button("MARIO", { 55, 10 },false));
        buttons.push_back(Button("WORLD", { 365, 10 },false));
        buttons.push_back(Button("TIME", { 505, 10 },false));
    }
}