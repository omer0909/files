/*
00 empty

01 a pion
02 a rook
03 a knight
04 a bishop
05 a queen
06 a king

07 b pion
08 b rook
09 b knight
10 b bishop
11 b queen
12 b king
*/

#include<stdio.h>

typedef struct s_pos{
	int x;
	int y;
} s_pos;

int table[8][8];
int way[8][8];

int charToInt(char* number){
	return (number[0] - 48) * 10 + (number[1] - 48);
}

void readTable()
{
	FILE *file;
	file= fopen("table.txt", "r");
	
	if(file!=NULL){

		for(int x = 0; x < 8; x++){
			for(int y = 0; y < 8; y++){

				char number [2];
				number[0] = fgetc(file);
				number[1] = fgetc(file);
				table[x][y] = charToInt(&number[0]);
				fgetc(file);
			}
		}
	}
	fclose(file);
}

void printTable()
{

	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			printf("%i ", table[x][y]);
		}
		printf("\n");
	}
}
void printWay()
{

	printf("\n");
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			printf("%i ", way[x][y]);
		}
		printf("\n");
	}
}

int controlOut(s_pos pos){
	return pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7;  
}

int controlDraw(s_pos pos)
{
	if(controlOut(pos))
		return 1;

	int stone =  table[pos.x][pos.y];
	if(stone > 0 && stone < 7)
		return 1;

	way[pos.x][pos.y] = 1;

	if(stone > 6)
		return 1;
	return 0;
}

int controlKing(s_pos queen)
{
	s_pos king;
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			if (table[x][y] == 6){
				king.x = x;
				king.y = y;
				x = 8;
				break;
			}
		}
	}

	int xDir = king.x - queen.x;
	int yDir = king.y - queen.y;

	if(!xDir){
		int add = ((yDir < 0) * 2) - 1;
		int y = queen.y;
		while (1){
			s_pos pos = {queen.x,y};
			if (controlOut(pos))
				break;
			int stone = table[queen.x][y];
			if(stone == 8 || stone == 11)
				return 1;
			
			if (stone != 0)
				break;

			y += add;
		}
	}
	
	if(!yDir){
		int add = ((xDir < 0) * 2) - 1;
		int x = queen.x;
		while (1){
			s_pos pos = {x,queen.y};
			if (controlOut(pos))
				break;
			int stone = table[x][queen.y];
			if(stone == 8 || stone == 11)
				return 1;

			if(stone != 0)
				break;

			x += add;
		}
	}

	if (xDir == yDir){
		int add = ((xDir < 0) * 2) - 1;
		s_pos pos = queen;
		while (1){
			
			if (controlOut(pos))
				break;

			int stone = table[pos.x][pos.y];
			if (stone == 10 || stone == 11)
				return 1;

			if (stone != 0)
				break;

			pos.x += add;
			pos.y += add;
		}
	}

	if (xDir == -yDir){
		int add = ((xDir < 0) * 2) - 1;
		s_pos pos = queen;
		while (1){
			
			if (controlOut(pos))
				break;

			int stone = table[pos.x][pos.y];
			if (stone == 10 || stone == 11)
				return 1;

			if (stone != 0)
				break;

			pos.x += add;
			pos.y -= add;
		}
	}

	return 0;
}

void drawWay(s_pos queen)
{
	for(int x = 0; x < 8; x++){
		for(int y = 0; y < 8; y++){
			way[x][y] = 0;
		}
	}
	
	if (controlKing(queen)){
		printf("check");
		return;
	}
	
	int index;

	for(int i = -1; i < 2; i += 2){

		index = 0;
		while(1){
			index += i;
			s_pos pos = {queen.x + index, queen.y};
			if(controlDraw(pos))
				break;
		}

		index = 0;
		while(1){
			index += i;
			s_pos pos = {queen.x, queen.y + index};
			if(controlDraw(pos))
				break;
		}

		index = 0;
		while(1){
			index += i;
			s_pos pos = {queen.x + index, queen.y + index};
			if(controlDraw(pos))
				break;
		}

		index = 0;
		while(1){
			index += i;
			s_pos pos = {queen.x + index, queen.y - index};
			if(controlDraw(pos))
				break;
		}
	}
}

int main(int argc, char *argv[])
{
	readTable();
	printTable();
	s_pos queen = {3, 5};
	drawWay(queen);
	printWay();
	return 0;
}

