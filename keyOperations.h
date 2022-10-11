//All operations performed on the key before rounds

//steps of flow:
//key_PermuteC1( original key ) --> shift_key( output,round number) --> key_PermuteC2(output);
	
//Permutation choice 1
string key_PermuteC1(string originalKey)
{
	int PC1[] = { 57, 49, 41, 33, 25, 17, 9,
					1, 58, 50, 42, 34, 26, 18,
					10, 2, 59, 51, 43, 35, 27,
					19,	11,	3, 60, 52, 44, 36,
					63, 55, 47, 39, 31, 23, 15,
					7, 62, 54, 46, 38, 30, 22,
					14, 6, 61, 53, 45, 37, 29,
					21, 13, 5, 28, 20, 12, 4 };

	//the permuted key output : 56 bit
	string PC1_key = "";

	//length of original key : 64 bit
	for (int i = 0; i < 56; i++)
	{
		PC1_key += originalKey[PC1[i]-1];
	}

	return PC1_key;
}

//Permutation choice 2
string key_PermuteC2(string shiftedKey)
{
	int PC2[] =  {  14, 17, 11, 24, 1, 5,
					3, 28, 15, 6, 21, 10,
					23, 19, 12, 4, 26, 8,
					16, 7, 27, 20, 13, 2,
					41, 52, 31, 37, 47, 55,
					30, 40, 51, 45, 33, 48,
					44, 49, 39, 56, 34, 53,
					46, 42, 50, 36, 29, 32 };

	//the permuted key output : 48 bit
	string PC2_key = "";

	//length of shifted key : 56 bit
	for (int i = 0; i < 48; i++)
	{
		PC2_key += shiftedKey[PC2[i] - 1];
	}

	return PC2_key;

}

string shift_halfKey(int shiftNo, string halfKey)
	{
		//start from the nth bit after shift as first bit of new key
		string shiftedKey = "";
		for (int i = shiftNo; i < halfKey.length(); i++)
		{
			shiftedKey += halfKey[i];
		}
		for (int i = 0; i < shiftNo ; i++)
		{
			shiftedKey += halfKey[i];
		}
		return shiftedKey;
	}

	string shift_key(string key , int RoundNo)
	{
		int shift[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
		string leftKey = "";
		string rightKey = "";
		for (int i = 0; i < 28; i++)
		{
			leftKey += key[i];
		}
		for (int i = 28; i < 56; i++)
		{
			rightKey += key[i];
		}
		return shift_halfKey(shift[RoundNo - 1], leftKey) + shift_halfKey(shift[RoundNo - 1], rightKey);

	}
