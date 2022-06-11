#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

enum Color { white, grey, black };

struct Vertex {
    std::vector<int> neighbours;
    Color color{Color::white};
};

int main() {
    std::ifstream in("topsort.in");
    std::ofstream out("topsort.out");

    int N, M;
    in >> N >> M;

    std::vector<Vertex> graph(N);
    std::vector<int> topological_order;
    std::stack<int> dfs;

    int v1_i, v2_i;
    for (int i = 0; i < M; ++i) {
        in >> v1_i >> v2_i;
        graph[v1_i - 1].neighbours.push_back(v2_i - 1);
    }

    for (int i = 0; i < N; ++i) {
        dfs.push(i);
        while (!dfs.empty()) {
            int vertex_i = dfs.top();
            if (graph[vertex_i].color == Color::white) {
                graph[vertex_i].color = Color::grey;
                for (const int &neighbour_i : graph[vertex_i].neighbours) {
                    if (graph[neighbour_i].color == Color::grey) {
                        out << -1;
                        return 0;
                    }
                    dfs.push(neighbour_i);
                }
            } else {
                if (graph[vertex_i].color == Color::grey) {
                    topological_order.push_back(vertex_i);
                }
                graph[vertex_i].color = Color::black;
                dfs.pop();
            }
        }
    }

    for (int i = topological_order.size() - 1; i >= 0; --i) {
        out << topological_order[i] + 1 << " ";
    }

    return 0;
}
