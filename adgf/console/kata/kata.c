/*****************************************************************************
 *
 *	Kata - programming exercises
 *
 *	File:	kata.c
 *
 *	Author: Brian Lingard
 *
 *	Date:	01/15/2021
 *
 *	Revs:
 *	  0.0 	01/15/2021  originated
 *
 *	Usage:	soundex [surname string]
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "kata.h"


#define DEBUG


// Local functions to be called by kata()
//

char SwapNibble( char num )
{
  char result = 0;

  result = ( num << 4) | ( (num & 0xF0) >> 4);

  return result;
}

void ReverseString( char *input, char *output )
{
  int length = strlen(input);
  char *buffer = malloc(strlen(input)+1);

  for (int i = 0; i < length; i++)
  {
    buffer[length - i - 1] = *input++;
  }

  strcpy(output, buffer);
}

void ReverseStringInPlace( char *input )
{
  int length = strlen(input);

  char *startPtr;
  char *endPtr;
  char temp;

  startPtr = input;
  endPtr = input + length - 1;

  while (endPtr > startPtr)
  {
    //printf("start is %c - end is %c\n", *startPtr, *endPtr);
    temp = *endPtr;
    *endPtr = *startPtr;
    *startPtr = temp;
    startPtr++;
    endPtr--;
  }
}

int NPower(int nums[], int len, int n)
{
  int power = -1;  // default power is -1

  // if index is less than or equal to length of array
  if ( n <= len )
  {
    // compute x^n power for the nth number
    power = pow(nums[n-1], n);
  }

  return power;
}

int IsVowel(char letter)
{
  switch (letter | 0x20)  // force to upper case
  {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      return 1;
    default:
      return 0;
  }
}
int VowelCount(char *str)
{
  int vowels = 0;

  // for all letters in the string, count the vowels
  for (int i = 0; i < strlen(str); i++)
  {
    if (IsVowel(str[i]))
    {
      vowels++;
    }
  }

  return vowels;
}


// External function to be called by main()
//
void kata(int number)
{
  printf("Kata %d\n", number);

  switch(number)
  {
    case 1:
      {
        char input = 0x12;
        char output;
        output = SwapNibble(input);
        printf("input was 0x%x - result is 0x%x\n", input, output);
      }
      break;
    case 2:
      {
        char *input = "Reverse";
        char *output = malloc(strlen(input)+1);
        ReverseString(input, output);
        printf("input was %s - result was %s\n", input, output);
      }
      break;
    case 3:
      {
        char *input = "Reverse";
        char inString[10];
        strcpy(inString, input);
        printf("input was %s\n", inString);
        ReverseStringInPlace(inString);
        printf("result is %s\n", inString);
      }
      break;
    case 4:
      {
        int numarray[] = { 1, 2, 3, 4, 5, 6 };
        int length = sizeof(numarray) / sizeof(numarray[0]);
        int index = 3;
        int power = NPower(numarray, length, index);
        printf("index was %d - power is %d\n", index, power);
      }
      break;
    case 5:
      {
        char string[] = "Another test string";
        int count = 0;
        count = VowelCount(string);
        printf("string was %s - count is %d\n", string, count);
      }
      break;
    case 99:
      {

      }
      break;
    default:
      break;
  }
}

/* end of kata.c */