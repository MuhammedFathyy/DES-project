#include <iostream>
#include <string>
#include <vector>
#include "permutations.h"
#include "keyoperations.h"
using namespace std;

int main()
{
    string str = "";
    string output = "";
    convert_file_to_string(str);
    //str = "0123456789ABCDEF";
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
        cout << convert_binary_to_hexa("000000010010001101000101011001111000100110101011110011011110111");
        string data = v[i];
        data = Initial_Permutation_function(v[i]);
        string key = convert_hexa_to_binary("0123456789ABCDEF");
        string c1 = key_PermuteC1(key);
        for (int round = 1; round <= 16; round++) {
            string keyround = shift_key(c1, round);
            //we generate the key for every round 
            string c2 = key_PermuteC2(keyround);

            //start each round
            string roundOutput = Round(data, c2);

            //final step before entring the success round
            c1 = keyround;
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
    convert_string_to_file(hexaData);
    return 0;
}
