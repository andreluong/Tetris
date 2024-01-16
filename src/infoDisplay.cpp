#include "infoDisplay.h"

InfoDisplay::InfoDisplay(Font font, const char *title, Vector2 titlePos, Rectangle rect) {
    this -> font = font;
    this -> title = title;
    this -> titlePos = titlePos;
    this -> rect = rect;
    value = nullptr;
}

InfoDisplay::InfoDisplay(Font font, const char *title, Vector2 titlePos, Rectangle rect, int* value) {
    this -> font = font;
    this -> title = title;
    this -> titlePos = titlePos;
    this -> rect = rect;
    this -> value = value;
}

void InfoDisplay::draw() {
    DrawTextEx(font, title, titlePos, FONT_SIZE, FONT_SPACING, WHITE);
    DrawRectangleRounded(rect, RECT_ROUNDNESS, RECT_SEGMENTS, lightPink);

    if (value != nullptr) {
        char scoreText[10];
        sprintf(scoreText, "%d", *value);
        Vector2 scoreTextSize = MeasureTextEx(font, scoreText, FONT_SIZE, FONT_SPACING);
        DrawTextEx(font, scoreText, {RIGHT_CONTAINER_START + (RECT_WIDTH - scoreTextSize.x) / 2, rect.y + 10}, FONT_SIZE, FONT_SPACING, WHITE);
    }
}
    