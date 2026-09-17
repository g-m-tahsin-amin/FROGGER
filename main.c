#include <stdio.h>
#include "raylib.h"
#include <stdbool.h>


#define SCREEN_WIDTH 940
#define SCREEN_HEIGHT 780
#define LANE_SIZE 60
#define score_side 200


typedef enum GameState { 
    STATE_MENU,
    STATE_CREDITS, 
    STATE_PLAYING, 
    STATE_GAMEOVER, 
    STATE_VICTORY 
} GameState;


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
    
    GameState currentState = STATE_MENU;
    int currentLevel = 1;
    int frogsSavedInHouses = 0; // Track completed safe houses (up to 5)
    
    
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

   // Each rectangle represents: { X, Y, Width, Height }
  Rectangle safe_house[5] = {
    { 20.0f,  0.0f, (float)LANE_SIZE, (float)LANE_SIZE }, // House 1 (Far Left)
    { 180.0f, 0.0f, (float)LANE_SIZE, (float)LANE_SIZE }, // House 2
    { 340.0f, 0.0f, (float)LANE_SIZE, (float)LANE_SIZE }, // House 3 (Center)
    { 500.0f, 0.0f, (float)LANE_SIZE, (float)LANE_SIZE }, // House 4
    { 660.0f, 0.0f, (float)LANE_SIZE, (float)LANE_SIZE }  // House 5 (Far Right)
   };



     //OBSTACLE MOVEMENTS and SPEEDS .. TAHSIN

    float car_speeds[5] = { 2.5, -1.5, 2.0, -3.5, 1.2 };      
    float log_speeds[3] = { 1.5, 2.2, 1.8 };                   
    float turtle_speeds[2] = { -2.0, -1.6 };                     

   // BASE VELOCITIES STORED TO SCALE SPEEDS PER LEVEL
   float base_car_speeds[5] = { 2.5, -1.5, 2.0, -3.5, 1.2 };
    float base_log_speeds[3] = { 1.5, 2.2, 1.8 };
    float base_turtle_speeds[2] = { -2.0, -1.6 };


    // --- MAIN GAME LOOP ---
    while (!WindowShouldClose())
    { //Global resets across game loops
        const float dt = GetFrameTime();
        
        // Dynamic frog bounding area calculations
        Rectangle frog_area = { position.x + 4, position.y + 4, 52, 52 };
        int frog_row = (int)(position.y / cellHeight); 

        bool on_river = false;
        bool safe_on_object = false;
        float drift_speed = 0.0f;

        // Variables management configuration setups
        bool isBlasting = false;
        Vector2 blastPosition = { 0, 0 };
        int blastFrameCounter = 0;
        const int BLAST_DURATION = 60; // 60 frames = exactly 1 second at 60 FPS

        // Track which safe houses have been successfully locked down by a frog (0 = empty, 1 = filled)
        int safeHouseFilled[5] = { 0, 0, 0, 0, 0 }; 

        switch (currentState)
        {   
            case STATE_MENU:
                if (IsKeyPressed(KEY_SPACE)) {
                    currentState = STATE_CREDITS;
                }

                else if(IsKeyPressed(KEY_ENTER))
                {
                  // Reset full match parameters on new play start
                    total_lives = 5;
                    score = 0;
                    currentLevel = 1;
                    frogsSavedInHouses = 0;
                    for(int i = 0; i < 5; i++) safeHouseFilled[i] = 0;
                    
                    // Reset speed arrays to base baseline rates
                    for(int i = 0; i < 5; i++) car_speeds[i] = base_car_speeds[i];
                    for(int i = 0; i < 3; i++) log_speeds[i] = base_log_speeds[i];
                    for(int i = 0; i < 2; i++) turtle_speeds[i] = base_turtle_speeds[i];

                    // Reset Frog spawn coordinate points
                    position.x = (float)((SCREEN_WIDTH - score_side) / 2 - LANE_SIZE / 2);
                    position.y = (float)(SCREEN_HEIGHT - LANE_SIZE);
                    currentState = STATE_PLAYING; 
                }
                break;
            case STATE_CREDITS:
             if(IsKeyPressed(KEY_ENTER))
                {
                  // Reset full match parameters on new play start
                    total_lives = 5;
                    score = 0;
                    currentLevel = 1;
                    frogsSavedInHouses = 0;
                    for(int i = 0; i < 5; i++) safeHouseFilled[i] = 0;
                    
                    // Reset speed arrays to base baseline rates
                    for(int i = 0; i < 5; i++) car_speeds[i] = base_car_speeds[i];
                    for(int i = 0; i < 3; i++) log_speeds[i] = base_log_speeds[i];
                    for(int i = 0; i < 2; i++) turtle_speeds[i] = base_turtle_speeds[i];

                    // Reset Frog spawn coordinate points
                    position.x = (float)((SCREEN_WIDTH - score_side) / 2 - LANE_SIZE / 2);
                    position.y = (float)(SCREEN_HEIGHT - LANE_SIZE);
                    currentState = STATE_PLAYING; 
                }
                break;
            
            case STATE_PLAYING:
                // Check general failure match over triggers
                if (total_lives <= 0) {
                    currentState = STATE_GAMEOVER;
                    break;
                }

                // --- 1. KEYBOARD INPUT INPUT HANDLING ---
                if (IsKeyPressed(KEY_UP) && position.y > 0) {
                    position.y -= LANE_SIZE; // Changed to instant lane jump spacing 
                    //PlaySound(jumpSound);
                    if (y == 0) { score += 10; }
                    if (y > 0) ++y;
                }
                if (IsKeyPressed(KEY_DOWN) && position.y < SCREEN_HEIGHT - LANE_SIZE) {
                    position.y += LANE_SIZE;
                  //  PlaySound(jumpSound);
                    ++y;
                }
                if (IsKeyPressed(KEY_LEFT) && position.x > 0) {
                    position.x -= LANE_SIZE;
                   // PlaySound(jumpSound);
                }
                if (IsKeyPressed(KEY_RIGHT) && position.x < SCREEN_WIDTH - score_side - LANE_SIZE) {
                    position.x += LANE_SIZE;
                   // PlaySound(jumpSound);
                }

                // --- 2. MOVE ENVIRONMENT ELEMENTS CONTROLS ---
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 3; j++) {
                        car_position[i][j].x += car_speeds[i];
                        if (car_speeds[i] > 0 && car_position[i][j].x > SCREEN_WIDTH - score_side) {
                            car_position[i][j].x = -car_position[i][j].width;
                        }
                        else if (car_speeds[i] < 0 && car_position[i][j].x < -car_position[i][j].width) {
                            car_position[i][j].x = SCREEN_WIDTH - score_side - car_position[i][j].width;
                        }
                    }
                }

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        log_position[i][j].x += log_speeds[i];
                        if (log_speeds[i] > 0 && log_position[i][j].x > SCREEN_WIDTH - score_side) {
                            log_position[i][j].x = -log_position[i][j].width;
                        }
                    }
                }

                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 3; j++) {
                        turtle_position[i][j].x += turtle_speeds[i];
                        if (turtle_position[i][j].x < -turtle_position[i][j].width) {
                            turtle_position[i][j].x = SCREEN_WIDTH - score_side;
                        }
                    }
                }

                // --- 3. DYNAMIC COLLISIONS AREA CHECKS ---
                Rectangle frog_area = { position.x + 4, position.y + 4, 52, 52 };
                int frog_row = (int)(position.y / cellHeight); 

                bool on_river = false;
                bool safe_on_object = false;
                float drift_speed = 0.0f;

                // Checking Water-Zone River elements 
                if (frog_row == 5 || frog_row == 2) {
                    on_river = true;
                    int i = (frog_row == 5) ? 0 : 1; 
                    for (int j = 0; j < 3; j++) {
                        if (CheckCollisionRecs(frog_area, turtle_position[i][j])) {
                            safe_on_object = true;
                            drift_speed = turtle_speeds[i];
                            break; 
                        }
                    }
                }
                else if (frog_row == 4 || frog_row == 3 || frog_row == 1) {
                    on_river = true;
                    int i = (frog_row == 4) ? 0 : ((frog_row == 3) ? 1 : 2);
                    for (int j = 0; j < 3; j++) {
                        if (CheckCollisionRecs(frog_area, log_position[i][j])) {
                            safe_on_object = true;
                            drift_speed = log_speeds[i];
                            break;
                        }
                    }
                }

                // Process Water Row Outcomes
                if (on_river) {
                    if (safe_on_object) {
                        position.x += drift_speed;
                        // Dead boundary safety checks
                        if (position.x < 0 || position.x > SCREEN_WIDTH - score_side - LANE_SIZE) {
                            isBlasting = true;
                            blastPosition = (Vector2){ position.x + LANE_SIZE/2, position.y + LANE_SIZE/2 };
                            blastFrameCounter = 0;
                        //    PlaySound(drownSound);
                            
                            position.x = (float)((SCREEN_WIDTH - score_side) / 2 - LANE_SIZE / 2);
                            position.y = (float)(SCREEN_HEIGHT - LANE_SIZE);
                            --total_lives;
                        }
                    } else {
                        // Triggers Drown Action Events
                        isBlasting = true;
                        blastPosition = (Vector2){ position.x + LANE_SIZE/2, position.y + LANE_SIZE/2 };
                        blastFrameCounter = 0;
                      //  PlaySound(drownSound);

                        position.x = (float)((SCREEN_WIDTH - score_side) / 2 - LANE_SIZE / 2);
                        position.y = (float)(SCREEN_HEIGHT - LANE_SIZE);
                        --total_lives;
                    }
                }

                // Ground Road Vehicle Hit Collision Logic
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (CheckCollisionRecs(frog_area, car_position[i][j]) && position.y > 6 * LANE_SIZE && position.y < 12 * LANE_SIZE) {
                            isBlasting = true;
                            blastPosition = (Vector2){ position.x + LANE_SIZE/2, position.y + LANE_SIZE/2 };
                            blastFrameCounter = 0;
                         //   PlaySound(blastSound);

                            position.x = (float)((SCREEN_WIDTH - score_side) / 2 - LANE_SIZE / 2);
                            position.y = (float)(SCREEN_HEIGHT - LANE_SIZE);
                            --total_lives;
                        }
                    }
                }

                // --- 4. TOP SAFE HOUSES VICTORY LOGIC MAP ---
                                // --- 4. TOP SAFE HOUSES LOGIC INTERSECTIONS ---
                if (frog_row == 0) {
                    bool hit_house = false;
                    for (int i = 0; i < 4; i++) { 
                        if (CheckCollisionRecs(frog_area, safe_house[i])) {
                            hit_house = true;
                            
                            // 🎯 PRO TIP: Even if they hit an already filled house, we still advance them!
                            currentLevel++;
                            score += 200;
                            
                            // Clear out all safe houses so the next level starts completely clean
                            for (int k = 0; k < 4; k++) safeHouseFilled[k] = 0;
                            
                            // Check if they beat the final level
                            if (currentLevel > 5) {
                                currentState = STATE_VICTORY;
                            } else {
                                // ⚡ IMMEDIATE SPEED BOOST: Make obstacles notably faster for the new level
                                for (int s = 0; s < 5; s++) car_speeds[s] *= 1.35f;
                                for (int s = 0; s < 3; s++) log_speeds[s] *= 1.30f;
                                for (int s = 0; s < 2; s++) turtle_speeds[s] *= 1.30f;
                            }

                            // Instantly reset frog back to spawn area for the next level
                            position.x = (float)((SCREEN_WIDTH - score_side) / 2 - LANE_SIZE / 2);
                            position.y = (float)(SCREEN_HEIGHT - LANE_SIZE);
                            break;
                        }
                    }
                    
                    // Landed in a top wall slot (green bush) instead of a safe house open frame
                    if (!hit_house) {
                        isBlasting = true; 
                        blastPosition = (Vector2){ position.x + LANE_SIZE / 2.0f, position.y + LANE_SIZE / 2.0f };
                        blastFrameCounter = 0;

                        position.x = (float)((SCREEN_WIDTH - score_side) / 2 - LANE_SIZE / 2);
                        position.y = (float)(SCREEN_HEIGHT - LANE_SIZE);
                        
                        --total_lives; 
                    }
                   }
                    break; 
            
                 // This ends STATE_PLAYING

            case STATE_GAMEOVER:
                  break;
            case STATE_VICTORY:
                if (IsKeyPressed(KEY_ENTER)) {
                    currentState = STATE_MENU;
                    break;                
                }
       } 


        BeginDrawing();
            ClearBackground(BLACK);
        if (currentState == STATE_CREDITS) {
        DrawText("Roll: 2505059 ", SCREEN_WIDTH/2 - 220, SCREEN_HEIGHT/3, 45, GREEN);
        DrawText("NAME: G.M. TAHSIN AMIN",SCREEN_WIDTH/2 - 220, SCREEN_HEIGHT/3+50, 45, GREEN);
         
        DrawText("Roll: 2505039 ", SCREEN_WIDTH/2 - 220, SCREEN_HEIGHT/3+98, 45, BLUE);
        DrawText("NAME: ABIR HOSSAIN",SCREEN_WIDTH/2 - 220, SCREEN_HEIGHT/3+140, 45,BLUE);

        DrawText("PRESS [ENTER] TO START MISSION", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT - 120, 20, WHITE);
        }
           
        else if (currentState == STATE_MENU) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, DARKBLUE);
            DrawText("FROGGER ARCADE", SCREEN_WIDTH/2 - 220, SCREEN_HEIGHT/3, 45, GREEN);
            DrawText("PRESS [ENTER] TO START MISSION", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2, 20, WHITE);
            DrawText("PRESS [SPACE] TO SEE CREDITS", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2+200, 20, WHITE);
            
        }


        else if (currentState == STATE_PLAYING) {
            // Draw background layout elements
            DrawTexturePro(bg_image, bg_src, bg_position, origin, 0, WHITE);

            // Draw locked goal units onto safe houses maps
            for (int i = 0; i < 5; i++) {
                if (safeHouseFilled[i] == 1) {
                    DrawTexturePro(endfrog, srcEndFrog, safe_house[i], origin, 0, WHITE);
                }
            }

            // Draw world actors
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    DrawTexturePro(log[i], srcImglog[i], log_position[i][j], origin, 0, WHITE);
                }
            }
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 3; j++) {
                    DrawTexturePro(turtles[i], srcImgturtles[i], turtle_position[i][j], origin, 0, WHITE);
                }
            }
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 3; j++) {
                    DrawTexturePro(car[i], srcImgcar[i], car_position[i][j], origin, 0, WHITE);
                }
            }

            // Draw player frog model bounds
            Rectangle frog_draw_rect = { position.x - 4, position.y - 2, 52, 52 };
            DrawTexturePro(frog[1], srcImgFrog[1], frog_draw_rect, origin, 0.0f, WHITE);

            // Handle death blast visual animations over layouts
            if (isBlasting) {
              blastFrameCounter++;
    
                // Slow down expansion speed so it doesn't get too massive over 60 frames
               float radius = (float)blastFrameCounter * 1.0f; 
    
                 // Calculate fading smoothly relative to the new 60-frame maximum duration
                Color blastColor = (Color){ 255, 80, 0, (unsigned char)(255 * (1.0f - (float)blastFrameCounter / BLAST_DURATION)) };
    
                DrawCircleLines(blastPosition.x, blastPosition.y, radius, blastColor);
                DrawCircle(blastPosition.x, blastPosition.y, radius * 0.4f, YELLOW);
    
                 if (blastFrameCounter >= BLAST_DURATION) isBlasting = false;
                }

            // --- 5. RENDER MENU BAR & DASHBOARD SIDEBAR PANEL ---
            DrawRectangle(SCREEN_WIDTH - score_side, 0, score_side, SCREEN_HEIGHT, DARKGRAY);
            DrawLine(SCREEN_WIDTH - score_side, 0, SCREEN_WIDTH - score_side, SCREEN_HEIGHT, WHITE);
            
            DrawText("DASHBOARD", SCREEN_WIDTH - score_side + 35, 40, 22, GREEN);
            DrawText(TextFormat("SCORE\n%05d", score), SCREEN_WIDTH - score_side + 20, 120, 20, WHITE);
            DrawText(TextFormat("LEVEL\n%d / 5", currentLevel), SCREEN_WIDTH - score_side + 20, 220, 20, GOLD);
            DrawText("REMAINING LIVES:", SCREEN_WIDTH - score_side + 20, 480, 16, RED);

            // Draw visual image status representing lives count left safely
            if (total_lives >= 1 && total_lives <= 5) {
                DrawTexturePro(lives[total_lives - 1], srcImglives[total_lives - 1], lives_position, origin, 0, WHITE);
            }
        }
        else if (currentState == STATE_GAMEOVER) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            DrawText("GAME OVER", SCREEN_WIDTH/2 - 130, SCREEN_HEIGHT/2 -130, 45, RED);
           // DrawText("PRESS [ENTER] TO RETURN TO MENU", SCREEN_WIDTH/2 - 180, SCREEN_HEIGHT/2 + 30, 18, WHITE);
           DrawText(TextFormat("SCORE\n%05d",score),SCREEN_WIDTH/2 - 130, SCREEN_HEIGHT/2 - 40, 45, WHITE);
        }
        else if (currentState == STATE_VICTORY) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            DrawText("VICTORY CONQUERED!", SCREEN_WIDTH/2 - 220, SCREEN_HEIGHT/2 - 40, 40, GOLD);
            DrawText("YOU BEAT ALL 5 LEVELS!", SCREEN_WIDTH/2 - 130, SCREEN_HEIGHT/2 + 20, 20, GREEN);
           // DrawText("PRESS [ENTER] TO RELOAD MENU", SCREEN_WIDTH/2 - 160, SCREEN_HEIGHT/2 + 70, 18, WHITE);
            
        }


        EndDrawing();
    }
    //UnloadSound(jumpSound);
    //UnloadSound(drownSound);
    //UnloadSound(blastSound);
   // CloseAudioDevice();

    UnloadTexture(bg_image);
    UnloadTexture(fly);
    UnloadTexture(endfrog);
    
    for (int i = 0; i < 2; i++) {
        UnloadTexture(frog[i]);
        UnloadTexture(turtles[i]);
    }
    for (int i = 0; i < 3; i++) {
        UnloadTexture(log[i]);
        UnloadTexture(shells[i]);
    }
    for (int i = 0; i < 5; i++) {
        UnloadTexture(car[i]);
        UnloadTexture(lives[i]);
    }

    CloseWindow();
    return 0;
}


