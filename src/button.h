#pragma once
#include "game.h"

class Button {
    public:
        Button(Rectangle rect, Texture2D offTexture, Texture2D onTexture);
        void draw();
        void handleUserInput(Vector2 mousePoint, bool& toggleState, void (Game::*function)(), Game& game);
        void handleAction(void (Game::*function)(), Game& game);
    private:
        Rectangle rect;
        Texture2D offTexture;
        Texture2D onTexture;
        bool useAction;
        bool isEnabled;
};