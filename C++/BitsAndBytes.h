/*
Program:    BitsAndBytes
Purpose:    Make it easier to work with numbers at the bit and byte levels
Author:     The Geek on Skates
Created:    June 22, 2018
License:    WTFL
*/
#include <stdio.h>

typedef unsigned char byte;

/**
 * Gets a specific bit in a number
 * @param[in] The number to get a bit from
 * @param[in] The index of the bit to get
 * @return The value of the specified bit
 */
int GetBit(unsigned int n, unsigned int i)
{
    return (n & ( 1 << i )) >> i;
}

void SetBit(unsigned int *n, unsigned int i, unsigned int v)
{
    *n  = (*n & ~(1<<i)) | (v<<i);
}

/**
 * Gets a specific byte in a number
 * @param[in] The number to get a byte from
 * @param[in] The index of the byte to get (0 to 3)
 * @return The value of the specified byte
 */
byte GetByte(unsigned int n, unsigned int i)
{
    return ((n >> (i * 8)) & 0xFF);
}

/**
 * Sets a specific byte in a number
 * @param[out] The number to be changed
 * @param[in] The index of the byte to set (0 to 3)
 * @param[in] The new value of the specified byte
 */
void SetByte(unsigned int *n, unsigned int i, unsigned int v)
{
    byte currentValue = GetByte(*n, i);
    *n -= (currentValue << (i * 8));
    *n += (v << (i * 8));
}

/**
 * This is an example of how and why these functions are useful.
 * Using some basic bit-shifting, it's possible to store tons of
 * data in very little space.  These days space is cheap and not
 * going anywhere, but there are still cases when we need to use
 * it sparingly.  For me, this is mostly Arduino and Raspberry Pi
 * projects, and of course games. :)
 */

// These constants are known at compile time,
// so we can let the pre-processor translate them
// (saving more space).  At least I think that's
// how it works. :)
#define HEALTH 0
#define RUPEES 1
#define BOMBS 2
#define ARROWS 3
#define MASTER_SWORD 0
#define HAMMER 1
#define HOOKSHOT 2
#define FIRE_ROD 3

int example()
{
    // Set up one number to contain things that are counted
    unsigned int value=0x11223344;
    SetByte(&value, HEALTH, 100);  // First byte - player's health
    SetByte(&value, RUPEES, 77);   // Second byte - player's Rupees
    SetByte(&value, ARROWS, 5);    // Third byte - player's bombs
    SetByte(&value, BOMBS, 10);    // Fourth byte - player's arrows

    printf("Link has: \n");
    printf("%d percent health,\n", GetByte(value, HEALTH));
    printf("%d Rupees,\n", GetByte(value, RUPEES));
    printf("%d bombs,\n", GetByte(value, BOMBS));
    printf("and %d arrows\n", GetByte(value, ARROWS));

    // But let's not stop there.
    // Let's set another variable to store things that Link either has or he doesn't
    unsigned int others = 0b00100011;   // 1 byte
    if (GetBit(others, MASTER_SWORD) == 1)
        printf("The Master Sword,\n");
    if (GetBit(others, HAMMER) == 1)
        printf("The Magic Hammer,\n");
        if (GetBit(others, HOOKSHOT) == 1)
        printf("The Hookshot,\n");
    if (GetBit(others, FIRE_ROD) == 1)
        printf("The Fire Rod,\n");  // He's not gonna have this one yet

    // And now let's give him the hookshot (cuz the hookshot is awesome)!
    SetBit(&others, HOOKSHOT, 1);
    if (GetBit(others, HOOKSHOT) == 1)
        printf("and he just got the Hookshot!\n");

    // And print the variables we stored all that info in
    printf("\nvalue = %d (0x%08x)", value, value);
    printf("\nothers = %d (0x%08x)", others, others);
    printf("\nAll that data was stored in %d bytes!", sizeof(int) * 2);

    // Notice that to the average user, These numbers seem
    // totally random.  This makes them a BIT more secure
    // (no cheesy pun intended).  They won't stop a serious
    // enough hacker from figuring out which number mean what,
    // But a game save file that's just a bunch of numbers
    // will definitely keep the average wanna-be cheater from
    // breaking stuff (until the ones that do put it on the web,
    // but if people are doing that with my games that's still a
    // good thing IMO - it means my games are freakin' popular! :))

    // Notice also that ALL THAT INFORMATION, from Link's health to
    // his weapons, was stored in 8 bytes of data (and note that the
    // second int could have stored WAY more boolean values - 32!).
    // If you used an int for all health/bombs/arrows/Rupees, it would
    // require a twice as much and not even be capable of storing all
    // those booleans!

    return 0;
}
