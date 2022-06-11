#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

enum Type { first, second };

struct Vertex {
    std::vector<int> neighbours;
    bool visited{false};
    int deg_in{0};
    int deg_out{0};
};

class Graph {
  private:
    std::vector<Vertex> vertexes;
    std::vector<int> top_order;
    bool detected_hamilton_path{false};

  private:
    void top_sort(int vertex_i) {
        vertexes[vertex_i].visited = true;
        for (int neighbour_i : vertexes[vertex_i].neighbours) {
            if (!vertexes[neighbour_i].visited) {
                top_sort(neighbour_i);
            }
        }
        top_order.push_back(vertex_i);
    }
    int get_start_vertex() {
        int start_i = -1;
        for (int i = 0; i < vertexes.size(); ++i) {
            if (vertexes[i].deg_in == 0) {
                if (start_i == -1)
                    start_i = i;
                else
                    return -1;
            }
        }
        return start_i;
    }
    std::pair<int, int> get_next_vertex(int vertex_i, int top_order_position) {
        if (vertexes[vertex_i].neighbours.empty()) return {-1, -1};
        for (int i = top_order_position; i < vertexes.size(); ++i) {
            for (int neighbour_i : vertexes[vertex_i].neighbours) {
                if (top_order[i] == neighbour_i) {
                    return {neighbour_i, i};
                }
            }
        }
        return {-1, -1};
    }

  public:
    Graph(std::istream &in) {
        int N, M;
        in >> N >> M;

        vertexes.resize(N);

        int v1_i, v2_i;
        for (int i = 0; i < M; ++i) {
            in >> v1_i >> v2_i;
            vertexes[v1_i - 1].neighbours.push_back(v2_i - 1);
            vertexes[v1_i - 1].deg_out += 1;
            vertexes[v2_i - 1].deg_in += 1;
        }
    }
    void top_sort() {
        for (int i = 0; i < vertexes.size(); ++i) {
            if (!vertexes[i].visited) {
                top_sort(i);
            }
        }
        std::reverse(top_order.begin(), top_order.end());
    }

    bool contains_hamiltonian_path() {
        top_sort();
        int vertex_i = get_start_vertex();
        if (vertex_i == -1) return false;
        int path_len = 1;
        int top_order_position = 0;
        while (true) {
            auto vertex = get_next_vertex(vertex_i, top_order_position);
            vertex_i = vertex.first;
            top_order_position = vertex.second;
            if (vertex_i == -1) break;
            path_len += 1;
        }
        return path_len == vertexes.size();
    }
};

int main() {
    std::ifstream in("hamiltonian.in");
    std::ofstream out("hamiltonian.out");

    Graph graph(in);
    out << ((graph.contains_hamiltonian_path()) ? "YES" : "NO");
    return 0;
}
