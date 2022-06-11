#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

enum Color { white, grey, black };

struct Vertex {
    std::vector<int> neighbours;
    Color color{white};
};

std::shared_ptr<std::vector<int>> find_cycle(std::vector<Vertex> &graph) {
    auto cycle = std::make_shared<std::vector<int>>(std::vector<int>());
    std::stack<int> dfs;
    for (int i = 0; i < graph.size(); ++i) {
        dfs.push(i);
        while (!dfs.empty()) {
            int vertex_i = dfs.top();
            if (graph[vertex_i].color == white) {
                graph[vertex_i].color = grey;
                for (int &neighbour_i : graph[vertex_i].neighbours) {
                    if (graph[neighbour_i].color == grey) {
                        int current_i = neighbour_i;
                        while (current_i != vertex_i) {
                            cycle->push_back(current_i);
                            for (int &cycle_i : graph[current_i].neighbours) {
                                if (graph[cycle_i].color == grey) {
                                    current_i = cycle_i;
                                    break;
                                }
                            }
                        }
                        cycle->push_back(vertex_i);
                        return cycle;
                    }
                    dfs.push(neighbour_i);
                }
            } else {
                graph[vertex_i].color = black;
                dfs.pop();
            }
        }
    }
    return cycle;
}

int main() {
    std::ifstream in("cycle.in");
    std::ofstream out("cycle.out");

    int N, M;
    in >> N >> M;

    std::vector<Vertex> graph(N);

    int v1_i, v2_i;
    for (int i = 0; i < M; ++i) {
        in >> v1_i >> v2_i;
        graph[v1_i - 1].neighbours.push_back(v2_i - 1);
    }

    auto cycle = find_cycle(graph);
    out << ((cycle->empty()) ? "NO" : "YES") << std::endl;
    for (int &i : *cycle) {
        out << i + 1 << " ";
    }
    return 0;
}
