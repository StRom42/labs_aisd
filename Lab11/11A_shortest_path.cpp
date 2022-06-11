#include <fstream>
#include <iostream>
#include <set>
#include <vector>
 
struct Edge {
    long to;
    long long weight;
    Edge(long t_to = 0, long t_weight = 1) : to(t_to), weight(t_weight){};
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
    long long shortest_path_weight(long t_from, long t_to) {
        std::vector<long long> distances(vertexes.size(), INT64_MAX);
        std::set<std::pair<long long, long>> queue;
 
        distances[t_from] = 0;
        queue.insert({0, t_from});
 
        while (!queue.empty()) {
            auto current = *queue.begin();
            queue.erase(queue.begin());
            long long accum_distance = current.first;
            long vertex_i = current.second;
 
            for (Edge &edge : vertexes[vertex_i].edges) {
                long long new_distance = accum_distance + edge.weight;
                if (new_distance < distances[edge.to]) {
                    queue.erase({distances[edge.to], edge.to});
                    queue.insert({new_distance, edge.to});
                    distances[edge.to] = new_distance;
                }
            }
        }
 
        return (distances[t_to] == INT64_MAX) ? -1 : distances[t_to];
    }
};
 
int main() {
    std::ifstream in("pathmgep.in");
    std::ofstream out("pathmgep.out");
 
    long N, S, F;
    in >> N >> S >> F;
 
    DiGraph graph(N);
 
    long long weight = 0;
    for (long from_i = 0; from_i < N; ++from_i) {
        for (long to_i = 0; to_i < N; ++to_i) {
            in >> weight;
            if (weight != -1) {
                graph.add_edge(from_i, to_i, weight);
            }
        }
    }
 
    out << graph.shortest_path_weight(S - 1, F - 1);
 
    return 0;
}