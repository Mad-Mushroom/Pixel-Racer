#include "main.h"
#include <cstdlib>
#include <type_traits>

using namespace std;

/* Textures */
Texture2D RoadTexture;
Texture2D PlayerCar;
Texture2D RedCar;
Texture2D YellowCar;
Texture2D ArrowRightTexture;
Texture2D ArrowLeftTexture;
Texture2D GrassBackground;
Texture2D BlackBackground;
Texture2D Coin;
Texture2D RedPlayerCar;
Texture2D BluePlayerCar;

/* Variables */
// Game
int gameState = 0;
int score = 0;
int coins = 0;
// Player
int playerX = 400;
float playerSpeed = 0;
float playerMaxSpeed = 4;
// Roads
int Road1Pos = 0;
int Road2Pos = 320;
int Road3Pos = 640;
// Backgrounds
int bkg1Pos = 0;
int bkg2Pos = 600;
// Enemy Cars
int RedCarPosY = 400;
int RedCarPosX = 800/2-80;
int YellowCarPosY = 50;
int YellowCarPosX = 800/2+10;
// Coin
int coinPosX = 800/2-10;
int coinPosY = -100;

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

void SelectVehicle(){
	BeginDrawing();
		DrawTexture(BlackBackground, 0, 0, WHITE);
		
		DrawTexture(ArrowLeftTexture, 800/2-50, 210, WHITE);
		DrawTexture(ArrowRightTexture, 800/2+15, 210, WHITE);

		if(select == 1) DrawTexture(RedPlayerCar, 800/2-35, 200, WHITE);
		if(select == 2) DrawTexture(BluePlayerCar, 800/2-35, 200, WHITE);
	EndDrawing();

	if(IsKeyPressed(KEY_RIGHT) && select < 2) select++;
	if(IsKeyPressed(KEY_LEFT) && select > 1) select--;
}

void SelectMap(){

}

void ResetGame(){
	score = 0;
	playerX = 400;
	playerSpeed = 0;
	Road1Pos = 0;
	Road2Pos = 320;
	Road3Pos = 640;
	bkg1Pos = 0;
	bkg2Pos = 600;
	RedCarPosX = 800/2-80;
	RedCarPosY = 400;
	YellowCarPosX = 800/2+10;
	YellowCarPosY = 50;
	gameState = 2;
}

void GameOver(){
	BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Game Over!", 1, 1, 20, WHITE);
		DrawText("Score:", 1, 40, 20, WHITE);
		DrawText(to_string(score).c_str(), 1, 60, 20, WHITE);

		DrawText("Press Enter to play again.", 1, 200, 20, WHITE);
		DrawText("Press Backspace to go to the MainMenu", 1, 220, 20, WHITE);
	EndDrawing();
	if(IsKeyPressed(KEY_ENTER)) ResetGame();
	if(IsKeyPressed(KEY_BACKSPACE)) gameState = 1;
}

void MainGame(){
	/* Update Variables */
	Road1Pos += playerSpeed;
	Road2Pos += playerSpeed;
	Road3Pos += playerSpeed;
	if(Road1Pos >= 600) Road1Pos = 0-320;
	if(Road2Pos >= 600) Road2Pos = 0-320;
	if(Road3Pos >= 600) Road3Pos = 0-320;
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
	bkg1Pos += playerSpeed;
	bkg2Pos += playerSpeed;
	if(bkg1Pos >= 600) bkg1Pos = 0-600;
	if(bkg2Pos >= 600) bkg2Pos = 0-600;
	score += playerSpeed / 2;
	coinPosY += playerSpeed;
	if(coinPosY > 610){
		coinPosY = -100;
		coinPosX = GetRandomValue(310, 420);
	}


	/* Draw Stuff */
	BeginDrawing();
		DrawTexture(GrassBackground, 0, bkg1Pos, WHITE);
		DrawTexture(GrassBackground, 0, bkg2Pos, WHITE);
		DrawTexture(RoadTexture, 800/2-80, Road1Pos, WHITE);
		DrawTexture(RoadTexture, 800/2-80, Road2Pos, WHITE);
		DrawTexture(RoadTexture, 800/2-80, Road3Pos, WHITE);

		DrawTexture(Coin, coinPosX, coinPosY, WHITE);

		DrawTexture(RedCar, RedCarPosX, RedCarPosY, WHITE);
		DrawTexture(YellowCar, YellowCarPosX, YellowCarPosY, WHITE);

		DrawTexture(PlayerCar, playerX, 500, WHITE);

		DrawRectangle(600, 0, 200, 600, BLACK);
		DrawText("SCORE:", 600, 1, 40, WHITE);
		DrawText(to_string(score).c_str(), 600, 50, 30, WHITE);
		DrawText("COINS:", 600, 90, 40, WHITE);
		DrawText(to_string(coins).c_str(), 600, 140, 30, WHITE);
	EndDrawing();

	/* Input */
	if(IsKeyDown(KEY_RIGHT) && playerX < 425) playerX += 2;
	if(IsKeyDown(KEY_LEFT) && playerX > 305) playerX -= 2;
	if(IsKeyDown(KEY_UP) && playerSpeed <= playerMaxSpeed) playerSpeed += 1;
	if(IsKeyReleased(KEY_UP) && playerSpeed >= playerMaxSpeed) playerSpeed=0;

	/* Check Collision */
	if(RedCarPosY >= 455 && RedCarPosY <= 530 && playerX > RedCarPosX-35 && playerX < RedCarPosX+35) gameState = 3;
	if(YellowCarPosY >= 455 && YellowCarPosY <= 530 && playerX > YellowCarPosX-35 && playerX < YellowCarPosX+35) gameState = 3;
	if(coinPosY >= 455 && coinPosY <= 530 && playerX > coinPosX-32 && playerX < coinPosX+32){
		coinPosY = -150;
		coinPosX = GetRandomValue(310, 420);
		coins++;
	}
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
		DrawTexture(ArrowRightTexture, 360, ArrowPos, WHITE);
		DrawText("Pixel Racer", 200, 1, 50, WHITE);
		DrawText("Play", 400, 200, 20, WHITE);
		DrawText("Select Vehicle", 400, 220, 20, WHITE);
		DrawText("Select Map", 400, 240, 20, WHITE);
		DrawText("Quit", 400, 260, 20, WHITE);
	EndDrawing();

	if(IsKeyPressed(KEY_DOWN) && select <= 3) select++;
	if(IsKeyPressed(KEY_UP) && select >= 2) select--;
	if(IsKeyPressed(KEY_ENTER)){
		if(select == 1){ CleanScreen(); ResetGame(); }
		if(select == 2){ CleanScreen(); select=1; gameState=4; }
		if(select == 3){ CleanScreen(); select=1; gameState=5; }
		if(select == 4){ Exit(); }
	}
}

void init(){
	/* Load Textures */
	RoadTexture = LoadTexture("resource/img/RoadScale.png");
	PlayerCar = LoadTexture("resource/img/player/Car1.png");
	RedCar = LoadTexture("resource/img/enemy/CarRed.png");
	YellowCar = LoadTexture("resource/img/enemy/CarYellow.png");
	ArrowRightTexture = LoadTexture("resource/img/ArrowRight.png");
	ArrowLeftTexture = LoadTexture("resource/img/ArrowLeft.png");
	GrassBackground = LoadTexture("resource/img/background/grass.png");
	Coin = LoadTexture("resource/img/Coin.png");
	RedPlayerCar = LoadTexture("resource/img/player/Car1.png");
	BluePlayerCar = LoadTexture("resource/img/player/Car2.png");
	BlackBackground = LoadTexture("resource/img/background/black.png");

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
		if(gameState == 4) SelectVehicle();
		if(gameState == 5) SelectMap();
    	}

    	Exit();
    	return 0;
}
