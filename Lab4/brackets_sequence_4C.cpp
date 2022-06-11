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
    ifstream in("brackets.in");
    ofstream out("brackets.out");

    string sequence = "";
    stack_struct stack(1000000);

    while (!in.eof())
    {
        sequence.clear();
        stack.clear();
        in >> sequence;

        if (sequence.size() == 0)
        {
            break;
        }

        for (int i = 0; i < sequence.size(); ++i)
        {
            if (!stack.is_empty() &&
               (sequence[i] == ')' && stack.get() == '(' ||
                sequence[i] == ']' && stack.get() == '['))
            {
                stack.pop();
            }
            else
            {
                stack.add(sequence[i]);
            }
        }

        if (stack.is_empty())
        {
            out << "YES\n";
        }
        else
        {
            out << "NO\n";
        }
    }


    return 0;
}
