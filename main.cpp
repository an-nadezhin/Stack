#include <iostream>

#include <math.h>

#include <cassert>

#define NMAX 5

#define ASSERT_OK(var) if(!(var).OK())        \
                        {                     \
                        (var).Dump();         \
                        assert(!"!!!");       \
                        }                     \

const double POISON = atan(M_PI);

FILE *f = fopen("log.txt", "w+");

typedef double Elem_t;

class Stack {
public:



    Stack();

    int Push(Elem_t value);

    Elem_t Pop();

    bool OK();

    void Dump();

    Elem_t hash();

    ~Stack();

private:
    double canary1 = POISON;
    Elem_t *data;
    int count;
    Elem_t hash_sum;
    double canary2 = POISON;

};

int main() {

    Stack s1;

}

int Stack::Push(Elem_t value) {

    ASSERT_OK(*this)
    if (count < NMAX) {
        data[count++] = value;
        hash_sum = hash();
    } else {
        std::cout << "Stack is full" << std::endl;
        return 1;
    }
    ASSERT_OK(*this)
    return 0;

}

Stack::Stack() {

    count = 0;

    data = (Elem_t *) calloc(sizeof(data), NMAX + 3);
    if (data == NULL)
        exit(2);
    data[0] = POISON;
    data[NMAX + 2] = POISON;
    data++;
    hash_sum = hash();
    ASSERT_OK(*this)
}

Elem_t Stack::Pop() {//wine??

    Elem_t elem = 0;
    ASSERT_OK(*this)

    if (count >= 0) {
        elem = data[--count];
        hash_sum = hash();
        return elem;
    } else
        std::cout << "Stack is end" << std::endl;
    ASSERT_OK(*this)
}

Stack::~Stack() {
    ASSERT_OK(*this)
    count = -1;
    free(data - 1);
}

bool Stack::OK() {

    return count >= 0
           && data
           && count <= NMAX
           && canary1 == POISON
           && canary2 == POISON
           && data[-1] == POISON
           && data[NMAX + 1] == POISON
           && hash_sum == hash();

}


void Stack::Dump() {

    fprintf(f, "Stack (ERROR!!!)\n");
    fprintf(f, "count = %d\n", count);
    fprintf(f, "data[NMAX] %p = \n", data);
    for (int i = 0; i <= NMAX; i++)
        fprintf(f, "[%d] = %f\n", i, data[i]);
    fflush(f);
}


Elem_t Stack::hash() {

    Elem_t sum = 0;

    for (int i = 0; i <= NMAX; i++, sum += data[i+1]);
    sum += count;
    return sum;
}

