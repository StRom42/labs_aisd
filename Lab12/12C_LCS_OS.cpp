#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

template <class T>
T reverse(T sequence) {
    std::reverse(sequence.begin(), sequence.end());
    return sequence;
}

std::vector<long> calc_LCS_last_line(std::string& a, std::string& b) {
    std::vector<long> current_line(b.size() + 1, 0);
    for (auto& elem_a : a) {
        auto previous_line = std::vector<long>(current_line);
        for (long i = 0; i < b.size(); ++i) {
            if (elem_a == b[i]) {
                current_line[i + 1] = previous_line[i] + 1;
            } else {
                current_line[i + 1] =
                    std::max(current_line[i], previous_line[i + 1]);
            }
        }
    }
    return current_line;
}

std::string find_LCS(std::string& x, std::string& y) {
    if (x.size() == 0) {
        return "";
    }
    if (x.size() == 1) {
        if (y.find(x[0]) != std::string::npos) {
            return std::string(1, x[0]);
        }
        return "";
    }

    long middle_i = x.size() / 2;

    auto x_1 = x.substr(0, middle_i);
    auto x_2 = x.substr(middle_i);
    auto x_2_reversed = reverse(x_2);
    auto y_reversed = reverse(y);

    auto lcs1 = calc_LCS_last_line(x_1, y);
    auto lcs2 = reverse(calc_LCS_last_line(x_2_reversed, y_reversed));

    long max = -1;
    long index_max = -1;

    for (long i = 0; i < lcs1.size(); ++i) {
        if (lcs1[i] + lcs2[i] >= max) {
            max = lcs1[i] + lcs2[i];
            index_max = i;
        }
    }

    auto y_1 = y.substr(0, index_max);
    auto y_2 = y.substr(index_max);

    return find_LCS(x_1, y_1) + find_LCS(x_2, y_2);
}

int main() {
    std::string str1, str2;

    std::cin >> str1 >> str2;

    auto LCS = find_LCS(str1, str2);
    std::cout << LCS << std::endl;
    return 0;
}
