#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

long calc_max_knapsack_weight(long capacity, std::vector<long>& weights) {
    std::vector<bool> dp(capacity + 1, false);
    dp[0] = true;
    for (long i = 0; i < weights.size(); ++i) {
        for (long j = capacity; j >= 0; --j) {
            if (j >= weights[i]) {
                dp[j] = dp[j] || dp[j - weights[i]];
            }
        }
    }
    long max_weight = 0;
    for (long i = capacity; i >= 0; --i) {
        if (dp[i]) {
            max_weight = i;
            break;
        }
    }
    return max_weight;
}

int main() {
    std::ifstream in("knapsack.in");
    std::ofstream out("knapsack.out");

    long S, N;
    in >> S >> N;

    std::vector<long> weights(N);
    for (long i = 0; i < N; ++i) {
        in >> weights[i];
    }

    out << calc_max_knapsack_weight(S, weights);

    return 0;
}
