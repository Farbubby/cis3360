#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string readText(string filePath);
// string checkSum8(string text);
// string checkSum16(string text);
// string checkSum32(string text);

int main(int args, char *argv[]) {
    
    if (args != 3) return 0;

    string text = readText(argv[1]);

    if (stoi(argv[2]) == 8) {
        //checkSum8(text);
        return 0;
    }
    else if (stoi(argv[2]) == 16)
        //checkSum16(text);
        return 1;
    else if (stoi(argv[2]) == 32)
        //checkSum32(text);
        return 1;
    else
        cerr << "Invalid checksum type" << endl;
}

string readText(string filePath) {

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

    return text;
}