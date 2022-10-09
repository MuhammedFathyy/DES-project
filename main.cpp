#include <iostream>

using namespace std;

int Initial_Permutation[65] = { 0 , 58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 , 60 , 52  , 44 , 36 , 28 , 20 , 12 , 4 , 62 , 54 , 46 , 38 , 30 , 22 , 14 ,
                                6 , 64 , 56 , 48 , 40 , 32 , 24 , 16 , 8 , 57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 , 59 , 51 , 43 , 35 , 27 , 19 , 11 ,
                                3 , 61 , 53 , 45 , 37 , 29 , 21 , 13 , 5 , 63 , 55 , 47 , 39 , 31 , 23 , 15 , 7};

int Inverse_Initial_Permutation[65] = {0 , 40 , 8 , 48 , 16 , 56 , 24 , 64 , 32 , 39 , 7 ,47 , 15 , 55 , 23 , 63 , 31 , 38 , 6 , 46 , 14 , 54 , 22 , 62 ,
                                       30 , 37 , 5 , 45 , 13 , 53 , 21 , 61 , 29 , 36 , 4 , 44 , 12 , 52 , 20 , 60 , 28 ,35 , 3 , 43 , 11 , 51 , 19 , 59 ,
                                       27 , 34 , 2 , 42 , 10 , 50 , 18 , 58 , 26 , 33 , 1 , 41 , 9 , 49 , 17 , 57 , 25 };

int Expansion_Permutation[49] = {0 , 32 , 1 , 2 , 3 , 4 , 5 , 4 , 5 , 6 , 7 , 8 , 9 ,  8 , 9 , 10 , 11 , 12 , 13 , 12 , 13 , 14 , 15 , 16 , 17 , 16 , 17 ,
                                 18 , 19 , 20 , 21 , 20 , 21 , 22 , 23 , 24 , 25 , 24 , 25 , 26 , 27 , 28 , 29 , 28 , 29 , 30 , 31 , 32 , 1};


string Expansion_Permutation_function(string str)
{
    string output ="";
    for(int i = 1 ; i <= str.length() ; i++)
    {
        int index = Expansion_Permutation[i];
        output += str[index];
    }
    return output;
}

string Initial_Permutation_function(string str)
{
    string output = "";
    for(int i = 1 ; i <= str.length() ; i++)
    {
        int index = Initial_Permutation[i];
        output += str[index];
    }
    return output;

}

string Inverse_Initial_Permutation_function(string str)
{
    string output = "";
    for(int i = 1 ; i <= str.length() ; i++)
    {
        int index = Inverse_Initial_Permutation[i];
        output += str[index];
    }
    return output;

}

string XOR_func(string str , string key)
{
    string output = "";
    for(int i = 1; i <= str.length() ; i++)
    {
        output[i] += char (int(str[i]) ^ int(key[i]));
    }

    return output;
}

int main()
{


    string str;
    string binaryFile;
    cin >> str;

    int i =0;
    while( str[i] != '\0')
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

    return 0;
}