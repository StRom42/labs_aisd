#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n = 0;
    in >> n;

    vector<vector<int>> adjacent_matrix(n, vector<int>(n, 0));

    for (int row_i = 0; row_i < n; ++row_i)
    {
        for (int col_i = 0; col_i < n; ++col_i)
        {
            in >> adjacent_matrix[row_i][col_i];
        }
    }

    for (int row_i = 0; row_i < n; ++row_i)
    {
        for (int col_i = 0; col_i < n; ++col_i)
        {
            if (adjacent_matrix[row_i][col_i] != adjacent_matrix[col_i][row_i])
            {
                out << "NO\n";
                return 0;
            }
            if (col_i == row_i && adjacent_matrix[col_i][row_i] == 1)
            {
                out << "NO\n";
                return 0;
            }
        }
    }
    out << "YES\n";

    return 0;
}
