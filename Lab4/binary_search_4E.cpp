#include <iostream>
#include <fstream>

using namespace std;

long binary_search(long array[], long length, long key, bool find_first = true)
{
    long begin = 0;
    long end = length - 1;

    while (begin <= end)
    {
        long middle = (begin + end) / 2;

        if (array[middle] < key || ((!find_first) && array[middle] == key))
        {
            begin = middle + 1;
        }
        else if (array[middle] > key || (find_first && array[middle] == key))
        {
            end = middle - 1;
        }
    }

    long result_i =  find_first ? begin : end;
    if (result_i < 0 || result_i >= length || array[result_i] != key)
    {
        return -1;
    }
    else
    {
        return result_i;
    }
}

int main()
{
    long n, m, request, left_i, right_i;
    cin >> n;

    long array[n];
    for (long i = 0; i < n; ++i)
    {
        cin >> array[i];
    }

    cin >> m;
    for (long i = 0; i < m; ++i)
    {
        cin >> request;

        left_i = binary_search(array, n, request);
        right_i = binary_search(array, n, request, false);


        cout << left_i << " " << right_i << endl;
    }
    return 0;
}
