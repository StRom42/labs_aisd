#include <iostream>
#include <fstream>

using namespace std;

struct stack_struct
{
    long* array;
    int top;
    int size;
    stack_struct(int size)
    {
        this->size = size;
        array = new long[this->size];
        fill(array, array + this->size, 0);
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
    long pop()
    {
        --top;
        long val_to_get = array[top];
        array[top] = 0;
        return val_to_get;
    }
    long get()
    {
        return array[top - 1];
    }
    bool is_empty()
    {
        return (top == 0);
    }
    void clear()
    {
        fill(array, array + size, 0);
        top = 0;
    }
};

int main()
{
    ifstream in("postfix.in");
    ofstream out("postfix.out");

    long operand1, operand2;
    string symbols;
    stack_struct stack(100);

    while (!in.eof())
    {
        symbols.clear();
        in >> symbols;

        if (symbols.size() == 0)
        {
            break;
        }

        if (symbols == "*")
        {
            operand2 = stack.pop();
            operand1 = stack.pop();
            stack.add(operand1 * operand2);
        }
        else if (symbols == "-")
        {
            operand2 = stack.pop();
            operand1 = stack.pop();
            stack.add(operand1 - operand2);
        }
        else if (symbols == "+")
        {
            operand2 = stack.pop();
            operand1 = stack.pop();
            stack.add(operand1 + operand2);
        }
        else
        {
            stack.add(stol(symbols));
        }
    }
    out << stack.pop();

    return 0;
}
