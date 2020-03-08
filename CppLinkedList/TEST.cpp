#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <memory>
#include <string>
#include <list>

using namespace std;

bool d = false;

// Classe Célula
template<typename ElemType>
class Cell
{
public:
	typedef Cell<ElemType> ThisCell;

	// Fields
	ElemType element;
	ThisCell *next;
	ThisCell *previous;

	// Constructors
	Cell(ElemType element, ThisCell *next, ThisCell *previous)
		: element(element), next(next), previous(previous) { }

	Cell(ElemType element) : element(element) { }

	Cell() : Cell(0) { }

	// Operators
	ThisCell *operator[](int index)
	{
		ThisCell *cell = this;
		int i;
		
		if (index >= 0)
		{
			for (i = 0; cell != nullptr && i < index; i++)
			{
				cell = cell->next;
			}
		}

		else
		{
			index = -index;

			for (i = 0; cell != nullptr && i < index; i++)
			{
				cell = cell->previous;
			}
		}

		return cell;
	}
};

// toString Célula
template<typename ElemType>
ostream& operator<<(ostream &strm, Cell<ElemType> &cell)
{
	return strm << cell.element;
}

// Classe Lista
template<typename ElemType>
class List
{
public:
	typedef Cell<ElemType> ListCell;
	typedef List<ElemType> ThisList;

private:
	// Fields
	ListCell *_head;
	ListCell *_last;
	size_t _size;

	void changeSizeBy(int value)
	{
		_size += value;
	}

	ListCell &head()
	{
		return *_head;
	}

	ThisList &thisObj()
	{
		return *this;
	}

public:
	// Constructors
	List() : _head(new ListCell()), _last(_head), _size(0) { }

	// Destructors
	~List()
	{
		while (_last != _head)
		{
			_last = _last->previous;
			delete _last->next;
		}

		delete _head;
	}

	// Methods
	bool isEmpty()
	{
		return _size == 0;
	}

	size_t size()
	{
		return _size;
	}

	ListCell *getCell(int index)
	{
		return head()[index + 1];
	}

	ElemType get(int index)
	{
		ListCell *cell = getCell(index);

		return cell == nullptr ? 0 : cell->element;
		//return ( cell == nullptr ? nullptr : cell->element );
	}

	ListCell *set(int index, ElemType element)
	{
		ListCell *cell = getCell(index);

		if (cell != nullptr)
		{
			cell->element = element;
		}

		return cell;
	}

	void add(ElemType element)
	{
		thisObj() + element;
	}

	ThisList &clear()
	{
		int __size = size();

		for (size_t i = 0; i < __size; i++)
		{
			thisObj() - 0;
		}

		return thisObj();
	}

	int indexOf(ElemType element)
	{
		int index = -1;
		int __size = size();

		for (size_t i = 0; index == -1 && i < __size; i++)
		{
			if (get(i) == element)
			{
				index = i;
			}
		}
		
		return index;
	}

	ThisList &shiftLeft(int start, int endExclusive)
	{
		if (start > -1 && endExclusive <= size())
		{
			if (start == 0) start++;
			ElemType first = get(0);

			for (size_t i = start; i < endExclusive; i++)
			{
				set(i - 1, get(i));
			}

			set(size() - 1, first);
		}
	}

	ThisList &shiftRight(int start, int endExclusive)
	{
		if (start > -1 && endExclusive <= size())
		{
			ElemType lastElem = _last->element;

			for (size_t i = endExclusive - 1; i > start; i--)
			{
				set(i, get(i - 1));
			}

			set(0, lastElem);
		}
	}

	// Operators
	ElemType operator[](int index)
	{
		return get(index);
	}

	ThisList &operator+(ElemType element)
	{
		ListCell *cell = new ListCell(element, nullptr, _last);

		_last->next = cell;
		_last = _last->next;

		changeSizeBy(1);

		return thisObj();
	}

	ThisList &operator+(ThisList &listToMerge)
	{
		int __size = listToMerge.size();

		for (size_t i = 0; i < __size; i++)
		{
			thisObj() + listToMerge.get(i);
		}
		
		return thisObj();
	}

	ThisList &operator+()
	{
		ThisList *list = new ThisList();
		int __size = size();

		for (size_t i = 0; i < __size; i++)
		{
			*list + get(i);
		}
		
		return *list;
	}

	ThisList &operator-()
	{
		ThisList *list = new ThisList();
		int __size = size();

		for (int i = __size - 1; i >= 0; i--)
		{
			*list + get(i);
		}
		
		return *list;
	}

	ThisList &operator-(int index)
	{
		ListCell *cell = getCell(index);

		if (cell != nullptr && cell != _head)
		{
			// atualiza o ponteiro de último caso o último elemento da lista esteja sendo removido
			if (index == size() - 1) _last = cell->previous;

			cell->previous->next = cell->next; // atualiza o ponteiro next da célula da esquerda

			// atualiza o ponteiro previous da célula da direita
			if (cell->next != nullptr) cell->next->previous = cell->previous;

			cell->previous = cell->next = nullptr; // joga os dois ponteiros da célula a ser removida para null

			changeSizeBy(-1);

			delete cell;
		}

		return thisObj();
	}

	ThisList &operator-(ThisList &listToRemove)
	{
		if (&listToRemove == &thisObj()) clear();

		else
		{
			int __size = listToRemove.size();

			for (size_t i = 0; i < __size; i++)
			{
				thisObj() - indexOf(listToRemove.get(i));
			}
		}
		
		return thisObj();
	}

	ThisList &operator--()
	{
		return thisObj() - 0;
	}

	ThisList &operator--(int)
	{
		int lastIndex = size() - 1;
		
		return thisObj() - lastIndex;
	}

	ThisList &operator<<(int shiftCount)
	{
		for (size_t i = 0; i < shiftCount; i++)
		{
			shiftLeft(0, size());
			cout << thisObj();
			if (d) Sleep(1000);
		}
		
		return thisObj();
	}

	ThisList &operator>>(int shiftCount)
	{
		for (size_t i = 0; i < shiftCount; i++)
		{
			shiftRight(0, size());

			if (d) Sleep(1000);
		}

		return thisObj();
	}

	ThisList &operator*()
	{
		for (int i = size() - 1; i >= 0; i--)
		{
			set(i, 0);
		}

		return thisObj();
	}

	ThisList &operator*(int value)
	{
		ThisList &thisList = thisObj();

		if (value > 0)
		{
			for (size_t i = 1; i < value; i++)
			{
				thisList + thisList;
			}
		}

		else if (value == 0) clear();
		
		return thisObj();
	}

	ThisList &operator&(ThisList &listToMerge)
	{
		return thisObj() + listToMerge;
	}

	ThisList &operator|(ThisList &listToMerge)
	{
		int __size = listToMerge.size();
		ElemType element;

		for (size_t i = 0; i < __size; i++)
		{
			element = listToMerge.get(i);

			if (indexOf(element) == -1)
			{
				thisObj() + element;
			}
		}
		
		return thisObj();
	}

	ThisList &operator^(ThisList &listToXOR)
	{
		ThisList &thisList = thisObj();
		ThisList &clone = +thisList;

		clone - listToXOR;
		listToXOR - thisList;

		return clear() + clone + listToXOR;
	}
};
	// List<int> list;		list + 0 + 1 + 2 + 3 + 4;
	// List<int> list2;	list2 + 5 + 6 + 7 + 8 + 9;
	// List<int> list;		list + 5 + 0 + 7 + 8 + 1;
	// List<int> list2;	list2 + 5 + 6 + 7 + 8 + 9;

// toString Lista
template<typename ElemType>
ostream& operator<<(ostream &strm, List<ElemType> &list)
{
	strm << "{ ";

	if (!list.isEmpty())
	{
		strm << list[0];

		size_t size = list.size();

		for (size_t i = 1; i < size; i++)
		{
			strm << ", " << list[i];
		}
	}

	strm << " }" << endl;

	return strm;
}

int main()
{

	// d = true;
	List<int> list;		list + 5 + 0 + 7 + 8 + 1;
	// List<int> list3;	list3 + 5 + 6 + 7 + 8 + 9 + 5 + 6 + 7 + 8 + 9 + 5 + 6 + 7 + 8 + 9 + 5;

	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 10; i < 20; i++)
		{
			list + i;
			if (i == 19) cout << list << endl;
		}

		#pragma omp for
		for (int i = 50; i < 60; i++)
		{
			list + i;
			if (i == 59) cout << list << endl;
		}
	}

	// list.add(0); list.add(1); list.add(2); list.add(3); list.add(4);
	// list2.add(5); list2.add(6); list2.add(7); list2.add(8); list2.add(9);
	
	// cout << list << endl;
	
	// cout << -list << endl;
	
	// cout << *list << endl;

	// fetch adição de elementos

	// cout << (list << 2) << endl;

	// cout << (list << 7) << endl;

	// cout << (list << 2) - 1 << endl;

	// cout << (list << 2) - 4 - 3 - 2 - 1 << endl;

	// cout << (list >> 1 << 1 >> 2 << 2 >> 3 << 3 >> 4 << 4 >> 5 << 5 >> 3) << endl;
	
	// cout << --list << endl;
	
	// cout << list-- << endl;
	
	// cout << --list-- << endl;
	
	// cout << ----list---- << endl;
	
	// cout << list * 2 << endl;

	// cout << (list & list2) << endl;
	
	// cout << list - list + 77 << endl;
	
	// cout << (list & list2) - list + list << endl;

	// cout << (list | list2) << endl;

	// cout << (list ^ list2) << endl;

	// getc(stdin);

    return 0;
}
