#include <fstream>
#include <iostream>
#include <limits.h>
#include <queue>
#include <vector>

struct Edge {
  public:
    int m_weight{INT_MAX};
    int m_begin_i{-1};
    int m_end_i{-1};

  public:
    Edge(int t_begin_i = 0, int t_end_i = 0, int t_weight = 1)
        : m_weight(t_weight), m_begin_i(t_begin_i), m_end_i(t_end_i){};
};

struct Vertex {
    std::vector<Edge> m_edges;
};

class Graph {
  private:
    std::vector<Vertex> vertexes;

  public:
    Graph(std::istream &in) {
        int n, m;
        in >> n >> m;
        vertexes.resize(n);

        int b_i, e_i, w_i;
        for (int i = 0; i < m; ++i) {
            in >> b_i >> e_i >> w_i;
            --b_i, --e_i;
            vertexes[b_i].m_edges.push_back(Edge(b_i, e_i, w_i));
            vertexes[e_i].m_edges.push_back(Edge(e_i, b_i, w_i));
        }
    }

    long long MST_sum() {
        long long sum = 0;
        std::vector<bool> in_MST(vertexes.size(), false);
        auto comp = [](Edge a, Edge b) { return a.m_weight > b.m_weight; };

        std::priority_queue<Edge, std::vector<Edge>, decltype(comp)> mst_queue(
            comp);
        auto add_edges = [&mst_queue, &in_MST, this](int vertex_i) mutable {
            in_MST[vertex_i] = true;
            for (Edge &edge : this->vertexes[vertex_i].m_edges) {
                if (!in_MST[edge.m_end_i]) {
                    mst_queue.push(edge);
                }
            }
        };

        add_edges(0);
        while (!mst_queue.empty()) {
            Edge edge = mst_queue.top();
            mst_queue.pop();

            if (!in_MST[edge.m_end_i]) {
                sum += edge.m_weight;
            }
            add_edges(edge.m_end_i);
        }
        return sum;
    }
};

int main() {
    std::ifstream in("spantree3.in");
    std::ofstream out("spantree3.out");

    Graph G(in);
    out << G.MST_sum();

    return 0;
}
