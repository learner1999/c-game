/* ▇ */

# include <stdio.h>
# include <stdlib.h>
# include <time.h>


# define SIZE_OF_MINE 13	//雷区的边长
# define NUM_OF_MINE 20		//地雷的个数


int mine[SIZE_OF_MINE + 1][SIZE_OF_MINE + 1] = { 0 };	//纪录雷区每个点为空(0)、数字(1~8)、雷(>=9)
int mine_copy[SIZE_OF_MINE + 1][SIZE_OF_MINE + 1] = { 0 };	//纪录雷区每个点是否已经显示出来，隐藏0，显示1
int mine_note[NUM_OF_MINE][2];	 //纪录地雷的坐标


void init_game(void);	//初始化游戏
void rand_mine(int num_of_mine);	//随机生成地雷
void print_mine(void);	//打印“雷区”
void is_zero(int x, int y);	//判断用户输入的点是否为“0点”，如果是，则递归将附近的“0点显示出来”


int main(void)
{
	int x, y, i, j;
	int cout = 0;

	system("mode con cols=30 lines=20");
	printf("正在生成雷区，请稍后……\n");

	init_game();

	while (1)
	{
		printf("请输入要选择的点的坐标，左上角为1，1：");
		scanf("%d%d", &x, &y);
		if (mine[x][y] < 9 && mine[x][y] > 0)
		{
			mine_copy[x][y] = 1;
			system("cls");
			print_mine();
		}
		else if (mine[x][y] >= 9)
		{
			for (cout = 0; cout < NUM_OF_MINE; cout++)
			{
				mine_copy[mine_note[cout][0]][mine_note[cout][1]] = 1;
			}
			system("cls");
			print_mine();

			printf("GAME OVER!\n");
			exit(-1);
		}
		else
		{
			is_zero(x, y);
			system("cls");
			print_mine();
		}

		for (i = 1; i <= SIZE_OF_MINE; i++)
		{
			for (j = 1; j <= SIZE_OF_MINE; j++)
			{
				if (0 == mine_copy[i][j] && mine[i][j] < 9)
					goto out_loop;
			}
		}
		out_loop:
		if (i > SIZE_OF_MINE)
		{
			printf("YOU ARE WIN!\n");
			getchar();
			exit(-1);
		}
	}
	
	return 0;
}


void init_game(void)
{
	/* 随机生成地雷位置 */
	rand_mine(NUM_OF_MINE);

	system("cls");

	/* 打印“雷区” */
	print_mine();

	return;
}


void print_mine(void)
{
	int i, j;

	for (i = 1; i <= SIZE_OF_MINE; i++)
	{
		for (j = 1; j <= SIZE_OF_MINE; j++)
		{
			if (1 == mine_copy[i][j] && mine[i][j] < 9)
			{
				printf(" %d", mine[i][j]);
			}
			else if (1 == mine_copy[i][j] && mine[i][j] >= 9)
			{
				printf(" *");
			}
			else
			{
				printf("▇");
			}
		}

		printf("\n");
	}

	return;
}

void rand_mine(int num_of_mine)
{
	int i, j;
	int cout = 0;

	/* 随机生成地雷的坐标 */
	srand((int)time(NULL) * 189);
	while (num_of_mine--)
	{
		while (1)
		{
			i = 1 + SIZE_OF_MINE * rand() / RAND_MAX;
			j = 1 + SIZE_OF_MINE * rand() / RAND_MAX;
			if (9 != mine[i][j])	//9代表该点为地雷
			{
				mine[i][j] = 9;
				break;
			}
		}

		/* 将地雷的坐标纪录下来 */
		mine_note[cout][0] = i;
		mine_note[cout][1] = j;
		cout++;
	}

	/* 计算出每个点的数值，地雷周围的点自增1 */
	for (i = 1; i <= SIZE_OF_MINE; i++)
	{
		for (j = 1; j <= SIZE_OF_MINE; j++)
		{
			if (mine[i][j] >= 9)
			{
				if (i - 1 >= 1 && j - 1 >= 1)
					mine[i - 1][j - 1]++;
				if (i - 1 >= 1)
					mine[i - 1][j]++;
				if (i - 1 >= 1 && j + 1 <= SIZE_OF_MINE)
					mine[i - 1][j + 1]++;
				if (j - 1 >= 1)
					mine[i][j - 1]++;
				if (j + 1 <= SIZE_OF_MINE)
					mine[i][j + 1]++;
				if (i + 1 <= SIZE_OF_MINE && j - 1 >= 1)
					mine[i + 1][j - 1]++;
				if (i + 1 <= SIZE_OF_MINE)
					mine[i + 1][j]++;
				if (i + 1 <= SIZE_OF_MINE && j + 1 <= SIZE_OF_MINE)
					mine[i + 1][j + 1]++;
			}
		}
	}

	return;
}

void is_zero(int x, int y)
{
	if (x < 1 || x > SIZE_OF_MINE || y < 1 || y > SIZE_OF_MINE)
	{
		return;
	}
	else if (0 == mine[x][y] && 1 == mine_copy[x][y])
	{
		return;
	}
	else if (0 != mine[x][y])
	{
		mine_copy[x][y] = 1;
		return;
	}
	
	mine_copy[x][y] = 1;
		
	is_zero(x - 1, y);
	is_zero(x, y - 1);
	is_zero(x, y + 1);
	is_zero(x + 1, y);

	return;
}