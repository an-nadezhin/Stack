#include <iostream>
#include <cassert>
#include <math.h>

#define NMAX 5
#define ASSERT_OK() if(!StackOK(s)) { StackDump(s); assert(0);}
const double POISON = atan(M_PI);

typedef double StackElem_t;

struct CStack {
    StackElem_t *data;
    int count;
};

void StackDump(CStack *s);

void StackConstruct(CStack *s);

int StackPush(CStack *s, StackElem_t num);

StackElem_t StackPop(CStack *s);

void StackDestruct(CStack *s);

bool StackOK(const CStack *s);




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
    ASSERT_OK();
    s->data = (StackElem_t *) calloc(sizeof(s), NMAX);
    s->count = 0;
    ASSERT_OK();
}


int StackPush(CStack *s, StackElem_t num) {
    ASSERT_OK();
    if (s->count < NMAX)
        s->data[s->count++] = num;
    else
        std::cout << "Stack is full" << std::endl;
    ASSERT_OK();
}

StackElem_t StackPop(CStack *s) {
    ASSERT_OK();
    if (s->count > 0)
        return s->data[s->count--];
    else
        std::cout << "Stack is end" << std::endl;/////////////////ifami
    ASSERT_OK();
    return 0;
}

void StackDestruct(CStack *s) {
    ASSERT_OK();
    s->count = 0;
    free(s->data);
    ASSERT_OK();
}

bool StackOK(const CStack *s) {
    return s && s->count >= 0 && s->data && s->count < NMAX;
}


void StackDump(CStack *s) {
    FILE *f = fopen("log.txt", "a");
    fprintf(f, "error in StackDump");////////////////////zapilit, classes
    fclose(f);
}
