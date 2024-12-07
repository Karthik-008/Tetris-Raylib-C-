#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

#define FPS 60

double lastUpdateTime = 0;

bool EventTrigger(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    
    return false;
}

int main()
{
    Color darkBlue = {44, 44, 127, 255};
    InitWindow(800, 620, "Tetris Raylib");
    SetTargetFPS(FPS);
    int frameCounter = 0;
    bool showText = true;

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while(WindowShouldClose() == false) 
    {
        if(!game.gamePause)
        {
            UpdateMusicStream(game.music);
        }
        frameCounter++;
        if(frameCounter >= 30)
        {
            showText = !showText;
            frameCounter = 0;
        }
        game.HandleInput();
        if(EventTrigger(0.25) && !game.gamePause)
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if(game.gameOver && showText)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        } 
        if(game.gamePause && showText)
        {
            DrawTextEx(font, "GAME PAUSED", {320, 450}, 38, 2, WHITE);
        }

        //Score window
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);

        //Next block window
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}