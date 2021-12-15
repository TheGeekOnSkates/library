#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "Twist.h"
#include "simplify.h"

void print(Twist *t)
{
	printf("%s\n\n", t->story);
	for (int i = 0; i < t->length; i++)
		printf("%d. %s\n", i + 1, t->options[i]);
}
int ask(Twist *t)
{
	// Let the leter R repeat the story content
	char c;
	scanf_s(" %c", &c, sizeof(char));
	if (c == 'r')
	{
		int x = CharToInt(&c);
		printf("x = %d\n", x);
		print(t);
		int answer = ask(t);
		return answer;
	}

	// Let the letter X exit the game
	if (c == 'x')
	{
		// TO-DO: Have it ask the player if they want to save first
		exit(DONE);
	}

	// If the user entered an invalid number, try again
	int x = CharToInt(&c); 
	if (x < 1 || x > t->length)
	{
		printf("Invalid choice.  ");
		int tryAgain = ask(t);
		return tryAgain;
	}
	
	// Otherwise, we're good
	return x;
}
int show(Twist *t)
{
	print(t);
	return ask(t);
}