/*
 *    @file     proj1.c
 *    @author   Matej Soroka <xsorok02>
 *    @date     2017-10-25
 *    @brief    1BIT Project 1
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define LOCATION_MAX_LENGTH 100 /* konstanta pre maximalnu dlzku lokality */


/**
 *  Makes character uppercased
 *  @param character
 */
char makeUppercase(char character)
{
    if (character >= 'a' && character <= 'z')
    {
        character = character - ('a' - 'A');
    }
    return character;
}

/**
 *  Makes whole string uppercase
 *  @param string
 */
void strupp(char *string) {
    for (unsigned i = 0; i < strlen(string); i++)
    {
        string[i] = makeUppercase(string[i]);
    }
}

/**
 *  Returns character from line which is one
 *  position after last character from argument
 *  @param line string from database
 *  @param argument argument string
 */
char getEnabledChar(char *argument, char *line)
{
    int len = strlen(argument);
    return line[len];
}

/**
 *  Returns true if string is empty
 *  @param string
 */
bool stringIsNotEmpty(char *line)
{
    return strlen(line) > 1;
}

bool validCharacter(char character)
{
    return (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9') || (character == ' ') || (character == '-') || (character == '.');
}

/**
 *  If length of argument is equal to count
 *  of equal characters from argument and
 *  characters from locality returns true
 *  @param line string from database
 *  @param argument argument string
 */
bool argumentIsValid(char *line, char *argument)
{
    unsigned len = strlen(argument);
    unsigned validCharacters = 0;
    for (size_t i = 0; i < len; i++) {
        if(line[i] == argument[i])
            validCharacters++;
    }
    // if argument length is equal to count of valid characters && locality has same length as argument and locality is not empty string
    if((validCharacters == strlen(line) - 1) && ( strlen(line) - 1 == strlen(argument) ) && stringIsNotEmpty(line))
        printf("Found: %s\n", argument);

    return validCharacters == len;
}

/**
 *  Adds character and null byte to string
 *  @param list simple string
 *  @param character simple character
 */
void addToList(char *list, char character)
{
    if(validCharacter(character))
    {
        int len = strlen(list);

        list[len] = character;
        list[len + 1] = '\0';
    }
}

/**
 *  Sorting string alphabeticly
 *  @param string string which will be sorted
 */
void sort(char *string)
{
    char temp;
    int i, j;
    int n = strlen(string);
    
    for (i = 0; i < n - 1; i++)
    {

        for (j = i + 1; j < n; j++)
        {

            if (string[i] > string[j]) {

                temp = string[i];
                string[i] = string[j];
                string[j] = temp;

            }

        }

    }
}

/**
 *  If we have program arguments, returs true
 *  @param enabled array of enable characters
 *  @param locality string of found locality
 *  @param counter counter of valit locations
*/
void output(char *enabled, char *locality, int counter) {
    if(counter == 0)
    {
        printf("Not found\n");
    }
    else if(counter == 1)
    {
        locality[strlen(locality) - 1] = '\0';
        printf("Found: %s\n", locality);
    }
    else
    {
        char sorted[26] = "\0";

        for (size_t i = 0; i < strlen(enabled); i++) {
            if(strchr(sorted, enabled[i]) == NULL)
            {
                addToList(sorted, enabled[i]);
            }
        }

        sort(sorted);
        printf("Enable: %s\n", sorted);
    }
}

/**
 *  If we have program arguments, returs true
 *  @param argc argument counter
*/
bool haveArgument(int argc)
{
    return argc > 1;
}

/**
 *  if argument has invalid character returns false
 *  @param string argument
*/
bool checkArgument(char *string)
{
    bool valid = true;
    unsigned len = strlen(string);
    for (size_t i = 0; i < len; i++) {
        if(!validCharacter(string[i]))
        {
            valid = false;
        }
    }
    return valid;
}

/* main function */
int main(int argc, char *argv[])
{
    char line[LOCATION_MAX_LENGTH + 1] = "\0";  // iterated line from database
    char locality[LOCATION_MAX_LENGTH + 1] = "\0";  // found location
    char enabled[25] = "\0";                    // list of enabled characters
    unsigned counter = 0;                       // counter of valid locations
    char *argument;

    if(haveArgument(argc))
    {
        argument = argv[1];
        strupp(argument);
        if(!checkArgument(argument))
        {
            fprintf(stderr, "Character contains invalid character\n");
            return -1;
        }
    }
    if(argc > 2)
    {
        fprintf(stderr, "Count of arguments is more than one\n");
        return -1;
    }

/*  db iteration with limit of LOCATION_MAX_LENGTH + NULL byte
    and one byte for checking if line is longer then MAX    */
    while(fgets(line, LOCATION_MAX_LENGTH + 2, stdin))
    {
        strupp(line);
        if(haveArgument(argc))
        {
            if(argumentIsValid(line, argument))
            {
                addToList(enabled, getEnabledChar(argument, line));
                if(!counter)
                    strcat(locality, line);
                counter++;
            }
        }
        else
        {
            addToList(enabled, line[0]); // adds first character to array of enabled characters
            counter++;
        }
    }

    output(enabled, locality, counter);
    return 0;
}