#include<stdio.h>
#include <raylib.h>

typedef struct paddle{
    int x;
    int y;
}paddle;

typedef struct ball{
    int x;
    int y;
    int radius;
}ball;

void eventHandling(paddle *p, int speed){
     if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
            p->y += speed;
        }
        else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
            p->y -= speed;
        }
}

int collision_Detection(paddle *p1, paddle *p2, ball * b){
    if(b->radius + b->x == p1->x || b->radius - b->x == p1->x){
        return 1;
    }

}

int main(){

    InitWindow(800, 800, "Pong in C");
    SetTargetFPS(60);
    paddle p1;
    paddle p2;
    ball b;
    p1.x = 0;
    p1.y = 400;
    p2.x = 750;
    p2.y = 400;
    b.x = 400;
    b.y = 400;
    b.radius = 20;
    int speed = 5;
    
    while(!WindowShouldClose()){
        // Event handling
        eventHandling(&p1, speed);
       
        // Collision detection
        collision_Detection();
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircle(b.x, b.y, b.radius, PURPLE);
            DrawRectangle(p1.x, p1.y, 50, 100, GREEN);
            DrawRectangle(p2.x, p2.y, 50, 100, BLUE);
        EndDrawing();

    }

    CloseWindow();

    return 0;
}