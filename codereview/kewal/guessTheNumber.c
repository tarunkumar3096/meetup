#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CHANCE 7
#define NUM_MAX 99
#define NUM_MIN 0
#define MAX_RAND_NUM 100

static int Continue(void);
static void rem_space(char *str);
static int read_int(int *intp);
static void runGame(int rand_num);
static int cmp_values(int rand_num, int guess_num);

int main(void)
{
	int rand_num;

	srand(time(NULL));

	do {
		rand_num = rand() % MAX_RAND_NUM;

		runGame(rand_num);
	} while (Continue());

	return 0;
}

static void runGame(int rand_num)
{
	int guess_num;
	int chance = MAX_CHANCE;
	char cont;
	int ret;

	while (1) {
		printf("Guess the number : ");
		
		ret = read_int(&guess_num);
		if (ret == -2) {
			printf("Guessed number out of range\n");
			ret = 0;
			continue;
		} else if (ret == -1) {
			printf("You should enter a number\n");
			ret = 0;
			continue;
		}

		if (cmp_values(rand_num, guess_num)) {
			chance = MAX_CHANCE;
			break;
		} else
			chance--;
		
		if (!chance) {
			printf("\nYou complited all chancess!!\n");
			chance = MAX_CHANCE;
			break;
		}

		guess_num = 0;
	}

}

static int cmp_values(int rand_num, int guess_num)
{
	if (rand_num == guess_num) {
		printf("\nCongrats you got the number\n");
		return 1;
	} else if (guess_num > rand_num)
		printf("guessed number is greter\n");
	else if (guess_num < rand_num) 
		printf("Guessed number is smoller\n");

	return 0;
}

static void rem_space(char *str)
{
	int cont = 0;
	int i = 0;

	while (str[i]) {
		if (str[i] != ' ')
			str[cont++] = str[i];
		i++;
	}
	str[cont] = '\0';
}

static int read_int(int *intp)
{
	char buf[16];
	char *retp;
	char *endptr;
	long input;

	retp = fgets(buf, sizeof(buf), stdin);
	if (retp == NULL)
		return -1;

	rem_space(retp);

	input = strtol(retp, &endptr, 10);
	if (*endptr != '\n')
		return -2;
	if (input > NUM_MAX)
		return -2;
	if (input < NUM_MIN)
		return -2;
	if (input == 0)
		return -1;

	*intp = (int) input;

	return 0;
}

static int Continue(void)
{
	char choice;

	printf("\nYou want to replay enter 'y' : ");
	scanf("%c", &choice);

	while (getchar() != '\n')
		;

	if (choice == 'y')
		return 1;
	else
		return 0;
}

