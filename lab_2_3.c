#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#define up 4
#define le 4


int funct(int plat[le][up], int graf[up * le][up * le])
{
	int i, j, dis = 0, i1, i2, j1, j2, n, m, new_dis;
	for (i = 0; i < up * le; i++)
		for (j = i; j < up * le; j++)
			if (graf[i][j] == 1)
			{
				for (i1 = 0; i1 < le; i1++)
					for (j1 = 0; j1 < up; j1++)
						if (plat[i1][j1] == i)
						{
							i2 = i1;
							j2 = j1;
							i1 = le;
							j1 = up;
						}
				for (i1 = 0; i1 < le; i1++)
					for (j1 = 0; j1 < up; j1++)
						if (plat[i1][j1] == j)
						{
							dis = dis + abs(i2 - i1) + abs(j1 - j2);
							i1 = le;
							j1 = up;
						}
			}
	return dis;
}


int swap(int plat[le][up], int graf[up * le][up * le])
{
	int i, j, dis = 0, i1, i2, j1, j2, n, m, new_dis;
	dis = funct(plat, graf);
	for (n = 0; n < up - 1; n++)
		for (m = 0; m < le; m++)
		{
			i = plat[m][n];
			plat[m][n] = plat[m][n + 1];
			plat[m][n + 1] = i;
			new_dis = funct(plat, graf);
			if (new_dis > dis)
			{
				i = plat[m][n];
				plat[m][n] = plat[m][n + 1];
				plat[m][n + 1] = i;
			}
			else
				dis = new_dis;
		}
	for (n = 0; n < le - 1; n++)
		for (m = 0; m < up; m++)
		{
			i = plat[n][m];
			plat[n][m] = plat[n + 1][m];
			plat[n + 1][m] = i;
			new_dis = funct(plat, graf);
			if (new_dis > dis)
			{
				i = plat[n][m];
				plat[n][m] = plat[n + 1][m];
				plat[n + 1][m] = i;
			}
			else
				dis = new_dis;
		}
	return 0;
}


int multi(int plat[le][up], int graf[up * le][up * le])
{
	int counter, i, j, order[up * le], x, y, min, max, dis, max_num;
	for (i = 0; i < le; i++)
	{
		for (j = 0; j < up; j++)
		{
			plat[i][j] = -1;
		}
	}
	for (i = 0; i < up * le; i++)
		order[i] = 0;
	for (counter = 0; counter < up * le; counter++)
	{
		min = 999999999;
		x = -1;
		y = -1;
		max = -1;
		for (i = 0; i < up * le; i++)
		{
			if (order[i] != 1)
			{
				dis = 0;
				for (j = 0; j < up * le; j++)
					if (graf[i][j] == 1)
						dis++;
				if (dis > max)
				{
					max = dis;
					max_num = i;
				}
			}
		}
		for (i = 0; i < le; i++)
		{
			for (j = 0; j < up; j++)
			{
				if (plat[i][j] == -1)
				{
					plat[i][j] = max_num;
					if (min > funct(plat, graf))
					{
						min = funct(plat, graf);
						x = i;
						y = j;
					}
					plat[i][j] = -1;
				}
			}
		}
		for (i = 0; i < le; i++)
		{
			for (j = 0; j < up; j++)
			{
				printf("%d ", plat[i][j]);
			}
			printf("\n");
		}
		printf("---dis=%d\n", funct(plat, graf));
		plat[x][y] = max_num;
		order[max_num] = 1;
	}

	return 0;
}


int main(int argc, const char *argv[])
{
	int j, i, c = 0, plat[le][up], graf[up * le][up * le];
	srand(time(NULL));
	for (i = 0; i < up * le; i++)
		for (j = i; j < up * le; j++)
			if (i == j)
				graf[i][j] = 0;
			else
			{
				graf[i][j] = rand() % 2;
				graf[j][i] = graf[i][j];
			}
	for (i = 0; i < up * le; i++)
	{
		for (j = 0; j < up * le; j++)
			printf("%d ", graf[i][j]);
		printf("\n");
	}
	for (i = 0; i < le; i++)
	{
		for (j = 0; j < up; j++)
		{
			plat[i][j] = c;
			c++;
			printf("%d ", plat[i][j]);
		}
		printf("\n");
	}
	printf("dis=%d\n", funct(plat, graf));
	swap(plat, graf);
	for (i = 0; i < le; i++)
	{
		for (j = 0; j < up; j++)
		{
			printf("%d ", plat[i][j]);
		}
		printf("\n");
	}
	printf("dis=%d\n", funct(plat, graf));
	multi(plat, graf);
	for (i = 0; i < le; i++)
	{
		for (j = 0; j < up; j++)
		{
			printf("%d ", plat[i][j]);
		}
		printf("\n");
	}
	printf("dis=%d\n", funct(plat, graf));
	return 0;
}
