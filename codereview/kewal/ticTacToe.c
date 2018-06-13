#include <stdio.h>
#include <string.h>

#define MAX_TERN 9
#define MATRIX 3

struct path {
	int valid;
	int r_A, c_A;
	int r_B, c_B;
	int r_C, c_C;
};

static struct path paths[] = {
	{ 1,   0, 0,   0, 1,   0, 2 },
	{ 1,   1, 0,   1, 1,   1, 2 },
	{ 1,   2, 0,   2, 1,   2, 2 },

	{ 1,   0, 0,   1, 0,   2, 0 },
	{ 1,   0, 1,   1, 1,   2, 1 },
	{ 1,   0, 2,   1, 2,   2, 2 },

	{ 1,   0, 0,   1, 1,   2, 2 },
	{ 1,   0, 2,   1, 1,   2, 0 },

	{ 0,  0, 0,   0, 0,   0, 0 }
};

static void runGame(char board[MATRIX][MATRIX]);
static int getPosition(int *i, int *j);
static int checkWinner(char board[MATRIX][MATRIX]);
static void printResult(int ret);
static int validation(char board[][MATRIX], int i, int j);
static void printMatrix(char buff[][MATRIX]);
static int Continue(void);

int main(void)
{
	int i;
	char board[MATRIX][MATRIX];

	do {
		for (i = 0; i < MATRIX; i++)
			memset(board[i], ' ', MATRIX);

		runGame(board);
	} while (Continue());

	return 0;
}

static void runGame(char board[MATRIX][MATRIX])
{
	int turn = 1;
	int r_itr;
	int c_itr;
	int ret;

	printMatrix(board);

	while (1) {
		if (turn)
			printf("enter possition for mark 'X' pos : ");
		else
			printf("enter possition for mark 'O' pos : ");

		if (getPosition(&r_itr, &c_itr))
			continue;

		if (validation(board, r_itr, c_itr))
			continue;

		if (turn) {
			turn = 0;
			board[r_itr][c_itr] = 'X';
		} else {
			turn = 1;
			board[r_itr][c_itr] = 'O';
		}

		printMatrix(board);

		ret = checkWinner(board);
		if (ret) {
			printResult(ret);
			break;
		}
	}
}

static int getPosition(int *i, int *j)
{
	int pos;

	if (!scanf("%d", &pos))
		return 1;
	else if (getchar() != '\n') {
		while (getchar() != '\n')
			;
		return 1;
	}

	*i = pos / MATRIX;
	*j = pos % MATRIX;

	return 0;
}		

static int checkWinner(char board[MATRIX][MATRIX])
{
	int a, b, c;
	int available = 0;
	struct path *ptr;

	for (ptr = paths; ptr->valid; ptr++) {
		a = board[ptr->r_A][ptr->c_A];
		b = board[ptr->r_B][ptr->c_B];
		c = board[ptr->r_C][ptr->c_C];

		if (a == b && b == c && a == c) {
			if (a == 'X')
				return 1;
			else if (a == 'O')
				return -1;
		} else if (a == ' ' || b == ' ' || c == ' ')
			available = 1;
	}

	if (!available)
		return 2;

	return 0;
}

static void printResult(int ret)
{
	if (ret == 1)
		printf("X wins this game..!\n");
	else if (ret == -1)
		printf("O wins this game..!\n");
	else if (ret == 2)
		printf("this game is tayed..!\n");
}

static void printMatrix(char buff[][MATRIX])
{
	int i, j;
	int pos = 0;

	for (i = 0; i < MATRIX; i++) {
		printf(" ====================\n|");
		for (j = 0; j < MATRIX; j++)
			printf(" %c    |", buff[i][j]);
		
		printf("\n|");

		for (j = 0; j < MATRIX; j++)
			printf("    %d |", pos++);

		printf("\n");
	}
	printf(" ====================\n");
}

static int Continue(void)
{
	char choice;

	printf("\nYou want replay enter 'y' : ");
	while (getchar() != '\n')
		;
	scanf("%c", &choice);

	if (choice == 'y')
		return 1;
	else
		return 0;
}

static int validation(char board[][MATRIX], int i, int j)
{
	if (!(i < MATRIX && i >= 0 && j < MATRIX && j >= 0))
		return 1;
	else if (board[i][j] == 'X' || board[i][j] == 'O')
		return 1;

	return 0;
}

