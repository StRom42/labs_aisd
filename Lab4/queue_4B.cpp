#include <iostream>
#include <fstream>

using namespace std;

struct queue_struct
{
    long* array;
    int head;
    int tail;
    int size;

    queue_struct(int size)
    {
        this->size = size;
        array = new long[this->size];
        fill(array, array + this->size - 1, 0);
        head = 0;
        tail = 0;
    }
    ~queue_struct()
    {
        delete [] array;
    }

    void add(long element)
    {
        array[tail] = element;
        ++tail;
        if (tail == size)
        {
            tail = 0;
        }
    }
    long get()
    {
        long val_to_get = array[head];
        array[head] = 0;
        ++head;
        if (head == size)
        {
            head = 0;
        }
        return val_to_get;
    }
};

int main()
{
    ifstream in("queue.in");
    ofstream out("queue.out");

    long M;
    in >> M;
    char operation;
    long operand;

    queue_struct queue(1000000);

    for (long i = 0; i < M; ++i)
    {
        in >> operation;
        if (operation == '+')
        {
            in >> operand;
            queue.add(operand);
        }
        if (operation == '-')
        {
            out << queue.get() << endl;
        }
    }
    return 0;
}
