#pragma once
#include <vector>
#include <raylib.h>
#include "constants.h"
#include "colors.h"

class Grid {
    public:
        Grid();
        void init();
        void draw();
        bool isCellOutOfBounds(int row, int col);
        bool isCellEmpty(int row, int col);
        int clearCompletedRows();
        int grid[MAX_ROWS][MAX_COLS];
    private:
        bool isRowFull(int row);
        void clearRow(int row);
        void moveRowDown(int row, int numRows);
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> colors;
};