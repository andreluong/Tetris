#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
    public:
        Game();
        ~Game();
        void draw(Font font);
        void handleUserInput();
        void moveBlockDown();
        void pauseGame();
        void pausePlayMusic();
        bool gameOver;
        int score;
        int highScore;
        Music music;
        bool isPaused;
        bool isMusicMuted;
    private:
        void drawGameState(Font font);
        void moveBlockLaterally(int x);
        Block getRandomBlock();
        std::vector<Block> getAllBlocks();
        bool isBlockOutOfBounds();
        void rotateBlock();
        void lockBlock();
        bool blockFits();
        void updateScore(int rowsCleared, int moveDownPoints);
        void reset();
        void endGame();
        Grid grid;
        std::vector<Block> blocks;
        Block curBlock;
        Block nextBlock;
        Sound rotateSound;
        Sound clearSound;
        Sound gameStartSound;
        Sound gameOverSound;
        Sound pauseSound;
        Sound speedUpSound;
};