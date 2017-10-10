#include <iostream>
#include <cassert>
#include <math.h>

#define NMAX 5

const double POISON = atan(M_PI);

typedef double StackElem_t;

#define ASSERT_OK() if(!StackOK(str1))        \
                        {                     \
                        StackDump(str1);      \
                        assert(!"!!!");       \
                        }                     \

FILE *f = fopen("log.txt", "w+");

struct CStack {
    double canary1 = POISON;
    StackElem_t *data;
    int count;
    StackElem_t hash_sum;
    double canary2 = POISON;
};

void StackDump(CStack *str1);

void StackConstruct(CStack *str1);

int StackPush(CStack *str1, StackElem_t num);

StackElem_t StackPop(CStack *str1);

void StackDestruct(CStack *str1);

bool StackOK(CStack *str1);

StackElem_t hash(CStack *str1);


int main() {

    CStack str1 = {};
    StackConstruct(&str1);

    return 0;
}


void StackConstruct(CStack *str1) {
    str1->count = 0;

    str1->data = (StackElem_t *) calloc(sizeof(str1->data), NMAX + 3);
    if (str1->data == NULL)
        exit(2);
    str1->data[0] = POISON;
    str1->data[NMAX + 2] = POISON;
    str1->data++;
    str1->hash_sum = hash(str1);
    ASSERT_OK()
}


int StackPush(CStack *str1, StackElem_t value) {
    ASSERT_OK()
    if (str1->count < NMAX) {
        str1->data[str1->count++] = value;
        str1->hash_sum = hash(str1);
    } else {
        std::cout << "Stack is full" << std::endl;
        return 1;
    }
    ASSERT_OK()
    return 0;
}

StackElem_t StackPop(CStack *str1) {

    StackElem_t elem = 0;
    ASSERT_OK()

    if (str1->count >= 0) {
        elem = str1->data[--str1->count];
        str1->hash_sum = hash(str1);
        return elem;
    } else
        std::cout << "Stack is end" << std::endl;
    ASSERT_OK()
}

void StackDestruct(CStack *str1) {
    ASSERT_OK()
    str1->count = -1;
    free(str1->data - 1);
}

bool StackOK(CStack *str1) {
    return str1->count >= 0
           && str1->data
           && str1->count <= NMAX
           && str1->canary1 == POISON
           && str1->canary2 == POISON
           && str1->data[-1] == POISON
           && str1->data[NMAX + 1] == POISON
           && str1->hash_sum == hash(str1);
}


void StackDump(CStack *str1) {

    fprintf(f, "Stack (ERROR!!!)\n");
    fprintf(f, "count = %d\n", str1->count);
    fprintf(f, "data[NMAX] %p = \n", str1->data);
    for (int i = 0; i <= NMAX; i++)
        fprintf(f, "[%d] = %f\n", i, str1->data[i]);
    fflush(f);
}


StackElem_t hash(CStack *str1) {

    StackElem_t sum = 0;

    for (int i = 0; i <= NMAX; i++, sum += str1->data[i + 1]);
    sum += str1->count;
    return sum;
}