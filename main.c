#include <stdio.h>
#include <raylib.h>



int main(void) {
    InitWindow(800, 600, "My First Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(0, 100, 800, 20, PURPLE);
            DrawText("Hello, Raylib!", 300, 280, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}