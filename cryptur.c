/*
 * FILE:	"cryptur.h"
 * AUTHOR:	Maxime Desmet Vanden Stock
 * LICENSE:	MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define KEYLENGTH 9

char* keyString( bool key[] )
{
	static char str[KEYLENGTH];
	
	for (int i = 0; i < KEYLENGTH; i++) {
		if (key[i] == 1) {
			str[i] = '#';
		}
		else {
			str[i] = '.';
		}
	}
	
	return str;
}

int keyInt( bool key[] )
{
	int total = 0;
	int pow = 1;

	for (int i = 0; i < KEYLENGTH; i++) {
		if (key[i] == 1) {
			total += pow;
		}
		pow *= 2;
	}
	return total;
}

bool addBool( bool a, bool b)
{
	if (a == 1 && b == 1) {
		return 0;
	}
	else if ((a == 1 && b == 0) || (a == 0 && b == 1)) {
		return 1;
	}
	else {
		return 0;
	}
}

bool* addKeys( bool first[], bool second[] )
{
	static bool r[KEYLENGTH];

	for (int i = 0; i < KEYLENGTH; i++) {
		r[i] = addBool( first[i], second[i] );
	}

	return r;
}

bool* intToKey( int n )
{
	bool temp[KEYLENGTH];
	static bool r[KEYLENGTH];
	int k;
	int i = 0;
	for (int c = 8; c >= 0; c--) {
		k = n >> c;

		if (k & 1) {
			temp[i] = 1;
		}
		else {
			temp[i] = 0;
		}
		i++;
	}
	i = 0;
	for (int n = KEYLENGTH - 1; n >= 0; n--) {
		r[i] = temp[n];
		i++;
	}
	return r;
}

int range( int n )
{
	return abs(n) % 512;
}

int main( int argc, const char* argv[] )
{
	bool hundredone[] = { 1, 1, 1, 1, 0, 1, 1, 0, 0 };
	int input;
	if (argc > 1) {
		input = range(atoi(argv[1]));
	}
	else {
		input = 0;
	}
	bool* userKey = intToKey(input);
	bool* writeKey = addKeys( hundredone, userKey );
	printf("%s", keyString(writeKey));
	char shift[3];
	sprintf(shift, "%d", keyInt(writeKey));
	if (argc > 2) {
		int s = 0;
		for (int i = 0; argv[2][i] != '\0'; ++i) {
			int add = shift[s] - '0';
			printf("%c", argv[2][i] + add);
			s = (s + 1) % 3;
		}
	}

	printf("\n");
	return 0;
}
