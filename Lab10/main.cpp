#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>

struct Edge {
  public:
    int to{-1};
    int weight{INT_MAX};

  public:
    Edge(int t_to = 0, int t_weight = 1) : to(t_to), weight(t_weight){};
    bool operator<(Edge edge) {
        return weight < edge.weight;
    }
};

struct Vertex {
    std::vector<Edge> edges;
};

class Graph {
  private:
    std::vector<Vertex> vertexes;

  private:
    Graph(int vertexes_amount) {
        vertexes.resize(vertexes_amount);
    }

    void top_sort(int vertex_i, std::vector<int> &top_order,
                  std::vector<bool> &visited) {
        visited[vertex_i] = true;
        for (Edge &edge : vertexes[vertex_i].edges) {
            if (!visited[edge.to]) {
                top_sort(edge.to, top_order, visited);
            }
        }
        top_order.push_back(vertex_i);
    }

    void mark_component(int vertex_i, int component_id,
                        std::vector<int> &components) {
        components[vertex_i] = component_id;
        for (Edge &edge : vertexes[vertex_i].edges) {
            if (components[edge.to] == -1) {
                mark_component(edge.to, component_id, components);
            }
        }
    }
    void reverse_edges(Graph &graph, Graph &reversed_graph) {
        for (int v_i = 0; v_i < graph.vertexes.size(); ++v_i) {
            for (Edge &edge : graph.vertexes[v_i].edges) {
                reversed_graph.add_edge(edge.to, v_i, edge.weight);
            }
        }
    }

    bool is_reachable_from(int vertex_i) {
        std::vector<int> components(vertexes.size(), -1);
        mark_component(vertex_i, 0, components);
        for (int component_id : components) {
            if (component_id != 0) {
                return false;
            }
        }
        return true;
    }

    int condense_graph(std::vector<int> &components) {
        std::vector<int> top_order;
        std::vector<bool> visited(vertexes.size(), false);
        for (int i = 0; i < vertexes.size(); ++i) {
            if (!visited[i]) {
                top_sort(i, top_order, visited);
            }
        }
        int component_counter = -1;
        Graph reversed_graph(vertexes.size());
        reverse_edges(*this, reversed_graph);
        for (int i = top_order.size() - 1; i >= 0; --i) {
            if (components[top_order[i]] == -1) {
                component_counter += 1;
                reversed_graph.mark_component(top_order[i], component_counter,
                                              components);
            }
        }
        return component_counter + 1;
    }

    long long MST_sum(int root) {
        long long mst_sum = 0;

        std::vector<int> min_weights(vertexes.size(), INT_MAX);
        for (int v_i = 0; v_i < vertexes.size(); ++v_i) {
            for (Edge &edge : vertexes[v_i].edges) {
                min_weights[edge.to] =
                    std::min(edge.weight, min_weights[edge.to]);
            }
        }

        Graph G_O(vertexes.size());
        for (int v_i = 0; v_i < vertexes.size(); ++v_i) {
            if (v_i != root) {
                mst_sum += min_weights[v_i];
            }
            for (Edge &edge : vertexes[v_i].edges) {
                if (edge.weight == min_weights[edge.to]) {
                    G_O.add_edge(v_i, edge.to, 0);
                }
            }
        }

        if (G_O.is_reachable_from(root)) {
            return mst_sum;
        }

        std::vector<int> zero_components(vertexes.size(), -1);
        int new_components_amount = G_O.condense_graph(zero_components);
        Graph G_new(new_components_amount);

        for (int v_i = 0; v_i < vertexes.size(); ++v_i) {
            for (Edge &edge : vertexes[v_i].edges) {
                if (zero_components[v_i] != zero_components[edge.to]) {
                    G_new.add_edge(zero_components[v_i],
                                   zero_components[edge.to],
                                   edge.weight - min_weights[edge.to]);
                }
            }
        }
        mst_sum += G_new.MST_sum(zero_components[root]);

        return mst_sum;
    }

  public:
    Graph(std::istream &in) {
        int n, m;
        in >> n >> m;
        vertexes.resize(n);

        int b_i, e_i, w_i;
        for (int i = 0; i < m; ++i) {
            in >> b_i >> e_i >> w_i;
            --b_i, --e_i;
            add_edge(b_i, e_i, w_i);
        }
    }
    bool is_reachable_from_root() {
        return is_reachable_from(0);
    }

    long long MST_sum() {
        return MST_sum(0);
    }

    void add_edge(int begin_v, int end_v, int weight = 1) {
        vertexes[begin_v].edges.push_back(Edge(end_v, weight));
    }
};

int main() {
    std::ifstream in("chinese.in");
    std::ofstream out("chinese.out");

    Graph G(std::cin);
    if (G.is_reachable_from_root()) {
        std::cout << "YES\n" << G.MST_sum();
    } else {
        std::cout << "NO";
    }

    return 0;
}
