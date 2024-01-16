#include "block.h"

Block::Block() {
    cellSize = CELL_SIZE;
    rotationState = 0;
    colors = getCellColors();
    rowOffset = 0;
    colOffset = 0;
}

void Block::draw(int offsetX, int offsetY) {
    std::vector<Position> tiles = getCellPositions();
    for (Position pos : tiles) {
        DrawRectangle(pos.col * cellSize + offsetX, pos.row * cellSize + offsetY,  cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::move(int rows, int cols) {
    rowOffset += rows;
    colOffset += cols;
}

std::vector<Position> Block::getCellPositions() {
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;

    for (Position pos : tiles) {
        Position newPos = Position(pos.row + rowOffset, pos.col + colOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::rotate() {
    rotationState++;
    if (rotationState == (int)cells.size()) {
        rotationState = 0;
    }
}

void Block::undoRotate() {
    rotationState--;
    if (rotationState == -1) {
        rotationState = (int)cells.size() - 1;
    }
}
