#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

class Trie {
public:
    Trie() {
    }
    void add_string(const std::string& str, long substr_id) {
        Vertex* current_v = root;
        for (auto& ch : str) {
            if (!current_v->children.count(ch)) {
                current_v->children[ch] = new Vertex;
            }
            current_v = current_v->children[ch];
        }
        current_v->pattern_id = substr_id;
    }

    void link_suffixes() {

        root->suf_link = root;
        std::queue<Vertex*> bst_queue;

        for (auto& child : root->children) {
            child.second->suf_link = root;
            bst_queue.push(child.second);
        }

        while (!bst_queue.empty()) {
            Vertex* current_v = bst_queue.front();
            bst_queue.pop();

            for (auto& child : current_v->children) {
                char ch = child.first;
                Vertex* temp = current_v->suf_link;

                while (temp->children.count(ch) == 0 && temp != root) {
                    temp = temp->suf_link;
                }

                if (temp->children.count(ch)) {
                    child.second->suf_link = temp->children[ch];
                } else {
                    child.second->suf_link = root;
                }

                bst_queue.push(child.second);
            }

            if (current_v->suf_link->pattern_id >= 0) {
                current_v->out_link = current_v->suf_link;
            } else {
                current_v->out_link = current_v->suf_link->out_link;
            }
        }
    }

    void check_substrs_occur(const std::string& str,
                             std::vector<bool>& checks) {
        Vertex* current_state = root;
        for (long i = 0; i < str.size(); ++i) {
            char ch = str[i];
            if (current_state->children.count(ch)) {
                current_state = current_state->children[ch];

                if (current_state->pattern_id >= 0) {
                    checks[current_state->pattern_id] = true;
                }

                Vertex* temp = current_state->out_link;
                while (temp != nullptr) {
                    temp = temp->out_link;
                }
            } else {
                while (current_state != root &&
                       current_state->children.count(ch) == 0) {
                    current_state = current_state->suf_link;
                }
                if (current_state->children.count(ch) != 0) {
                    i -= 1;
                }
            }
        }
    }

private:
    struct Vertex {
        std::map<char, Vertex*> children;
        Vertex* suf_link{nullptr};
        Vertex* out_link{nullptr};
        long pattern_id{-1};
    };

    Vertex* root{new Vertex};
};

int main() {
    std::ifstream in("search4.in");
    std::ofstream out("search4.out");

    long n;
    in >> n;

    std::string S_i;
    Trie trie;
    for (long i = 0; i < n; ++i) {
        in >> S_i;
        trie.add_string(S_i, i);
    }
    trie.link_suffixes();

    std::string t;
    in >> t;

    std::vector<bool> substrs_occur(n, false);
    trie.check_substrs_occur(t, substrs_occur);

    for (bool substr_occurs : substrs_occur) {
        out << ((substr_occurs) ? "YES" : "NO") << std::endl;
    }

    return 0;
}
