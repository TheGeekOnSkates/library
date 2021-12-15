#pragma once

// Twists are bits of story that lead to/result from players' choices
typedef struct {

	// The story content
	const char * story;

	// The choices the player can make after reading the content
	const char ** options;

	// The number of options
	int length;

} Twist;

/**
* Prints a Twist to standard output (stdout)
* @param[in] Pointer to a Twist structure
**/
void print(Twist *t);

/**
* Gets, validates, and returns the user's choice
* @param[in] Pointer to a Twist structure
* @return The user's choice
**/
int ask(Twist *t);

/**
* Prints the twist and gets the player's input on the next direction for the story
* @param[in] Pointer to a Twist structure
* @return The player's choice
**/
int show(Twist *t);