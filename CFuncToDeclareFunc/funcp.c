#include <stdio.h>
#include <stdlib.h>

#define type char
typedef type (*func_type_type)(type);

#define declare_func(funcName, returnType) \
    returnType funcName(returnType x) \
    { \
        return (returnType) (x * 2); \
    }

void print(func_type_type func)
{
    for (size_t i = 34; i < 39; i++)
    {
        printf("num = %c\n", func(i));
    }
}

declare_func(myint, int)
declare_func(mychar, char)

int main()
{
    print(mychar);

    return EXIT_SUCCESS;
}