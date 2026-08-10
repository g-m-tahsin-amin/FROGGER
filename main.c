#include "raylib.h"
#include<stdio.h>
#include<stdbool.h>


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 780;
    const int screenHeight = 780;
    const int log_width=screenHeight/13;
    const int circle_radius=20;
    const int turtle=55;

    
    
    InitWindow(screenWidth, screenHeight, "FROGGER");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    int total_lives=3; 
    bool y=1;         //abir. add an extra life after 20000 points  
    Vector2 position={screenWidth/2-30,screenHeight-30};
    float speed=60;
    float deltaTime=GetFrameTime();
   
// Obstackes c=car,l=log

 int score=0, x=0; //abir
 Vector2 c_position1={780,screenHeight-120};
 float c_speed1=7;
 Vector2 c_size1={45,58};

 Vector2 c_position2={720,screenHeight-180};
 float c_speed2=6;
 Vector2 c_size2={75,58};

 Vector2 c_position3={320,screenHeight-240};
 float c_speed3=7.2;
 Vector2 c_size3={100,58};

 Vector2 c_position4={0,screenHeight-300};
 float c_speed4=9;
 Vector2 c_size4={60,58};

 Vector2 c_position5={20,screenHeight-360};
 float c_speed5=6.7;
 Vector2 c_size5={86,58};
//logs


 Vector2 l_position1[3];
float l_speed1[3] = {3.5,3.5,3.5}; 
  int s_length = 85;
  Vector2 s_size[3];

for(int i=0;i<3;i++)
{ l_position1[i].x=7+(s_length+100)*i;
  l_position1[i].y=240;
  s_size[i].x=s_length;
  s_size[i].y=55;
}



Vector2 l_position2[3];
float l_speed2[3] = {2.5,2.5,2.5}; 
  int l_length = 160;
  Vector2 l_size[3];

for(int i=0;i<3;i++)
{ l_position2[i].x=40+(l_length+100)*i;
  l_position2[i].y=180;
  l_size[i].x=l_length;
  l_size[i].y=55;
}



Vector2 l_position3[3];
float l_speed3[3] = {3,3,3}; 
  int m_length = 110;
  Vector2 m_size[3];

for(int i=0;i<3;i++)
{ l_position3[i].x=60+(m_length+100)*i;
  l_position3[i].y=60;
  m_size[i].x=m_length;
  m_size[i].y=55;
}

//Turtles (helping + Submerge)

Vector2 t_position1[3];
Vector2 ts_position1[3];
float t_speed1[3]={4,4,4};
Vector2 t_size={turtle,55};

for(int i=0;i<3;i++)
{ t_position1[i].x=10+turtle*i;
  t_position1[i].y=300;
  ts_position1[i].x=400+turtle*i;
  ts_position1[i].y=300;
}


Vector2 t_position2[2];
Vector2 t_position3[2];
Vector2 t_position4[2];
float t_speed2=4;
for(int i=0;i<2;i++)
{ t_position2[i].x=5+turtle*i;
  t_position3[i].x=300+turtle*i;
  t_position4[i].x=600+turtle*i;

  t_position2[i].y=120;
  t_position3[i].y=120;
  t_position4[i].y=120;
}









//collison check


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if(total_lives){ //abir. changed collides to total_lives, and transfered from drawrectangle portion, so player control shall be available as long as life is not 0
        if(IsKeyPressed(KEY_RIGHT)) position.x+=speed;
        if(IsKeyPressed(KEY_LEFT)) position.x-=speed;
        if(IsKeyPressed(KEY_UP)) {position.y-=speed;
            //updating player score
             if(x==0) score+=10;
             if(x<0) x++;
            }
        if(IsKeyPressed(KEY_DOWN)){
            position.y+=speed;
            x--;
        } 
        }
        
        if(position.x-30<0) position.x=30;
        if(position.x+30>screenWidth) position.x=screenWidth-30;
        
        if(position.y+30>780) position.y=screenHeight-30;
        if(position.y-30<0) position.y=30;
       
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        if(score>=20000 && y==1) total_lives++; //abir. add extra life after 20k points
 bool collide= ( CheckCollisionCircleRec(position,circle_radius,(Rectangle){c_position1.x,c_position1.y,c_size1.x,c_size1.y}) ||
 CheckCollisionCircleRec(position,circle_radius,(Rectangle){c_position2.x,c_position2.y,c_size2.x,c_size2.y}) ||
 CheckCollisionCircleRec(position,circle_radius,(Rectangle){c_position3.x,c_position3.y,c_size3.x,c_size3.y}) ||
 CheckCollisionCircleRec(position,circle_radius,(Rectangle){c_position4.x,c_position4.y,c_size4.x,c_size4.y}) ||
 CheckCollisionCircleRec(position,circle_radius,(Rectangle){c_position5.x,c_position5.y,c_size5.x,c_size5.y}) );


bool Is_stand_on1= (CheckCollisionCircleRec(position,circle_radius,(Rectangle){l_position1[0].x,l_position1[0].y,s_size[0].x,s_size[0].y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){l_position1[1].x,l_position1[1].y,s_size[1].x,s_size[1].y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){l_position1[2].x,l_position1[2].y,s_size[2].x,s_size[2].y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){l_position2[0].x,l_position2[0].y,l_size[0].x,l_size[0].y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){l_position2[1].x,l_position2[1].y,l_size[1].x,l_size[1].y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){l_position2[2].x,l_position2[2].y,l_size[2].x,l_size[2].y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){l_position3[0].x,l_position3[0].y,m_size[0].x,m_size[0].y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){l_position3[1].x,l_position3[1].y,m_size[1].x,m_size[1].y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){l_position3[2].x,l_position3[2].y,m_size[2].x,m_size[2].y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){t_position2[0].x,t_position2[0].y,t_size.x,t_size.y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){t_position2[1].x,t_position2[1].y,t_size.x,t_size.y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){t_position3[0].x,t_position3[0].y,t_size.x,t_size.y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){t_position3[1].x,t_position3[1].y,t_size.x,t_size.y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){t_position4[0].x,t_position4[0].y,t_size.x,t_size.y}) ||
CheckCollisionCircleRec(position,circle_radius,(Rectangle){t_position4[1].x,t_position4[1].y,t_size.x,t_size.y})
);


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GRAY);
            
            // Drawing rectangle Outline
       
            DrawRectangle(0,screenHeight-60,780,60,DARKGREEN);
            DrawRectangle(0,screenHeight-360,780,300,GRAY);
            DrawRectangle(0,360,780,60,PURPLE);
            DrawRectangle(0,60,780,300,DARKBLUE);
            DrawRectangle(0,0,780,60,DARKGREEN);

// player drawing
     DrawCircleV(position,30,GREEN);
//Obstackles   

//CARS movement....TAHSIN
     c_position1.x-=c_speed1;
       if(c_position1.x+100<0) c_position1.x=780;
     DrawRectangleV(c_position1,c_size1,BLUE);

     c_position2.x+=c_speed2;
       if(c_position2.x-60>screenWidth) c_position2.x=0;
     DrawRectangleV(c_position2,c_size2,BLUE);

     c_position3.x-=c_speed3;
       if(c_position3.x+100<0) c_position3.x=780;
     DrawRectangleV(c_position3,c_size3,BLUE);

     c_position4.x+=c_speed4;
       if(c_position4.x-80>screenWidth) c_position4.x=0;
     DrawRectangleV(c_position4,c_size4,BLUE);

     c_position5.x-=c_speed5;
       if(c_position5.x+100<0) c_position5.x=780;
     DrawRectangleV(c_position5,c_size5,BLUE);
     
    
    
// log movement....TAHSIN
for(int i=0;i<3;i++)
{
l_position1[i].x+=l_speed1[i];
DrawRectangleV(l_position1[i],s_size[i],BROWN);
if(l_position1[i].x>780) l_position1[i].x=0;
}

for(int i=0;i<3;i++)
{
l_position2[i].x+=l_speed2[i];
DrawRectangleV(l_position2[i],l_size[i],BROWN);
if(l_position2[i].x>780) l_position2[i].x=0;
}


for(int i=0;i<3;i++)
{
l_position3[i].x+=l_speed3[i];
DrawRectangleV(l_position3[i],m_size[i],BROWN);
if(l_position3[i].x>780) l_position3[i].x=0;
}

//Turtle movement....TAHSIN

for(int i=0;i<3;i++)
{
t_position1[i].x-=t_speed1[i];
ts_position1[i].x-=t_speed1[i];
DrawRectangleV(t_position1[i],t_size,RED);
DrawRectangleV(ts_position1[i],t_size,BLACK);
if(ts_position1[i].x<0) ts_position1[i].x=780;
if(t_position1[i].x<0) t_position1[i].x=780;
}

for(int i=0;i<2;i++)
{
t_position2[i].x-=t_speed2;
t_position3[i].x-=t_speed2;
t_position4[i].x-=t_speed2;
DrawRectangleV(t_position2[i],t_size,RED);
DrawRectangleV(t_position3[i],t_size,RED);
DrawRectangleV(t_position4[i],t_size,RED);

if(t_position2[i].x<0) t_position2[i].x=780;
if(t_position3[i].x<0) t_position3[i].x=780;
if(t_position4[i].x<0) t_position4[i].x=780;


}





// Game Over
if((collide)){
    total_lives--; //abir collision will decrease total lives
    position.y=screenHeight- 30;
    position.x=screenWidth/2- 30; //abir  player starts from base position after collision
}
if(!total_lives) DrawText("GAME OVER",screenWidth/2-350,screenHeight/2-100,100,BLACK); //abir





// Player movement

float deltaTime=GetFrameTime();





// Road divider
int y=420;    
for(int i=1;i<=4;i++)
    { Vector2 start={0, y+i*60};
      Vector2 end={780,y+i*60};
      DrawLineDashed(start,end,20,8,RAYWHITE);
    }



            DrawText(TextFormat("SCORE: %d",score), 2, 2, 20,RAYWHITE); //abir

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

  }  // De-Initialization
    //----------------
