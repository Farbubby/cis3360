#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int args, char *argv[]) {

    if (args != 3)
    {
        return 0;
    }

    string key {argv[1]};
    //string text {argv[2]};
    string output;
    string buffer;

    ifstream keyFile {key};
    ifstream textFile {};

    //textStream.open(text);

    if (!keyFile.is_open()) return 0;

    while (!keyFile.eof())
    {
        keyFile >> buffer;
        if (keyFile.eof()) break;
        output += buffer;
    }

    cout << output << endl;

    keyFile.close();

    return 0;
}