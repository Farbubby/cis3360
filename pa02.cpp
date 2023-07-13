#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

string readText(string filePath, int checkSumSize);
string getHexString(string text);
int checkSum8(string text);
string checkSum16(string text);
string checkSum32(string text);
int hexToDec(string hex);
void addToCheckSum(int &checkSum, int buffer);
void printFormat(string text, string checksum);

int main(int args, char *argv[]) {
    
    if (args != 3) return 0;

    string filePath = argv[1];
    int checkSumSize = stoi(argv[2]);

    string text = readText(filePath, checkSumSize);

    if (checkSumSize == 8) {

        cout << hex << checkSum8(text) << endl;
        return 1;
    }
    else if (checkSumSize == 16) {
        
        return 1;
    }
    else if (checkSumSize == 32) {
        
        return 1;
    }
    else {
        cerr << "Invalid checksum type" << endl;
        return 0;
    }
}

string readText(string filePath, int checkSumSize) {

    string text;
    ifstream inputFile;

    inputFile.open(filePath);

    if (!inputFile.is_open()) return "";

    while (!inputFile.eof()) {
        string buffer;
        getline(inputFile, buffer);
        text += buffer;
    }

    text += "\n";

    while ((text.length()*8) % checkSumSize != 0) {
        text += "X";
    }

    return text;
}

string getHexString(string text) {

    string buffer = "";

    for (int i = 0; i < text.length(); i++) {
        if (int(text[i]) == 0x0a) {
            buffer += "0a";
        }
        else {
            stringstream stream;
            stream << hex << int(text[i]);
            buffer += stream.str();
        }
    }

    return buffer;
}

int hexToDec(string hex) {

    int numDigits = hex.length();
    int dec = 0;
    int buffer = 0;

    for (int i = 0; i < numDigits; i++) {
        if (tolower(hex[i]) >= 'a' && tolower(hex[i]) <= 'f') {
            buffer = tolower(hex[i]) - 'a' + 10;
        }
        else {
            buffer = hex[i] - '0';
        }
        dec = (dec * 16) + buffer;
    }

    return dec;
}

void addToCheckSum(int &checkSum, int buffer) {
    
    checkSum += buffer;
    checkSum &= 0xff;

}

int checkSum8(string text) {

    int checkSum = 0;
    string hexString = getHexString(text);

    for (int i = 0; i < hexString.length(); i += 2) {

        int buffer = hexToDec(hexString.substr(i, 2));
        addToCheckSum(checkSum, buffer);
    }

    return checkSum;

}