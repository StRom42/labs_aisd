#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n = 0, m = 0;
    in >> n >> m;

    int v1 = 0, v2 = 0;

    vector<vector<int>> adjacent_matrix(n, vector<int>(n, 0));

    for (int i = 0; i < m; ++i)
    {
        in >> v1 >> v2;
        if (adjacent_matrix[v1 - 1][v2 - 1] == 1 || adjacent_matrix[v2 - 1][v1 - 1] == 1)
        {
            out << "YES\n";
            return 0;
        }
        else
        {
            adjacent_matrix[v1 - 1][v2 - 1] = 1;
        }
    }
    out << "NO\n";

    return 0;
}
