#include "button.h"

Button::Button(Rectangle rect, Texture2D offTexture, Texture2D onTexture) {
    this -> rect = rect;
    this -> offTexture = offTexture;
    this -> onTexture = onTexture;
    useAction = false;
    isEnabled = false;
}

void Button::draw() {
    Texture2D texture = isEnabled ? onTexture : offTexture;
    DrawTexture(texture, rect.x, rect.y, WHITE);
}

void Button::handleUserInput(Vector2 mousePoint, bool& toggleState, void (Game::*function)(), Game& game) {
    // Check if state was changed by keyboard input
    isEnabled = toggleState;

    // Cursor collision
    if (CheckCollisionPointRec(mousePoint, rect) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        isEnabled = !isEnabled;
        useAction = true;
    }

    handleAction(function, game);
}

void Button::handleAction(void (Game::*function)(), Game& game) {
    if (useAction) {
        (game.*function)();
        useAction = false;
    }
}
