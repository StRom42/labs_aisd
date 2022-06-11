#include <fstream>
#include <iostream>
#include <vector>

struct Vertex {
    std::vector<int> neighbours;
};

class Graph {
  private:
    std::vector<Vertex> vertexes;

  public:
    Graph(std::istream &in) {
        int n, m;
        in >> n >> m;
        vertexes.resize(n);

        int v1, v2;
        for (int i = 0; i < m; ++i) {
            in >> v1 >> v2;
            vertexes[v1 - 1].neighbours.push_back(v2 - 1);
            vertexes[v2 - 1].neighbours.push_back(v1 - 1);
        }
    }

    std::vector<int> degrees() {
        std::vector<int> vertex_degrees;
        for (Vertex &vertex : vertexes) {
            vertex_degrees.push_back(vertex.neighbours.size());
        }
        return vertex_degrees;
    }
};

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    Graph G(in);
    for (int degree : G.degrees()) {
        out << degree << " ";
    }
    return 0;
}
