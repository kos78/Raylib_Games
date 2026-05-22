#include <stdio.h>
#include <raylib.h>



int main(void) {
    InitWindow(800, 600, "My First Game");
    SetTargetFPS(60);
    int speed = 5;
    int ballX = 400;
    int ballY = 300;

    while (!WindowShouldClose()) {
        // Event Handling
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)){
            ballX += speed;
        }
        else if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
            ballY -= speed;
        }
        else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
            ballY += speed;
        }
        else if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
            ballX-= speed;
        }

        // Updating Positions
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircle(ballX, ballY, 30, PURPLE);
            DrawText("Hello, Raylib!", 300, 280, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}