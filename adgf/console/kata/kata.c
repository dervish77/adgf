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

  // for each letter in string
  for (int i = 0; i < length; i++)
  {
    // copy current input letter to current output letter
    output[length - i - 1] = *input++;
  }
}


void ReverseStringInPlace( char *input )
{
  int length = strlen(input);

  char *startPtr;
  char *endPtr;
  char temp;

  // initialize head and tail ptrs
  startPtr = input;
  endPtr = input + length - 1;

  // while tail ptr is greater than head ptr
  while (endPtr > startPtr)
  {
    // swap current head and tail values
    temp = *endPtr;
    *endPtr = *startPtr;
    *startPtr = temp;
    // advance head and tail pointers
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
    // compute nth power for the nth number
    power = pow(nums[n-1], n);
  }

  return power;
}


int IsVowel(char letter)
{
  switch (letter | 0x20)  // force letter to upper case
  {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      return 1;  // yes it's a vowel
    default:
      return 0;  // no, it's not a vowel
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


int FindLongSeq(int numList[], int length)
{
  int count = 0;
  int longest = 0;

  for (int i = 0; i < length; i++)
  {
    if ( (numList[i]+1) == numList[i+1] )
    {
      count++;
    }
    else
    {
      if (count > longest)
      {
        longest = count;
      }
      count = 0;
    }
  }

  return longest;
}



#define ELEMENT 5
int posfun(int *numlist, int length, int position)
{
  int value = -1;

  if (position <= length)
  {
    value = numlist[position-1];
  }
  
  return value;
}


#define TO_UPPER(c) (c & 0xDF)
#define TO_LOWER(c) (c | 0x20)
char *Accum(char *input)
{
  size_t length = strlen(input);
  char *buffer = malloc(length * length);
  char *output;

  // save start of output buffer
  output = buffer;

  // for each character of input string
  for (int n=0; n < length; n++)
  {
    char c = input[n];
    
    // copy input character to output string 'n' times where first one is upper case 
    // and remaining are lower case
    for (int i=0; i < (n+1); i++)
    {
      if (i == 0)
        *buffer++ = TO_UPPER(c);
      else
        *buffer++ = TO_LOWER(c);
    }

    *buffer++ = '-';
  }

  // remove last '-' character
  buffer--;
  *buffer = 0;

  return output;
}


// External function to be called by main()
//
void kata(int number)
{
  printf("Kata %d\n", number);

  switch(number)
  {
    case 1:
      // Write a C program function "swapByteNibble()" to swap the nibbles
      // in a byte.
      {
        char input = 0x12;
        char output;
        output = SwapNibble(input);
        printf("input was 0x%x - result is 0x%x\n", input, output);
      }
      break;
    case 2:
      // Implement the function "RevString()" as given in below prototype
      // to reverse the input string.
      {
        char *input = "Reverse";
        char *output = malloc(strlen(input)+1);
        ReverseString(input, output);
        printf("input was %s - result was %s\n", input, output);
      }
      break;
    case 3:
      // Same as above, but perform reverse string in place
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
      // Calculate the nth power of the nth item in the array,
      // return -1 if n is greater than the number of elements in the array
      {
        int numarray[] = { 1, 2, 3, 4, 5, 6 };
        int length = sizeof(numarray) / sizeof(numarray[0]);
        int index = 3;
        int power = NPower(numarray, length, index);
        printf("index was %d - power is %d\n", index, power);
      }
      break;
    case 5:
      // Write function to count the vowels in a string
      {
        char string[] = "Another test string";
        int count = 0;
        count = VowelCount(string);
        printf("string was %s - count is %d\n", string, count);
      }
      break;
    case 6:
      // Write a C program "find_long_seq" to find and return the length of the
      // longest sequence of consecutive elements in the given array.
      {
        int seqList[] = {0,2,3,8,9,10,11,12,18,19,20,21,22,23,24};
        int elements = sizeof(seqList)/sizeof(seqList[0]);
        unsigned int len;
        len = FindLongSeq(seqList, elements);
        printf("The longest sequence is of length %d\n",len);
      }
      break;
    case 7:
      // Write a C program function to return the Nth element of an array using
      // pointer to a function.
      {
        int arrList[9] = {11,22,33,44,55,66,77,88,99};
	      int length = sizeof(arrList) / sizeof(arrList[0]);
        // define pointer to function 'posfun'
        int (*posfun_ptr)(int[],int,int);
        posfun_ptr = &posfun;
        // call 'posfun' via the function pointer
        int posValue = (*posfun_ptr)(arrList, length, ELEMENT);
      	printf("Value at position %d = %d\n",ELEMENT,posValue);
      }
      break;
    case 8:
      // Write a function 'accum()' that performs the following examples:
      //   accum("abcd") -> "A-Bb-Ccc-Dddd"
      //   accum("RqaEzty") -> "R-Qq-Aaa-Eeee-Zzzzz-Tttttt-Yyyyyyy"
      //   accum("cwAt") -> "C-Ww-Aaa-Tttt"
      // The parameter of accum is a string which includes only letters from a..z and A..Z
      {
	char *output;
	output = Accum("HelLo");
	printf("Accum output is %s\n", output);
      }
      break;
    case 99:
      {

      }
      break;
    default:
      printf("Unknown kata specified\n");
      break;
  }
}

/* end of kata.c */
