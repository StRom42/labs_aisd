#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

enum Type { first, second };

struct Vertex {
    std::vector<int> neighbours;
    std::vector<int> parents;
    bool visited{false};
    int component_number{0};
};

class Graph {
  private:
    std::vector<Vertex> vertexes;
    std::vector<int> top_order;
    int component_counter{0};

  public:
    Graph(std::istream &in) {
        int N, M;
        in >> N >> M;

        vertexes.resize(N);

        int v1_i, v2_i;
        for (int i = 0; i < M; ++i) {
            in >> v1_i >> v2_i;
            vertexes[v1_i - 1].neighbours.push_back(v2_i - 1);
            vertexes[v2_i - 1].parents.push_back(v1_i - 1);
        }
    }

    void top_sort(int vertex_i) {
        vertexes[vertex_i].visited = true;
        for (int neighbour_i : vertexes[vertex_i].neighbours) {
            if (!vertexes[neighbour_i].visited) {
                top_sort(neighbour_i);
            }
        }
        top_order.push_back(vertex_i);
    }

    void mark_component(int vertex_i) {
        vertexes[vertex_i].component_number = component_counter;
        for (int neighbour_i : vertexes[vertex_i].parents) {
            if (vertexes[neighbour_i].component_number == 0) {
                mark_component(neighbour_i);
            }
        }
    }

    void print_condensed_graph(std::ostream &out) {
        for (int i = 0; i < vertexes.size(); ++i) {
            if (!vertexes[i].visited) {
                top_sort(i);
            }
        }
        for (int i = top_order.size() - 1; i >= 0; --i) {
            if (vertexes[top_order[i]].component_number == 0) {
                component_counter += 1;
                mark_component(top_order[i]);
            }
        }
        out << component_counter << std::endl;
        for (Vertex &v : vertexes) {
            out << v.component_number << " ";
        }
    }
};

int main() {
    std::ifstream in("cond.in");
    std::ofstream out("cond.out");

    Graph graph(std::cin);
    graph.print_condensed_graph(std::cout);
    return 0;
}
