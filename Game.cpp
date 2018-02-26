#include "stdafx.h"
#include "Game.h"

HANDLE Game::hStdin;
int Game::score = 0;
COORD_SNAKE_MAP Game::snakeMap[(MAXWIDTH - 2)*(MAXHEIGHT - 2)];
COORD_SNAKE_MAP Game::scoresPosition;
COORD_GLOBLE_MAP Game::globalMap[MAXWIDTH][MAXHEIGHT];

int Game::tailIndex;
int Game::headerIndex;

int Game::xCenter = MAXHEIGHT % 2 == 0 ? MAXHEIGHT / 2 : MAXHEIGHT / 2 + 1;
int Game::yCenter = MAXWIDTH % 2 == 0 ? MAXWIDTH / 2 : MAXWIDTH / 2 + 1;

void Game::init()
{
	int x, y,  index;

	CONSOLE_CURSOR_INFO cci;//控制台光标信息

	if (MAXWIDTH < 16)
	{
		printf("'MAXWIDTH' is too small!");
		_getch();
		exit(0);
	}

	//设置窗口大小 
	system("mode con: cols=96 lines=32");

	//隐藏光标
	hStdin = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hStdin, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(hStdin, &cci);

	for (x = 0; x < MAXHEIGHT; x++)
	{
		for (y = 0; y < MAXWIDTH; y++)
		{
			//处理外框
			if (y == 0 || y == MAXWIDTH - 1 || x == 0 || x == MAXHEIGHT - 1)
			{
				globalMap[x][y].type = charBorder.type;
				setColor(charBorder.color);

				printf("%s", charBorder.ch);
			}
			else
			{
				//处理贪吃蛇运动的地图区域
				index = (x - 1)*(MAXWIDTH - 2) + (y - 1);
				snakeMap[index].x = x;
				snakeMap[index].y = y;
				globalMap[x][y].type = charBg.type;
				globalMap[x][y].index = index;

				setColor(charBg.color);
				printf("%s", charBg.ch);
			}
		}
		printf("\n");
	}

}

void Game::setColor(int color)
{
	SetConsoleTextAttribute(hStdin, color);
}

void Game::setPosition(int x, int y)
{
	//坐标系是垂直是x轴,水平是y轴
	COORD coord;
	coord.X = 2 * y;//这里乘以2的原因是输出的字符是宽字符,需要占用两个位置
	coord.Y = x;
	SetConsoleCursorPosition(hStdin, coord);
}

char Game::pause()
{
	return _getch();
}

void Game::info()
{
	//设置程序信息
	setPosition(xCenter, MAXWIDTH + 2);
	printf("Author: Tang Shi");
	scoresPosition.x = xCenter - 1;
	scoresPosition.y = MAXWIDTH +2;
}
