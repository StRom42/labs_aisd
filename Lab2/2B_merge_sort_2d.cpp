#include <iostream>
#include <fstream>

using namespace std;

void merge_sort(string array[][2], long begin, long end)
{
    if (begin + 1 < end)
    {
        long middle = (begin + end) / 2;
        merge_sort(array, begin, middle);
        merge_sort(array, middle, end);

        long left_len = middle - begin, right_len = end - middle;
        string left[left_len][2], right[right_len][2];

        for (long i = 0; i < left_len; ++i)
        {
            left[i][0] = array[begin + i][0];
            left[i][1] = array[begin + i][1];
        }
        for (long i = 0; i < right_len; ++i)
        {
            right[i][0] = array[middle + i][0];
            right[i][1] = array[middle + i][1];
        }

        long left_i = 0, right_i = 0, k = begin;
        for (; k < end && left_i < left_len && right_i < right_len; ++k)
        {
            if (left[left_i][0] <= right[right_i][0])
            {
                array[k][0] = left[left_i][0];
                array[k][1] = left[left_i++][1];
            }
            else
            {
                array[k][0] = right[right_i][0];
                array[k][1] = right[right_i++][1];
            }
        }
        while (left_i < left_len)
        {
            array[k][0] = left[left_i][0];
            array[k++][1] = left[left_i++][1];
        }
        while (right_i < right_len)
        {
            array[k][0] = right[right_i][0];
            array[k++][1] = right[right_i++][1];
        }
    }
}

int main()
{
    long n;
    ifstream in_file("race.in");
    ofstream out_file("race.out");

    in_file >> n;
    string array[n][2];
    for (long i = 0; i < n; ++i)
    {
        in_file >> array[i][0];
        in_file >> array[i][1];
    }
    merge_sort(array, 0, n);
    string current_country = "";
    for (long i = 0; i < n; ++i)
    {
        if (current_country != array[i][0])
        {
            current_country = array[i][0];
            out_file << "=== " << current_country << " ===" << endl;
        }
        out_file << array[i][1] << endl;
    }
    return 0;
}
