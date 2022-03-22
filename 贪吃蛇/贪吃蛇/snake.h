#pragma once
#include <stdio.h>
#include "wall.h"
struct BODY {
	int X;
	int Y;
};
struct SNAKE
{
	struct BODY body[(WIDTH - 2)*(HEIGHT - 2)];//蛇身体的一维数组
	int size;
}snake;
void initSnake();
int offset_x;
int offset_y;

int tile_x;
int tile_y;

int IsRool;