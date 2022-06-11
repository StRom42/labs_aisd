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
    long n;
    std::string s;
    std::cin >> n >> s;

    std::vector<std::vector<long>> machine(s.size() + 1, std::vector<long>(n));
    auto prefix = calc_prefix(s);
    const char a_charcode = 'a';

    for (long q = 0; q <= s.size(); ++q) {
        for (long char_i = 0; char_i < n; ++char_i) {
            char current_char = a_charcode + char_i;
            if (q > 0 && current_char != s[q]) {
                machine[q][char_i] = machine[prefix[q - 1]][char_i];
            } else {
                machine[q][char_i] = q + ((current_char == s[q]) ? 1 : 0);
            }
        }
    }

    for (auto& line : machine) {
        for (auto& elem : line) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
