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

std::vector<long> kmp_find(const std::string& str, const std::string& substr) {
    std::vector<long> occurances;
    auto prefix = calc_prefix(substr);
    for (long k = 0, i = 0; i < str.size(); ++i) {
        while (k > 0 && str[i] != substr[k]) {
            k = prefix[k - 1];
        }
        if (str[i] == substr[k]) {
            k += 1;
        }
        if (k == substr.size()) {
            occurances.push_back(i - substr.size() + 2);
        }
    }
    return occurances;
}

int main() {
    std::ifstream in("search1.in");
    std::ofstream out("search1.out");

    std::string p, t;
    in >> p >> t;

    auto occurances = kmp_find(t, p);
    out << occurances.size() << std::endl;
    for (auto& elem : occurances) {
        out << elem << " ";
    }

    return 0;
}
