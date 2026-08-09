
#include "raylib.h"
#include<stdio.h>
#include<stdbool.h>


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 780;
    const int log_width=screenHeight/13;

    InitWindow(screenWidth, screenHeight, "FROGGER");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    int total_lives=3;   
    Vector2 position={screenWidth/2-30,screenHeight-30};
    float speed=60;
    float deltaTime=GetFrameTime();
   
// Obstackes c=car,l=log


 Vector2 c_position1={800,screenHeight-120};
 float c_speed1=8;
 Vector2 c_size1={80,58};

 Vector2 c_position2={720,screenHeight-180};
 float c_speed2=10;
 Vector2 c_size2={75,58};

 Vector2 c_position3={320,screenHeight-240};
 float c_speed3=12;
 Vector2 c_size3={100,58};

 Vector2 c_position4={460,screenHeight-300};
 float c_speed4=13;
 Vector2 c_size4={90,58};

 Vector2 c_position5={20,screenHeight-360};
 float c_speed5=14;
 Vector2 c_size5={86,58};

//collison check


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if(IsKeyPressed(KEY_RIGHT)) position.x+=speed;
        if(IsKeyPressed(KEY_LEFT)) position.x-=speed;
        if(IsKeyPressed(KEY_UP)) position.y-=speed;
        if(IsKeyPressed(KEY_DOWN)) position.y+=speed;
        
        if(position.x-30<0) position.x=30;
        if(position.x+30>800) position.x=770;
        
        if(position.y+30>780) position.y=750;
        if(position.y-30<0) position.y=30;
       
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
 bool collide= ( CheckCollisionCircleRec(position,30,(Rectangle){c_position1.x,c_position1.y,c_size1.x,c_size1.y}) ||
 CheckCollisionCircleRec(position,30,(Rectangle){c_position2.x,c_position2.y,c_size2.x,c_size2.y}) ||
 CheckCollisionCircleRec(position,30,(Rectangle){c_position3.x,c_position3.y,c_size3.x,c_size3.y}) ||
 CheckCollisionCircleRec(position,30,(Rectangle){c_position4.x,c_position4.y,c_size4.x,c_size4.y}) ||
 CheckCollisionCircleRec(position,30,(Rectangle){c_position5.x,c_position5.y,c_size5.x,c_size5.y}) );


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GRAY);
            
            // Drawing rectangle Outline
            DrawRectangle(0,screenHeight-60,800,60,DARKGREEN);
            DrawRectangle(0,screenHeight-360,800,300,GRAY);
            DrawRectangle(0,360,800,60,PURPLE);
            DrawRectangle(0,60,800,300,DARKBLUE);
            DrawRectangle(0,0,800,60,DARKGREEN);

// player drawing
     DrawCircleV(position,30,GREEN);
//Obstackles   

if(!collide)
   { c_position1.x-=c_speed1;
       if(c_position1.x+100<0) c_position1.x=800;
     DrawRectangleV(c_position1,c_size1,BLUE);

     c_position2.x-=c_speed2;
       if(c_position2.x+100<0) c_position2.x=800;
     DrawRectangleV(c_position2,c_size2,BLUE);

     c_position3.x-=c_speed3;
       if(c_position3.x+100<0) c_position3.x=800;
     DrawRectangleV(c_position3,c_size3,BLUE);

     c_position4.x-=c_speed4;
       if(c_position4.x+100<0) c_position4.x=800;
     DrawRectangleV(c_position4,c_size4,BLUE);

     c_position5.x-=c_speed5;
       if(c_position5.x+100<0) c_position5.x=800;
     DrawRectangleV(c_position5,c_size5,BLUE);
   }
// Game Over
if(collide){
    DrawText("GAME OVER",screenWidth/2-350,screenHeight/2-100,100,BLACK);
}




// Player movement

float deltaTime=GetFrameTime();





// Road divider
int y=420;    
for(int i=1;i<=4;i++)
    { Vector2 start={0, y+i*60};
      Vector2 end={800,y+i*60};
      DrawLineDashed(start,end,20,8,RAYWHITE);
    }



            DrawText("SCORE: ", 2, 2, 20,RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
