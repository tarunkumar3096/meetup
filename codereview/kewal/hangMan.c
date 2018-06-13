#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <error.h>
#include <errno.h>

static char *words[] = {"india", "linux", "book", "chennai",
	"zilogic", "work", "technology", "creativity"};

#define TOTALWORDS sizeof(*words)
#define FILE_NAME "hangMan.txt"

static char *guessWord(char *word, FILE *fd);
static int mapTheLetter(char *print, char *word, char letter);
static int print_HangMan(FILE *fd);
static int validation(char letter);
static int Continue(void);

int main(void)
{
	char *word;
	FILE *fd;
	char *res;

	srand(time(NULL));

	fd = fopen(FILE_NAME, "r");
	if (fd == NULL)
		error(1, errno, "open failed");

	do {
		word = words[rand() % TOTALWORDS];

		res = guessWord(word, fd);

		printf("\nword  : %s\n", word);

		if (!strcmp(word, res))
			printf("You found correct word..!!\n");
		else
			printf("Try better next time..!!\n");

		fseek(fd, 0, SEEK_SET);

	} while (Continue());

	return 0;
}

static char *guessWord(char *word, FILE *fd)
{
	int ret;
	char letter;
	char *print_word;

	print_word = calloc(strlen(word), sizeof(char));
	memset(print_word, '-', strlen(word));
	printf("\n%s\n", print_word);

	while (1) {
		printf("Enter a letter = ");
		scanf("%c", &letter);

		if (validation(letter))
			continue;

		ret = mapTheLetter(print_word, word, letter);
		printf("\n%s\n", print_word);
		if (!ret) {
			if (print_HangMan(fd))
				break;
		}

		if (!strcmp(word, print_word))
			break;
	}
	return print_word;
}

static int mapTheLetter(char *print, char *word, char letter)
{
	int i;
	int found = 0;

	for (i = 0; i < strlen(word); i++) {
		if ((word[i] == letter) || (word[i] == (letter + 32))) {
			if (print[i] != '-')
				return 0;
			print[i] = word[i];
			found = 1;
		}
	}

	if (found)
		return 1;
	else
		return 0;
}

static int print_HangMan(FILE *fd)
{
	char ptr;
	int ret;

	while (1) {
		ret = fread(&ptr, sizeof(char), 1, fd);
		if (!ret)
			return 1;

		if (ptr == '#')
			break;

		else if (!printf("%c", ptr))
			return 1;
	}

	return 0;
}

static int validation(char letter)
{		
		if (getchar() != '\n') {
			while (getchar() != '\n')
				;
			return 1;
		}

		if (!isalpha(letter))
			return 1;

		return 0;
}

static int Continue(void)
{
	char choice;

	printf("\nYou want replay enter 'y' : ");
	scanf("%c", &choice);
	while (getchar() != '\n')
		;

	if (choice == 'y')
		return 1;
	else
		return 0;
}

