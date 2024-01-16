#pragma once
#include <raylib.h>
#include "constants.h"
#include "colors.h"
#include <stdio.h>

class InfoDisplay {
    public:
        InfoDisplay(Font font, const char *title, Vector2 titlePos, Rectangle rect);
        InfoDisplay(Font font, const char *title, Vector2 titlePos, Rectangle rect, int* value);
        void draw();
    private:
        const char *title;
        Font font;
        Vector2 titlePos;
        Rectangle rect;
        int* value;
};