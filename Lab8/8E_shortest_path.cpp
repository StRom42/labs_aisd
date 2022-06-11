#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Vertex
{
    vector<int> neighbours;
    int path_length = 0;
    bool visited = false;
};

int main()
{
    ifstream in("pathbge1.in");
    ofstream out("pathbge1.out");

    int n = 0, m = 0;

    in >> n >> m;

    vector<Vertex> vertexes(n);
    int v1 = 0, v2 = 0;

    for (int i = 0; i < m; ++i)
    {
        in >> v1 >> v2;

        if (v1 == v2) continue;

        vertexes[v1 - 1].neighbours.push_back(v2 - 1);
        vertexes[v2 - 1].neighbours.push_back(v1 - 1);
    }

    queue<int> bfs_queue;
    bfs_queue.push(0);
    while (!bfs_queue.empty())
    {
        int vertex_i = bfs_queue.front(); bfs_queue.pop();
        vertexes[vertex_i].visited = true;

        for (int neighbour_i: vertexes[vertex_i].neighbours)
        {
            if (!vertexes[neighbour_i].visited)
            {
                vertexes[neighbour_i].path_length = vertexes[vertex_i].path_length + 1;
                bfs_queue.push(neighbour_i);
                vertexes[neighbour_i].visited = true;
            }
        }
     }

    for (int i = 0; i < n; ++i)
    {
        out << vertexes[i].path_length << " ";
    }

    return 0;
}
