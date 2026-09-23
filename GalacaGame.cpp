#include <iostream>
#include <vector>
#include "raylib.h"
using namespace std;




struct Bullet{  //Keeps track of the bullets x and y coordiante 
    int x;
    int y;
};

std::vector<Bullet> firingbullets(150);

struct HardEnemy{
    int x;
    int y;
};

struct BasicEnemy{ // Holds the top left and bottom right of the image, with a method 
                   // that tells the enemy how to move
    bool moveBacknForth;
    bool right = true;
    int moveValue = 0;
    int x;
    int y;
    int bottomx;
    int bottomy;
    bool isHit = false;
    Texture2D enemyimage = LoadTexture("Graphics/enemy1.png");
    Texture2D explosion = LoadTexture("Graphics/explosion.png");
    int opaqueness = 255;
    bool dead = false;
    
    void updateframe(){
        
        checkCollision(firingbullets);
        
        if(isHit && !dead){
            opaqueness-= 5;
                if(opaqueness < 5){
                    dead = true;
                }
            return;
        }
        
        
        if(moveBacknForth){ //If moveBacknForth is true, this tells the enemy how to do that 
            if(right){ //Moves the enemy to the right
                x+=2;
                bottomx +=2;
                y += 2;
                bottomy +=2;
                moveValue++;
                    if(moveValue == 40){
                        right = false;
                        }
            } else { //Moves the enemy to the left
                x-=2;
                bottomx -=2;
                y += 2;
                bottomy +=2; 
                moveValue--;
                    if(moveValue == 0){
                        right = true;
                    }  
           }

        } 
        else{ //Basic Enemy goes straight down
            y += 2;
            bottomy +=2;
        }
        
    }
    //This will make isHit true 
    void checkCollision(std::vector<Bullet>& firingbullets){
        for(size_t i = 0; i < firingbullets.size(); i++){
            
            
            if(firingbullets[i].x > x && firingbullets[i].x < bottomx && firingbullets[i].y < bottomy && firingbullets[i].y > y){
                isHit = true;
                enemyimage = explosion;
                firingbullets.erase(firingbullets.begin() + i);
                break;
        }   
        }
        
    }
    
    
};



//-------------------
// GLOBAL variables |
//-------------------













//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 600;
    const int screenHeight = 900;
    
    int userpositionx = 235;
    int userpositiony = 800;
    int userpositionbottomx = userpositionx + 76;
    int userpositionbottomy = userpositiony + 76; 
    
    int userLives = 3;
    
    int backgroundY1 = 0;
	int backgroundY2 = -4900;
    
    float speed = 3;
    

    InitWindow(screenWidth, screenHeight, "Galaca Game - Singplayer");
    Image icon = LoadImage("Graphics/user.png");
    SetWindowIcon(icon);
    UnloadImage(icon);
    
    
    
    
    
    //Load in all textures 
    Texture2D usersprite = LoadTexture("Graphics/user.png");
    Texture2D userspriteleft = LoadTexture("Graphics/userleft.png");
    Texture2D userspriteright = LoadTexture("Graphics/userright.png");
    Texture2D currentusersprite = usersprite;; //This gets changed during the code for the users tilt left and right
    Texture2D background = LoadTexture("Graphics/background.png");
    Texture2D bulletimage = LoadTexture("Graphics/bullet.png");
    Texture2D enemyimage = LoadTexture("Graphics/enemy1.png");
    Texture2D ThreeLivesImage = LoadTexture("Graphics/HealthBar-3.png");
    Texture2D TwoLivesImage = LoadTexture("Graphics/HealthBar-2.png");
    Texture2D OneLivesImage = LoadTexture("Graphics/HealthBar-1.png");
    Texture2D ZeroLivesImage = LoadTexture("Graphics/HealthBar-0.png");
    Texture2D explosion = LoadTexture("Graphics/explosion.png");
    
    //Logo Processing
    Texture2D logoimage = LoadTexture("Graphics/logo1.png");
    int logox = -123;
    int logoy = 75;
    float logoOp = 255;
    
    
    
    
    
    
    
    //LEVEL 1 ENEMY LAYOUT
    std::vector<BasicEnemy> level1; // This holds enemy positions for the first wave
    
    int enemypos = 100;
    
    for(int i = 0; i < 5; i++){
        BasicEnemy enemy;
        enemy.x = enemypos;
        enemy.y = -250;
        enemy.bottomx = enemy.x+50;
        enemy.bottomy = enemy.y+50;
        
        enemy.moveBacknForth = true;
        
        
        level1.push_back(enemy);
        enemypos+=75;
    }
    //Level 2 ENEMY LAYOUT
    std::vector<BasicEnemy> level2; // This holds enemy positions for the first wave
    enemypos = 50;
    int enemyY = -450;
    
    for(int i = 0; i < 24; i++){
        if (i == 8){
            enemypos = 50;
            enemyY = -500;
        } else if (i == 16){
            enemypos = 50;
            enemyY = -550;
        }
        
        BasicEnemy enemy;
        enemy.x = enemypos;
        enemy.y = enemyY;
        enemy.bottomx = enemy.x+50;
        enemy.bottomy = enemy.y+50;
        
        enemy.moveBacknForth = false;//Turn this true to make them shake
        
        level2.push_back(enemy);
        enemypos+=65;
    }
    
    //LEVEL 3 ENEMY LAYOUT
        std::vector<BasicEnemy> level3; // This holds enemy positions for the first wave
    enemypos = 50;
    enemyY = -450;
    
    for(int i = 0; i < 18; i++){
        if (i == 6){
            enemypos = 25;
            enemyY = -500;
        } else if (i == 12){
            enemypos = 75;
            enemyY = -550;
        }
        
        BasicEnemy enemy;
        enemy.x = enemypos;
        enemy.y = enemyY;
        enemy.bottomx = enemy.x+50;
        enemy.bottomy = enemy.y+50;
        
        enemy.moveBacknForth = true;//Turn this true to make them shake
        
        level3.push_back(enemy);
        enemypos+=65;
    }
      
    
    

    
    
    
    

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    

    // Main game loop
    
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Clears background first 
        ClearBackground(BLACK);
        
        //MOVEMENT
        bool moving = false;
        
        float dx = 0, dy = 0;
        if (IsKeyDown(KEY_A) && userpositionx >= 0) dx -= 1;
        if (IsKeyDown(KEY_D) && userpositionx <= 530) dx += 1;
        if (IsKeyDown(KEY_W) && userpositiony >= 200) dy -= 1;
        if (IsKeyDown(KEY_S) && userpositiony <= 865) dy += 1;

        if (dx != 0 && dy != 0) {
            dx *= 0.70710678f;
            dy *= 0.70710678f;
        }

        userpositionx += dx * speed;
        userpositiony += dy * speed;
        
        if (IsKeyDown(KEY_A)) {// This code runs only once each frame, when a button is pressed 
            if (userpositionx >= 0){// Sets the border ie. cannot go too far left
            userpositionx-= speed;
            currentusersprite = userspriteleft;
            moving = true;
            }
            
        } 
        if (IsKeyDown(KEY_D)){// Sets the border ie. cannot go too far right
            if (userpositionx <= 530){
            userpositionx+= speed;
            currentusersprite = userspriteright;
            moving = true;
            }
        }
        if (IsKeyDown(KEY_W)) {
            if (userpositiony >= 200){
                userpositiony -= speed;
                currentusersprite = usersprite;
                moving = true;
            }
        }
        if (IsKeyDown(KEY_S)){
            if (userpositiony <= 865){
                userpositiony += speed;
                currentusersprite = usersprite;
                moving = true;
            }
        } 
        if (!moving){
            currentusersprite = usersprite;
        }
        

        //SHOOTING
        if (IsKeyPressed(KEY_ENTER)){
            //When the mouse is pressed, create a new strcut with the bullet x and y being (35,17) from the users
            // then update the y axis by increasing by 8 everytime after
            
            
            Bullet newbullet;
            newbullet.x = userpositionx + 35;
            newbullet.y = userpositiony - 17;
            
            firingbullets.push_back(newbullet); //Adds the struct to a vector, that gets displayed later
            
            
        }
        
        
        //-----------------------------------------
        
        
        
        
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
		backgroundY2 += 17; // Moves the background down
        backgroundY1 += 17;  // Move first background down
        
        if (backgroundY1 >= 4900) {
			backgroundY1 = backgroundY2 - 4900;
		}
		if (backgroundY2 >= 4900) {
			backgroundY2 = backgroundY1 - 4900;
		}
        
        
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            DrawTexture(background, 0, backgroundY1, WHITE);
			DrawTexture(background, 0, backgroundY2, WHITE);
            
            DrawTexture(currentusersprite, userpositionx, userpositiony, WHITE);//Draws users position
            
            //The bool will tell which level to start drawing. 
            bool RunLevel2 = false;
            bool RunLevel3 = false;
            //loop that draws all enemies in level1
            int i = 0;
            while(i < level1.size() && level1.size() != 0){
                
                    level1[i].updateframe();
                    
                    DrawTexture(level1[i].enemyimage, level1[i].x, level1[i].y,(Color){255, 255, 255, (unsigned char)level1[i].opaqueness});
                    
                    
                    if(level1[i].bottomy > 895){
                        userLives--;
                        level1.erase(level1.begin() + i);
                    } else if(level1[i].dead){
                        level1.erase(level1.begin() + i);
                    }

                    //If you make a user collision with the enemy do it here
                    
                i++;
                if(i > level1.size()){
                    i = 0;
                }
                continue;
            }
            
            //Loop for level 2
            if(level1.size() == 0){
                int i = 0;
                //RunLevel2 = true;
                RunLevel2 = true;
                
            }
            
            while(RunLevel2 && i < level2.size() && level2.size() != 0){
                
                level2[i].updateframe();
                
                DrawTexture(level2[i].enemyimage,level2[i].x,level2[i].y,(Color) {255,255,255, (unsigned char)level2[i].opaqueness});
                
                if(level2[i].bottomy > 895){
                    userLives--;
                    level2.erase(level2.begin() + i);
                } else if(level2[i].dead){
                        level2.erase(level2.begin() + i);
                    }
                
                i++;
                if(i > level2.size()){
                    i = 0;
                }
                continue;
                
            }
            
            //Loop for level 3
            if(level2.size() == 0){
                int i = 0;
                RunLevel3 = true;
            }
            
            while(RunLevel3 && i < level3.size() && level3.size() != 0){
                
                level3[i].updateframe();
                
                DrawTexture(level3[i].enemyimage,level3[i].x,level3[i].y,(Color) {255,255,255, (unsigned char)level3[i].opaqueness});
                
                if(level3[i].bottomy > 895){
                    userLives--;
                    level3.erase(level3.begin() + i);
                } else if(level3[i].dead){
                        level3.erase(level3.begin() + i);
                    }
                
                i++;
                if(i > level3.size()){
                    i = 0;
                }
                continue;
                
            }
            
            
            //loop that draws all bullets
            for(size_t i = 0; i < firingbullets.size(); i++){
                
                if (firingbullets[i].y < 5){ //If the bullet goes out of bounds, offload it
                    firingbullets.erase(firingbullets.begin() + i);
                }
                
                firingbullets[i].y -= 8;
                DrawTexture(bulletimage, firingbullets[i].x, firingbullets[i].y, WHITE);   
            }
            

            
            
            
            
        if(userLives == 3){
            DrawTexture(ThreeLivesImage, 300,0,WHITE);
        } else if (userLives == 2){
            DrawTexture(TwoLivesImage, 300,0,WHITE);
        } else if (userLives == 1){
            DrawTexture(OneLivesImage, 300,0,WHITE);
        } else {
            DrawTexture(ZeroLivesImage, 300,0,WHITE);
            DrawRectangle(0, 0, 600, 900, (Color){255, 0, 0, 128});
        }
        
        if(logoOp > 1){
            DrawTexture(logoimage, logox,logoy,(Color){255, 255, 255, (unsigned char)logoOp});
            logoOp-=0.8;
            if (logoOp < 100){
                logoOp-=0.8;
            }
            
        }
        

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(usersprite);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}