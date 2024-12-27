#include "layout.h"
#include "app_config.h"
#include "raylib.h"

//void UpdateLayout(std::vector<Button>& buttons, Config& config, int screenWidth, int screenHeight) {
//    for (auto &button: buttons) {
//        float scaleX = (float) screenWidth / config.baseScreenWidth;
//        float scaleY = (float) screenHeight / config.baseScreenHeight;
//
//        Vector2 newPosition = Vector2(button.GetOriginalPosition().x * scaleX, button.GetOriginalPosition().y * scaleY);
//        Rectangle newBounds = Rectangle(button.getBounds().x * scaleX, button.getBounds().y * scaleY
//        , button.getBounds().width * scaleX, button.getBounds().height * scaleY);
//        button.setBounds(newBounds);
//        button.setPosition(newPosition);
//        button.setSize(config.baseFontSize * scaleY);
//    }
//}

void UpdateLayout(std::vector<Button>& buttons, Config& config, int screenWidth, int screenHeight) {
    for (auto &button : buttons) {
        float scaleX = (float) screenWidth / config.baseScreenWidth;
        float scaleY = (float) screenHeight / config.baseScreenHeight;

        // Ensure that GetOriginalPosition() returns a Vector2
        Vector2 newPosition = { button.GetOriginalPosition().x * scaleX, button.GetOriginalPosition().y * scaleY };
        
        // Correctly update button's bounds
        Rectangle newBounds = { button.getBounds().x * scaleX, button.getBounds().y * scaleY,
                                button.getBounds().width * scaleX, button.getBounds().height * scaleY };
        
        button.setBounds(newBounds);
        button.setPosition(newPosition);
        button.setSize(config.baseFontSize * scaleY);
    }
}
