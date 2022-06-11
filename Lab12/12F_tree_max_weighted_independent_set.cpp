#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

class Tree {
    struct Vertex {
        std::vector<long> children;
        long weight{1};
        long including_sum{0};
        long excluding_sum{0};
    };

private:
    std::vector<Vertex> vertexes;
    long root_index{0};

    void calc_ind_set(long vertex_i) {
        for (long child_i : vertexes[vertex_i].children) {
            calc_ind_set(child_i);
            vertexes[vertex_i].including_sum += vertexes[child_i].excluding_sum;
            vertexes[vertex_i].excluding_sum +=
                std::max(vertexes[child_i].excluding_sum,
                         vertexes[child_i].including_sum);
        }
        vertexes[vertex_i].including_sum += vertexes[vertex_i].weight;
    }

public:
    Tree(long vertex_amount = 1) {
        vertexes.resize(vertex_amount);
    }

    void add_edge(long from_i, long to_i) {
        vertexes[from_i].children.push_back(to_i);
    }
    void set_vertex_weight(long vertex_i, long t_weight) {
        vertexes[vertex_i].weight = t_weight;
    }
    void mark_root(long vertex_i) {
        root_index = vertex_i;
    }

    long calc_max_ind_set() {
        calc_ind_set(root_index);

        return std::max(vertexes[root_index].excluding_sum,
                        vertexes[root_index].including_sum);
    }
};

int main() {
    std::ifstream in("selectw.in");
    std::ofstream out("selectw.out");

    long N;
    in >> N;

    Tree tree(N);

    long parent_i, weight_i;
    for (long i = 0; i < N; ++i) {
        in >> parent_i >> weight_i;
        tree.set_vertex_weight(i, weight_i);
        if (parent_i != 0)
            tree.add_edge(parent_i - 1, i);
        else
            tree.mark_root(i);
    }

    out << tree.calc_max_ind_set();

    return 0;
}
