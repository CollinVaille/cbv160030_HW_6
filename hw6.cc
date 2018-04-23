
//Collin Vaille (cbv160030), CS 3377 Section 501, Homework 6

//This is based on the CDK example in the class notes.
//This is the main and only source file for the program. It firsts read in...
//object data from a binary file and then displays that data in a visual...
//matrix. Finally, it waits for user input and exits on any button.

//I could split this into multiple files but the project is short enough to...
//where it's still readable to put it in one place so I just did that.

#include <string> //For char array manipulation to set text of display matrix
#include <cstdint> //For uint32_t and uint64_t
#include <fstream> //For reading in the binary file
#include <iostream> //For waiting on keyboard input to exit and for debugging
#include "cdk.h" //For the display matrix


#define MATRIX_ROWS 5
#define MATRIX_COLUMNS 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

//Used to create char arrays displayed in cdk matrix
//Defined at the very bottom of the file
void combineCharArrays(char*, int, char*, int, char*);

void setCharArray(char*, string, int, bool);

//Definition of the header object
class BinaryFileHeader
{
  public:
   uint32_t magicNumber; //Should be 0xFEEDFACE
   uint32_t versionNumber;
   uint64_t numRecords;
}; //Have to end class names with semicolon in c++

//Defined length of the stringBuffer in the class below
const int maxRecordStringLength = 25;

//Definition of the record object
class BinaryFileRecord
{
  public:
   uint8_t strLength;
   char stringBuffer[maxRecordStringLength];
};

int main()
{
  //---------------------BINARY FILE INPUT PART---------------------------

  //First read in the header record...

  //Create header object
  BinaryFileHeader *header = new BinaryFileHeader();

  //Create binary input stream
  ifstream binaryInput ("cs3377.bin", ios::in | ios::binary);

  //Initialize header to object returned by binary input stream read
  binaryInput.read((char *) header, sizeof(BinaryFileHeader));

  //Close stream
  binaryInput.close();

  //--------------------DISPLAY MATRIX OUTPUT PART------------------------

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"0", "a", "b", "c", "4", "5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_ROWS, MATRIX_COLUMNS, MATRIX_ROWS, MATRIX_COLUMNS,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
  {
    printf("Error creating Matrix\n");
    _exit(1);
  }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  //Enter (the char arrays for) the entries of the matrix...
 
  //Enter magic number at (1, 1)
  char magicArray[24]; //9 for label + 15 for number = 24
  setCharArray(magicArray, "Magic: 0x", header->magicNumber, true);
  setCDKMatrixCell(myMatrix, 1, 1, magicArray);
  
  //Enter the version number at (1, 2)
  char versionArray[24]; //9 for label + 15 for number = 24
  setCharArray(versionArray, "Version: ", header->versionNumber, false);
  setCDKMatrixCell(myMatrix, 1, 2, versionArray);

  //Enter the number of records at (1, 3)
  char numRecordsArray[28]; //13 for label + 15 for number = 28
  setCharArray(numRecordsArray, "Num Records: ", header->numRecords, false);
  setCDKMatrixCell(myMatrix, 1, 3, numRecordsArray);
  
  //Refresh display to show changes
  drawCDKMatrix(myMatrix, true);

  //So we can see results, pause until a key is pressed.
  unsigned char x;
  cin >> x;

  // Clean up screen
  endCDK();
  
  //Clean up the pointers used to hold the header and record objects
  delete header;
}

//-------------------------HELPER METHODS-------------------------------

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

