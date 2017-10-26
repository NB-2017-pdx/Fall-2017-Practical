/* 
 * Ian Winter
 * New Beginnings
 * Problem 4
 *
 * Functions is_vowel and is_consonant, for testing if a character is a vowel
 * or a consonant. 
 */
#include <stdio.h>

#define TRUE 1
#define FALSE 0

/* Returns TRUE if character is a vowel, otherwise returns false. */
int is_vowel(char letter)
{
    if (letter == 'a' || letter == 'A' || letter == 'e' || letter == 'E' ||
        letter == 'i' || letter == 'I' || letter == 'o' || letter == 'O' ||
        letter == 'u' || letter == 'U' )
        return TRUE;
    else
        return FALSE;
}

/* Returns TRUE if character is a consonant, otherwise returns false. */
int is_consonant(char letter)
{
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') &&
        !(is_vowel(letter)))
        return TRUE;
    else
        return FALSE;
}
