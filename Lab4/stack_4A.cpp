#include <iostream>
#include <fstream>

using namespace std;

struct stack_struct
{
    long* array;
    int top;
    stack_struct()
    {
        array = new long[1000000];
        fill(array, array + 100000, 0);
        top = 0;
    }
    ~stack_struct()
    {
        delete [] array;
    }

    void add(long element)
    {
        array[top] = element;
        ++top;
    }
    long get()
    {
        --top;
        long val_to_get = array[top];
        array[top] = 0;
        return val_to_get;
    }
};

int main()
{
    ifstream in("stack.in");
    ofstream out("stack.out");

    long M;
    in >> M;
    char operation;
    long operand;

    stack_struct stack;

    for (long i = 0; i < M; ++i)
    {
        in >> operation;
        if (operation == '+')
        {
            in >> operand;
            stack.add(operand);
        }
        if (operation == '-')
        {
            out << stack.get() << endl;
        }
    }
    return 0;
}
