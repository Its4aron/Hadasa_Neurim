#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef enum {FALSE,TRUE} booly;

typedef struct Direction
{
	int nCol;
	int nRow;
}Direction;

void build_mat(char mat[][SIZE]);
void print_mat(char mat[][SIZE+2]);
void build_wall(char mat[][SIZE], char matb[SIZE + 2][SIZE + 2]);
Direction FindWord(char mat[][SIZE + 2], char target[], Direction vec_D[]);
int Search_matrix_for_letter(char mat[][SIZE + 2], char Target, Direction**ptr);
Direction Search_for_target(Direction dir, char target, Direction mov, char mat[][SIZE + 2]);

void main()
{
	Direction vec_dec[] =
	{
		{0,0},//No movment
		{-1,-1},//left top corner
		{0,-1},//up
		{1,-1},//right top corner
		{1,0},//right
		{1,1},//bottom right corner
		{0,1},//bottom
		{-1,1},//bottom left corner
		{-1,0}//left
	};
	char target[SIZE];
	char mat[SIZE][SIZE] = {};
	/*char mat[SIZE][SIZE] = {
	{'r', 'h','0','o','o','e','f','g','d','i'},
	{'a', 'o' ,'z' ,'d' ,'l', 'n','o','p','q','r'},
	{'r', 't' ,'r' ,'z' ,'a' ,'l' ,'q' ,'w' ,'s' ,'x' },
	{'d' ,'d' ,'e' ,'d' ,'f' ,'v' ,'e' ,'w','g' ,'t' },
	{'n', 'd', 'y', 'w', 'j', 'm', 'w', 'd', 'w', 'l' },
	{'o', 'p', 'h', 'l', 'o', 'n', 'l', 'e', 'y', 'z' },
	{'x', 'c', 'v', 'b', 'n', 'm', 'a', 's', 'f', 'g'},
	{'d', 'j', 'k', 'l', 'b', 'z', 'z', 't', 'y', 'u' },
	{'o', 'h', 'q', 'z', 'z', 'b' ,'n' ,'h', 'y', 't'},
	{'r' ,'e' ,'k' ,'l' ,'j' ,'g' ,'d' ,'r' ,'s' ,'a' }
	};*/
	build_mat(mat);
	char matB[SIZE + 2][SIZE + 2] = {};
	build_wall(mat, matB);
	print_mat(matB);
	printf("Enter Word to search for:\n");
	gets_s(target, sizeof(target));
	Direction d=  FindWord(matB, target,vec_dec);
	if (d.nCol == -1)printf("WORD NOT FOUND\n");
	else printf("WE FOUND IT COLUM: %d ROW :%d\n", d.nCol, d.nRow);
}


//looks for letter in matrix and puts them in a dynamic array
int Search_matrix_for_letter(char mat[][SIZE+2],char Target,Direction **ptr)
{
	//each row
	booly Found=FALSE;
	*ptr = (Direction*)calloc(1, sizeof(Direction));
	int ctr = 0, size = 1;
	Direction d;
	for (int i = 1; i < SIZE + 1; i++) 
	{
		for (int k = 1; k < SIZE + 1; k++)
		{
			if(mat[i][k]==Target) 
			{
				Found = TRUE;
				d.nCol = k;
				d.nRow = i;
				*(*ptr+ctr) = d;
				ctr++;
				size++;
				*ptr = (Direction*)realloc(*ptr, size * sizeof(Direction));
			}
		}
	}
	if (Found)return ctr;
	else return FALSE;
}

//if cant find next letter in current direction returns -1 -1 
Direction Search_for_target(Direction dir, char target,Direction mov,char mat[][SIZE+2])
{
	Direction dur;
	dur.nCol = -1;
	dur.nRow = -1;
	if (mat[dir.nRow + mov.nRow][dir.nCol + mov.nCol] == '#')return dur;
	    else if (mat[dir.nRow + mov.nRow][dir.nCol + mov.nCol] == target)
		{
			dur.nCol = dir.nCol + mov.nCol;
			dur.nRow = dir.nRow + mov.nRow;
			return dur;
		}
		else
		{
			return dur;
		}			
}



Direction FindWord(char mat[][SIZE + 2], char target[],Direction vec_D[])
{
	//A dynamic array holding all locations of the first letter of the word.
	Direction saveD,curr_d,*ptr2d=NULL;
	booly Found = FALSE;
	int ctr = 0, ar_length = strlen(target),size;
	char curr_target=target[0];
	size = Search_matrix_for_letter(mat, curr_target,&ptr2d);
	if(size==FALSE)	return { -1,-1 };
	curr_d = ptr2d[0];
	while(!Found)
	{
		//goes over each direction
		for (int j = 1; j < 9; j++) 
		{
			curr_d = ptr2d[ctr];
			if (Found)break;
			//goes over each letter
			for (int i = 1; i < ar_length; i++)
			{
				//Next letter im searching for
				curr_target = target[i];
				//search a direction at a time
				curr_d = Search_for_target(curr_d, curr_target,vec_D[j],mat);
				if (curr_d.nCol == -1 || curr_d.nRow == -1)
				{
					Found = FALSE;
					break;
				}
				else Found = TRUE;
			}
		}
		if (Found == TRUE)saveD = ptr2d[ctr];
		ctr++;
		curr_d = ptr2d[ctr];
		if (ctr == size&&Found==FALSE)
		{
			return { -1,-1 };
		}
	}
	return saveD;
}

//creates the mat by the user
void build_mat(char mat[][SIZE])
{
	char let = 0;
	//each row
	for (int i = 0; i < SIZE; i++)
	{
		for (int k = 0; k < SIZE; k++)
		{
			printf("ENTER LETTER FOR ROW: %d,COLM: %d\n",i,k);
			scanf("%c ", &let);
			mat[i][k] = let;
		}
	}
}


//puts mat into matb and builds wall for matb with #
void build_wall(char mat[][SIZE], char matb[SIZE+2][SIZE+2] )

{
	//each row
	for (int i = 1; i < SIZE + 1; i++)
	{
		//each colm for row i
		for (int k = 1; k < SIZE + 1; k++)
		{
			matb[i][k] = mat[i - 1][k - 1];
		}
	}
		//builds the safety wall for new Board
		for (int i = 0; i < SIZE+2; i++)
		{
			matb[0][i] = matb[i][0] = '#';
			matb[SIZE+2 - 1][i] = matb[i][SIZE+2 - 1] = '#';
		}
}



void print_mat(char mat[][SIZE+2])
{
	//go over each row
	for (int i = 0; i < SIZE+2; i++)
	{
		//go over each colm in row i
		for (int k = 0; k < SIZE+2; k++)
		{
			printf("%c", mat[i][k]);
		}
		printf("\n");
	}


}

