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
| Due Date: 6/23/23
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
    // Ensures correct number of arguments
    if (args != 3) return 0;
    
    vector<vector<int>> key = getMatrix(argv[1]);
    string plaintext = getPlaintext(argv[2], key.size());
    string ciphertext = encrpyt(key, plaintext);

    printFormat(key, plaintext, ciphertext);

    return 0;
}

vector<vector<int>> getMatrix(string filePath) 
{
    int i, j, n, buffer;

    ifstream keyFile;
    keyFile.open(filePath);

    if (!keyFile.is_open()) return vector<vector<int>>(0);

    // Gets matrix dimension for n x n matrix
    keyFile >> n;

    vector<vector<int>> matrix;

    for (i = 0; i < n; i++)
    {
        vector<int> row;
        // Gets n numbers for each row
        for (j = 0; j < n; j++)
        {
            keyFile >> buffer;
            row.push_back(buffer);
        }
        // Row is complete and pushes to matrix
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

    // Checks if file is open
    if (!textFile.is_open()) return "";

    while (!textFile.eof())
    {
        // Get next character
        textFile.get(buffer);

        // Checks if end of file
        if (textFile.eof()) break;

        // Only adds to output if character is a letter and lowercase it
        if (isalpha(buffer)) {
            buffer = tolower(buffer);
            output += buffer;
        }
    }

    // Adds padding if necessary
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

    // Converts string to 1D vector of integers
    for (i = 0; i < n; i++)
    {
        word.push_back(split[i] - 'a');
    }

    // Multiplies key matrix with word vector with matrix multiplication
    for (i = 0; i < n; i++)
    {
        int result = 0;
        for (j = 0; j < n; j++)
        {
            result += key[i][j] * word[j];
        }
        output.push_back(result%26);
    }

    // Adds result as characters to buffer
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

    // Splits plaintext into n length substrings and encrypts each substring
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

    // Prints key matrix
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            cout << "\t" << key[i][j];
            if (j == n - 1) cout << endl;
        }
    }

    cout << endl << "Plaintext:" << endl;

    // Prints plaintext
    for (i = 0; i < plaintext.length(); i++)
    {
        cout << plaintext[i];
        countPlain++;
        if (countPlain % 80 == 0) cout << endl;
    }

    cout << endl << endl << "Ciphertext:" << endl;

    // Prints ciphertext
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
