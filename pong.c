#include<stdio.h>
#include <raylib.h>
#define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

typedef struct paddle{
    int x;
    int y;
    int width;
    int height;
}paddle;

typedef struct ball{
    int x;
    int y;
    int radius;
    int speed_x;
    int speed_y;
}ball;

void eventHandling(paddle *p, int speed){
    if( p->y >= 0 || p->y <=800)
    {
        if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S) ){
            p->y += speed;
        }
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)){
            p->y -= speed;
        }
        if (p->y <=0)
        {
            p->y = 0;
        }
        if (p->y + p->height >= GetScreenHeight())
        {
            p->y = GetScreenHeight() - p->height;
        }
        
    }
     
}

void ball_collision_Detection(ball * b,  int y){

    if (b->radius + b->y >= GetScreenHeight() || b->y - b->radius <= 0 ) // check if it bounces on the bottom or top of screen
    {
        b->speed_y *= -1;
    }
    if (b->radius + b->x >= GetScreenWidth() || b->x - b->radius <= 0 )
    {
        b->speed_x *= -1;
    }
}

void ball_Paddle_collision(paddle *p1, paddle *p2, ball * b){
    if(CheckCollisionCircleRec((Vector2){b->x, b->y}, b->radius, (Rectangle){p1->x, p1->y, p1->width, p1->height} ))
    {
        b->speed_x *= -1;
        
    }
    
    if (CheckCollisionCircleRec((Vector2){b->x, b->y}, b->radius, (Rectangle){p2->x, p2->y, p2->width, p2->height} )){
        b->speed_x *= -1;
        printf("Connect2\n");
    }
}

void Move_Ball(ball *b, int speed){
    // start of the game the ball moves to one of the paddles to start the game
    b->x += b->speed_x;
    b->y += b->speed_y;
}



void CPU_Move(paddle *p, int speed, ball * b){
    // to move the non-user paddle, just moves up and down
    // paddle should move up and down once it has reached bottom or top of window.
    if (p->y + p->height > b->y ){
        p->y = p->y - (speed);
    }
    else{
        p->y = p->y + (speed);
    }
}

int main(){

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong in C");
    SetTargetFPS(60);
    paddle p1;
    paddle p2;
    ball b;
    p1.x = 0;
    p1.y = 400;
    p2.x = 770;
    p2.y = 400;
    p1.width = 30;
    p1.height = 100;
    p2.width = 30;
    p2.height = 100;
    b.x = 400;
    b.y = 300;
    int speed = 5;
    b.radius = 20;
    b.speed_x = 5;
    b.speed_y = 5;
    
    while(!WindowShouldClose()){
        // Event handling
       
            
        Move_Ball(&b, speed);
        eventHandling(&p1, speed);
        CPU_Move(&p2, speed, &b);
        // Collision detection
        ball_collision_Detection(&b, SCREEN_HEIGHT);
        ball_Paddle_collision(&p1, &p2, &b);
  
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Pong", 380, 0, 24, WHITE);
            DrawLine(SCREEN_WIDTH/2, 0, SCREEN_WIDTH /2, SCREEN_HEIGHT, WHITE);
            DrawCircle(b.x, b.y, b.radius, PURPLE);
            DrawRectangle(p1.x, p1.y, p1.width, p1.height, GREEN);
            DrawRectangle(p2.x, p2.y, p2.width, p2.height, BLUE);
            
           
        EndDrawing();

    }

    CloseWindow();

    return 0;
}