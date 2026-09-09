#include <iostream>
#include <vector>
#include "raylib.h"


struct Bullet{  //Keeps track of the bullets x and y coordiante 
    int x;
    int y;
};

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
    Texture2D enemyimage = LoadTexture("enemy1.png");
    
    void updateframe(){
        if(moveBacknForth){ //If moveBacknForth is true, this tells the enemy how to do that 
            if(right){ //Moves the enemy to the right
                x+=2;
                bottomx +=2;
                y += 2;
                bottomy +=2;
                moveValue++;
            if(moveValue == 40){
                right = false;}
           } 
           else { //Moves the enemy to the left
                x-=2;
                bottomx -=2;
                y += 2;
                bottomy +=2; 
                moveValue--;
                if(moveValue == 0){
                    right = true;
                }
                
           }

        } else{ //Basic Enemy goes straight down
            y += 2;
            bottomy +=2;
        }
        
    }
};
struct ExplodingEnemy{ //Holds the x and y position of where an enemy was killed, so we 
                        // know where to put the explosion
    int x;
    int y;
    int opaqueness = 128;
    
    void updateframe(){
        opaqueness -= 5;
    }
};






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
	int backgroundY2 = -900;
    
    int speed = 5;
    

    InitWindow(screenWidth, screenHeight, "Galaca Game - Singplayer");
    Image icon = LoadImage("user.png");
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
    Texture2D explosion = LoadTexture("Graphics/explosion.png");
    Texture2D ThreeLivesImage = LoadTexture("Graphics/HealthBar-3.png");
    Texture2D TwoLivesImage = LoadTexture("Graphics/HealthBar-2.png");
    Texture2D OneLivesImage = LoadTexture("Graphics/HealthBar-1.png");
    Texture2D ZeroLivesImage = LoadTexture("Graphics/HealthBar-0.png");
    
    //Logo Processing
    Texture2D logoimage = LoadTexture("Graphics/logo1.png");
    int logox = -123;
    int logoy = 75;
    float logoOp = 255;
    
    std::vector<Bullet> firingbullets; //This vector holds all active bullets on the screenHeight
    
    // This holds enemy positions for the first wave
    std::vector<BasicEnemy> level1;
    std::vector<ExplodingEnemy> currentlyExploding;
    
    
    
    
    //LEVEL 1 ENEMY LAYOUT
    int enemypos = 100;
    for(int i = 0; i < 6; i++){
        BasicEnemy enemy;
        enemy.x = enemypos;
        enemy.y = -250;
        enemy.bottomx = enemy.x+50;
        enemy.bottomy = enemy.y+50;
        
        enemy.moveBacknForth = true;
        
        level1.push_back(enemy);
        enemypos+=75;
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
        if (IsKeyDown(KEY_A)) {// This code runs only once each frame, when a button is pressed 
            if (userpositionx != 0){// Sets the border ie. cannot go too far left
            userpositionx-= speed;
            currentusersprite = userspriteleft;
            }
            
        } else if (IsKeyDown(KEY_D)){// Sets the border ie. cannot go too far right
            if (userpositionx != 530){
            userpositionx+= speed;
            currentusersprite = userspriteright;
            }
        } else if (IsKeyDown(KEY_W)) {
            if (userpositiony != 200){
                userpositiony -= speed;
                currentusersprite = usersprite;
            }
        } else if (IsKeyDown(KEY_S)){
            if (userpositiony != 865){
                userpositiony += speed;
                currentusersprite = usersprite;
            }
        } else {
            currentusersprite = usersprite;
        }
        

        //SHOOTING
        if (IsMouseButtonPressed(0)){
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
		backgroundY2 += 10; // Moves the background down
        backgroundY1 += 10;  // Move first background down
        
        if (backgroundY1 >= 900) {
			backgroundY1 = backgroundY2 - 900;
		}
		if (backgroundY2 >= 900) {
			backgroundY2 = backgroundY1 - 900;
		}
        
        
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            DrawTexture(background, 0, backgroundY1, WHITE);
			DrawTexture(background, 0, backgroundY2, WHITE);
            
            DrawTexture(currentusersprite, userpositionx, userpositiony, WHITE);//Draws users position
            

            
            //loop that draws all enemies in level1
            for(int i = (int)level1.size() - 1; i >= 0; i--){
                
                bool hit = false;
                for(int j = (int)firingbullets.size() - 1; j >= 0; j--){
                    
                    if(firingbullets[j].x > level1[i].x && firingbullets[j].x < level1[i].bottomx && firingbullets[j].y < level1[i].bottomy && firingbullets[j].y > level1[i].y){
                        
                        //This is where the collision happens
                        ExplodingEnemy exploding;
                        exploding.x = level1[i].x;
                        exploding.y = level1[i].y;
                        
                        currentlyExploding.push_back(exploding);
                        
                        hit = true;
                        firingbullets.erase(firingbullets.begin() + j);
                        break;
                        
                    }
                    
                }
              
                if(!hit) {  // Only draw and update if NOT hit
                    DrawTexture(level1[i].enemyimage, level1[i].x, level1[i].y, WHITE);
                    level1[i].updateframe();
                    
                    if(level1[i].bottomy > 895){
                        userLives--;
                        level1.erase(level1.begin() + i);
                    }
                    
                    
                } else {
                    // Draw explosion here if you want
                    level1.erase(level1.begin() + i);
                }
                    
                
            }
            
            //loop that draws all bullets
            for(size_t i = 0; i < firingbullets.size(); i++){
                
                if (firingbullets[i].y < 5){ //If the bullet goes out of bounds, offload it
                    firingbullets.erase(firingbullets.begin() + i);
                }
                
                firingbullets[i].y -= 8;
                DrawTexture(bulletimage, firingbullets[i].x, firingbullets[i].y, WHITE);   
            }
            
            for(size_t i = 0; i < currentlyExploding.size(); i++){
                if(currentlyExploding[i].opaqueness <= 10){
                    currentlyExploding.erase(currentlyExploding.begin() + (int)i);
                }                    
                DrawTexture(explosion,currentlyExploding[i].x, currentlyExploding[i].y, (Color){255, 255, 255, (unsigned char)currentlyExploding[i].opaqueness});
                currentlyExploding[i].updateframe();
                
                
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