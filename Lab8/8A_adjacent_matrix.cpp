#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int v1 = 0, v2 = 0;
    int n = 0, m = 0;

    in >> n >> m;

    vector<vector<int>> adjacent_matrix(n, vector<int>(n, 0));

    for (int i = 0; i < m; ++i)
    {
        in >> v1 >> v2;
        adjacent_matrix[v1 - 1][v2 - 1] = 1;
    }

    for (int row_i = 0; row_i < n; ++row_i)
    {
        for (int col_i = 0; col_i < n; ++col_i)
        {
            out << adjacent_matrix[row_i][col_i] << " ";
        }
        out << endl;
    }
    return 0;
}
