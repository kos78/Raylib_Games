#include <raylib.h>
#include <stdio.h>
# include <stdlib.h>

#define TILE_SIZE 32

#define MAP_ROWS 17
#define MAP_COLS 30
#define SKY 0
#define GROUND 1
#define EMPTY 2
#define PIZZA 3



int main(){
    InitWindow(MAP_COLS * TILE_SIZE, MAP_ROWS * TILE_SIZE, "Pete's Pizza");
printf("Working directory: %s\n", GetWorkingDirectory());
    SetTargetFPS(60);

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
            for (int row = 0; row < MAP_ROWS; row++)
            {
                for(int col = 0; col < MAP_COLS; col++)
                {
                    int tile = map[row][col];
                    DrawTexture(tiles[tile], col *TILE_SIZE, row * TILE_SIZE, WHITE);
                    
                }
            }
        EndDrawing();

    }
     
    return 0;
}