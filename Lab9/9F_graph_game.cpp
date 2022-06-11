#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

enum Player { first, second };

struct Vertex {
    std::vector<int> neighbours;
    bool visited{false};
    Player who_moves{first};
};

class Graph_game {
  private:
    std::vector<Vertex> vertexes;
    int start_position;

  private:
    void mark_graph(int vertex_i) {
        vertexes[vertex_i].visited = true;
        if (vertexes[vertex_i].neighbours.empty()) {
            return;
        }
        for (int neighbour_i : vertexes[vertex_i].neighbours) {
            if (!vertexes[neighbour_i].visited) {
                mark_graph(neighbour_i);
            }
        }
        for (int neighbour_i : vertexes[vertex_i].neighbours) {
            if (vertexes[neighbour_i].who_moves == first &&
                vertexes[neighbour_i].visited) {
                vertexes[vertex_i].who_moves = second;
                return;
            }
        }
    }

  public:
    Graph_game(std::istream &in) {
        int N, M;
        in >> N >> M >> start_position;
        start_position -= 1;
        vertexes.resize(N);

        int v1_i, v2_i;
        for (int i = 0; i < M; ++i) {
            in >> v1_i >> v2_i;
            vertexes[v1_i - 1].neighbours.push_back(v2_i - 1);
        }
    }

    bool will_first_win() {
        mark_graph(start_position);
        return vertexes[start_position].who_moves != first;
    }
};

int main() {
    std::ifstream in("game.in");
    std::ofstream out("game.out");

    Graph_game game(in);
    out << ((game.will_first_win()) ? "First player wins"
                                    : "Second player wins");
    return 0;
}
