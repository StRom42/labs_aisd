#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long heap_size = 0;

void max_heapify(vector<long> &array, int node_i)
{
    int left = 2 * (node_i + 1) - 1;
    int right = 2 * (node_i + 1);
    int largest = 0;
    if (left < heap_size && array[left] > array[node_i])
    {
        largest = left;
    }
    else
    {
        largest = node_i;
    }
    if (right < heap_size && array[right] > array[largest])
    {
        largest = right;
    }


    if (largest != node_i)
    {
        swap(array[node_i], array[largest]);
        max_heapify(array, largest);
    }
}

void build_max_heap(vector<long> &array)
{
    for (int i = array.size() / 2; i >= 0; --i)
    {
        max_heapify(array, i);
    }
}

void heapsort(vector<long> &array)
{
    heap_size = array.size();
    build_max_heap(array);
    for (int i = array.size() - 1; i >= 1; --i)
    {
        swap(array[0], array[i]);
        heap_size -= 1;
        max_heapify(array, 0);
    }
}

int main()
{
    ifstream in("sort.in");
    ofstream out("sort.out");

    int n = 10;
    in >> n;
    vector<long> array(n);
    for (int i = 0; i < n; ++i)
    {
        in >> array[i];
    }

    heapsort(array);

    for (long i: array)
    {
        out << i << " ";
    }

    return 0;
}
