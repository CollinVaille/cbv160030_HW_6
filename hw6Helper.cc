
//Collin Vaille (cbv160030), CS 3377 Section 501, Homework 6

//This file holds two helpers methods both for string/char array manipulation.

//There's probably an easier way than what I did but I couldn't find one.
//Basically I had trouble getting the number from the binary objects into...
//an acceptable format for the CDK entries and settled on a way that uses...
//char arrays with the bulk of the manipulation of them done in the helper...
//methods below.

#include <hw6.h> //Upper method calls lower one so need lower to be defined ahead of time

#include <cstdio> //For sprintf
#include <cstring> //For strcpy
#include <string> //Used to hold the label parameter of first method

using namespace std; //String uses std

//Sets toSet to be the label + number (and number is in hex if specified)
void setCharArray(char* toSet, string label, int number, bool hexNumber)
{
  //Convert int number to char[] numberHolder
  char numberHolder[15];
  if(hexNumber)
    sprintf(numberHolder, "%X", number);
  else
    sprintf(numberHolder, "%u", number);

  //Convert string label to char* labelHolder
  char* labelHolder = new char[label.length() + 1];
  strcpy(labelHolder, label.c_str());

  //Label + number = toSet (finally sets toSet)
  combineCharArrays(labelHolder, label.length() + 1, numberHolder, 15, toSet);

  //Delete temporary pointers used in method
  delete labelHolder;
}

//returned array = array1 + array2
//lengthX = length of arrayX (excluding null character at end)
void combineCharArrays(char* array1, int length1, char* array2, int length2, char* returnArray)
{
  //Index of next empty space in returnArray
  int nextIndex = 0;

  //Copy over first array
  for(int x = 0; x < length1; x++)
  {
    if(array1[x] == '\0')
      break;
    else
      returnArray[nextIndex++] = array1[x];
  }

  //Copy over second array
  for(int x = 0; x < length2; x++)
  {
    if(array2[x] == '\0')
      break;
    else
      returnArray[nextIndex++] = array2[x];
  }

  //Add null-termination
  returnArray[nextIndex] = '\0';

  //That should be it
}

