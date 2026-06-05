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

void Draw_Start_Button(Button *sb){
    
}
void Draw_Quit_Button(Button *qb){
    Rectangle rec = {qb->x, qb->y, qb->height, qb->width};
    DrawRectangleRounded(rec, 0.2f, 10, qb->colour);

    int fontsize = 24;
    int textWidth = MeasureText(qb->text, fontsize);
    
    int textX = qb->x + (qb->width - textWidth) / 2;
    int textY = qb->y + (qb->height - fontsize) / 2;

    DrawText(qb->text, textX, textY, fontsize, WHITE);
}
bool button_pressed(Button *btn){
    printf("%u\n", btn->colour);
    Rectangle rec = {btn->x, btn->y, btn->height, btn->width,};
    DrawRectangleRounded(rec, 0.2f, 10, btn->colour);

    int fontsize = 24;
    int textWidth = MeasureText(btn->text, fontsize);

    int textX = btn->x + (btn->width - textWidth) / 2;
    int textY = btn->y + (btn->height - fontsize) / 2;

   
    bool hovering = CheckCollisionPointRec(GetMousePosition(), rec); // checks if mouse is in rectangle
    if (hovering == false) { // if the mouse isn't hovering over the button
        btn->colour = btn->colour; // should be the buttons original colour
        
     } // changes color if hovering 
    else {
        DrawRectangleRounded(rec, 0.2f, 10, ColorBrightness(btn->colour, -0.3f));// darker shade
        
    }

     DrawText(btn->text, textX, textY, 100, WHITE);
    

    if(hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // if buttoned clicked
    {
        TraceLog(LOG_INFO, "Start Pressed");
        
        return true;
    }
    else{
        return false;
    }
    
}

bool quit_button_Pressed(Button *quitButton){
    
    Rectangle rec = {quitButton->x, quitButton->y, quitButton->height, quitButton->width,};

    bool hovering = CheckCollisionPointRec(GetMousePosition(), rec);
    if (hovering) {
        quitButton->colour = BLUE;
        // DrawRectangleRec(quitButton, RED); 
        // DrawText("QUIT", 360, 315, 24, WHITE);
     } // changes color if hovering
    else {
        quitButton->colour = DARKBLUE;
        // DrawRectangleRec(quitButton, DARKBLUE); 
        // DrawText("QUIT", 360, 315, 24, WHITE);
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
    SetTargetFPS(60);

    bool st_clicked;
    bool qt_clicked;
    state game_state = MENU;

    //Rectangle startButton = {300, 200, 200, 50};
    //Rectangle quitButton = {300, 200, 200, 150};
    Button startButton = {200,200, 100, 60, GREEN}; // x, y, height, width
    Button quitButton = {300, 200, 300, 150, BLUE};
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