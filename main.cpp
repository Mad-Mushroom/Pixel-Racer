#include "main.h"

using namespace std;

/* Textures */
Texture2D RoadTexture;
Texture2D PlayerCar;
Texture2D RedCar;
Texture2D YellowCar;
Texture2D ArrowTexture;

/* Variables */
// Game
int gameState = 0;
// Player
int playerX = 400;
float playerSpeed = 0;
float playerMaxSpeed = 4;
// Roads
int Road1Pos = 1;
int Road2Pos = 320;
int Road3Pos = 640;
// Enemy Cars
int RedCarPosY = 400;
int RedCarPosX = 800/2-80;
int YellowCarPosY = 50;
int YellowCarPosX = 800/2+10;

int select = 1;

void CleanScreen(){
	BeginDrawing();
		ClearBackground(BLACK);
	EndDrawing();
}

void Exit(){
	CloseWindow();
	cout << "-----------" << endl;
	cout << "Goodbye! :)" << endl << endl;
	return;
}

void GameOver(){
	BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Game Over!", 1, 1, 20, WHITE);
	EndDrawing();
}

void MainGame(){
	/* Update Variables */
	Road1Pos += playerSpeed;
	Road2Pos += playerSpeed;
	Road3Pos += playerSpeed;
	if(Road1Pos > 600) Road1Pos = 0-320;
	if(Road2Pos > 600) Road2Pos = 0-320;
	if(Road3Pos > 600) Road3Pos = 0-320;
	RedCarPosY += 1 + playerSpeed;
	YellowCarPosY += 1 + playerSpeed;
	if(RedCarPosY > 610){
		RedCarPosY = -50;
		RedCarPosX = GetRandomValue(310, 420);
	}
	if(YellowCarPosY > 610){
		YellowCarPosY = -50;
		YellowCarPosX = GetRandomValue(310, 420);
	}


	/* Draw Stuff */
	BeginDrawing();
		DrawTexture(RoadTexture, 800/2-80, Road1Pos, WHITE);
		DrawTexture(RoadTexture, 800/2-80, Road2Pos, WHITE);
		DrawTexture(RoadTexture, 800/2-80, Road3Pos, WHITE);

		DrawTexture(RedCar, RedCarPosX, RedCarPosY, WHITE);
		DrawTexture(YellowCar, YellowCarPosX, YellowCarPosY, WHITE);

		DrawTexture(PlayerCar, playerX, 500, WHITE);
	EndDrawing();

	/* Input */
	if(IsKeyDown(KEY_RIGHT) && playerX < 425) playerX += 2;
	if(IsKeyDown(KEY_LEFT) && playerX > 305) playerX -= 2;
	if(IsKeyDown(KEY_UP) && playerSpeed <= playerMaxSpeed) playerSpeed = playerMaxSpeed;
	if(IsKeyReleased(KEY_UP) && playerSpeed >= playerMaxSpeed) playerSpeed = 0;

	/* Check Collision */
	if(RedCarPosY == 455 && playerX > RedCarPosX-35 && playerX < RedCarPosX+35) gameState = 3;
	if(YellowCarPosY == 455 && playerX > YellowCarPosX-35 && playerX < YellowCarPosX+35) gameState = 3;
}

void MainMenu(){
	if(gameState != 1){ CleanScreen(); return; }
	int ArrowPos;
	if(select == 1) ArrowPos = 200-5+20*0;
	if(select == 2) ArrowPos = 200-5+20*1;
	if(select == 3) ArrowPos = 200-5+20*2;
	if(select == 4) ArrowPos = 200-5+20*3;
	BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(ArrowTexture, 360, ArrowPos, WHITE);
		DrawText("Pixel Racer", 200, 1, 50, WHITE);
		DrawText("Play", 400, 200, 20, WHITE);
		DrawText("Select Vehicle", 400, 220, 20, WHITE);
		DrawText("Select Map", 400, 240, 20, WHITE);
		DrawText("Quit", 400, 260, 20, WHITE);
	EndDrawing();

	if(IsKeyPressed(KEY_DOWN) && select <= 3) select++;
	if(IsKeyPressed(KEY_UP) && select >= 2) select--;
	if(IsKeyPressed(KEY_ENTER)){
		if(select == 1){ CleanScreen(); gameState = 2; }
	}
}

void init(){
	/* Load Textures */
	RoadTexture = LoadTexture("resource/img/RoadScale.png");
	PlayerCar = LoadTexture("resource/img/player/Car1.png");
	RedCar = LoadTexture("resource/img/enemy/CarRed.png");
	YellowCar = LoadTexture("resource/img/enemy/CarYellow.png");
	ArrowTexture = LoadTexture("resource/img/Arrow.png");

	gameState++;
}

int main(void){
    	InitWindow(800, 600, "PixelRacer");
    	SetTargetFPS(60);

	BeginDrawing();
            	ClearBackground(BLACK);
	EndDrawing();

    	while (!WindowShouldClose()){
		if(gameState == 0) init();
		if(gameState == 1) MainMenu();
		if(gameState == 2) MainGame();
		if(gameState == 3) GameOver();
    	}

    	Exit();
    	return 0;
}
