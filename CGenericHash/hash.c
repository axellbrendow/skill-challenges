#include <stdlib.h>

#ifndef HashType
	#define HashType int
#endif

#ifndef EMPTY
	#define EMPTY -2147483647
#endif

typedef struct Hash Hash;

// sintaxe de ponteiro de função -> <tipo_retorno> (*<nome_do_ponteiro>)(<param1?>, ...)
typedef void (*VoidVoidFunc)(void);
typedef void (*VoidHashTypeFunc)(HashType);
typedef int (*IntHashTypeFunc)(HashType);
typedef HashType (*HashTypeIntFunc)(int);

struct Hash
{
	HashType			*table;
	int					tableSize;
	IntHashTypeFunc		hash;		// recebe um elemento e realiza hash(elemento) gerando a posição dele
	HashTypeIntFunc		get;		// obtém um elemento num certo índice da hash
	VoidHashTypeFunc	add;		// adiciona um elemento à hash
	VoidHashTypeFunc	printElem;	// printa um elemento qualquer da hash
	VoidVoidFunc		print;		// printa a hash
	VoidVoidFunc		free;		// libera as memórias que a hash tenha alocado
} *this;

HashType hash_get(int index)
{
	return this->table[index];
}

void hash_add(HashType elem)
{
	int index = this->hash(elem);
	index = ( index < 0 ? -index : index );
	index = index % this->tableSize;
	
	if (this->table[index] == EMPTY)
	{
		this->table[index] = elem;
	}
}

void hash_print()
{
	for (int i = 0; i < this->tableSize; i++)
	{
		this->printElem( this->get(i) );
	}
}

void hash_free()
{
	free(this->table);
	free(this);
}

Hash *newHash(int tableSize, IntHashTypeFunc hashFunction, VoidHashTypeFunc printElemFunction)
{
	if (tableSize >= 0)
	{
		this = (Hash *) malloc( sizeof(Hash) ); // aloca espaço para uma struct do tipo Hash
		this->table = (HashType *) malloc( sizeof(HashType) * tableSize ); // aloca espaço para a tabela
		this->tableSize = tableSize;
		this->hash = hashFunction;
		this->get = hash_get;
		this->add = hash_add;
		this->printElem = printElemFunction;
		this->print = hash_print;
		this->free = hash_free;
		
		for (int i = 0; i < tableSize; i++) { this->table[i] = EMPTY; } // inicializa todas as posições
	}
	
	return this;
}
