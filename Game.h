#pragma once
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>
#include <utility>
//最大宽度定义
#define MAXWIDTH 30
//最大高度定义
#define MAXHEIGHT MAXWIDTH



//程序中用到的各种字符，以及它们的颜色和类型（以数字表示）
typedef struct
{
	const char * ch;
	int color;
	char type;
}OBJ;

//用一个结构体数组保存地图中的各个点
typedef struct
{
	char type;
	int index;
}COORD_GLOBLE_MAP;

//贪吃蛇有效活动范围地图的索引
typedef struct
{
	int x;
	int y;
}COORD_SNAKE_MAP;

const OBJ charBorder = { "□", 4, 1 };  //边框
const OBJ charBg = { "■", 2, 2 };  //背景
const OBJ charSnake = { "●", 0xe, 3 };  //贪吃蛇节点
const OBJ charFood = { "★", 0xc, 4 };  //食物

const int snakeMapLen = (MAXWIDTH - 2)*(MAXHEIGHT - 2);


class Game
{

public:
	static void init();
	static void setColor(int color);
	static void setPosition(int x, int y);
	static char pause();
	static void info();
	static void setHearderIndex(int i) { headerIndex = i; }
	static void setTailIndex(int i) { tailIndex = i; }
	static int getHearderIndex(void) { return headerIndex; }
	static int getTailIndex(void) { return tailIndex; }

	//返回地图中心点坐标
	static std::pair<int, int> getCenter()
	{
		return std::make_pair(xCenter, yCenter);
	}
	//GlobleMap的设置接口

	static void setGlbMapType(int x, int y, int type = 0)
	{
		globalMap[x][y].type = type;
	}

	static void setGlbMapIndex(int x, int y, int index = 0)
	{
		globalMap[x][y].index = index;
	}

	//返回指定的Globalmap
	static std::pair<int, char> getGlbMap(int x, int y)
	{
		return std::make_pair(globalMap[x][y].index, globalMap[x][y].type);
	}


	//SnakeMap的设置接口
	static void setSnakeMap(int index, int x, int y)
	{
		snakeMap[index].x = x;
		snakeMap[index].y = y;
	}

	//返回指定的Snakemap
	static std::pair<int, int> getSnakeMap(int index)
	{
		return std::make_pair(snakeMap[index].x, snakeMap[index].y);
	}

	//返回首尾
	static std::pair<int, int>getHearderTail()
	{
		return std::make_pair(headerIndex, tailIndex);
	}

	static std::pair<int, int> get_scoresPosition()
	{
		return std::make_pair(scoresPosition.x, scoresPosition.y);
	}

	static int getScore() { return score; }
	static int addScore() 
	{
		score++; return score;
	}
private:
	static HANDLE hStdin;//控制台句柄
	static int score;//得分

	//地图中心点坐标
	static int xCenter;
	static int yCenter;

	//蛇头蛇尾对应的snakeMap中的索引（下标）
	static int headerIndex;
	static int tailIndex;

	//贪吃蛇的活动区域是一维数组
	static COORD_SNAKE_MAP snakeMap[(MAXWIDTH - 2)*(MAXHEIGHT - 2)];
	static COORD_SNAKE_MAP scoresPosition;
	//整个地图是二维数组的
	//地图的垂直为x轴,水平是y轴
	static COORD_GLOBLE_MAP globalMap[MAXWIDTH][MAXHEIGHT];
};

