#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int mod(int a, int b)
{
	return (a % b + b) % b;
}

char** create2DArray(int rowCount, int colCount) {
	char** arr = (char**) malloc(rowCount);

	for (int i = 0; i < rowCount; ++i)
		arr[i] = (char*) malloc(colCount);

	return arr;
}

char* toUpper(char* str) {
	int strLen = strlen(str);
	char* output = (char*)malloc(strLen + 1);

	for (int i = 0; i < strLen; ++i)
		output[i] = toupper(str[i]);

	output[strLen] = '\0';
	return output;
}

char* getSubString(char* str, int index, int count) {
	int strLen = strlen(str);
	int lastIndex = index + count;

	if (index >= 0 && lastIndex > strLen) return "";

	char* subStr = (char*)malloc(count + 1);

	for (int i = 0; i < count; i++) {
		subStr[i] = str[index + i];
	}

	subStr[count] = '\0';

	return subStr;
}

char* appendString(const char* str1, const char* str2) {
	int str1Len = strlen(str1);
	int str2Len = strlen(str2);
	int strLen = str1Len + str2Len + 1;
	char* str = (char*)malloc(strLen);

	for (int i = 0; i < str1Len; i++)
		str[i] = str1[i];

	for (int i = 0; i < str2Len; i++)
		str[(str1Len + i)] = str2[i];

	str[strLen - 1] = '\0';

	return str;
}

char* removeString(char* str, int index, int count) {
	int strLen = strlen(str);
	int lastIndex = index + count;

	char* s = getSubString(str, 0, index);
	s = appendString(s, getSubString(str, lastIndex, strLen - lastIndex));

	return s;
}

char* insertString(char* str, int index, char* subStr) {
	char* s = getSubString(str, 0, index);
	s = appendString(s, subStr);
	s = appendString(s, getSubString(str, index, strlen(str) - index));

	return s;
}

char* removeChar(char* str, char ch) {
	char* output = str;

	for (int i = 0; i < strlen(output); ++i)
		if (output[i] == ch)
			output = removeString(output, i, 1);

	return output;
}

int* addItemInArray(int* arr, int count, int item) {
	int* newArr = (int*)malloc(sizeof(int) * (count + 1));

	for (int i = 0; i < count; ++i) {
		newArr[i] = arr[i];
	}

	newArr[count] = item;

	return newArr;
}

int* findAllOccurrences(char* str, char value, int* count)
{
	int* indexes = (int*)malloc(sizeof(int));
	char *tmp = str;
	*count = 0;

	tmp = strchr(tmp, value);
	while (tmp != NULL) {
		indexes = addItemInArray(indexes, *count, (tmp - str));
		++(*count);
		tmp = strchr(tmp + 1, value);
	}

	return indexes;
}

char* removeAllDuplicates(char* str, int* indexes, int count)
{
	char* retVal = str;

	for (int i = count - 1; i >= 1; i--)
		retVal = removeString(retVal, indexes[i], 1);

	return retVal;
}

char** generateKeySquare(char* key)
{
	char** keySquare = create2DArray(5, 5);
	char* defaultKeySquare = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	char* tempKey = (strlen(key) <= 0) ? "CIPHER" : toUpper(key);

	tempKey = removeChar(tempKey, 'J');
	tempKey = appendString(tempKey, defaultKeySquare);

	for (int i = 0; i < 25; ++i)
	{
		int count = 0;
		int* indexes = findAllOccurrences(tempKey, defaultKeySquare[i], &count);
		tempKey = removeAllDuplicates(tempKey, indexes, count);
	}

	tempKey = getSubString(tempKey, 0, 25);

	for (int i = 0; i < 25; ++i)
		keySquare[(i / 5)][(i % 5)] = tempKey[i];

	return keySquare;
}

void getPosition(char** keySquare, char ch, int* row, int* col)
{
	if (ch == 'J')
		getPosition(keySquare, 'I', row, col);

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			if (keySquare[i][j] == ch)
			{
				*row = i;
				*col = j;
				return;
			}
}

char* sameRow(char** keySquare, int row, int col1, int col2, int encipher)
{
	char* output = (char*)malloc(3);
	output[0] = keySquare[row][mod((col1 + encipher), 5)];
	output[1] = keySquare[row][mod((col2 + encipher), 5)];
	output[2] = '\0';
	return output;
}

char* sameColumn(char** keySquare, int col, int row1, int row2, int encipher)
{
	char* output = (char*)malloc(3);
	output[0] = keySquare[mod((row1 + encipher), 5)][col];
	output[1] = keySquare[mod((row2 + encipher), 5)][col];
	output[2] = '\0';
	return output;
}

char* sameRowColumn(char** keySquare, int row, int col, int encipher)
{
	char* output = (char*)malloc(3);
	output[0] = keySquare[mod((row + encipher), 5)][mod((col + encipher), 5)];
	output[1] = keySquare[mod((row + encipher), 5)][mod((col + encipher), 5)];
	output[2] = '\0';
	return output;
}

char* differentRowColumn(char** keySquare, int row1, int col1, int row2, int col2)
{
	char* output = (char*)malloc(3);
	output[0] = keySquare[row1][col2];
	output[1] = keySquare[row2][col1];
	output[2] = '\0';
	return output;
}

char* removeOtherChars(char* input)
{
	char* output = input;
	int strLen = strlen(input);

	for (int i = 0; i < strLen; ++i)
		if (output[i] != '\0' && !isalpha(output[i]))
			output = removeString(output, i, 1);

	return output;
}

char* adjustOutput(char* input, char* output)
{
	char* retVal = output;
	int strLen = strlen(input);

	for (int i = 0; i < strLen; ++i)
	{
		if (!isalpha(input[i])) {
			char s[2] = { input[i], '\0' };
			retVal = insertString(retVal, i, s);
		}

		if (islower(input[i]))
			retVal[i] = tolower(retVal[i]);
	}

	return retVal;
}

char* cipher(char* input, char* key, bool encipher)
{
	char* retVal = "";
	char** keySquare = generateKeySquare(key);
	char* tempInput = removeOtherChars(input);
	int e = encipher ? 1 : -1;
	int tempInputLen = strlen(tempInput);

	if ((tempInputLen % 2) != 0)
		tempInput = appendString(tempInput, "X");

	for (int i = 0; i < tempInputLen; i += 2)
	{
		int row1 = 0;
		int col1 = 0;
		int row2 = 0;
		int col2 = 0;

		getPosition(keySquare, toupper(tempInput[i]), &row1, &col1);
		getPosition(keySquare, toupper(tempInput[i + 1]), &row2, &col2);

		if (row1 == row2 && col1 == col2)
		{
			retVal = appendString(retVal, sameRowColumn(keySquare, row1, col1, e));
		}
		else if (row1 == row2)
		{
			char* a = sameRow(keySquare, row1, col1, col2, e);
			retVal = appendString(retVal, a);
		}
		else if (col1 == col2)
		{
			retVal = appendString(retVal, sameColumn(keySquare, col1, row1, row2, e));
		}
		else
		{
			retVal = appendString(retVal, differentRowColumn(keySquare, row1, col1, row2, col2));
		}
	}

	retVal = adjustOutput(input, retVal);

	return retVal;
}

char* encipher(char* input, char* key)
{
	return cipher(input, key, true);
}

char* decipher(char* input, char* key)
{
	return cipher(input, key, false);
}

int main()
{
    char* text = "Hello World";
    char* cipherText = encipher(text, "cipher");
    char* plainText = decipher(cipherText, "cipher");

    return 0;
}
