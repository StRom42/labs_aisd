#include <fstream>
#include <iostream>
#include <set>
#include <vector>

const long long INF = 5e18 + 10;

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

  private:
    void mark_reachable(std::vector<bool> &reachable, long vertex_i) {
        reachable[vertex_i] = true;
        for (Edge &edge : vertexes[vertex_i].edges) {
            if (!reachable[edge.to]) {
                mark_reachable(reachable, edge.to);
            }
        }
    }

  public:
    DiGraph(int vertexes_amount = 1) {
        vertexes.resize(vertexes_amount);
    }
    void add_edge(long t_from, long t_to, long long t_weight) {
        vertexes[t_from].edges.push_back(Edge(t_to, t_weight));
    }
    std::vector<long long> find_distances_from(long t_from) {
        std::vector<long long> distances(vertexes.size(), INF);
        std::vector<long> negative_cycle_vertexes;

        distances[t_from] = 0;

        for (long i = 0; i < vertexes.size() - 1; ++i) {
            for (long vertex_i = 0; vertex_i < vertexes.size(); ++vertex_i) {
                for (Edge &edge : vertexes[vertex_i].edges) {
                    long long new_distance = distances[vertex_i] + edge.weight;

                    if (distances[vertex_i] < INF &&
                        new_distance < distances[edge.to]) {

                        distances[edge.to] = std::max(new_distance, -INF);
                    }
                }
            }
        }
        for (long vertex_i = 0; vertex_i < vertexes.size(); ++vertex_i) {
            for (Edge &edge : vertexes[vertex_i].edges) {
                if (distances[vertex_i] < INF) {
                    if (distances[vertex_i] + edge.weight <
                        distances[edge.to]) {
                        negative_cycle_vertexes.push_back(vertex_i);
                    }
                }
            }
        }
        std::vector<bool> reachable_from_neg_cycle(vertexes.size(), false);
        for (long vertex_i : negative_cycle_vertexes) {
            if (!reachable_from_neg_cycle[vertex_i]) {
                mark_reachable(reachable_from_neg_cycle, vertex_i);
            }
        }
        for (long i = 0; i < vertexes.size(); ++i) {
            if (reachable_from_neg_cycle[i]) {
                distances[i] = -INF;
            }
        }

        return distances;
    }
};

int main() {
    std::ifstream in("path.in");
    std::ofstream out("path.out");

    long N, M, S;
    in >> N >> M >> S;

    DiGraph graph(N);

    long from_i, to_i;
    long long weight_i;
    for (long i = 0; i < M; ++i) {
        in >> from_i >> to_i >> weight_i;
        --from_i, --to_i;
        graph.add_edge(from_i, to_i, weight_i);
    }

    auto distances = graph.find_distances_from(S - 1);
    for (long long &distance : distances) {
        if (distance == INF) {
            out << "*";
        } else if (distance == -INF) {
            out << "-";
        } else {
            out << distance;
        }
        out << "\n";
    }

    return 0;
}
