/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Farhan Mahbub
| Language: C++
|
| To Compile: g++ -o pa01 pa01.cpp
|
| To Execute: C++ -> ./pa01 kX.txt pX.txt
|             where kX.txt is the keytext file
|             and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Summer 2023
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> getMatrix(string filePath);
string getPlaintext(string filePath, int n);
string matrixMultiply(vector<vector<int>> key, string split);
string encrpyt(vector<vector<int>> key, string plaintext);
void printFormat(vector<vector<int>> key, string plaintext, string ciphertext);

int main(int args, char *argv[]) 
{
    if (args != 3) return 0;
    
    vector<vector<int>> key = getMatrix(argv[1]);
    string plaintext = getPlaintext(argv[2], key.size());
    string ciphertext = encrpyt(key, plaintext);

    printFormat(key, plaintext, ciphertext);

    return 0;
}

vector<vector<int>> getMatrix(string filePath) 
{
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

string getPlaintext(string filePath, int n)
{
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

    while (output.length() % n != 0)
    {
        output += 'x';
    }

    textFile.close();

    return output;
}

string matrixMultiply(vector<vector<int>> key, string split)
{
    int i, j, n = key.size();
    vector<int> word, output;
    string buffer = "";

    for (i = 0; i < n; i++)
    {
        word.push_back(split[i] - 'a');
    }

    for (i = 0; i < n; i++)
    {
        int result = 0;
        for (j = 0; j < n; j++)
        {
            result += key[i][j] * word[j];
        }
        output.push_back(result%26);
    }

    for (i = 0; i < n; i++)
    {
        buffer += char(output[i] + 'a');
    }

    return buffer;
}

string encrpyt(vector<vector<int>> key, string plaintext)
{
    int i, n = key.size(), length = plaintext.length();
    string output = "";

    for (i = 0; i < length; i += n)
    {
        string split = plaintext.substr(i, n);
        output += matrixMultiply(key, split);
    }

    return output;
}

void printFormat(vector<vector<int>> key, string plaintext, string ciphertext) 
{
    int i, j, n = key.size(), countPlain = 0, countCipher = 0;

    cout << endl << "Key matrix:" << endl;

    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            cout << "\t" << key[i][j];
            if (j == n - 1) cout << endl;
        }
    }

    cout << endl << "Plaintext:" << endl;

    for (i = 0; i < plaintext.length(); i++)
    {
        cout << plaintext[i];
        countPlain++;
        if (countPlain % 80 == 0) cout << endl;
    }

    cout << endl << endl << "Ciphertext:" << endl;

    for (i = 0; i < ciphertext.length(); i++)
    {
        cout << ciphertext[i];
        countCipher++;
        if (countCipher % 80 == 0) cout << endl;
    }

    cout << endl;
}

/*=============================================================================
| I Farhan Mahbub (fa203667) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
