#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int** getMatrix(string filePath);
string getPlaintext(string filePath);

int main(int args, char *argv[]) {

    if (args != 3)
    {
        return 0;
    }
    
    int** key = getMatrix(argv[1]);
    string text = getPlaintext(argv[2]);

    return 0;
}

int** getMatrix(string filePath) {

    int n;

    ifstream keyFile;
    keyFile.open(filePath);

    if (!keyFile.is_open()) return NULL;

    keyFile >> n;

    int** matrix = new int*[n];

    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            keyFile >> matrix[i][j];
        }
    }

    keyFile.close();

    return matrix;
}

string getPlaintext(string filePath) {
    string output;
    char buffer;

    ifstream textFile;
    textFile.open(filePath);

    if (!textFile.is_open()) return "";

    while (!textFile.eof())
    {
        textFile.get(buffer);

        if (textFile.eof()) break;

        if (isalpha(buffer)) {
            buffer = tolower(buffer);
            output += buffer;
        }
    }

    textFile.close();

    return output;
}
