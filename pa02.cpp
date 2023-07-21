/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
|             checksum on an ASCII input file
|
| Author: Farhan Mahbub
| Language: C++
|
| To Compile: g++ -o pa02 pa02.cpp
|
| To Execute: C++ -> ./pa02 inputFile.txt 8
|             where inputFile.txt is an ASCII input file
|             and the number 8 could also be 16 or 32
|             which are the valid checksum sizes, all
|             other values are rejected with an error message
|             and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Summer 2023
| Instructor: McAlpin
| Due Date: 7/23/23
|
+=============================================================================*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string readText(string filePath, int checkSumSize);
int blockNumber(string hex);
void addToCheckSum8(int &checkSum, int buffer);
void addToCheckSum16(int &checkSum, int buffer);
void addToCheckSum32(int &checkSum, int buffer);
int checkSum8(string text);
int checkSum16(string text);
int checkSum32(string text);
void printFormat(string text, int checkSumSize);

int main(int args, char *argv[]) 
{
    if (args != 3) return 0;

    string filePath = argv[1];
    int checkSumSize = stoi(argv[2]);

    if (checkSumSize != 8 && checkSumSize != 16 && checkSumSize != 32) 
    {
        cerr << "Valid checksum sizes are 8, 16, or 32" << endl;
        return 0;
    }

    string text = readText(filePath, checkSumSize);
    
    printFormat(text, checkSumSize);
}

string readText(string filePath, int checkSumSize) 
{
    string text;
    ifstream inputFile;

    inputFile.open(filePath);

    if (!inputFile.is_open()) return "";

    while (!inputFile.eof()) 
    {
        string buffer;
        getline(inputFile, buffer);
        text += buffer;
    }

    text += "\n";

    while ((text.length()*8) % checkSumSize != 0) 
    {
        text += "X";
    }

    return text;
}

int blockNumber(string subString) 
{
    int num = 0;

    for (int i = 0; i < subString.length(); i++) 
    {
        num += subString[i];
        if (i != subString.length() - 1) num <<= 8;
    }

    return num;
}

void addToCheckSum8(int &checkSum, int buffer) 
{    
    checkSum += buffer;
    checkSum &= 0xff;
}

void addToCheckSum16(int &checkSum, int buffer) 
{
    checkSum += buffer;
    checkSum &= 0xffff;
}

void addToCheckSum32(int &checkSum, int buffer) 
{ 
    checkSum += buffer;
    checkSum &= 0xffffffff;
}

int checkSum8(string text) 
{
    int checkSum = 0;

    for (int i = 0; i < text.length(); i++) 
    {
        int buffer = blockNumber(text.substr(i, 1));
        addToCheckSum8(checkSum, buffer);
    }

    return checkSum;
}

int checkSum16(string text) 
{
    int checkSum = 0;

    for (int i = 0; i < text.length(); i += 2) 
    {
        int buffer = blockNumber(text.substr(i, 2));
        addToCheckSum16(checkSum, buffer);
    }

    return checkSum;
}

int checkSum32(string text) 
{
    int checkSum = 0;

    for (int i = 0; i < text.length(); i += 4) 
    {
        int buffer = blockNumber(text.substr(i, 4));
        addToCheckSum32(checkSum, buffer);
    }

    return checkSum;
}

void printFormat(string text, int checkSumSize) 
{
    int checkSum = 0, count = 0;
    string checkSumString;
    stringstream stream;

    if (checkSumSize == 8) 
    {
        checkSum = checkSum8(text);
    }

    else if (checkSumSize == 16) 
    {
        checkSum = checkSum16(text);
    }

    else if (checkSumSize == 32) 
    {
        checkSum = checkSum32(text);
    }

    stream << hex << checkSum;
    checkSumString = stream.str();

    cout << endl;

    for (int i = 0; i < text.length(); i++) 
    {
        cout << text[i];
        count++;

        if (count % 80 == 0) 
        {
            cout << endl;
        }
    }

    cout << endl;
    cout << checkSumSize << " bit checksum is " << checkSumString << " for all " << text.length() << " chars" << endl;
}

/*=============================================================================
| I Farhan Mahbub (fa203667) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+============================================================================*/