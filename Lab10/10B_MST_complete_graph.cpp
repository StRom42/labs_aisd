#include <algorithm>
#include <cmath>
#include <float.h>
#include <fstream>
#include <iostream>
#include <vector>
 
struct Vertex {
  private:
    int m_x, m_y;
    double m_weight{DBL_MAX};
 
  public:
    Vertex(int t_x = 0, int t_y = 0) : m_x(t_x), m_y(t_y){};
    void update_weight(double t_weight) {
        m_weight = std::min(t_weight, m_weight);
    }
    double distance_to(Vertex &v) {
        return std::sqrt(std::pow(v.m_x - m_x, 2) + std::pow(v.m_y - m_y, 2));
    }
    bool operator<(Vertex &v) {
        return m_weight > v.m_weight;
    }
    double get_weight() const {
        return m_weight;
    }
};
 
class Graph {
  private:
    std::vector<Vertex> vertexes;
 
  public:
    Graph(std::istream &in) {
        int n;
        in >> n;
 
        int x_i, y_i;
        for (int i = 0; i < n; ++i) {
            in >> x_i >> y_i;
            vertexes.push_back(Vertex(x_i, y_i));
        }
    }
 
    double MST_sum() {
        double sum = 0;
        vertexes[0].update_weight(0);
        while (!vertexes.empty()) {
            Vertex current_vertex = vertexes.front();
            sum += current_vertex.get_weight();
            vertexes.erase(vertexes.begin());
            for (int i = 0; i < vertexes.size(); ++i) {
                double new_weight = vertexes[i].distance_to(current_vertex);
                vertexes[i].update_weight(new_weight);
            }
            std::make_heap(vertexes.begin(), vertexes.end());
        }
        return sum;
    }
};
 
int main() {
    std::ifstream in("spantree.in");
    std::ofstream out("spantree.out");
 
    Graph G(in);
    out.precision(10);
    out << G.MST_sum();
 
    return 0;
}