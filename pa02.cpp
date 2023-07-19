#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string readText(string filePath, int checkSumSize);
string getHexString(string text);
int hexToDec(string hex);
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

string getHexString(string text) 
{
    string buffer = "";

    for (int i = 0; i < text.length(); i++) 
    {
        if (int(text[i]) == 0x0a) 
        {
            buffer += "0a";
        }

        else 
        {
            stringstream stream;
            stream << hex << int(text[i]);
            buffer += stream.str();
        }
    }

    return buffer;
}

int hexToDec(string hex) 
{
    int numDigits = hex.length(), dec = 0, buffer = 0;

    for (int i = 0; i < numDigits; i++) 
    {
        if (tolower(hex[i]) >= 'a' && tolower(hex[i]) <= 'f') 
        {
            buffer = tolower(hex[i]) - 'a' + 10;
        }

        else 
        {
            buffer = hex[i] - '0';
        }

        dec = (dec * 16) + buffer;
    }

    return dec;
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
    string hexString = getHexString(text);

    for (int i = 0; i < hexString.length(); i += 2) 
    {
        int buffer = hexToDec(hexString.substr(i, 2));
        addToCheckSum8(checkSum, buffer);
    }

    return checkSum;
}

int checkSum16(string text) 
{
    int checkSum = 0;
    string hexString = getHexString(text);

    for (int i = 0; i < hexString.length(); i += 4) 
    {
        int buffer = hexToDec(hexString.substr(i, 4));
        addToCheckSum16(checkSum, buffer);
    }

    return checkSum;
}

int checkSum32(string text) 
{
    int checkSum = 0;
    string hexString = getHexString(text);

    for (int i = 0; i < hexString.length(); i += 8) 
    {
        int buffer = hexToDec(hexString.substr(i, 8));
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