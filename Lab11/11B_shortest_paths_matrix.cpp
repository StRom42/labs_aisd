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
    std::vector<long long> shortest_paths_weight(long t_from) {
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
 
        return distances;
    }
};
 
int main() {
    std::ifstream in("pathsg.in");
    std::ofstream out("pathsg.out");
 
    long N, M;
    in >> N >> M;
 
    DiGraph graph(N);
 
    long from_i, to_i, weight_i;
    for (int i = 0; i < M; ++i) {
        in >> from_i >> to_i >> weight_i;
        --from_i, --to_i;
        graph.add_edge(from_i, to_i, weight_i);
    }
 
    for (int i = 0; i < N; ++i) {
        for (long long &weight_i : graph.shortest_paths_weight(i)) {
            out << weight_i << " ";
        }
        out << std::endl;
    }
 
    return 0;
}