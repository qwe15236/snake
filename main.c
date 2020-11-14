// snake.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>

#define N 100//蛇的最大长度
#define SIZE 10

enum Ch{ up = 72,down = 80,left = 75,rigth = 77};

struct Coor
{
	int x;
	int y;
};

struct Snake
{
	int n;   //长度
	Ch ch;   //坐标
	struct Coor szb[N]; //方向
};

struct Food
{
	struct Coor fzb;//坐标
	int iseat;//标记 食物是否被吃掉
};

struct Food food;//食物
struct Snake snake; //snake 一条蛇

//初始化
void GameInit()
{
	//初始化窗口 640 * 480   SHOWCONSOLE 显示控制台
	initgraph(640, 480);
	srand((unsigned int)time(NULL));

	snake.n = 3;
	snake.ch = rigth;
	snake.szb[0].x = 100;
	snake.szb[0].y = 100;
	snake.szb[1].x = 90;
	snake.szb[1].y = 100;
	snake.szb[2].x = 80;
	snake.szb[2].y = 100;

	food.iseat = true;
}

void CreateFood()
{
	while (1)
	{
		int flag;
		flag = 0;
		food.fzb.x = rand() % 64 * 10;//窗口的最宽 32 * 10 = 320
		food.fzb.y = rand() % 48 * 10;//窗口的最高

		for (int i = 0; i < snake.n; i++)
		{
			if (snake.szb[i].x == food.fzb.x &&
				snake.szb[i].y == food.fzb.y)
			{
				flag = 1;
				break;
			}
		}
		if (flag)
			continue;
		else
		{
			food.iseat = false;
			break;
		}
	}
}


void DrawSnake() //画蛇
{
	/*system("cls");*/
	cleardevice();
	/*printf("蛇的当前节数：%d\n", snake.n);
	printf("蛇的当前方向：%d\n", snake.ch);*/

	for (int i = 0;i < snake.n;i++)
	{
		/*printf("第%d节蛇的坐标x = %d,y = %d\n"
			, i, snake.szb[i].x, snake.szb[i].y);*/
		setfillcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
		fillrectangle(snake.szb[i].x, snake.szb[i].y
			, snake.szb[i].x + SIZE, snake.szb[i].y + SIZE);
	}
	fillrectangle(food.fzb.x, food.fzb.y
		, food.fzb.x + SIZE, food.fzb.y + SIZE);
}

//蛇的移动
void SnakMove()
{
	for (int i = snake.n - 1;i > 0;i--)
	{
		snake.szb[i].x = snake.szb[i - 1].x;
		snake.szb[i].y = snake.szb[i - 1].y;
	}

	switch (snake.ch)
	{
	case up:snake.szb[0].y -= SIZE;break;
	case down:snake.szb[0].y += SIZE;break;
	case left:snake.szb[0].x -= SIZE;break;
	case rigth:snake.szb[0].x += SIZE;break;
	}
}

//控制方向
void ChangeCh()
{
	char key;
	key = _getch();//检测输入
	switch (key)
	{
	case up:
		if (snake.ch != down)
			snake.ch = up;
		break;
	case down:
		if (snake.ch != up)
			snake.ch = down;
		break;
	case left:
		if (snake.ch != rigth)
			snake.ch = left;
		break;
	case rigth:
		if (snake.ch != rigth)
			snake.ch = rigth;
		break;
	}
}

void EatFood()
{
	if (snake.szb[0].x == food.fzb.x &&
		snake.szb[0].y == food.fzb.y)
	{
		snake.n++;
		food.iseat = true;
	}
}

int main()
{
	GameInit();
	while (1)
	{
		while (!_kbhit())
		{
			if (food.iseat == true)
				CreateFood();
			DrawSnake();
			SnakMove();
			EatFood();
			Sleep(100);
		}
		ChangeCh();
	}


	return 0;
}
