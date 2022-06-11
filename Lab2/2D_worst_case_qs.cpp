#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    long n;
    ifstream in_file("antiqs.in");
    ofstream out_file("antiqs.out");

    in_file >> n;
    vector<long> array(n);
    long begin = n - 1;
    for (long i = n; i > 0; --i)
    {
        array[begin] = i;
        swap(array[begin], array[(begin + n + 1) / 2 - 1]);
        --begin;
    }

    for (long i = 0; i < n; ++i)
    {
        out_file << array[i] << " ";
    }

    return 0;
}
