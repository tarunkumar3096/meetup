#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHANCE 8
#define MAX_NUM 4

static int guessNumber(char *rand_val, char *user_val);
static void calBullCow(char *r_val, char *u_val, int *bull, int *cow);
static void getRandNumber(char *buff);
static int validation(char *num);
static int Continue(void);

int main(void)
{
	int bull;
	char user_val[MAX_NUM];
	char rand_val[MAX_NUM];

	srand(time(NULL));

	do {
		getRandNumber(rand_val);

		bull = guessNumber(rand_val, user_val);

		printf("\nNumber  : %s\n", rand_val);

		if (bull == MAX_NUM)
			printf("You found correct number..!!\n");
		else
			printf("Try better next time..!!\n");

	} while (Continue());

	return 0;
}

static int guessNumber(char *rand_val, char *user_val)
{
	int itr;
	int cow;
	int bull;

	for (itr = 0; itr < MAX_CHANCE; itr++) {
		cow = 0;
		bull = 0;

		printf("Enter your guess = ");
		scanf("%[^\n]", user_val);
		getchar();

		if (validation(user_val)) {
			itr--;
			continue;
		}

		calBullCow(rand_val, user_val, &bull, &cow);

		printf("%d bull  %d cow\n\n", bull, cow);
		if (bull == MAX_NUM)
			break;
	}
	return bull;
}

static void calBullCow(char *r_val, char *u_val, int *bull, int *cow)
{
	int i, j;

	for (i = 0; i < MAX_NUM; i++) {
		for (j = 0; j < MAX_NUM; j++) {
			if (r_val[i] == u_val[j]) {
				if (i == j)
					(*bull)++;
				else
					(*cow)++;
			}
		}
	}
}

static void getRandNumber(char *buff)
{
	int itr;
	int i;
	char *num = "0123456789";
	char tmp;
	int copy = 0;

	for (itr = 0; itr < MAX_NUM; itr++) {
		tmp = num[rand() % 10];

		for (i = 0; i < itr; i++) {
			if (buff[i] == tmp) {
				itr--;
				copy = 1;
			}
		}

		if (!copy)
			buff[itr] = tmp;
		copy = 0;
	}
}

static int validation(char *num)
{
	int itr;
	int i;
	int j;

	if (strlen(num) > MAX_NUM)
		return 1;

	for (i = 0; i < MAX_NUM; i++) {
		for (j = 0; j < MAX_NUM; j++)
			if (i != j && num[i] == num[j])
				return 1;
	}

	for (itr = 0; itr < MAX_NUM; itr++)
		if (!isdigit(num[itr]))
			return 1;

	return 0;
}

static int Continue(void)
{
	char choice;

	printf("\nYou want replay enter 'y' : ");
	scanf("%c", &choice);
	getchar();

	if (choice == 'y')
		return 1;
	else
		return 0;
}
