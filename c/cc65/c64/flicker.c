#include <peekpoke.h>

unsigned char speed = 50, i = 0, j = 0;

/* Makes the screen flicker, like on Retro Recipes */
void flicker() {
	i = 0;
	while(1) {
		POKE(53280L, i);
		i++;
		for (j = 0; j < speed; j++);
		if (i == 16) i = 0;
	}
}
