#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

/**
 * This is basically a non-blocking getchar() for Linux.
 */
int GetKey() {
    int c;   
    static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr(STDIN_FILENO, &oldt);

    /* Copy these so we can restore them later*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON);          

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    /*This is your part:
    I choose 'e' to end input. Notice that EOF is also turned off
    in the non-canonical mode*/
    c = getchar();

    /*restore the old settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return c;
}
