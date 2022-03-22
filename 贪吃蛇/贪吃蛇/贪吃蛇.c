#include <stdio.h>
#include "wall.h"
#include <Windows.h>
#include "snake.h"
#include "food.h"

int score = 0;
int sleepTime = 300;
void gotoxy(int x, int y) {
	if (x == 0 && y == 0) {
		return;
	}
	COORD coord;
	coord.X = x;
	coord.Y = y;
	//设置控制台光标的位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void update() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

	for (int i = 0; i < snake.size; i++)
	{
		gotoxy(snake.body[i].X, snake.body[i].Y);//光标去到蛇的身体的位置
		if (i==0)
		{
			printf( "@");
		}
		else
		{
			printf ( "#");
		}
	}
	gotoxy(food.x,food.y);
	printf("x");
	gotoxy(tile_x, tile_y);
	printf(" ");

	if (IsRool) {
		gotoxy(snake.body[0].X, snake.body[0].Y);
		printf("@");
	}
	gotoxy(0, HEIGHT);
	printf("分数:%d", score);
}
void GameOver(int mode) {
	if (mode == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

		gotoxy(snake.body[0].X, snake.body[0].Y);
		printf("@");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	gotoxy(0, HEIGHT + 1);
	printf("GameOver!\n");
	system("pause");
	exit(1);
}
int main() {
	//去掉控制台光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);

	srand((unsigned int)time(NULL));

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

	initWall();
	initSnake();
	initFood();
	update();
	
	
	//方向
	char key = 'd';//默认向右
	char prekey = 'd';
	while (snake.body[0].X >= 1 && snake.body[0].X <= WIDTH - 2
		&& snake.body[0].Y>=1&&snake.body[0].Y<=HEIGHT-2) {
		//如果没有键盘输入返回0
		if (_kbhit()) {
			key = _getch();
		}
		//判断当前方向输入是否逆向
		if (key == 'a'&&prekey == 'd' || key == 'd'&&prekey == 'a' ||
			key == 'w'&&prekey == 's' || key == 's'&&prekey == 'w') 
		{
			key = prekey;
		}
		else
		{
			prekey = key;
		}

		switch (key)
		{
		case 'a':
			offset_x = -1;
			offset_y = 0;
			break;
		case 'w':
			offset_x = 0;
			offset_y = -1;
			break;
		case 's':
			offset_x = 0;
			offset_y = 1;
			break;
		case 'd':
			offset_x = 1;
			offset_y = 0;
			break;
		}
		//判断是否吃到食物
		if (snake.body[0].X == food.x&&snake.body[0].Y == food.y) {
			snake.size++;
			score += 100;
			sleepTime -= 10;
			initFood();
		}

	             
		for (int i = 1; i < snake.size; i++) {
			if (snake.body[0].X == snake.body[i].X&&snake.body[0].Y == snake.body[i].Y) {
				GameOver(1);
			}
		}
		tile_x = snake.body[snake.size - 1].X;
		tile_y = snake.body[snake.size - 1].Y;
		//身体移动
		for (int i = snake.size - 1; i > 0; i--) {
			snake.body[i] = snake.body[i - 1];
		}                                                        
		snake.body[0].X += offset_x;
		snake.body[0].Y += offset_y;
		if (snake.body[0].X == tile_x && snake.body[0].Y == tile_y) {
			IsRool = 1;
		}
		else
		{
			IsRool = 0;
		}
		update(sleepTime);
		Sleep(200);


	}
	GameOver(2);
	//getchar();
	//system("pause");
	return EXIT_SUCCESS;
}