#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CHANCE 20
#define NUM_RANG 100
#define MAX_OPT 2

#define TWENTY_PER (MAX_CHANCE * 20) / 100
#define FIFTY_PER (MAX_CHANCE * 50) / 100
#define SEVENTY_FIVE_PER (MAX_CHANCE * 75) / 100

static void quiz(int *correct);
static int arithmaticOperetion(int n1, int n2, char opt);
static int get_rand(int *n1, int *n2);
static int get_rand(int *n1, int *n2);
static void printResult(int correct);
static int Continue(void);

int main(void)
{
	int correct = 0;

	do {
		quiz(&correct);

		printResult(correct);

		correct = 0;

	} while (Continue());

	return 0;
}

static void quiz(int *correct)
{
	char *opt = "+-";
	int res;
	int opt_select;
	int user_val;
	int itr;
	int n1;
	int n2;

	for (itr = 0; itr < MAX_CHANCE; itr++) {

		opt_select = get_rand(&n1, &n2);

		res = arithmaticOperetion(n1, n2, opt[opt_select]);

		printf("%d %c %d  ? ", n1, opt[opt_select], n2);

		if (!scanf("%d", &user_val)) {
			while (getchar() != '\n')
				;
			continue;
		}

		if (user_val == res) {
			(*correct)++;
			printf("Correct\n");
		} else
			printf("Wrong\n");
	}
}

static int arithmaticOperetion(int n1, int n2, char opt)
{
	switch (opt) {
	case '+':
		return n1 + n2;
	case '-':
		return n1 - n2;
	default:
		printf("%c not available", opt);
	}
	return 0;
}

static int get_rand(int *n1, int *n2)
{
	srand(time(NULL));

	*n1 = rand() % NUM_RANG;
	*n2 = rand() % NUM_RANG;

	return rand() % MAX_OPT;
}

static void printResult(int correct)
{
	if (correct == MAX_CHANCE)
		printf("You are ginius...!!\n");
	else if (correct >= SEVENTY_FIVE_PER)
		printf("You played excellent...!!\n");
	else if (correct >= FIFTY_PER)
		printf("You played good...!!\n");
	else if (correct >= TWENTY_PER)
		printf("You can do better...!!\n");
	else
		printf("Try better next time...!!\n");

	printf("\nYour score is %d/%d\n", correct, MAX_CHANCE);
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

