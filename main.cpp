#include <iostream>
#include <string>
#include <vector>
#include "permutations.h"
#include "keyoperations.h"
using namespace std;

void Encrypt()
{
    string str = "";
    string output = "";
    convert_file_to_string(str , "Text.txt");
    vector <string> v;

    string binary = convert_hexa_to_binary(str);
    int j = 0;
    int index = 0;
    for (int i = 0; i < binary.size(); i = i + 64) {
        v.push_back("");
        for (; j < i + 64; j++) {

            v[index] += binary[j];
        }
        index++;
    }
    string hexaData = "";

    string initialPermutation;

    for (int i = 0; i < v.size(); i++) {
        string data = v[i];
        data = Initial_Permutation_function(v[i]);
        vector <string> keys;
        keys = generateKeys(keys);

        for (int round = 1; round <= 16; round++) {
            //start each round
            string roundOutput = Round(data, keys[round-1]);

            //final step before entring the success round
            data = roundOutput;
        }
        string dataLeft, dataRight;
        for (int i = 0; i < 32; i++)
        {
            dataLeft += data[i];
        }
        for (int i = 32; i < 64; i++)
        {
            dataRight += data[i];
        }
        //reverse data last time
        string finaloutput = dataRight + dataLeft;
        output = Inverse_Initial_Permutation_function(finaloutput);
        hexaData += convert_binary_to_hexa(output);
    }
    convert_string_to_file(hexaData , "Encryption.txt");
}

void Decrypt()
{
    string str = "";
    string output = "";
    convert_file_to_string(str , "Encryption.txt");
    //str = "85E813540F0AB405";
    vector <string> v;

    string binary = convert_hexa_to_binary(str);
    int j = 0;
    int index = 0;
    for (int i = 0; i < binary.size(); i = i + 64) {
        v.push_back("");
        for (; j < i + 64; j++) {

            v[index] += binary[j];
        }
        index++;
    }
    string hexaData = "";

    string initialPermutation;

    for (int i = 0; i < v.size(); i++) {
        string data = v[i];
        data = Initial_Permutation_function(v[i]);
        vector <string> keys;
        keys = generateKeys(keys);
        
        for (int round = 1; round <= 16; round++) {
            //start each round
            string roundOutput = Round(data, keys[16-round]);

            //final step before entring the success round
            data = roundOutput;
        }
        string dataLeft, dataRight;
        for (int i = 0; i < 32; i++)
        {
            dataLeft += data[i];
        }
        for (int i = 32; i < 64; i++)
        {
            dataRight += data[i];
        }
        //reverse data last time
        string finaloutput = dataRight + dataLeft;
        output = Inverse_Initial_Permutation_function(finaloutput);
        hexaData += convert_binary_to_hexa(output);
    }
    convert_string_to_file(hexaData , "Decryption.txt");
}

int main()
{
    Encrypt();
    Decrypt();
    return 0;

}
