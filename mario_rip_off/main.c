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
    int height;
    int width;
    int x;
    int y;
    char colour[50];
} Button;

void Draw_Start_Button(Rectangle startButton){
    DrawRectangleRounded(startButton, 0.2f, 10, GREEN);
    const char *text = "START";
    int fontsize = 24;
    int textWidth = MeasureText(text, fontsize);

    int textX = startButton.x + (startButton.width - textWidth) / 2;
    int textY = startButton.y + (startButton.height - fontsize) / 2;

    DrawText(text, textX, textY, fontsize, WHITE);
}
void Draw_Quit_Button(Rectangle quitbutton){
    DrawRectangleRounded(quitbutton, 0.2f, 10, RED);
    const char *text = "Quit";
    int fontsize = 24;
    int textWidth = MeasureText(text, fontsize);

    int textX = quitbutton.x + (quitbutton.width - textWidth) / 2;
    int textY = quitbutton.y + (quitbutton.height - fontsize) / 2;

    DrawText(text, textX, textY, fontsize, WHITE);
}
bool start_button_Pressed(Rectangle startButton){
    
    
    bool hovering = CheckCollisionPointRec(GetMousePosition(), startButton);
    if (hovering) {
        DrawRectangleRec(startButton, GREEN); 
        DrawText("START", 360, 215, 24, WHITE);
     } // changes color if hovering
    else {
        DrawRectangleRec(startButton, DARKGREEN); 
        DrawText("START", 360, 215, 24, WHITE);
    }

    if(hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // if buttoned clicked
    {
        TraceLog(LOG_INFO, "Start Pressed");
        
        return true;
    }
    else{
        return false;
    }
    
}

bool quit_button_Pressed(Rectangle quitButton){
    
    
    bool hovering = CheckCollisionPointRec(GetMousePosition(), quitButton);
    if (hovering) {
        DrawRectangleRec(quitButton, RED); 
        DrawText("QUIT", 360, 315, 24, WHITE);
     } // changes color if hovering
    else {
        DrawRectangleRec(quitButton, DARKBLUE); 
        DrawText("QUIT", 360, 315, 24, WHITE);
    }

    if(hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // if buttoned clicked
    {
        TraceLog(LOG_INFO, "Quit Pressed");
        
        return true;
    }
    else{
        return false;
    }
    
}




int main(){
    InitWindow(MAP_COLS * TILE_SIZE, MAP_ROWS * TILE_SIZE, "Pete's Pizza");
    printf("Working directory: %s\n", GetWorkingDirectory());
    SetTargetFPS(60);
    bool st_clicked;
    bool qt_clicked;
    state game_state = MENU;

    Rectangle startButton = {300, 200, 200, 50};
    Rectangle quitButton = {300, 200, 200, 150};
    
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
            Draw_Start_Button(startButton);
            Draw_Quit_Button(quitButton);
            st_clicked = start_button_Pressed(startButton);
            qt_clicked = quit_button_Pressed(quitButton);
            printf("%d", st_clicked);
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
                CloseWindow();
            }
            
            
        EndDrawing();

    }
     
    return 0;
}