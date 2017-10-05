#include <iostream>
#include <cassert>
#include <math.h>

#define NMAX 5

const double POISON = atan(M_PI);

typedef double StackElem_t;

//struct CStack {
 //   StackElem_t *data;
//    int count;
//};

void StackDump(CStack *s);

void StackConstruct(CStack *s);

void StackPush(CStack *s, StackElem_t num);

StackElem_t StackPop(CStack *s);

void StackDestruct(CStack *s);

bool StackOK(const CStack *s);

class Stack {
private:
    struct CStack {
        StackElem_t *data;
        int count;
    };
public:
    void push(CStack *s, StackElem_t num) {
        if (s->count < NMAX)
            s->data[s->count++] = num;
        else
            std::cout << "Stack is full" << std::endl;
    }

};


int main() {

    StackElem_t num = 0;
    int chek = 0;

    CStack s = {};
    StackConstruct(&s);
    chek = StackPush(&s, num);
    if (chek = POISON) {


    }
    StackElem_t val = StackPop(&s);
    StackDestruct(&s);
    return 0;
}


void StackConstruct(CStack *s) {
    s->data = (StackElem_t *) calloc(sizeof(s), NMAX);
    s->count = 0;
}


void push(CStack *s, StackElem_t num) {
    if (s->count < NMAX)
        s->data[s->count++] = num;
    else
        std::cout << "Stack is full" << std::endl;
}

StackElem_t StackPop(CStack *s) {
    if (s->count > 0)
        return s->data[s->count--];
    else
        std::cout << "Stack is end" << std::endl;/////////////////ifami
    return 0;
}

void StackDestruct(CStack *s) {
    s->count = 0;
    free(s->data);
}

bool StackOK(CStack *s) {
    return s && s->count >= 0 && s->data && s->count < NMAX;
}


void StackDump(CStack *s) {
    FILE *f = fopen("log.txt", "a");
    fprintf(f, "error in StackDump");////////////////////zapilit, classes
    fclose(f);
}
