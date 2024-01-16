#include "game.h"
#include <random>

Game::Game() {
    grid = Grid();
    blocks = getAllBlocks();
    curBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    gameOver = false;
    score = 0;
    highScore = 0;
    isPaused = false;
    isMusicMuted = false;

    // Load assets
    InitAudioDevice();
    music = LoadMusicStream("assets/audio/music.mp3");
    PlayMusicStream(music);
    gameStartSound = LoadSound("assets/audio/gameStart.wav");
    PlaySound(gameStartSound);
    rotateSound = LoadSound("assets/audio/rotate.wav");
    clearSound = LoadSound("assets/audio/clear.wav");
    gameOverSound = LoadSound("assets/audio/gameOver.wav");
    pauseSound = LoadSound("assets/audio/pause.wav");
    speedUpSound = LoadSound("assets/audio/speedUp.wav");
}

Game::~Game() {
    // Unload assets
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadSound(gameStartSound);
    UnloadSound(gameOverSound);
    UnloadSound(pauseSound);
    UnloadSound(speedUpSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

void Game::draw(Font font) {
    grid.draw();
    curBlock.draw(BORDER_SIZE, BORDER_SIZE);

    // Draw next block for InfoDisplay
    switch (nextBlock.id) {
        case IBlockId:
            nextBlock.draw(255, 130);
            break;
        case OBlockId:
            nextBlock.draw(255, 120);
            break;
        default:
            nextBlock.draw(270, 110);
            break;
    }

    // Game states
    drawGameState(font);
}

void Game::drawGameState(Font font) {
    if (isPaused) {
        DrawRectangle(SCREEN_WIDTH / 2 - (PAUSE_WIDTH * 1.5), PAUSE_POS_Y, PAUSE_WIDTH, PAUSE_HEIGHT, WHITE);
        DrawRectangle(SCREEN_WIDTH / 2 + (PAUSE_WIDTH * 0.5), PAUSE_POS_Y, PAUSE_WIDTH, PAUSE_HEIGHT, WHITE);
    }
    if (gameOver) {
        DrawRectangleRounded({120, 470, 260, 50}, RECT_ROUNDNESS, RECT_SEGMENTS, GRAY);
        DrawTextEx(font, "GAME OVER", {128, 470}, FONT_SIZE + 10, FONT_SPACING, WHITE);
    }
}

void Game::pauseGame() {
    if (!gameOver) {
        isPaused = !isPaused;
        if (isPaused) {
            PlaySound(pauseSound);
        }
    }
}

void Game::pausePlayMusic() {
    isMusicMuted = !isMusicMuted;
    if (isMusicMuted) {
        PauseMusicStream(music);
    } else {
        ResumeMusicStream(music);
    }
}

void Game::handleUserInput() {
    int keyPressed = GetKeyPressed();
    if (gameOver && (keyPressed != 0 && keyPressed != KEY_P && keyPressed != KEY_M)) {
        reset();
    }

    switch (keyPressed) {
        case KEY_LEFT:
            moveBlockLaterally(-1);
            break;
        case KEY_RIGHT:
            moveBlockLaterally(1);
            break;
        case KEY_DOWN:
            moveBlockDown();
            updateScore(0, MOVE_DOWN_POINTS);
            break;
        case KEY_UP:
            rotateBlock();
            break;
        case KEY_P:
            pauseGame();
            break;
        case KEY_M:
            pausePlayMusic();
            break;
        case KEY_R:
            reset();
            break;
    }
}

void Game::moveBlockLaterally(int x) {
    if (!gameOver) {
        curBlock.move(0, x);
        if (isBlockOutOfBounds() || !blockFits() || isPaused) {
            curBlock.move(0, -x);
        }
    }
}

void Game::moveBlockDown() {
    if (!gameOver) {
        curBlock.move(1, 0);
        if (isBlockOutOfBounds() || !blockFits() || isPaused) {
            curBlock.move(-1, 0);
            lockBlock();
        }
    }
}

bool Game::isBlockOutOfBounds() {
    std::vector<Position> tiles = curBlock.getCellPositions();
    for (Position pos : tiles) {
        if (grid.isCellOutOfBounds(pos.row, pos.col)) {
            return true;
        }
    }
    return false;
}

void Game::rotateBlock() {
    curBlock.rotate();
    if (isBlockOutOfBounds() || !blockFits() || isPaused) {
        curBlock.undoRotate();
    } else {
        PlaySound(rotateSound);
    }
}

Block Game::getRandomBlock() {
    if (blocks.empty()) {
        blocks = getAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::getAllBlocks() {
    return {LBlock(), JBlock(), IBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

// Lock the current block when it reaches the floor or collides with the top of another block
void Game::lockBlock() {
    std::vector<Position> tiles = curBlock.getCellPositions();
    for (Position pos : tiles) {
        grid.grid[pos.row][pos.col] = curBlock.id;
    }
    curBlock = nextBlock;

    if (!blockFits()) {
        endGame();
    }

    nextBlock = getRandomBlock();

    int completedRows = grid.clearCompletedRows();
    if (completedRows > 0) {
        PlaySound(clearSound);
        updateScore(completedRows, 0);
    }
}

bool Game::blockFits() {
    std::vector<Position> tiles = curBlock.getCellPositions();
    for (Position pos : tiles) {
        if (!grid.isCellEmpty(pos.row, pos.col)) {
            return false;
        }
    }
    return true;
}

void Game::updateScore(int rowsCleared, int moveDownPoints) {
    switch (rowsCleared) {
        case 1:
            score += SINGLE_LINE_CLEAR;
            break;
        case 2:
            score += DOUBLE_LINE_CLEAR;
            break;
        case 3:
            score += TRIPLE_LINE_CLEAR;
            break;
        case 4:
            score += TETRIS_LINE_CLEAR;
            break;
        default:
            break;
    }
    score += moveDownPoints;
}

void Game::reset() {
    grid.init();
    blocks = getAllBlocks();
    curBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    gameOver = false;
    score = 0;
    PlaySound(gameStartSound);
}

void Game::endGame() {
    gameOver = true;
    PlaySound(gameOverSound);
    if (highScore < score) {
        highScore = score;
    }
}
