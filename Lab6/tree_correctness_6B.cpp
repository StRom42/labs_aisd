#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("check.in");
    ofstream out("check.out");

    long n, key, left_child, right_child;
    in >> n;

    long nodes[n][2];
    bool valid = true;

    for (long i = 0; i < n; ++i)
    {
        in >> key >> left_child >> right_child;

        if (i != 0)
        {
            if (!(nodes[i][0] < key && nodes[i][1] > key))
            {
                valid = false;
                break;
            }
        }

        if (left_child != 0)
        {
            nodes[left_child - 1][0] = (i == 0) ? LONG_MIN : nodes[i][0];
            nodes[left_child - 1][1] = key;
        }
        if (right_child != 0)
        {
            nodes[right_child - 1][1] = (i == 0) ? LONG_MAX : nodes[i][1];
            nodes[right_child - 1][0] = key;
        }
    }

    out << (valid ? "YES" : "NO");
    return 0;
}
