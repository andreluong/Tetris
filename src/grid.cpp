#include "grid.h"

Grid::Grid() {
    numRows = MAX_ROWS;
    numCols = MAX_COLS;
    cellSize = CELL_SIZE;
    colors = getCellColors();
    init();
}

void Grid::init() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            grid[row][col] = 0;
        }
    }
}

void Grid::draw() {
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            int cellValue = grid[row][col];
            int posX = col * cellSize + BORDER_SIZE;
            int posY = row * cellSize + BORDER_SIZE;
            DrawRectangle(posX, posY, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::isCellOutOfBounds(int row, int col) {
    return !(row >= 0 && row < numRows && col >= 0 && col < numCols);
}

bool Grid::isCellEmpty(int row, int col) {
    return grid[row][col] == 0;
}

// Clears and returns the number of completed rows
int Grid::clearCompletedRows() {
    int completed = 0;
    for (int row = numRows-1; row >= 0; row--) {
        if (isRowFull(row)) {
            clearRow(row);
            completed++;
        } else if (completed > 0) {
            moveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::isRowFull(int row) {
    for (int col = 0; col < numCols; col++) {
        if (isCellEmpty(row, col)) {
            return false;
        }
    }
    return true;
}

void Grid::clearRow(int row) {
    for (int col = 0; col < numCols; col++) {
        grid[row][col] = 0;
    }
}

void Grid::moveRowDown(int row, int numRows) {
    for (int col = 0; col < numCols; col++) {
        grid[row + numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}
