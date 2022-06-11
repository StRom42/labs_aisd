#include <fstream>
#include <iostream>
#include <vector>

std::vector<long> calc_prefix(const std::string& str) {
    std::vector<long> prefix_lens(str.size());
    prefix_lens[0] = 0;
    for (long prefix_size = 0, i = 1; i < str.size(); ++i) {
        while (prefix_size > 0 && str[prefix_size] != str[i]) {
            prefix_size = prefix_lens[prefix_size - 1];
        }
        if (str[prefix_size] == str[i]) {
            prefix_size += 1;
        }
        prefix_lens[i] = prefix_size;
    }
    return prefix_lens;
}

int main() {
    std::ifstream in("prefix.in");
    std::ofstream out("prefix.out");

    std::string s;
    in >> s;

    auto prefix_lens = calc_prefix(s);
    for (auto& elem : prefix_lens) {
        out << elem << " ";
    }

    return 0;
}
