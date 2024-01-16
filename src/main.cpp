#include "game.h"
#include "button.h"
#include "infoDisplay.h"
#include "timer.h"

// std::vector<InfoDisplay> createInfoDisplays(Font font, Game game) {
    

//     return {nextBlockDisplay, scoreDisplay, highScoreDisplay};
// }

void drawGame(Font font, Game& game, Texture2D background, std::vector<InfoDisplay> displays, std::vector<Button> buttons) {
    BeginDrawing();
    
    // Background
    ClearBackground(WHITE);
    DrawTexture(background, 0, 0, WHITE);

    // Info display
    for (InfoDisplay display : displays) {
        display.draw();
    }

    // Buttons
    for (Button button : buttons) {
        button.draw();
    }

    // Game
    game.draw(font);

    EndDrawing();
}

void initGame() {
    // Load assets
    const Texture2D background = LoadTexture("assets/image/background.png");
    const Texture2D audioOff = LoadTexture("assets/image/muteMusicOff.png");
    const Texture2D audioOn = LoadTexture("assets/image/muteMusicOn.png");
    const Texture2D pauseOff = LoadTexture("assets/image/pauseOff.png");
    const Texture2D pauseOn = LoadTexture("assets/image/pauseOn.png");
    const Font font = LoadFontEx("assets/font/HelveticaNeueLight.ttf", 64, 0, 0);

    // Initialize objects
    Game game = Game();
    Button pauseBtn = Button({420, BTN_Y, BTN_SIZE, BTN_SIZE}, pauseOff, pauseOn);
    Button musicBtn = Button({460, BTN_Y, BTN_SIZE, BTN_SIZE}, audioOff, audioOn);
    // std::vector<InfoDisplay> infoDisplays = createInfoDisplays(font, game);
    Rectangle nextBlockRect = {RIGHT_CONTAINER_START, 55, RECT_WIDTH, RECT_HEIGHT * 3}; 
    InfoDisplay nextBlockDisplay = InfoDisplay(font, "Next", {370, 15}, nextBlockRect);

    Rectangle scoreRect = {RIGHT_CONTAINER_START, 285, RECT_WIDTH, RECT_HEIGHT};
    InfoDisplay scoreDisplay = InfoDisplay(font, "Score", {360, 245}, scoreRect, &game.score);

    Rectangle highScoreRect = {RIGHT_CONTAINER_START, 395, RECT_WIDTH, RECT_HEIGHT};
    InfoDisplay highScoreDisplay = InfoDisplay(font, "Best", {370, 355}, highScoreRect, &game.highScore);
    Vector2 mousePoint = {0.0f, 0.0f};
    Timer timer = Timer();

    // Game loop
    while (!WindowShouldClose()) {
        UpdateMusicStream(game.music);
        mousePoint = GetMousePosition();
        game.handleUserInput();
        pauseBtn.handleUserInput(mousePoint, game.isPaused, game.pauseGame, game);
        musicBtn.handleUserInput(mousePoint, game.isMusicMuted, game.pausePlayMusic, game);

        if (timer.triggerEvent(game.score) && !game.isPaused) {
            game.moveBlockDown();
        }   
        drawGame(font, game, background, {nextBlockDisplay, scoreDisplay, highScoreDisplay}, {pauseBtn, musicBtn});
    }

    // Unload assets
    UnloadFont(font);
    UnloadTexture(pauseOn);
    UnloadTexture(pauseOff);
    UnloadTexture(audioOn);
    UnloadTexture(audioOff);
    UnloadTexture(background);
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
    SetTargetFPS(MAX_FPS);
    initGame();
    CloseWindow();
    return 0;
}
