#include <calc.h>

int sp = 0;
double stack[MAX_STACK_SIZE]; // 2 for value and type

// push() - push f onto value stack
void push(double val[])
{
    if (sp < MAX_STACK_SIZE-1)
    {
        stack[sp++] = val[1];
        stack[sp++] = val[0];
        //printf("stack::push: %f (type: %f)\n", val[0], val[1]);
    }
    else
    {
        printf("Error; stack full.\n");
    }
}

// pop: return the top value/type pair from stack and decrement the stack pointer
void pop(double ret[])
{
    if (sp == 0)
    {
        printf("Error: stack empty.\n");
    }
    else if (sp < 1)
    {
        printf("Error: stack invalid.\n");
    }
    else
    {
        ret[0] = stack[--sp]; // val
        ret[1] = stack[--sp]; // type
        //printf("stack::pop: %f (type: %f)\n", ret[0], ret[1]);
    }
}

// peek: return the top value/type pair from stack without decrementing sp;
void peek(double ret[])
{
    if (sp == 0)
    {
        printf("Error: stack empty.\n");
    }
    else if (sp < 1)
    {
        printf("Error: stack invalid.\n");
    }
    else
    {
        ret[0] = stack[sp];   // val
        ret[1] = stack[sp-1]; // type
    }
}

// duplicate_top: instructions were unclear, but assuming that
// this means add another element equal to the top element.
void duplicate_top()
{
    // zero-initialize for -Werror=maybe-uninitialized
    double top[2] = {0.0, 0.0};
    
    pop(top); // and the fun don't stop!
    push(top);
    push(top);
}

// swap_top: switch the top two elements of the stack
void swap_top()
{
    // zero-initialize for -Werror=maybe-uninitialized
    double top[2] = {0.0, 0.0};
    double second[2] = {0.0, 0.0};
    
    pop(top);
    pop(second);
    push(top);
    push(second);
}

int get_stack_size()
{
    return sp / 2;
}

void display()
{
    double op1[2];

    // pop stack and display result, unless the resultant expression is bad
    if (get_stack_size() != 1)
    {
        printf("Error: expression resulted in invalid computation.\n");
    }
    else
    {
        pop(op1);
        printf("%8.g\n", op1[0]);
    }    
}