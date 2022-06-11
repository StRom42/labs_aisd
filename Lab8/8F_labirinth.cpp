#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Vertex
{
    char symbol;
    string path;
    bool visited;

    Vertex() : visited(false){};
};

struct Cell
{
    int row;
    int col;

    Cell(int row = 0, int col = 0) : row(row), col(col){};
    Cell step(int delta_row, int delta_col)
    {
        return Cell(row + delta_row, col + delta_col);
    }
};

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n = 0, m = 0;

    in >> n >> m;

    vector<vector<Vertex>> field(n, vector<Vertex>(m));
    Cell start;

    for (int row_i = 0; row_i < n; ++row_i)
    {
        for (int col_i = 0; col_i < m; ++col_i)
        {
            in >> field[row_i][col_i].symbol;
            if (field[row_i][col_i].symbol == 'S')
            {
                start = {row_i, col_i};
            }
        }
    }

    queue<Cell> bfs_queue;
    Cell current_cell, neighbour_cell;
    bfs_queue.push(start);
    while (!bfs_queue.empty())
    {
        current_cell = bfs_queue.front();
        bfs_queue.pop();

        if (!field[current_cell.row][current_cell.col].visited)
        {
            field[current_cell.row][current_cell.col].visited = true;

            for (int delta_row = -1; delta_row < 2; ++delta_row)
            {
                for (int delta_col = -1; delta_col < 2; ++delta_col)
                {
                    if (abs(delta_row) == abs(delta_col))
                        continue;

                    neighbour_cell = current_cell.step(delta_row, delta_col);

                    if (neighbour_cell.row < 0 || neighbour_cell.row >= n || neighbour_cell.col < 0 ||
                        neighbour_cell.col >= m)
                        continue;
                    if (field[neighbour_cell.row][neighbour_cell.col].symbol == '#')
                        continue;

                    if (!field[neighbour_cell.row][neighbour_cell.col].visited)
                    {
                        bfs_queue.push({neighbour_cell.row, neighbour_cell.col});

                        string direction = "";

                        if (delta_col == -1)
                            direction = "L";
                        else if (delta_col == 1)
                            direction = "R";
                        else if (delta_row == -1)
                            direction = "U";
                        else if (delta_row == 1)
                            direction = "D";

                        field[neighbour_cell.row][neighbour_cell.col].path =
                            field[current_cell.row][current_cell.col].path + direction;

                        if (field[neighbour_cell.row][neighbour_cell.col].symbol == 'T')
                        {
                            string shortest_path = field[neighbour_cell.row][neighbour_cell.col].path;
                            out << shortest_path.length() << endl;
                            out << shortest_path;
                            return 0;
                        }
                        //                        field[neighbour_cell.row][neighbour_cell.col].visited = true;
                    }
                }
            }
        }
    }

    out << -1;

    return 0;
}
