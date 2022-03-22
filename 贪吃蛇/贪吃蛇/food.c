#include "food.h"

void initFood()
{
	int flag = 0;
	while (1)
	{
		food.x = rand() % (WIDTH - 2) + 1;
		food.y = rand() % (HEIGHT - 2) + 1;
		for (int i = 0; i < snake.size; i++) {
			if (food.x == snake.body[i].X&&food.y == snake.body[i].Y) {
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			break;
		}

	}
	
}


