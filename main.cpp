// Snake.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include "Game.h"
#include "Snake.h"

void play()
{
	char in, dir = 'a';

	Snake Snake;
	Game::init();
	Snake.init();
	Snake.createFood();
	Game::info();

	//读取键盘输入
	in = tolower(_getch());
	dir = Snake.nextDirection(in, dir);
	while (1)
	{
		if (_kbhit())//检查当前是否有键盘输入
		{
			//如果输入是空格,表示暂停
			in = tolower(_getch());
			if (in == ' ')
			{
				in = Game::pause();
			}
			if (in == 27)
			{
				exit(1);
			}
			dir=Snake.nextDirection(in, dir);//切换方向
		}
		Snake.move(dir);//移动
		Sleep(500);
	}


}
int main()
{
	//
	play();
	system("pause");
	return 0;
}

