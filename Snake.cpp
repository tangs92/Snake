#include "stdafx.h"
#include "Snake.h"

void Snake::init()
{

	auto xCenter = Game::getCenter().first;
	auto yCenter = Game::getCenter().second;

	//初始化贪吃蛇(三格作为贪吃蛇)
	Game::setGlbMapType(xCenter, yCenter - 1, charSnake.type);
	Game::setGlbMapType(xCenter, yCenter, charSnake.type);
	Game::setGlbMapType(xCenter, yCenter + 1, charSnake.type);

	//设置头部坐标
	Game::setHearderIndex((xCenter - 1)*(MAXWIDTH - 2) + (yCenter - 1) - 1);

	//设置尾部坐标
	auto tailIndex = Game::getHearderIndex() + 2;
	Game::setTailIndex(tailIndex);

	//移动光标位置
	Game::setPosition(xCenter, yCenter - 1);

	Game::setColor(charSnake.color);

	//输出蛇
	for (int y = yCenter - 1; y <= yCenter + 1; y++) {
		printf("%s", charSnake.ch);
	}

}

void Snake::createFood()
{
	int index, range, x, y;
	srand((unsigned)time(NULL));

	//返回头尾坐标
	auto headerIndex = Game::getHearderTail().first;
	auto tailIndex = Game::getHearderTail().second;


	if (tailIndex < headerIndex)
	{
		range = headerIndex - tailIndex + 1;
		index = rand() % range + tailIndex + 1;
	}
	else
	{
		//蛇的最大长度减去蛇的现在的长度,算出一个范围
		range = snakeMapLen - (tailIndex - headerIndex + 1);
		//随机算一个index
		index = rand() % range;
		//如果这个index比蛇头下标大,那么就加一个蛇身的长度
		if (index >= headerIndex) {
			index += (tailIndex - headerIndex + 1);
		}
	}

	auto snakeMap = Game::getSnakeMap(index);

	//返回食物对应在贪吃蛇地图上的坐标
	x = snakeMap.first;
	y = snakeMap.second;

	//移动光标到对应的坐标
	Game::setPosition(x, y);
	Game::setColor(charFood.color);
	printf("%s", charFood.ch);
	Game::setGlbMapType(x, y , charFood.type);

}

//死掉
void Snake::die()
{
	int xCenter = MAXHEIGHT % 2 == 0 ? MAXHEIGHT / 2 : MAXHEIGHT / 2 + 1;
	int yCenter = MAXWIDTH % 2 == 0 ? MAXWIDTH / 2 : MAXWIDTH / 2 + 1;

	//改光标的位置
	Game::setPosition(xCenter, yCenter - 5);
	Game::setColor(0xC);

	printf("You die! Game Over!");
	_getch();
	exit(0);
}

void Snake::move(char direction)
{
	int newHeaderX, newHeaderY;  //新蛇头在全局坐标系下的坐标
	int newHeaderPreIndex;  //新蛇头坐标以前在贪吃蛇坐标系下对应的索引

	int newHeaderPreX, newHeaderPreY;  //新蛇头的索引以前在全局坐标系下对应的坐标
	int newHeaderPreType;  //新蛇头以前的类型
	int oldTailX, oldTailY;  //老蛇尾在全局坐标系下的坐标

	//返回蛇头在贪吃蛇坐标系下的索引
	auto headerIndex = Game::getHearderIndex();

	//根据方向设置新蛇头的坐标
	switch (direction)
	{
		case 'w':
		{
			//上
			newHeaderX = Game::getSnakeMap(headerIndex).first - 1;
			newHeaderY = Game::getSnakeMap(headerIndex).second;
			break;
		}
		case 's':
		{
			//下
			newHeaderX = Game::getSnakeMap(headerIndex).first + 1;
			newHeaderY = Game::getSnakeMap(headerIndex).second;
			break;
		}
		case 'a':
		{
			//左
			newHeaderX = Game::getSnakeMap(headerIndex).first ;
			newHeaderY = Game::getSnakeMap(headerIndex).second-1;
			break;
		}
		case 'd':
		{
			//右
			newHeaderX = Game::getSnakeMap(headerIndex).first;
			newHeaderY = Game::getSnakeMap(headerIndex).second+1;
			break;
		}
	}

	//计算新蛇头的索引
	auto tmp = headerIndex == 0 ? snakeMapLen - 1 : headerIndex - 1;
	Game::setHearderIndex(tmp);
	//重新返回一次新的蛇头索引
	headerIndex = Game::getHearderIndex();

	//新蛇头坐标以前在全局坐标系上对应的索引
	newHeaderPreIndex = Game::getGlbMap(newHeaderX, newHeaderY).first;

	//新蛇头的索引在贪吃蛇坐标系上以前对应的坐标
	newHeaderPreX = Game::getSnakeMap(headerIndex).first;
	newHeaderPreY = Game::getSnakeMap(headerIndex).second;

	//双向绑定新蛇头索引(贪吃蛇坐标系)与全局坐标系的对应关系
	Game::setSnakeMap(headerIndex, newHeaderX, newHeaderY);
	Game::setGlbMapIndex(newHeaderPreX, newHeaderPreY, newHeaderPreIndex);

	//新蛇头以前的类型
	newHeaderPreType = Game::getGlbMap(newHeaderX, newHeaderY).second;
	//设置新蛇头类型
	Game::setGlbMapType(newHeaderX, newHeaderY,charSnake.type);

	// 判断是否出界或撞到自己
	if (newHeaderPreType == charBorder.type || newHeaderPreType == charSnake.type)
	{
		die();
	}
	//输出新蛇头
	Game::setPosition(newHeaderX, newHeaderY);
	Game::setColor(charSnake.color);
	printf("%s", charSnake.ch);

	//判断是不是吃到食物
	if (newHeaderPreType == charFood.type)
	{
		//是
		createFood();
		//更改分数
		Game::setPosition(Game::get_scoresPosition().first, Game::get_scoresPosition().second);
		printf("Score: %d", Game::addScore());
	}
	else
	{
		//老蛇尾坐标
		auto tailIndex = Game::getTailIndex();
		oldTailX = Game::getSnakeMap(tailIndex).first;
		oldTailY = Game::getSnakeMap(tailIndex).second;
		//删除蛇尾
		Game::setPosition(oldTailX, oldTailY);
		Game::setColor(charBg.color);
		printf("%s", charBg.ch);
		Game::setGlbMapType(oldTailX, oldTailY, charBg.type);

		//如果尾部索引是0的话,强行改成snakeMapLen - 1,否则就tailIndex-1
		Game::setTailIndex((tailIndex == 0) ? snakeMapLen - 1 : tailIndex - 1);

	}

}

char Snake::nextDirection(char ch, char directionOld)
{
	int sum = ch + directionOld;
	ch = tolower(ch);
	//如果是a方向,如果输入d,自然是保持原来的方向
	///如果是w方向,如果输入s,自然是保持原来的方向
	//197和234就是处理这两种情况
	if ((ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') && sum != 197 && sum != 234) {
		return ch;
	}
	else {
		return directionOld;
	}
}
