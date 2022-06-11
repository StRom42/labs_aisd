#include <iostream>

using namespace std;

void merge_sort(long array[], long begin, long end)
{
    if (begin + 1 < end)
    {
        long middle = (begin + end) / 2;
        merge_sort(array, begin, middle);
        merge_sort(array, middle, end);

        long left[middle - begin + 1], right[end - middle + 1];
        left[middle - begin] = LONG_MAX;
        right[end - middle] = LONG_MAX;
        for (long i = 0; i < middle - begin; ++i)
        {
            left[i] = array[begin + i];
        }
        for (long i = 0; i < end - middle; ++i)
        {
            right[i] = array[middle + i];
        }

        for (long left_i = 0, right_i = 0, k = begin; k < end; ++k)
        {
            if (left[left_i] <= right[right_i])
            {
                array[k] = left[left_i++];
            }
            else
            {
                array[k] = right[right_i++];
            }
        }
    }
}

int main()
{
    long n;
    cin >> n;
    long array[n];
    for (long i = 0; i < n; ++i)
    {
        cin >> array[i];
    }
    merge_sort(array, 0, n);
    for (long i = 0; i < n; ++i) cout << array[i] << " ";
    cout << endl;

    return 0;
}
