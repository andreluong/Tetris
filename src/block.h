#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
#include "constants.h"

class Block {
    public:
        Block();
        void draw(int offsetX, int offsetY);
        void move(int rows, int cols);
        std::vector<Position> getCellPositions();
        void rotate();
        void undoRotate();
        int id;
        std::map<int, std::vector<Position>> cells;
    private:
        int cellSize;
        int rotationState;
        std::vector<Color> colors;
        int rowOffset;
        int colOffset;
};