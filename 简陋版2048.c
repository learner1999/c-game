#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define	size	4

int board[size][size] = { 0 };

void randNum(void);
void printBoard(void);
void initGame(void);
int move(char);

int main(void)
{
	char ch = 'w';

	initGame();

	while (1)
	{
		if (kbhit())
		{
			ch = getch();

			if (move(ch))
			{
				randNum();
			}
			system("cls");
			printBoard();
		}
	}

	return 0;
}

void printBoard(void)
{
	int i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			printf("%3d", board[i][j]);
		}
		printf("\n");
	}

	return;
}

void initGame(void)
{
	randNum();
	printBoard();

	return;
}

void randNum(void)
{
	int i, j;

	srand(time(NULL));

	while (1)
	{
		i = (int)(size * rand() / RAND_MAX);
		j = (int)(size * rand() / RAND_MAX);
		if (0 == board[i][j])
		{
			board[i][j] = 2;
			break;
		}
	}

	return;
}

int move(char ch)
{
	int a, b, i, j;
	int counter = 0;

	switch (ch)
	{
	case 'w':
	case 'W':
		for (j = 0; j < size; j++)
		{
			for (a = 0; a < size; a++)
			{
				for (b = a; b < size; b++)
				{
					if (0 != board[b][j])
					{
						if (a >= 1 && board[a - 1][j] == board[b][j])
						{
							board[a - 1][j] += board[b][j];
							board[b][j] = 0;
							a--;
							counter++;
						}
						else if (b != a)
						{
							board[a][j] = board[b][j];
							board[b][j] = 0;
							counter++;
						}
						break;
					}
				}
			}
		}
		break;
	case 's':
	case 'S':
		for (j = 0; j < size; j++)
		{
			for (a = size - 1; a >= 0; a--)
			{
				for (b = a; b >= 0; b--)
				{
					if (0 != board[b][j])
					{
						if (a <= size - 2 && board[a + 1][j] == board[b][j])
						{
							board[a + 1][j] += board[b][j];
							board[b][j] = 0;
							a++;
							counter++;
						}
						else if (b != a)
						{
							board[a][j] = board[b][j];
							board[b][j] = 0;
							counter++;
						}
						break;
					}
				}
			}
		}
		break;
	case 'a':
	case 'A':
		for (i = 0; i < size; i++)
		{
			for (a = 0; a < size; a++)
			{
				for (b = a; b < size; b++)
				{
					if (0 != board[i][b])
					{
						if (a >= 1 && board[i][a - 1] == board[i][b])
						{
							board[i][a - 1] += board[i][b];
							board[i][b] = 0;
							a--;
							counter++;
						}
						else if (b != a)
						{
							board[i][a] = board[i][b];
							board[i][b] = 0;
							counter++;
						}
						break;
					}
				}
			}
		}
		break;
	case 'd':
	case 'D':
		for (i = 0; i < size; i++)
		{
			for (a = size - 1; a >= 0; a--)
			{
				for (b = a; b >= 0; b--)
				{
					if (0 != board[i][b])
					{
						if (a <= size - 2 && board[i][a + 1] == board[i][b])
						{
							board[i][a + 1] += board[i][b];
							board[i][b] = 0;
							a++;
							counter++;
						}
						else if (b != a)
						{
							board[i][a] = board[i][b];
							board[i][b] = 0;
							counter++;
						}
						break;
					}
				}
			}
		}
		break;
	}

	return counter;
}