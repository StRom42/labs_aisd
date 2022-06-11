#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

const long long lim = 1e9;

long long calc_palindroms_amount(std::vector<long>& sequence) {
    std::vector<std::vector<long long>> dp(
        sequence.size(), std::vector<long long>(sequence.size(), 0));
    for (long i = sequence.size(); i >= 0; --i) {
        for (long j = 0; j < sequence.size(); ++j) {
            if (i == j) {
                dp[i][j] = 1;
            }
            if (i < j) {
                dp[i][j] = (dp[i + 1][j] + dp[i][j - 1] + 1) % lim;
                if (sequence[i] != sequence[j]) {
                    dp[i][j] = (lim + dp[i][j] - dp[i + 1][j - 1] - 1) % lim;
                }
            }
        }
    }
    return dp[0][sequence.size() - 1];
}

int main() {
    long N;
    std::cin >> N;

    std::vector<long> colors(N);
    for (long i = 0; i < N; ++i) {
        std::cin >> colors[i];
    }

    std::cout << calc_palindroms_amount(colors);

    return 0;
}
