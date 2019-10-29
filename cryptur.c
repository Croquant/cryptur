/*
 * FILE:	"cryptur.h"
 * AUTHOR:	Maxime Desmet Vanden Stock
 * LICENSE:	MIT
 */

#include <stdio.h>
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

int main( int argc, const char* argv[] )
{
	bool hundredone[] = { 1, 1, 1, 1, 0, 1, 1, 0, 0 };
	bool fileKey[] =    { 1, 0, 1, 0, 1, 0, 1, 0, 1 };
	
	bool* writeKey = addKeys( hundredone, fileKey );

	printf( "%s - %d\n", keyString( hundredone ), keyInt( hundredone ) );
	printf( "%s - %d\n", keyString( fileKey ), keyInt( fileKey ) );
	printf( "%s - %d\n", keyString( writeKey ), keyInt( writeKey ) );

	return 0;
}
