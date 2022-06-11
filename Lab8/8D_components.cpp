#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Vertex
{
    int component;
    vector<int> neighbours;
    Vertex() : component(0) {};
};

int main()
{
    ifstream in("components.in");
    ofstream out("components.out");

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

    int new_component_number = 0;

    for (int i = 0; i < n; ++i)
    {
        if (vertexes[i].component == 0)
        {
            new_component_number += 1;
            queue<int> bfs_queue;
            bfs_queue.push(i);
            while (!bfs_queue.empty())
            {
                int vertex_i = bfs_queue.front(); bfs_queue.pop();
                vertexes[vertex_i].component = new_component_number;
                for (int neighbour_i: vertexes[vertex_i].neighbours)
                {
                    if (vertexes[neighbour_i].component == 0)
                    {
                        bfs_queue.push(neighbour_i);
                    }
                }
            }
        }
    }

    out << new_component_number << endl;
    for (Vertex &vertex: vertexes)
    {
        out << vertex.component << " ";
    }


    return 0;
}
