#include <stdio.h>
#include <stdlib.h>
#define size 20

char map[size * size];

void createMap()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			map[x * size + y] = rand() % 10;
		}
	}
}

void printResult()
{
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (map[x * size + y] == -1)
				printf("#");
			else if (map[x * size + y])
				printf(".");
			else
				printf("X");
		}
		printf("\n");
	}
}

int controlX(int x1, int y1, int x2, int y2)
{
	int result = 1;
	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			if (map[x * size + y] == 0)
			{
				result = 0;
			}
		}
	}
	return result;
}

void paint(int x1, int y1, int x2, int y2)
{
	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			map[x * size + y] = -1;
		}
	}
}

void find()
{
	int max = 0;
	int rX1, rY1, rX2, rY2;
	for (int x2 = size - 1; x2 >= 0; x2--)
	{
		for (int y2 = size - 1; y2 >= 0; y2--)
		{
			for (int x1 = 0; x1 <= x2; x1++)
			{
				for (int y1 = 0; y1 <= y2; y1++)
				{
					int area = (x2 - x1) * (y2 - y1);
					if (max < area && controlX(x1, y1, x2, y2))
					{
						max = area;
						rX1 = x1;
						rY1 = y1;
						rX2 = x2;
						rY2 = y2;
					}
				}
			}
		}
	}

	paint(rX1, rY1, rX2, rY2);
}

int main(int argc, char *argv[])
{
	createMap();
	printResult();
	printf("\n");
	find();
	printResult();
	return 0;
}
