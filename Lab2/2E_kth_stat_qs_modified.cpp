#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void k_order(vector<int32_t> &array, int32_t left, int32_t right, int32_t k)
{
    if (left >= right) return;

    swap(array[left + rand() % (right - left)], array[(left + right) / 2]);

    int32_t sep_element = array[(left + right) / 2];
    int32_t begin = left, end = right;

    do
    {
        while (array[begin] < sep_element)
        {
            ++begin;
        }
        while (array[end] > sep_element)
        {
            --end;
        }
        if (begin <= end)
        {
            swap(array[begin++], array[end--]);
        }
    } while (begin <= end);
    if (k > end)
    {
        k_order(array, begin, right, k);
    }
    else
    {
        k_order(array, left, end, k);
    }
}

int main()
{
    int32_t n, k, A, B, C;
    ifstream in_file("kth.in");
    ofstream out_file("kth.out");

    in_file >> n >> k;
    vector<int32_t> array(n);
    in_file >> A >> B >> C >> array[0] >> array[1];

    for (int32_t i = 2; i < n; ++i)
    {
        array[i] = A * array[i - 2] + B * array[i - 1] + C;
    }
    k_order(array, 0, n - 1, k - 1);

    out_file << array[k - 1];

    return 0;
}
