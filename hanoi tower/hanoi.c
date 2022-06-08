#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define R 40 //window size
#define C 201
#define PLATES 5
#define TOWERS 3
#define LEVELS 5
#define PL_WID_1 7//bigger value = narrower plate;
#define PL_WID_2 10
#define PL_WID_3 16 
#define PL_WID_4 30
#define PL_WID_5 100
/*CHANGE MAKING :
1. adding a plate -
	- add an extra "case" under the "switch" in "plate(int, int, int)".
	- increase " #define LEVELS" and "#define PLATES" by 1*/
int i, j;
char mat[R][C];
int tow_mat[LEVELS][TOWERS] = { 0 };


int start();
void Game();
void window(char mat[R][C]);
void towers(char mat[][C]);
void print_window(char mat[][C]);
void plate(int num, int tower, int tower_level);
void plates_deafault(int tow_mat[][TOWERS]); //initializing plates to tower A
int op(int num, int tower, int tow_mat[][TOWERS]);
int op_scan(int* num, int* tower);
int win(); //winning indicator

void main()
{
	start();
	Game();
}
int start()
{
	printf("Hello and welcome to Hanoi!\n");
	printf("We would like to hospitile you in our temple but first, you must past THE TEST!\n\n");
	printf("To gain the right to visit the holy temple, \nyou need to transfer all the plates from tower number 1 to one of the other towers by following very strict rules.\n\n");
	printf("RULES : \n1 . You're allowed to pick up the top plates only.\n2 . You're not allowed to put down big plate on a smaller one.\n");
	printf("Please follow the instructions (below the screen) along the the quest. Press 'ENTER' after every wise choice you make.\n\n");
	printf("To reset the plates to tower number 1 enter '0' instead of the plate's number.\n\n");
	printf("You may begin!\n");

}
void Game()
{
	window(mat);
	towers(mat);
	plates_deafault(tow_mat);
	print_window(mat);

	int num, tower;
	while (win())
	{
		window(mat);
		towers(mat);
		do
		{
			op_scan(&num, &tower);
		} while (op(num, tower, tow_mat));
		print_window(mat);
	}
	printf("Congrats!!, you may enter the holy temple of Hanoi!\n\n");
}
int win()
{
	int win;
	for (j = 1; j < TOWERS; j++) //winning if plates are placed on the 2nd or the 3rd tower
	{
		for (i = 1, win = 1; i < LEVELS; i++)
			if (tow_mat[i][j] > tow_mat[i - 1][j])
				win++;
		if (win == PLATES)
			return 0;
	}
	return 1;
}
int op_scan(int* num, int* tower)
{
	do {
		printf("Instruction : \n");
		printf("Please input the plate's number : ");
		scanf_s("%d", num);
		printf("Please input the destination tower : ");
		scanf_s("%d", tower);
		if (0 > *num || *num > PLATES + 1 || 0 > *tower || *tower > TOWERS + 1)
		{
			printf("INVALID INPUT : there are %d plates, and %d towers. Please try again\n\n", PLATES, TOWERS);
			rewind(stdin);
		}
	} while (0 > *num || *num > PLATES + 1 || 0 > *tower || *tower > TOWERS + 1);
}

int op(int num, int tower, int tow_mat[][TOWERS])
{
	int t, l;
	if (num == 0)
		plates_deafault(tow_mat);
	else
	{
		for (i = 0; i < LEVELS; i++) //removing plate from it's current place
			for (j = 0; j < TOWERS; j++)
				if (tow_mat[i][j] == num)
					if (i != LEVELS - 1 && tow_mat[i + 1][j] != 0)
					{
						printf("INVALID MOVE : You must pick up the plates that on top!\n\n");
						return 1;
					}
					else
					{
						tow_mat[i][j] = 0;
						t = j, l = i;
					}

		for (i = 0, j = tower - 1; i < LEVELS; i++) //putting plate down in it's new place
			if (tow_mat[i][j] == 0)
				if (i != 0 && tow_mat[i - 1][j] > num)
				{
					printf("INVALID MOVE : You're not allowed to put down big plate on a smaller one.\n\n");
					tow_mat[l][t] = num;
					return 1;
				}
				else
				{
					tow_mat[i][j] = num;
					break;
				}
	}

	for (i = 0; i < LEVELS; i++)
		for (j = 0; j < TOWERS; j++)
			if (tow_mat[i][j] != 0)
				plate(tow_mat[i][j], j + 1, i + 1);
	return 0;
}
void plate(int num, int tower, int tower_level)
{
	int i, j, local_wid; //j and i defined locally for the loop continuation in the calling function

	switch (num)
	{
	case 1:
		local_wid = PL_WID_1;
		break;
	case 2:
		local_wid = PL_WID_2;
		break;
	case 3:
		local_wid = PL_WID_3;
		break;
	case 4:
		local_wid = PL_WID_4;
		break;
	case 5:
		local_wid = PL_WID_5;
		break;
	}
	for (i = R - tower_level * 3; i < R - tower_level * 3 + 2; i++)
	{
		for (j = 0; j < C; j++)

			if (tower * C / 4 - C / local_wid < j && j < tower * C / 4 + C / local_wid)
			{
				mat[i][j] = ' ';
				if (j == tower * C / 4 && i == R - 3 * tower_level)
					mat[i][j] = (char)(num + '0');
			}
	}
}
void towers(char mat[][C])
{
	int tow_num = 0;
	for (i = 5; i < R; i++) // 5 = space from top of the window
	{
		for (j = 0; j < C; j++)
		{
			if (j == C / 4 || j == 2 * C / 4 || j == 3 * C / 4) //printing towers, auto modified to the size of C;
				if (i == 5)
					mat[i][j] = ++tow_num + '0';
				else
					mat[i][j] = ' ';
		}
	}
}
void window(char mat[][C])
{

	char cube = 219;
	for (i = 0; i < R; i++) //creating a window
	{
		for (j = 0; j < C; j++)
		{
			if (!j)
				mat[i][j] = i + 1; //line numbers
			else
				mat[i][j] = cube;
		}
	}
}
void print_window(char mat[][C])
{
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
			if (!j)
				printf("%3d ", mat[i][j]);
			else
				printf("%c", mat[i][j]);
		printf("\n");
	}
}
void plates_deafault(int tow_mat[][TOWERS])
{
	for (i = 0; i < LEVELS; i++)
		for (j = 0; j < TOWERS; j++)
			if (j == 0)
				tow_mat[i][j] = i + 1;
			else
				tow_mat[i][j] = 0;
	for (i = 0; i < LEVELS; i++)
		for (j = 0; j < TOWERS; j++)
			if (tow_mat[i][j] != 0)
				plate(tow_mat[i][j], j + 1, i + 1);
}

