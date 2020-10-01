#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#define N 30
#define M 30

typedef struct 
{
	int nCol;
	int nLine;
}Direction;
void creating_border(int mat[][N + 2],Direction *trof);
void print_gameboard(int gameboard[][N + 2]);
void Trof_Movment(int mat[][N + 2], Direction vec[], Direction* ptr2trof);
int check_if_alive(Direction* ptr2trof, int mat[][N + 2]);
void kill_trons(Direction* ptr2trof, int mat[][N + 2]);

//-----------------------------------------------------------------------------
// Tron and Trof 2D game
// -----------
//
// General : The program is a 2D game.
//
// Input : Location of "Trof";
//
// Process : Generaiting the game board(mat/gameboard) , and running the game.
//
// Output : Prints the game board after every turn and the amount of "Trons" the "Trof" killed.
//
//-----------------------------------------------------------------------------
// Programmer : Aaron
// Student No : 69
// Date : 4/20/20
//-----------------------------------------------------------------------------
int main()
{
	// The trof's location
	Direction Trof;
	// Direction vector as request in question
	Direction vec_dec[] =
	{
		{0,0},
		{0,-1},
		{1,0},
		{0,1},
		{-1,0}
	};
	// The planet creation with room for the saftey wall.
	int gameboard[M+2][N+2];
	creating_border(gameboard,&Trof);
	print_gameboard(gameboard);
	Trof_Movment(gameboard, vec_dec, &Trof);
	return 0;
}

void creating_border(int mat[][N + 2],Direction *trof)
{
	// Fills up board with random number of trons
	for (int i = 0; i < N + 2; i++)
	{
		for (int k = 0; k < M + 2; k++)
		{
			mat[k][i] = rand() % (4 + 1 - 1) +1;
		}
	}
	// adds the safety wall
	// doing colums
	for (int i = 0; i < N + 2; i++)
	{
		mat[0][i] = mat[M + 1][i]  = -999;

	}
	// doing rows
	for (int k = 0;k < M + 2; k++)
	{
		mat[k][0] = mat[k][N+1] = -999;

	}
	printf("Trof starting pos\n");
	while (1)
	{
		scanf("%d %d",&trof->nCol,&trof->nLine);
		if (trof->nLine < M + 1 && trof->nCol < N + 1) 
		{
			break;
		}
		printf("$try again$\n");
	}
}


void Trof_Movment(int mat[][N + 2], Direction vec[],Direction *ptr2trof)
{
	// steps is left and direc is right
	int direc, steps,flag=1;
	// old pos
	int xtrof, ytrof;
	do
	{
		xtrof = ptr2trof->nCol, ytrof = ptr2trof->nLine;
		mat[ytrof][xtrof] = 0;
		printf("Enter amount of steps and direction\n");
		scanf("%d %d", &steps, &direc);
		for (int i = 0; i < steps && flag && direc; i++) {
			// moves up
			if (direc == 1 && mat[ytrof - 1][xtrof] != -999)ptr2trof->nLine += vec[direc].nLine;
			// movees right
			if (direc == 2 && mat[ytrof][xtrof + 1] != -999) ptr2trof->nCol += vec[direc].nCol;
			// moves down
			if (direc == 3 && mat[ytrof + 1][xtrof] != -999) ptr2trof->nLine += vec[direc].nLine;
			// move left
			if (direc == 4 && mat[ytrof][xtrof-1] !=-999) ptr2trof->nCol += vec[direc].nCol;
			flag = check_if_alive(ptr2trof, mat);
			if (flag)kill_trons(ptr2trof, mat);
			else
			{
				printf("Trof died to Tron at location: (%d,%d)\n", ptr2trof->nCol, ptr2trof->nLine);
				exit(1);
			}
			xtrof = ptr2trof->nCol, ytrof = ptr2trof->nLine;
		}
		print_gameboard(mat);

	} while (direc);

}


void kill_trons(Direction *ptr2trof,int mat[][N+2])
{
	// new pos
	int xtrof = ptr2trof->nCol, ytrof = ptr2trof->nLine;
	if (!mat[ytrof][xtrof]) printf("No trons found to kill\n");
	else printf("Trof killed %d Trons  at location (%d,%d) \n",mat[ytrof][xtrof],xtrof,ytrof);
	if (mat[ytrof][xtrof] != -999) mat[ytrof][xtrof] = 0;
}

int check_if_alive(Direction* ptr2trof, int mat[][N + 2])
{
	int xtrof = ptr2trof->nCol, ytrof = ptr2trof->nLine;
	if (mat[ytrof][xtrof] > 2) return 0;

	else return 1;
}


void print_gameboard(int gameboard[][N+2])
{
	system("@cls||clear");
	for (int i = 0; i < M+2; i++)
	{
		for (int k = 0; k < N+2; k++)printf("%d ", gameboard[i][k]);
		printf("\n");
	}
}