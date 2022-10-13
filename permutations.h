#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

int Initial_Permutation[64] = { 58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 , 60 , 52  , 44 , 36 , 28 , 20 , 12 , 4 , 62 , 54 , 46 , 38 , 30 , 22 , 14 ,
                                6 , 64 , 56 , 48 , 40 , 32 , 24 , 16 , 8 , 57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 , 59 , 51 , 43 , 35 , 27 , 19 , 11 ,
                                3 , 61 , 53 , 45 , 37 , 29 , 21 , 13 , 5 , 63 , 55 , 47 , 39 , 31 , 23 , 15 , 7 };

int Inverse_Initial_Permutation[64] = { 40 , 8 , 48 , 16 , 56 , 24 , 64 , 32 , 39 , 7 ,47 , 15 , 55 , 23 , 63 , 31 , 38 , 6 , 46 , 14 , 54 , 22 , 62 ,
                                       30 , 37 , 5 , 45 , 13 , 53 , 21 , 61 , 29 , 36 , 4 , 44 , 12 , 52 , 20 , 60 , 28 ,35 , 3 , 43 , 11 , 51 , 19 , 59 ,
                                       27 , 34 , 2 , 42 , 10 , 50 , 18 , 58 , 26 , 33 , 1 , 41 , 9 , 49 , 17 , 57 , 25 };

int Expansion_Permutation[48] = { 32 , 1 , 2 , 3 , 4 , 5 , 4 , 5 , 6 , 7 , 8 , 9 ,  8 , 9 , 10 , 11 , 12 , 13 , 12 , 13 , 14 , 15 , 16 , 17 , 16 , 17 ,
                                 18 , 19 , 20 , 21 , 20 , 21 , 22 , 23 , 24 , 25 , 24 , 25 , 26 , 27 , 28 , 29 , 28 , 29 , 30 , 31 , 32 , 1 };


int Permutation[32] = { 16, 7, 20, 21, 29 , 12 ,	28	,17 , 1	, 15 ,	23 , 26 , 5 , 18 ,	31	, 10 ,2 , 8 , 24 , 14 ,	32	, 27 , 3 ,	9 ,19 , 13 , 30 ,	6 , 22 , 11 , 4 , 25 };

string Expansion_Permutation_function(string str)
{
    string output = "";
    for (int i = 0; i < 48; i++)
    {

        output += str[Expansion_Permutation[i] - 1];
    }
    return output;
}

string Initial_Permutation_function(string str)
{
    string output = "";
    for (int i = 0; i < str.length(); i++)
    {

        output += str[Initial_Permutation[i] - 1];
    }
    return output;

}

string Inverse_Initial_Permutation_function(string str)
{
    string output = "";
    for (int i = 0; i < str.length(); i++)
    {

        output += str[Inverse_Initial_Permutation[i] - 1];
    }
    return output;


}

string Permutation_function(string str)
{
    string output = "";
    for (int i = 0; i < str.length(); i++)
    {

        output += str[Permutation[i] - 1];
    }
    return output;


}
string XOR_func(string str, string key)
{
    string output = "";

    for (int i = 0; i < str.length(); i++)
    {

        if (str[i] != key[i]) {
            output += "1";
        }
        else
            output += "0";
    }

    return output;
}



void convert_string_to_file(string data)
{
    ofstream outputFile("output.txt");
    outputFile << data;
    outputFile.close();
}

void convert_file_to_string(string& str) {
    ifstream myfile;
    myfile.open("Text.txt");

    if (myfile.is_open())
    {
        while (myfile)
        {
            string temp;
            myfile >> temp;
            str += temp;
        }
    }


    myfile.close();

}

string convert_hexa_to_binary(string str) {
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


string Round(string data, string roundkey) {
    string left, right = "";

    for (int i = 0; i < (data.size() / 2); i++) {
        left += data[i];

    }


    for (int i = 32; i < data.size(); i++) {
        right += data[i];
    }

    string expansionPerm = Expansion_Permutation_function(right);
    string Xor = XOR_func(expansionPerm, roundkey);

    //sbox implementation
    //string permutation = Permutation_function(sbox);
    //string nextright = XOR_func(permutation, left);
    //string nextleft = right;


    //return  nextleft + nextright;






}



