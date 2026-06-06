#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TILE_SIZE 32

#define MAP_ROWS 17
#define MAP_COLS 30
#define SKY 0
#define GROUND 1
#define EMPTY 2
#define PIZZA 3

typedef enum state
{
    MENU,
    GAME,
    QUIT
} state;

typedef struct Button
{
    int x;
    int y;
    int height;
    int width;
    Color colour;
    const char *text;
    const int y_pos;
    int direction;
} Button;

bool button_pressed(Button *btn)
{
    // draw the button
    Rectangle rec = {
        btn->x,
        btn->y,
        btn->height,
        btn->width,
    };

    int fontsize = 24;
    int textWidth = MeasureText(btn->text, fontsize);

    int textX = btn->x + (btn->width - textWidth) / 2;
    int textY = btn->y + (btn->height - textWidth) / 2;
    // button interaction
    bool hovering = CheckCollisionPointRec(GetMousePosition(), rec); // checks if mouse is in rectangle

    Color drawcolour = hovering ? ColorBrightness(btn->colour, -0.3f) : btn->colour; // if the mouse is hovering over the button
    DrawRectangleRounded(rec, 0.2f, 10, drawcolour);

    DrawText(btn->text, textX, textY, 20, WHITE);

    return hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

// function that makes the loading screen buttons move up and down like in old 2d games
void button_Bounce(Button *btn, int bounce)
{
    btn->y += bounce *btn->direction; // make it bounce down
    if (btn->y >= btn->y_pos +  40)
    {
        btn->direction = -1;
        //btn->y += bounce;
        printf("inside speed = %d\n", bounce);
    }
    if(btn->y <= btn->y_pos +bounce){
        btn->direction = 1;
    }
}

int main()
{
    InitWindow(MAP_COLS * TILE_SIZE, MAP_ROWS * TILE_SIZE, "Pete's Pizza");
    SetTargetFPS(60);

    bool st_clicked;
    bool qt_clicked;
    state game_state = MENU;

    // Rectangle startButton = {300, 200, 200, 50};
    // Rectangle quitButton = {300, 200, 200, 150};
    Button startButton = {200, 200, 100, 60, RED, "START", 200, 1}; // x, y, height, width
    Button quitButton = {700, 200, 100, 60, RED, "QUIT", 200, 1};
    Texture bg = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//start_background.png");

    Texture2D tiles[4];
    tiles[0] = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//sky.png");
    tiles[1] = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//ground.png");
    tiles[2] = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//pizza.png");
    tiles[3] = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//lava.png");

    int speed = 1; // button movement

    int map[MAP_ROWS][MAP_COLS];
    FILE *f = fopen("C://Users//Anas//Raylib_Game//mario_rip_off//map.dat", "r");
    if (f == NULL)
    {
        printf("map.dat failed to open\n");
        return -1; // stop here, don't continue
    }
    for (int row = 0; row < MAP_ROWS; row++)
    {
        for (int col = 0; col < MAP_COLS; col++)
        {
            fscanf(f, "%d", &map[row][col]);
        }
    }
    fclose(f);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(bg, 0, 0, WHITE);
        // Draw_Start_Button(&startButton);
        // Draw_Quit_Button(&quitButton);
        st_clicked = button_pressed(&startButton);
        qt_clicked = button_pressed(&quitButton);
        button_Bounce(&startButton, speed);
        button_Bounce(&quitButton, speed);

        if (st_clicked == true)
        {
            game_state = GAME;
        }
        else if (qt_clicked)
        {
            game_state = QUIT;
        }

        if (game_state == GAME)
        {
            ClearBackground(BLACK);
            for (int row = 0; row < MAP_ROWS; row++)
            {
                for (int col = 0; col < MAP_COLS; col++)
                {
                    int tile = map[row][col];
                    switch(tile){
                        case 0:
                            DrawTexture(tiles[0], col *TILE_SIZE, row * TILE_SIZE, WHITE);
                            break;
                        case 1:
                            int above = (row > 0) ? map[row - 1][col] : 0;

                            if(above == 0){
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color){139, 94, 60, 255});
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color){34, 139, 34, 255});
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color){20, 100, 20, 255});
                            }
                            else{
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color){139, 94, 60, 255});
                            }
                            break;
                        case 3:
                            DrawTexture(tiles[3], col *TILE_SIZE, row * TILE_SIZE, WHITE);
                            
                            break;
                    }
                }
            }
        }
        else if (game_state == QUIT)
        {
            break;
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}