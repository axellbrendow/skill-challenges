#include <stdio.h>
#include <stdlib.h>

// ----- SOME POINTERS

typedef void (*func_void)();

// ----- CELL

#define ElemType int

typedef struct Cell Cell;
typedef Cell* CellP;
typedef CellP (*func_cellp_int)(int);
typedef CellP (*func_cellp_elemtype)(ElemType);

CellP newCell(ElemType, CellP, CellP);

struct Cell
{
	ElemType element;
	CellP next;
	CellP prev;

	func_cellp_int get;
	func_cellp_elemtype addCell;
	func_void print;
	func_void free;

} *thisCell;

CellP get(int offset)
{
	if (offset > -1) // right
	{
		for (size_t i = 0; thisCell != NULL && i < offset; i++)
		{
			thisCell = thisCell->next;
		}
	}
	
	else // left
	{
		offset = -offset;
		
		for (size_t i = 0; thisCell != NULL && i < offset; i++)
		{
			thisCell = thisCell->prev;
		}
	}

	return thisCell;
}

CellP addCell(ElemType element)
{
	CellP cell = thisCell;
	CellP newcell = newCell(element, cell->next, cell);

	if (cell->next != NULL) cell->next->prev = newcell;

	cell->next = newcell;

	return newcell;
}

void printCells()
{
	if (thisCell != NULL)
	{
		printf("{ %d", thisCell->element);
		
		for (CellP cell = thisCell->next; cell != NULL; cell = cell->next)
		{
			printf(", %d", cell->element);
		}

		printf(" }\n");
	}
}

void freeCell()
{
	CellP prev = thisCell;
	CellP curr;

	while (prev != NULL)
	{
		curr = prev->next;
		free(prev);
		prev = curr;
	}
}

CellP newCell(ElemType element, CellP next, CellP prev)
{
	thisCell = (CellP) malloc( sizeof(Cell) );
	
	thisCell->element = element;
	thisCell->next = next;
	thisCell->prev = prev;
	thisCell->get = get;
	thisCell->addCell = addCell;
	thisCell->print = printCells;
	thisCell->free = freeCell;

	return thisCell;
}

// ----- LIST

typedef struct List List;
typedef List* ListP;
typedef ListP (*func_listp_elemtype_int)(ElemType, int);
typedef ListP (*func_listp_elemtype)(ElemType);

struct List
{
	CellP head;
	// CellP last;
	int size;

	func_listp_elemtype_int addByIndex;
	func_listp_elemtype add;
	func_cellp_int getCell;
	func_void print;
	func_void free;

} *thisList;

ListP addByIndex(ElemType element, int index)
{
	CellP copy = thisCell;
	CellP prevCell = thisList->getCell(index - 1);

	if (prevCell != NULL)
	{
		prevCell->addCell(element);
		thisList->size++;
	}

	thisCell = copy;

	return thisList;
}

ListP add(ElemType element)
{
	addByIndex(element, thisList->size);

	return thisList;
}

CellP getCell(int index)
{
	thisCell = thisList->head;

	return thisCell = thisCell->get(index + 1);
}

void printList()
{
	if (thisList->size > 0)
	{
		thisCell = thisList->head->next;
		thisCell->print();
	}
}

void freeList()
{
	thisList->head->free();
	free(thisList);
}

ListP newList()
{
	thisList = (ListP) malloc( sizeof(List) );
	
	thisList->head = newCell(0, NULL, NULL);
	thisList->size = 0;
	thisList->addByIndex = addByIndex;
	thisList->add = add;
	thisList->getCell = getCell;
	thisList->print = printList;
	thisList->free = freeList;

	thisCell = thisList->head;

	return thisList;
}

// ----- MAIN

int main()
{
	List list = *newList();

	list.add(88)->add(23)->add(32)->add(11)->add(34)->add(55)->add(13)->add(22)->add(21)->addByIndex(99, 0);

	list.print();

	printf("\nlist[1] = %d\n", list.getCell(2)->get(-1)->element);

	list.free();

	return EXIT_SUCCESS;
}
