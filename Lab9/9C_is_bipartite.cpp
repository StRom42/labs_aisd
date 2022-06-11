#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

enum Type { first, second };

struct Vertex {
    std::vector<int> neighbours;
    bool visited{false};
    Type type{first};
};

class Graph {
  private:
    std::vector<Vertex> vertexes;

  public:
    Graph(std::istream &in) {
        int N, M;
        in >> N >> M;

        vertexes.resize(N);

        int v1_i, v2_i;
        for (int i = 0; i < M; ++i) {
            in >> v1_i >> v2_i;
            vertexes[v1_i - 1].neighbours.push_back(v2_i - 1);
            vertexes[v2_i - 1].neighbours.push_back(v1_i - 1);
        }
    }

    bool is_bipartite() {
        std::queue<int> bfs;
        for (int i = 0; i < vertexes.size(); ++i) {
            if (vertexes[i].visited) continue;
            bfs.push(i);
            while (!bfs.empty()) {
                int vertex_i = bfs.front();
                bfs.pop();
                vertexes[vertex_i].visited = true;
                for (int neighbour_i : vertexes[vertex_i].neighbours) {
                    if (vertexes[neighbour_i].visited) {
                        if (vertexes[neighbour_i].type ==
                            vertexes[vertex_i].type) {
                            return false;
                        }
                    } else {
                        vertexes[neighbour_i].type =
                            (vertexes[vertex_i].type == first) ? second : first;
                        vertexes[neighbour_i].visited = true;
                        bfs.push(neighbour_i);
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    std::ifstream in("bipartite.in");
    std::ofstream out("bipartite.out");

    Graph graph(in);
    out << ((graph.is_bipartite()) ? "YES" : "NO");
    return 0;
}
