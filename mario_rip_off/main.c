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

typedef struct Player{
    Vector2 position;
    Texture2D image;
    float speed;
}Player;

typedef struct Platform{
    int x;
    int y;
    int height;
    int width;
    int direction;
    const int y_pos;
    const int x_pos;
} Platform;

void player_Movement(Player * p){
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        p->position.x -= p->speed;
    }
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        p->position.x += p->speed;
    }
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        p->position.y -= p->speed;
    }
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        p->position.y -= p->speed;
    }
}


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
        
    }
    if(btn->y <= btn->y_pos){
        btn->direction = 1;
    }
}
// function to draw any platform in the game
void drawPlatform(Platform *p){
    Rectangle rec = {p->x, p->y, p->width, p->height};
    DrawRectangleRec(rec, (Color){233, 41, 41, 255});

}

void platform_Move(Platform * p, int speed){
    
    p->y += speed * p->direction; // make it bounce down
    if (p->y + p->height >= GetScreenHeight()) // bottom limit
    {
        p->direction = -1;
        
    }
    if(p->y <= p->y_pos ) // upper limit
    {
        p->direction = 1;
        printf("%d", p->direction);
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

    int bounce = 1; // button movement
    int speed = 1;

    Platform block1 = {480, 96, TILE_SIZE, TILE_SIZE * 2, 1, 96, 480};

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
        button_Bounce(&startButton, bounce);
        button_Bounce(&quitButton, bounce);

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

                            if(row == 2){
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color){139, 94, 60, 255});
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE,15, (Color){34, 139, 34, 255});
                                //DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, 3, (Color){20, 100, 20, 255});
                            }
                            else if (above == 0 && row != 2){
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color){139, 94, 60, 255});
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, (TILE_SIZE/3), (Color){64, 64, 64, 255});
                            }
                            else{
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color){139, 94, 60, 255});
                                
                            }
                            break;
                       
                        case 3:
                                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE , (Color){255, 153,51, 255});
                                //DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, (TILE_SIZE/3), (Color){255, 153,51, 255});
                                break;
                    }
                    
                    
                }
            }
            drawPlatform(&block1);
            platform_Move(&block1, speed);
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