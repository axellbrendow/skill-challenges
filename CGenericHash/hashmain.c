#include <stdio.h>
#include <string.h>

// #define HashType char			// CARACTERES
// #define EMPTY '*'
#define HashType char*		// STRINGS
#define EMPTY "*"

#include "hash.c"

// Classe Principal

int myHashFunction(HashType elem)
{
	int len = strlen(elem);
	int num = 0;
	
	for (int i = 0; i < len; i++)
	{
		num += elem[i] * 31;
	}
	
	return ( num < 0 ? -num : num ); // PARA STRINGS
	// return elem * 31; // PARA INTEIROS E CARACTERES
}

void myPrintElemFunction(HashType elem)
{
	printf("'%s'\n", elem);
}

int main()
{
	Hash hash = *newHash(10, myHashFunction, myPrintElemFunction);
	
	// hash.add(7);
	// hash.add(5);
	// hash.add(7);
	// hash.add(22);
	// hash.add(14);
	// hash.add(0);
	// hash.add('a');
	// hash.add('b');
	// hash.add('c');
	// hash.add('d');
	// hash.add('e');
	// hash.add('7');
	hash.add("Holly");
	hash.add("Shit");
	hash.add("This");
	hash.add("Is");
	hash.add("Really");
	hash.add("Amazing");
	hash.add("Yeahh!!!");
	hash.print();
	hash.free();

	return 0;
}
