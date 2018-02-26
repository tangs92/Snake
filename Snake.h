#pragma once

#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

//贪吃蛇初始长度
#define INITLEN 3 


class Snake
{
	
public:
	 void init();
	 void createFood();
	 void die();
	 void move(char direction);
	 char nextDirection(char ch, char directionOld);

};

