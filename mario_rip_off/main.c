#include <raylib.h>
#include <stdio.h>
# include <stdlib.h>
#include <stdbool.h>

#define TILE_SIZE 32

#define MAP_ROWS 17
#define MAP_COLS 30
#define SKY 0
#define GROUND 1
#define EMPTY 2
#define PIZZA 3

typedef enum state{
    MENU,
    GAME, 
    QUIT
}state;

typedef struct Button{
    int x;
    int y;
    int height;
    int width;
    Color colour;
    const char *text;
} Button;


bool button_pressed(Button *btn){
    // draw the button
    Rectangle rec = {btn->x, btn->y, btn->height, btn->width,};
    
    int fontsize = 24;
    int textWidth = MeasureText(btn->text, fontsize);

    int textX = btn->x + (btn->width - textWidth) / 2;
    int textY = btn->y + (btn->height - textWidth) / 2;
    // button interaction
    bool hovering = CheckCollisionPointRec(GetMousePosition(), rec); // checks if mouse is in rectangle
    
    Color drawcolour = hovering ?  ColorBrightness(btn->colour, -0.3f) : btn->colour; // if the mouse is hovering over the button
    DrawRectangleRounded(rec, 0.2f, 10, drawcolour);

    DrawText(btn->text, textX, textY, 20, WHITE);
    

   return  hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}






int main(){
    InitWindow(MAP_COLS * TILE_SIZE, MAP_ROWS * TILE_SIZE, "Pete's Pizza");
    SetTargetFPS(60);

    bool st_clicked;
    bool qt_clicked;
    state game_state = MENU;

    //Rectangle startButton = {300, 200, 200, 50};
    //Rectangle quitButton = {300, 200, 200, 150};
    Button startButton = {200, 200, 100, 60, RED, "START"}; // x, y, height, width
    Button quitButton = {700, 200, 100, 60, RED, "QUIT"};
    Texture bg = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//start_background.png");

    Texture2D tiles[4];
    tiles[0] = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//sky.png");
    tiles[1] = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//ground.png");
    tiles[2] = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//pizza.png");
    tiles[3] = LoadTexture("C://Users//Anas//Raylib_Game//mario_rip_off//lava.png");

    int map[MAP_ROWS][MAP_COLS];
    FILE * f = fopen("C://Users//Anas//Raylib_Game//mario_rip_off//map.dat", "r");
    if (f == NULL) {
        printf("map.dat failed to open\n");
        return -1;  // stop here, don't continue
}
    for (int row = 0; row < MAP_ROWS; row++){
        for(int col = 0; col < MAP_COLS; col++){
            fscanf(f,"%d", &map[row][col]);
        }
    }
    fclose(f);
    


    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(bg, 0, 0, WHITE);
            // Draw_Start_Button(&startButton);
            //Draw_Quit_Button(&quitButton);
            st_clicked = button_pressed(&startButton);
            qt_clicked = button_pressed(&quitButton);
            
            if (st_clicked == true){
                printf("H");
                game_state = GAME;
            }
            else if(qt_clicked){
                game_state = QUIT;
            }
            
            if (game_state == GAME){
                ClearBackground(BLACK);
                for (int row = 0; row < MAP_ROWS; row++){
                    for (int col = 0; col < MAP_COLS; col++){
                        int tile = map[row][col];
                        DrawTexture(tiles[tile],col * TILE_SIZE, row *TILE_SIZE, WHITE);
                    }
                }
                
            }
            else if (game_state == QUIT){
                break;
            }
            
            
        EndDrawing();

    }
    CloseWindow();
     
    return 0;
}