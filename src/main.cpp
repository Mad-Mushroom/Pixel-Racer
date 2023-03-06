#include "main.h"

bool alive;

void init(){
	alive = true;
	InitWindow(800, 600, "PixelRacer");
	clearScreen();
}

void GameLoop(){
	drawRoad();
}

int main(int argc, char* argv[]){
	init();

	while(!WindowShouldClose() && alive){
		GameLoop();
	}
	return 0;
}
