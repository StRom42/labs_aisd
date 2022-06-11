#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void merge_sort(vector<string> &array, long begin, long end, long column)
{
    if (begin + 1 >= end) return;

    long middle = (begin + end) / 2;

    merge_sort(array, begin, middle, column);
    merge_sort(array, middle, end, column);

    vector<string> merged_array(end - begin);

    long shift_left = 0, shift_right = 0, merged_i = 0;

    while (begin + shift_left < middle && middle + shift_right < end)
    {
        if (array[begin + shift_left][column] <= array[middle + shift_right][column])
        {
            merged_array[merged_i] = array[begin + shift_left];
            ++merged_i; ++shift_left;
        }
        else
        {
            merged_array[merged_i] = array[middle + shift_right];
            ++merged_i; ++shift_right;
        }
    }
    while (begin + shift_left < middle)
    {
        merged_array[merged_i] = array[begin + shift_left];
        ++merged_i; ++shift_left;
    }
    while (middle + shift_right < end)
    {
        merged_array[merged_i] = array[middle + shift_right];
        ++merged_i; ++shift_right;
    }
    for (long i = 0; i < (end - begin); ++i)
    {
        array[begin + i] = merged_array[i];
    }
}

void radixsort(vector<string> &array, int cols_to_sort, int width)
{
    for (int i = 0; i < cols_to_sort; ++i)
    {
        merge_sort(array, 0, array.size(), width - 1 - i);
    }
}

int main()
{
    ifstream in("radixsort.in");
    ofstream out("radixsort.out");

    int n, m, k;
    in >> n >> m >> k;
    vector<string> array(n, string(m, ' '));
    for (int i = 0; i < n; ++i)
    {
        in >> array[i];
    }

    radixsort(array, k, m);

    for (int i = 0; i < n; ++i)
    {
        out << array[i] << "\n";
    }
    return 0;
}
