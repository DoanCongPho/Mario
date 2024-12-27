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
                InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Mario Game");
                    loadAllAnimations();
                    loadMusic();
                    vector<Texture2D> walkingTextures = ResourcesManager::getInstance().getA("smallMario");
                    vector<Texture2D> jumpingTextures = ResourcesManager::getInstance() .getA("smallMarioJump");
                    vector<Texture2D> runningTextures= ResourcesManager::getInstance().getA("smallMarioRun");
                    vector<Texture2D> tranfomationTextures = ResourcesManager::getInstance().getA("transToSuper");
                    vector<Texture2D> superMarioWalk = ResourcesManager::getInstance().getA("superMario");
                    vector<Texture2D> superMarioRun = ResourcesManager::getInstance().getA("superMarioRun");
                    vector<Texture2D> superMarioJump =ResourcesManager::getInstance().getA("superMarioJump");
                    vector<Texture2D> fireballs = ResourcesManager::getInstance().getA("fireballs");
                    Player player({100.0f, 100.0f}, walkingTextures, jumpingTextures,runningTextures, tranfomationTextures, fireballs);
                    Camera2D camera = initCamera(player);
                    Map map1("Resources/Map1.tmx", "Collision");
                    Map map2("Resources/Map2.tmx", "Collision");
                    SetTargetFPS(60);
                    SoundManager::getInstance().playMapMusic("Map1");
                    RunGame(player, map1, camera);
    
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
