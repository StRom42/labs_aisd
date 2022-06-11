#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

long long inversions_counter = 0;

void merge_sort(vector<long> &array, long begin, long end)
{
    if (begin + 1 >= end) return;

    long middle = (begin + end) / 2;

    merge_sort(array, begin, middle);
    merge_sort(array, middle, end);

    vector<long> merged_array(end - begin);

    long shift_left = 0, shift_right = 0, merged_i = 0;

    while (begin + shift_left < middle && middle + shift_right < end)
    {
        if (array[begin + shift_left] <= array[middle + shift_right])
        {
            merged_array[merged_i] = array[begin + shift_left];
            ++merged_i; ++shift_left;
        }
        else
        {
            merged_array[merged_i] = array[middle + shift_right];
            ++merged_i; ++shift_right;
            inversions_counter += middle - begin - shift_left;
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

int main()
{
    long n;
    ifstream in_file("inversions.in");
    ofstream out_file("inversions.out");

    in_file >> n;
    vector<long> array(n);
    for (long i = 0; i < n; ++i)
    {
        in_file >> array[i];
    }
    merge_sort(array, 0, n);
//    for (long i = 0; i < n; ++i) cout << array[i] << " ";
    out_file << inversions_counter;
    return 0;
}
