#ifndef CONSTANTS_H
#define CONSTANTS_H

// Window
constexpr int SCREEN_WIDTH {500};
constexpr int SCREEN_HEIGHT {620};

// Game
constexpr double STARTING_INTERVAL {0.2};
constexpr int SCORE_DIVISOR {500};
constexpr int MAX_FPS {60};

// Display
constexpr int BORDER_SIZE {11};
constexpr int RIGHT_CONTAINER_START {320};
constexpr int RECT_WIDTH {170};
constexpr int RECT_HEIGHT {60};
constexpr double RECT_ROUNDNESS {0.3};
constexpr int RECT_SEGMENTS {6};

// Button
constexpr int BTN_Y {465};
constexpr int BTN_SIZE {30};

// Font
constexpr int FONT_SIZE {38};
constexpr int FONT_SPACING {2};

// Pause
constexpr int PAUSE_WIDTH {20};
constexpr int PAUSE_HEIGHT {80};
constexpr int PAUSE_POS_Y {SCREEN_HEIGHT / 2 - (PAUSE_HEIGHT / 2)};

// Grid
constexpr int MAX_ROWS {20};
constexpr int MAX_COLS {10};
constexpr int CELL_SIZE {30};

// Scoring
constexpr int SINGLE_LINE_CLEAR {100};
constexpr int DOUBLE_LINE_CLEAR {300};
constexpr int TRIPLE_LINE_CLEAR {500};
constexpr int TETRIS_LINE_CLEAR {800};
constexpr int MOVE_DOWN_POINTS {1};

// Level
constexpr int FIRST_LEVEL {1500};
constexpr int SECOND_LEVEL {2500};
constexpr int FINAL_LEVEL {4000};

// Level multipliers
constexpr double BASE_MULTIPLIER {0.013};
constexpr double FIRST_MULTIPLIER {0.015};
constexpr double SECOND_MULTIPLIER {0.017};
constexpr double FINAL_MULTIPLIER {0.02};

// Block indices
enum blockId {
    LBlockId = 1,
    JBlockId = 2,
    IBlockId = 3,
    OBlockId = 4,
    SBlockId = 5,
    TBlockId = 6,
    ZBlockId = 7
};

#endif