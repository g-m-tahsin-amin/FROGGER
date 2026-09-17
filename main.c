#include <stdio.h>
#include "raylib.h"
#include <stdbool.h>


#define SCREEN_WIDTH 940
#define SCREEN_HEIGHT 780
#define LANE_SIZE 60
#define score_side 200

int main(void)
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FROGGER");
    SetTargetFPS(60);

    
    const int cell_width=LANE_SIZE;  
    const int cellHeight=LANE_SIZE; 
    const float dt=GetFrameTime();
    
    int total_lives=5;           
    int score=0; 
    int y=0;
    
    
    
    Vector2 position = { (float)((SCREEN_WIDTH-score_side)/2-LANE_SIZE/2),(float)(SCREEN_HEIGHT-LANE_SIZE)};
    float speed = 60; 



    Texture2D bg_image=LoadTexture("Frogger_sprites/background.png");
    Rectangle bg_src={ 0.0f,0.0f,(float)bg_image.width,(float)bg_image.height};
    Rectangle bg_position = { 0.0f, 0.0f,(float)SCREEN_WIDTH-score_side,(float)SCREEN_HEIGHT};
    Vector2 origin={ 0.0f, 0.0f };

    
    Texture frog[2]={ LoadTexture("Frogger_sprites/frog1.png"), LoadTexture("Frogger_sprites/frog2.png") };
    
    Rectangle srcImgFrog[2]={
        { 0.0f, 0.0f, (float)frog[0].width, (float)frog[0].height },  
        { 0.0f, 0.0f, (float)frog[1].width, (float)frog[1].height }
    };

    
    Texture log[3]={ LoadTexture("Frogger_sprites/log3.png"), LoadTexture("Frogger_sprites/log1.png"), LoadTexture("Frogger_sprites/log2.png") };
    Rectangle srcImglog[3] = {
        { 0,0,log[0].width,log[0].height},   
        { 0,0,log[1].width,log[1].height },
        { 0,0,log[2].width,log[2].height }
    };

    Texture fly = LoadTexture("Frogger_sprites/fly.png");
    
    Texture endfrog = LoadTexture("Frogger_sprites/endfrog.png");
    Rectangle srcEndFrog={0,0,endfrog.width,endfrog.height} ;


    Texture car[5]={
        LoadTexture("Frogger_sprites/car1.png"),
        LoadTexture("Frogger_sprites/car2.png"), 
        LoadTexture("Frogger_sprites/car3.png"),
        LoadTexture("Frogger_sprites/car4.png"),
        LoadTexture("Frogger_sprites/car5.png")
    };
    Rectangle srcImgcar[5]={
        { 0,0,car[0].width,car[0].height },
        { 0,0,car[1].width,car[1].height },   
        { 0,0,car[2].width,car[2].height },
        { 0,0,car[3].width,car[3].height },
        { 0,0,car[4].width,car[4].height }
    };

    Texture turtles[2] = {LoadTexture("Frogger_sprites/3turtles.png"), LoadTexture("Frogger_sprites/2turtles.png") };
    Rectangle srcImgturtles[2] = {
        { 0,0,turtles[0].width,turtles[0].height },   
        { 0,0,turtles[1].width,turtles[1].height }
    };

    Texture shells[3]={LoadTexture("Frogger_sprites/1shell.png"), LoadTexture("Frogger_sprites/2shells.png"), LoadTexture("Frogger_sprites/3shells.png") };
    Rectangle srcImgshells[3]={
        { 0,0,shells[0].width,shells[0].height },
        { 0,0,shells[1].width,shells[1].height },  
        { 0,0,shells[2].width,shells[2].height }
    };

    Texture lives[5]={
        LoadTexture("Frogger_sprites/1life.png"),
        LoadTexture("Frogger_sprites/2lives.png"), 
        LoadTexture("Frogger_sprites/3lives.png"), 
        LoadTexture("Frogger_sprites/4lives.png"), 
        LoadTexture("Frogger_sprites/5lives.png")
    };
    Rectangle srcImglives[5]={
        { 0,0,lives[0].width,lives[0].height },
        { 0,0,lives[1].width,lives[1].height },
        { 0,0,lives[2].width,lives[2].height },  
        { 0,0,lives[3].width,lives[3].height },
        { 0,0,lives[4].width,lives[4].height }
    };

    Rectangle lives_position={SCREEN_WIDTH-score_side+20,580,99,30};

   
    Rectangle car_position[5][3]={
        { { 0, 11 * cellHeight+7.5,cell_width, cellHeight-15 }, { 4 *cell_width, 11 * cellHeight+7.5,cell_width, cellHeight-15 }, { 8 *cell_width, 11 * cellHeight+7.5,cell_width, cellHeight-15 } },
        { { 0, 10 * cellHeight+7.5,cell_width, cellHeight -15}, { 5 *cell_width, 10 * cellHeight+7.5,cell_width, cellHeight-15 }, { 9 *cell_width, 10 * cellHeight+7.5,cell_width, cellHeight-15 } },
        { { 0, 9 * cellHeight+7.5,cell_width, cellHeight -15}, { 4 *cell_width, 9 * cellHeight+7.5,cell_width, cellHeight-15 }, { 8 *cell_width, 9 * cellHeight+7.5,cell_width, cellHeight-15 } },
        { { 0, 8 * cellHeight+7.5,cell_width, cellHeight-15}, { 4 *cell_width, 8 * cellHeight+7.5,cell_width, cellHeight -15}, { 8 *cell_width, 8 * cellHeight+7.5,cell_width, cellHeight-15 } },
        { { 0, 7 * cellHeight+7.5,cell_width * 2, cellHeight-15 }, { 5 *cell_width, 7 * cellHeight+7.5,cell_width* 2, cellHeight-15}, { 10 *cell_width, 7 * cellHeight+7.5,cell_width*2, cellHeight-15} }
    };

    Rectangle turtle_position[2][3]={
        { { 0, 5 * cellHeight, 3*cell_width, cellHeight}, { 4 *cell_width, 5 * cellHeight+2, 3*cell_width, cellHeight}, { 9*cell_width, 5 * cellHeight, 3*cell_width, cellHeight } },
        { { 0, 2 * cellHeight, 2*cell_width, cellHeight }, { 5 *cell_width, 2 * cellHeight, 2*cell_width, cellHeight }, { 10*cell_width, 2 * cellHeight, 2*cell_width, cellHeight } }
    };

    Rectangle log_position[3][3]={
        { { 0, 4 * cellHeight,cell_width * 2, cellHeight }, { 5 *cell_width, 4 * cellHeight,cell_width * 2, cellHeight }, { 10 *cell_width, 4 * cellHeight,cell_width*2, cellHeight } },
        { { 0, 3 * cellHeight,cell_width * 4, cellHeight }, { 7 *cell_width, 3 * cellHeight,cell_width * 4, cellHeight }, { 14 *cell_width, 3 * cellHeight,cell_width*4, cellHeight } },
        { { 0, cellHeight,cell_width*3, cellHeight }, { 7 *cell_width, cellHeight,cell_width*3, cellHeight }, { 14 *cell_width, cellHeight,cell_width*3, cellHeight } }
    };

    Rectangle safe_house[5]={{0,0,80,LANE_SIZE},{190,0,80,LANE_SIZE},{190*2,0,80,LANE_SIZE},
     {190*3,0,80,LANE_SIZE},{190*4,0,80,LANE_SIZE}
   };


     //OBSTACLE MOVEMENTS and SPEEDS .. TAHSIN

    float car_speeds[5] = { 2.5, -1.5, 2.0, -3.5, 1.2 };      
    float log_speeds[3] = { 1.5, 2.2, 1.8 };                   
    float turtle_speeds[2] = { -2.0, -1.6 };                     

    // --- MAIN GAME LOOP ---
    while (!WindowShouldClose() && total_lives!=0)
    {
        if (IsKeyPressed(KEY_UP) && position.y > 0) {
            position.y -=speed+speed*dt;
           if(y==0)
           {
            score+=10;
        
           }
           if(y>0) ++y;
        }
        if (IsKeyPressed(KEY_DOWN) && position.y < SCREEN_HEIGHT-LANE_SIZE) {
            position.y +=speed+speed*dt;
             ++y;
        }
        if (IsKeyPressed(KEY_LEFT) && position.x > 0) {
            position.x -=speed+speed*dt;
        }
        if (IsKeyPressed(KEY_RIGHT) && position.x < SCREEN_WIDTH-score_side-LANE_SIZE) {
            position.x +=speed+speed*dt;
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                car_position[i][j].x += car_speeds[i];
                if ( car_speeds[i] > 0 && car_position[i][j].x > SCREEN_WIDTH-car_position[i][j].width) {
                    car_position[i][j].x =-car_position[i][j].width;
                }
                else if (car_speeds[i] < 0 && car_position[i][j].x < -car_position[i][j].width) {
                    car_position[i][j].x = SCREEN_WIDTH-score_side-car_position[i][j].width;
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                log_position[i][j].x += log_speeds[i];
                if (log_position[i][j].x > SCREEN_WIDTH-log_position[i][j].width) {
                    log_position[i][j].x = -log_position[i][j].width;
                }
            }
        }

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                turtle_position[i][j].x += turtle_speeds[i];
                if (turtle_position[i][j].x < -turtle_position[i][j].width) {
                    turtle_position[i][j].x = SCREEN_WIDTH-score_side-turtle_position[i][j].width;
                }
            }
        }

// =================================================================
// 1. UPDATE THE FROG'S COLLISION RECTANGLE EVERY FRAME (CRITICAL!)
// =================================================================
// We update frog_area dynamically using the current position.x and position.y
Rectangle frog_area = { position.x - 4, position.y - 2, 52, 52 };

// Convert the frog's exact Y position to its current grid row index
int frog_row = (int)(position.y / cellHeight); 

bool on_river = false;
bool safe_on_object = false;
float drift_speed = 0.0f;

// =================================================================
// 2. CHECK TURTLE LANES (Row 5 and Row 2 in your array)
// =================================================================
if (frog_row == 5 || frog_row == 2) 
{
    on_river = true;
    
    // Map grid rows to your turtle_position array indices (Row 5 -> Index 0, Row 2 -> Index 1)
    int i = (frog_row == 5) ? 0 : 1; 
    
    for (int j = 0; j < 3; j++) {
        if (CheckCollisionRecs(frog_area, turtle_position[i][j])) {
            safe_on_object = true;
            drift_speed = turtle_speeds[i]+turtle_speeds[i]*dt;
            break; 
        }
    }
}

// =================================================================
// 3. CHECK LOG LANES (Row 4, Row 3, and Row 1 in your array)
// =================================================================
else if (frog_row == 4 || frog_row == 3 || frog_row == 1) 
{
    on_river = true;
    
    // Map grid rows to your log_position array indices (Row 4 -> 0, Row 3 -> 1, Row 1 -> 2)
    int i = 0;
    if (frog_row == 3) i = 1;
    if (frog_row == 1) i = 2;

    for (int j = 0; j < 3; j++) {
        if (CheckCollisionRecs(frog_area, log_position[i][j])) {
            safe_on_object = true;
            drift_speed = log_speeds[i]+log_speeds[i]*dt;
            break;
        }
    }
}

// =================================================================
// 4. PROCESS OUTCOME Outside of Loops
// =================================================================
if (on_river) {
    if (safe_on_object) {
        // Frog rides the platform safely
        position.x += drift_speed+drift_speed*dt;
    } else {
        // Frog missed everything and drowned -> Respawn
        position.x = (float)((SCREEN_WIDTH - score_side) / 2 - LANE_SIZE / 2);
        position.y = (float)(SCREEN_HEIGHT - LANE_SIZE);
        --total_lives;
    }
}

       for(int i=0;i<5;i++)
       {    for(int j=0;j<3;j++)
           { Rectangle car_area=car_position[i][j];
             
             if(CheckCollisionRecs(frog_area,car_area) && position.y>7*LANE_SIZE && position.y<12*LANE_SIZE)
             {
                position.x=(float)((SCREEN_WIDTH-score_side)/2-LANE_SIZE/2),
                position.y= (float)(SCREEN_HEIGHT- LANE_SIZE);

                --total_lives;
             }

           }
        }


/* for(int i=0;i<2;i++)
{    for(int j=0;j<3;j++)
    { Rectangle turtle_area=turtle_position[i][j];
     if(!CheckCollisionRecs(frog_area,turtle_area) && ((position.y>5*LANE_SIZE && position.y<6*LANE_SIZE) || (position.y>2*LANE_SIZE && position.y<3*LANE_SIZE)))
    {
     position.x=(float)((SCREEN_WIDTH-score_side)/2-LANE_SIZE/2),
     position.y= (float)(SCREEN_HEIGHT-LANE_SIZE);

    --total_lives;
   }
   else if((position.y>5*LANE_SIZE && position.y<6*LANE_SIZE) || (position.y>2*LANE_SIZE && position.y<3*LANE_SIZE))
  {
   position.x+=turtle_speeds[i];
   }
    }
}
for(int i=0;i<3;i++)
 {   for(int j=0;j<3;j++)
    { Rectangle log_area=log_position[i][j];
     if(!CheckCollisionRecs(frog_area,log_area) && ((position.y>4*LANE_SIZE && position.y<5*LANE_SIZE) || (position.y>3*LANE_SIZE && position.y<4*LANE_SIZE) || (position.y>LANE_SIZE && position.y<2*LANE_SIZE)))
    {
    position.x=(float)((SCREEN_WIDTH-score_side)/2-LANE_SIZE/2),
     position.y= (float)(SCREEN_HEIGHT- LANE_SIZE);

    --total_lives;
   }
   else if((position.y>4*LANE_SIZE && position.y<5*LANE_SIZE) || (position.y>3*LANE_SIZE && position.y<4*LANE_SIZE) || (position.y>LANE_SIZE && position.y<2*LANE_SIZE))
   {
    position.x+=log_speeds[i];
    }

    }

  }
*/
/*
            for(int i=0;i<5;i++)
{ Rectangle safe_area=safe_house[i];
  
  if(y<60 && !(CheckCollisionRecs(frog_area,safe_area)))
  {
    position.x=(float)((SCREEN_WIDTH-score_side)/2-LANE_SIZE/2),
     position.y= (float)(SCREEN_HEIGHT- LANE_SIZE);

    --total_lives;
  }
else if(y<60 && (CheckCollisionRecs(frog_area,safe_area)))
{
   DrawTexturePro(endfrog,srcEndFrog,safe_house[i],origin,0,WHITE);
}

}
 */ 


        BeginDrawing();
            ClearBackground(BLACK);

           DrawTexturePro(bg_image,bg_src,bg_position,origin,0,WHITE);
           //DrawRectangle(0,0,SCREEN_WIDTH-score_side,LANE_SIZE,DARKGREEN);
            
           
           /*for(int i=0;i<5;i++)
            {
            DrawRectangle(190*i,0,80,LANE_SIZE,GREEN);
            }
         */
           // incase amar background na ashle
          // DrawRectangle(0,6*LANE_SIZE,SCREEN_WIDTH-score_side,LANE_SIZE,VIOLET);
           //DrawRectangle(0,12*LANE_SIZE,SCREEN_WIDTH-score_side,LANE_SIZE,VIOLET);


            
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    DrawTexturePro(log[i], srcImglog[i],log_position[i][j], origin,0, WHITE);
                }
            }

            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 3; j++) {
                    DrawTexturePro(turtles[i], srcImgturtles[i], turtle_position[i][j], origin,0, WHITE);
                }
            }

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 3; j++) {
                   
                    DrawTexturePro(car[i], srcImgcar[i], car_position[i][j], origin,0, WHITE);
                }
            }


            // =================================================================
// 5. RENDERING (Pass your fresh coordinates here)
// =================================================================
//if (((int)position.y % 10) != 0 || ((int)position.x % 10) != 0) { 
    DrawTexturePro(frog[1], srcImgFrog[1], frog_area, origin, 0.0f, WHITE);
 //} else {
    //DrawTexturePro(frog[0], srcImgFrog[0], frog_area, origin, 0.0f, WHITE);
//}

           /*
               Rectangle frog_position={position.x-4,position.y-2,52,52};
                
            if (((int)position.y % 10) != 0 || ((int)position.x % 10) != 0) { 
                DrawTexturePro(frog[1], srcImgFrog[1], frog_position, origin, 0.0f, WHITE);
            } else {
                DrawTexturePro(frog[0], srcImgFrog[0],frog_position, origin, 0.0f, WHITE);
            }
         */
        DrawRectangle(SCREEN_WIDTH-score_side,0,score_side,SCREEN_HEIGHT,BLACK);

           DrawText("SCORE:\n",SCREEN_WIDTH-score_side+40,100,30,RAYWHITE);
            DrawText(TextFormat("%05d",score),SCREEN_WIDTH-score_side+50,150,30,RAYWHITE);

            DrawText("LIVES:\n",SCREEN_WIDTH-score_side+30,480,30,RAYWHITE);

            if(total_lives!=0)
            DrawTexturePro(lives[total_lives-1],srcImglives[total_lives-1],lives_position,origin,0,WHITE);



        EndDrawing();
    }
}
