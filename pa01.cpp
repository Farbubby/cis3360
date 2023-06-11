#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> getMatrix(string filePath);
string getPlaintext(string filePath);
string convert(vector<vector<int>> key, string plaintext);

int main(int args, char *argv[]) {

    if (args != 3)
    {
        return 0;
    }
    
    vector<vector<int>> key = getMatrix(argv[1]);
    // string text = getPlaintext(argv[2]);
    convert(key, "no");

    return 0;
}

vector<vector<int>> getMatrix(string filePath) {

    int n, buffer;

    ifstream keyFile;
    keyFile.open(filePath);

    if (!keyFile.is_open()) return vector<vector<int>>(0);

    keyFile >> n;

    vector<vector<int>> matrix;

    for (int i = 0; i < n; i++)
    {
        vector<int> row;
        for (int j = 0; j < n; j++)
        {
            keyFile >> buffer;
            row.push_back(buffer);
        }
        matrix.push_back(row);
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

string convert(vector<vector<int>> key, string plaintext) {

    vector<int> word;
    vector<int> output;
    int result;
    int n = key.size();

    for (int i = 0; i < n; i++)
    {
        word.push_back(plaintext[i] - 'a');
    }

    for (int i = 0; i < n; i++)
    {
        result = 0;
        for (int j = 0; j < n; j++)
        {
            result += key[i][j] * word[j];
        }
        output.push_back(result%26);
    }

    for (int i = 0; i < n; i++)
    {
        cout << char(output[i] + 'a') << " ";
    }

    return "";
}
