/*
 * Ian Winter
 * New Beginnings
 * Problem 4
 *
 * Converts words to pig latin.
 * 
 * If a word begins with a consonant, all letters before initial vowel are
 * placed after the word and 'ay' is added. 
 *
 * If a word begins with a vowel 'yay' is added to the end of the word.
 */

#include <stdio.h>

#define MAXSTRING 50
#define TRUE 1
#define FALSE 0

int is_vowel(char letter);
int is_consonant(char letter);

/* Returns number of characters in a string excluding \0 */
int str_length(char str[])
{
    int i; 
    char c;

    for (i = 0; (c = str[i]) != '\n' && c != '\0'; ++i);
    return i;
}

/* Converts characters to lowercase */
void str_lc(char in[])
{
    int i;
    int len = str_length(in);

    for (i = 0; i < len; ++i)
        if (in[i] >= 'A' && in[i] <= 'Z')
            in[i] += 32;
}

/* Append str[] with append[] */
int str_append(char in[], char append[])
{
    int i;
    int lenin = str_length(in);
    int lenappend = str_length(append); 

    for (i = 0; i < lenappend; ++i)
        in[lenin + i] = append[i];
    in[lenin + lenappend] = '\0';
}

/* Converts consonant-beginning word in[] to pig latin */
void consonant_pig(char in[])
{
    int i;
    int firstvowel;             /* position in array of first vowel */
    int len = str_length(in);

    for (i = 0; !(is_vowel(in[i])); ++i)
       in[len + i] = in[i];
    firstvowel = i;
    for (i = firstvowel; i < (len + firstvowel); ++i)
        in[i - firstvowel] = in[i];
    in[len] = '\0';
    str_append(in, "ay");
}

/* Tests for a valid string. Returns 0 if invalid. Returns 1 if valid */
int str_test(char in[])
{
    int i;
    char c;
    int vowelexists = 0; /* Switch for ensuring vowel exists */

    for (i = 0; (c = in[i]) != '\n' && c != '\0'; ++i)
        if (is_vowel(c))
            vowelexists = TRUE;
        else if (!(is_consonant(c))) /* there is a non-letter char */
           return 0; 
    if (vowelexists)
        return 1;
}

int main(void)
{
    char word[MAXSTRING];
    int i;

    printf("Word to convert to pig latin: ");
    scanf("%s", word);
    if (!(str_test(word))) {
        printf("Invalid entry\n");
        return 1;
    }
    str_lc(word);
    if (is_vowel(word[0])) {
        str_append(word, "yay");
    } else if (is_consonant(word[0])) {
        consonant_pig(word);
    }
    printf("%s\n", word);
    return 0;
}
