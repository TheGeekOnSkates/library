#include <time.h>

/**
 * Random number generator built on top of C's built-in randomness functions
 * @param int min The minimum (set to NULL if you don't need one)
 * @param int max The maximum (set to NULL if you don't need one)
 * @return int a random number
 * @author DojoMike
 */
int random(int min, int max)
{
    // "Seed" the random value
    srand(time(NULL));

    // If there's a maximum, factor it in
    int r;
    if (max != NULL)
        r = rand() % max;
    else
        r = rand();

    // If there's a minimum, factor that in
    if (min != NULL)
    {
        int i;
        for (i=min; i>0; i--)
        {
            if (r + i <= max)
            {
                r += min;
                break;
            }
        }
    }

    // And return the result
    return r;
}
