
//Collin Vaille (cbv160030), CS 3377 Section 501, Homework 6

//This file contains the definitions of two functions that are both defined...
//in hw6Helper.cc. Their purpose is to simplify and automate the process...
//of char array manuipulation used to set the contents of the matrix entries.

#include <string> //Use string object in function header

//Sets toSet to be label + number
void setCharArray(char* toSet, std::string label, int number, bool hexNumber);

//Sets returnArray to be array1 + array2
void combineCharArrays(char* array1, int length1, char* array2, int length2, char* returnArray);
