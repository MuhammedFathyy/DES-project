#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int SBOX_ROW_SIZE = 16;
const int SBOX_6BIT_SIZE = 64;
using namespace std;

int Initial_Permutation[65] = {0 , 58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 , 60 , 52  , 44 , 36 , 28 , 20 , 12 , 4 , 62 , 54 , 46 , 38 , 30 , 22 , 14 ,
                                6 , 64 , 56 , 48 , 40 , 32 , 24 , 16 , 8 , 57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 , 59 , 51 , 43 , 35 , 27 , 19 , 11 ,
                                3 , 61 , 53 , 45 , 37 , 29 , 21 , 13 , 5 , 63 , 55 , 47 , 39 , 31 , 23 , 15 , 7};

int Inverse_Initial_Permutation[65] = {0 , 40 , 8 , 48 , 16 , 56 , 24 , 64 , 32 , 39 , 7 ,47 , 15 , 55 , 23 , 63 , 31 , 38 , 6 , 46 , 14 , 54 , 22 , 62 ,
                                       30 , 37 , 5 , 45 , 13 , 53 , 21 , 61 , 29 , 36 , 4 , 44 , 12 , 52 , 20 , 60 , 28 ,35 , 3 , 43 , 11 , 51 , 19 , 59 ,
                                       27 , 34 , 2 , 42 , 10 , 50 , 18 , 58 , 26 , 33 , 1 , 41 , 9 , 49 , 17 , 57 , 25};

int Expansion_Permutation[49] = {0 , 32 , 1 , 2 , 3 , 4 , 5 , 4 , 5 , 6 , 7 , 8 , 9 ,  8 , 9 , 10 , 11 , 12 , 13 , 12 , 13 , 14 , 15 , 16 , 17 , 16 , 17 ,
                                 18 , 19 , 20 , 21 , 20 , 21 , 22 , 23 , 24 , 25 , 24 , 25 , 26 , 27 , 28 , 29 , 28 , 29 , 30 , 31 , 32 , 1};

int sbox_table[] = {
        14, 4, 13,  1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0 , 15 , 7 , 4 , 14 , 2 ,  13 , 1 , 10 ,6 , 12 , 11 , 9 , 5 , 3 , 8,
        4 , 1, 14 , 8 , 13 , 6 , 2 , 11 , 15 , 12 , 9 , 7 , 3 , 10 , 5, 0,
        15 , 12 , 8 , 2 , 4, 9, 1, 7, 5, 11 , 3, 14 ,10 , 0 , 6, 13,

        15 , 1, 8 , 14 , 6 , 11 , 3 , 4 , 9 , 7 , 2 , 13 , 12 , 0 , 5 , 10  ,
        3 , 13 , 4 , 7 , 15 , 2 , 8 , 14 , 12 , 0 , 1 , 10 , 6 , 9 , 11 , 5,
        0 , 14 , 7 , 11 , 10 , 4 , 13 , 1 , 5 , 8 , 12 , 6 , 9 , 3 , 2 , 15,
        13 , 8 , 10 , 1 , 3 , 15 , 4 , 2 , 11 , 6 , 7 , 12 , 0 , 5 , 14 , 9,

        10 , 0 , 9, 14 , 6 , 3 , 15 , 5 , 1 , 13 , 12 , 7 , 11 , 4 , 2 , 8,
        13 , 7 , 0 , 9 , 3 , 4 , 6 , 10 , 2 , 8 , 5 , 14 , 12 , 11 , 15 , 1,
        13 , 6 , 4 , 9 , 8 , 15 , 3 , 0 , 11 , 1 , 2 , 12 , 5 , 10 , 14 , 7,
        1 , 10 ,13 , 0 , 6 , 9, 8 , 7, 4 , 15 , 14 , 3 , 11 , 5 , 2 , 12,

        7 , 13 , 14 , 3 , 0 , 6 , 9 , 10 , 1 , 2, 8 , 5 , 11 , 12 , 4 , 15,
        13 , 8 , 11 , 5 , 6 , 15 , 0 , 3 , 4 , 7 , 2 , 12 , 1 , 10 , 14 , 9,
        10 , 6 , 9 , 0 , 12 , 11 , 7 , 13 , 15 , 1 , 3 , 14 , 5 , 2 , 8 , 4,
        3 , 15 , 0 , 6 , 10 , 1 , 13 , 8 , 9 , 4 , 5 , 11 , 12 , 7 , 2 , 14,

        2 , 12 , 4 , 1 , 7 , 10 , 11 , 6 , 8 , 5 , 3 , 15 , 13 , 0 , 14 , 9,
        14 , 11 , 2 , 12 , 4 , 7 , 13 , 1 , 5 , 0 , 15 , 10 , 3 , 9 , 8 , 6,
        4 , 2 , 1 , 11 , 10 , 13 , 7 , 8 , 15 , 9 , 12 , 5 , 6 , 3 , 0 , 14,
        11 , 8 , 12 , 7 , 1 , 14 , 2 , 13 , 6 , 15 , 0 , 9 , 10 , 4 , 5 , 3,

        12 , 1 , 10 , 15 , 9 , 2 , 6 , 8 , 0 , 13 , 3 , 4 , 14 , 7 , 5 , 11,
        10 , 15 , 4 , 2 , 7 , 12 , 9 , 5 , 6 , 1 , 13 , 14 , 0 , 11 , 3 , 8,
        9 , 14 , 15 , 5 , 2 , 8 , 12 , 3 , 7 , 0 , 4 , 10 , 1 , 13 , 11 , 6 ,
        4 , 3 , 2 , 12 , 9 , 5 , 15 , 10 , 11 , 14 , 1 , 7 , 6 , 0 , 8 , 13,

        4 , 11 , 2 , 14 , 15 , 0 , 8 , 13 , 3 , 12 , 9 , 7 , 5 , 10 , 6 , 1,
        13 , 0 , 11 , 7 , 4 , 9 , 1 , 10 , 14 , 3 , 5 , 12 , 2 , 15 , 8 , 6 ,
        1 , 4 , 11 , 13 , 12 , 3 , 7 , 14 , 10 , 15 , 6 , 8 , 0 , 5 , 9 , 2,
        6 , 11 , 13 , 8 , 1 , 4 , 10 , 7 , 9 , 5 , 0 , 15 , 14 , 2 , 3 , 12,

        13 , 2 , 8 , 4 , 6 , 15 , 11 , 1 , 10 , 9 , 3 , 14 , 5 , 0 , 12 , 7,
        1 , 15 , 13 , 8 , 10 , 3 , 7 , 4 , 12 , 5 , 6 , 11 , 0 , 14 , 9 , 2,
        7 , 11 , 4 , 1 , 9 , 12 ,14 , 2 , 0 , 6 , 10 , 13 , 15 , 3 , 5 , 8,
        2 , 1 , 14 , 7 , 4 , 10 , 8 , 13 , 15 , 12 , 9 , 0 , 3 , 5 , 6 , 11
};

string Expansion_Permutation_function (string str)
{
    string output = "";
    for (int i = 1; i <= str.length (); i++)
    {
        int index = Expansion_Permutation[i];
        output += str[index];
    }
    return output;
}

string Initial_Permutation_function (string str)
{
    string output = "";
    for (int i = 1; i <= str.length (); i++)
    {
        int index = Initial_Permutation[i];
        output += str[index];
    }
    return output;

}

string Inverse_Initial_Permutation_function (string str)
{
    string output = "";
    for (int i = 1; i <= str.length (); i++)
    {
        int index = Inverse_Initial_Permutation[i];
        output += str[index];
    }
    return output;

}

string XOR_func (string str, string key)
{
    string output = "";
    for (int i = 1; i <= str.length (); i++)
    {
        output[i] += char (int (str[i]) ^ int (key[i]));
    }

    return output;
}



void convert_string_to_file (string data)
{
    ofstream outputFile ("output.txt");
    outputFile << data;
    outputFile.close ();
}

void convert_file_to_string (string& str)
{
    ifstream myfile;
    myfile.open ("Text.txt");

    if (myfile.is_open ())
    {
        while (myfile)
        {
            string temp;
            myfile >> temp;
            str += temp;
        }
    }


    myfile.close ();

}

string convert_hexa_to_binary (string str)
{
    int i = 0;
    string binaryFile;
    while (str[i] != '\0')
    {
        switch (str[i])
        {

        case '0':
            binaryFile += "0000";
            break;

        case '1':
            binaryFile += "0001";
            break;
        case '2':
            binaryFile += "0010";
            break;
        case '3':
            binaryFile += "0011";
            break;
        case '4':
            binaryFile += "0100";
            break;
        case '5':
            binaryFile += "0101";
            break;
        case '6':
            binaryFile += "0110";
            break;
        case '7':
            binaryFile += "0111";
            break;
        case '8':
            binaryFile += "1000";
            break;
        case '9':
            binaryFile += "1001";
            break;
        case 'A':
        case 'a':
            binaryFile += "1010";
            break;
        case 'B':
        case 'b':
            binaryFile += "1011";
            break;
        case 'C':
        case 'c':
            binaryFile += "1100";
            break;
        case 'D':
        case 'd':
            binaryFile += "1101";
            break;
        case 'E':
        case 'e':
            binaryFile += "1110";
            break;
        case 'F':
        case 'f':
            binaryFile += "1111";
            break;
        }
        i++;
    }

    return binaryFile;
}

string char_hex_to_bin(string str) {
    string binaryFile = "";
    string intr = "";
    int temp = stoi(str);
    while (temp) {
        intr += to_string(temp % 2);
        temp /= 2;
    }

    int sz = intr.size();
    while (sz < 4) {
        binaryFile += "0";
        sz++;
    }

    for (int i = intr.size() - 1; i >= 0; i--)
        binaryFile += intr[i];

    return binaryFile;
}

string sbox (string s)
{
    string output = "";
    string test = "";
    for (int i = 0; i < 8; i++)
    {
        // define a variable to hold the first index of the sbox
        // bin is used to convert the binary to decimal in O(1)
        int f_elem = i * 6, column_indx = 0, bin = 8;
        int row_indx = (int(s[f_elem]) - int('0')) * 2 + (int(s[f_elem + 5]) - int('0'));
        for (int j = 1; j <= 4; j++)
        {
            column_indx += (int(s[f_elem + j]) - int('0')) * bin;
            bin /= 2;
        }
        test += to_string(sbox_table[row_indx * SBOX_ROW_SIZE + i * SBOX_6BIT_SIZE + column_indx]);
        output += char_hex_to_bin(to_string(sbox_table[row_indx * SBOX_ROW_SIZE + i * SBOX_6BIT_SIZE + column_indx]));
    }
    return output;
}

int main ()
{



    string str = "";

    convert_file_to_string (str);
    vector <string> v;

    string binary = convert_hexa_to_binary (str);
    int n = 1;
    int j = 0;
    int index = 0;
    for (int i = 0; i < binary.size (); i = i + 64)
    {
        v.push_back ("");
        for (; j <= n * 63; j++)
        {

            v[index] += binary[j];
        }
        j = n * 63;
        n++;
        index++;
    }

    string initialPermutation;
    for (int i = 0; i < v.size (); i++)
    {
        initialPermutation = Initial_Permutation_function (v[i]);

    }

    convert_string_to_file (initialPermutation);
    cout << initialPermutation;


    return 0;
}