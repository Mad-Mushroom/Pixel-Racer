#include "main.h"

void clearScreen(){
	BeginDrawing();
		ClearBackground(BLACK);
	EndDrawing();
}

void drawRoad(){
	BeginDrawing();
		DrawText("In development.", 1, 1, 20, WHITE);
	EndDrawing();
}
