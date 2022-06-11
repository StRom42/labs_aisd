#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

const long long INF = 1e12 + 10;

struct Edge {
    long to;
    long long weight;
    Edge(long t_to = 0, long long t_weight = 1) : to(t_to), weight(t_weight){};
};

struct Vertex {
    std::vector<Edge> edges;
};

class DiGraph {
  private:
    std::vector<Vertex> vertexes;

  public:
    DiGraph(int vertexes_amount = 1) {
        vertexes.resize(vertexes_amount);
    }
    void add_edge(long t_from, long t_to, long long t_weight) {
        vertexes[t_from].edges.push_back(Edge(t_to, t_weight));
    }
    std::vector<long> find_negative_cycle() {
        std::vector<long long> distances(vertexes.size(), INF);
        std::vector<long> parents(vertexes.size(), -1);

        long updated_vertex_i = -1;
        for (long i = 0; i < vertexes.size(); ++i) {
            updated_vertex_i = -1;
            for (long vertex_i = 0; vertex_i < vertexes.size(); ++vertex_i) {
                for (Edge &edge : vertexes[vertex_i].edges) {
                    long long new_distance = distances[vertex_i] + edge.weight;
                    if (new_distance < distances[edge.to]) {

                        distances[edge.to] = std::max(new_distance, -INF);
                        parents[edge.to] = vertex_i;
                        updated_vertex_i = edge.to;
                    }
                }
            }
        }

        std::vector<long> cycle;
        if (updated_vertex_i != -1) {
            for (long i = 0; i < vertexes.size(); ++i) {
                updated_vertex_i = parents[updated_vertex_i];
            }
            long current_vertex = updated_vertex_i;
            do {
                cycle.push_back(current_vertex);
                current_vertex = parents[current_vertex];
            } while (current_vertex != updated_vertex_i);

            cycle.push_back(current_vertex);
            std::reverse(cycle.begin(), cycle.end());
        }
        return cycle;
    }
};

int main() {
    std::ifstream in("negcycle.in");
    std::ofstream out("negcycle.out");

    long N;
    in >> N;

    DiGraph graph(N);

    long long weight_i;
    for (long from_i = 0; from_i < N; ++from_i) {
        for (long to_i = 0; to_i < N; ++to_i) {
            in >> weight_i;
            if (weight_i != 1e9) {
                graph.add_edge(from_i, to_i, weight_i);
            }
        }
    }

    auto cycle = graph.find_negative_cycle();
    if (cycle.empty()) {
        out << "NO";
    } else {
        out << "YES\n" << cycle.size() << "\n";
        for (long vertex_i : cycle) {
            out << vertex_i + 1 << " ";
        }
    }

    return 0;
}
