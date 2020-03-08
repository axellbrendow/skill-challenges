#define tuple(varName, expression)\
    int lambdaExp(int varName)\
    {\
        return (expression);\
    }\
\
    int main()\
    {\
        int varName;\
        int* varPtr = &varName;\
        printf("[(%d, %d)", 0, lambdaExp(0));

#define for for(

#define in = 1; *varPtr < 

#define range(end) \
        end ; (*varPtr)++ )\
        {\
            printf(", (%d, %d)", *varPtr, lambdaExp(*varPtr));\
        }\
\
        printf("]\n");\
\
        return 0;\
    }
