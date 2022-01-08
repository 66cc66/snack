#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
#define SNAKE_NUM 500

struct snake
{
	int size;
	int dir;
	float speed;
	POINT coor[SNAKE_NUM];
}snake;

struct food
{
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;

enum
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
void Gameinit();
void Gamedraw();
void Move();
void Keycontrol();
void Eat();
void FOOD();

int main()
{
	Gameinit();
	//Gamedraw();
	while (1)
	{

		Gamedraw();
		Move();
		Keycontrol();
		Eat();
		Sleep(35);
	}
	system("pause");
	return 0;
}

void Gameinit()
{
	mciSendString("open ./image/music.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
	//初始化窗口
	initgraph(640, 480);
	snake.size = 3;
	snake.speed = 5;
	snake.dir;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 20 - 10 * i;//与起始位置有关
		snake.coor[i].y = 9;
	}
	FOOD();
}

void Gamedraw()
{
	//双缓冲绘图
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(28, 115, 119));
	// 用背景色清空屏幕
	cleardevice();
	//绘制蛇
	setfillcolor(RED);
	for (int i = 0; i < snake.size; i++)
		fillcircle(snake.coor[i].x, snake.coor[i].y, 6);
	//绘制食物
	if (food.flag)
	{
		setfillcolor(GREEN);
		fillcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}

void Move()
{
	for (int i = snake.size - 1; i > 0; i--)// 关键是不能而不是关注循环
		snake.coor[i] = snake.coor[i - 1];

	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y + 6 <= 0)
			snake.coor[0].y = 480;
		break;
	case DOWN:
		snake.coor[0].y += snake.speed;
		if (snake.coor[0].y - 6 >= 480)
			snake.coor[0].y = 0;
		break;
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x + 6 <= 0)
			snake.coor[0].x = 640;
		break;
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x - 6 >= 640)
			snake.coor[0].x = 0;
		break;
	}


}
//通过按键改变方向
void Keycontrol()
{
	//判断是否有按键,有就返回真
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
			if (DOWN != snake.dir)
				snake.dir = UP;
			break;
		case 's':
		case 'S':
			if (UP != snake.dir)
				snake.dir = DOWN;
			break;
		case 'a':
		case 'A':
			if (RIGHT != snake.dir)
				snake.dir = LEFT;
			break;
		case 'd':
		case 'D':
			if (LEFT != snake.dir)
				snake.dir = RIGHT;
			break;
		case ' ':
			while (1)
			{
				if (_getch() == ' ')
					return;
			}
			break;
		}
	}
}

void Eat()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].y >= food.y - food.r && snake.coor[0].x <= food.x + food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)
	{
		FOOD();
	}
}

void FOOD()
{
	//获取系统开机到现在的毫秒数
	srand(GetTickCount());
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
	int sorce = 0;
	sorce += 10;//每个食物得10分
	snake.speed += 0.2;
}

