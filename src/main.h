#pragma once

#include "raylib.h"
#include <iostream>
#include <fstream>

extern bool alive;

/* main */
void init();
void GameLoop();

/* graphics */
void clearScreen();
void drawRoad();
