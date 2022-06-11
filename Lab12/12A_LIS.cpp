#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

const long INF = INT32_MAX;

std::vector<long> find_LIS(std::vector<long>& sequence) {
    std::vector<long> dp(sequence.size() + 1, INF);
    std::vector<long> parents(sequence.size() + 1, -1);
    std::vector<long> indexes_min(sequence.size() + 1, -1);

    dp[0] = -INF;
    long long LIS_len = 0;

    for (long i = 0; i < sequence.size(); ++i) {
        auto supremum_i = std::upper_bound(dp.begin(), dp.end(), sequence[i]);
        long long subseq_len = supremum_i - dp.begin();
        if (dp[subseq_len - 1] < sequence[i] && sequence[i] < dp[subseq_len]) {
            dp[subseq_len] = sequence[i];
            indexes_min[subseq_len] = i;
            parents[i] = indexes_min[subseq_len - 1];
            LIS_len = std::max(LIS_len, subseq_len);
        }
    }

    std::vector<long> LIS;
    long current_i = indexes_min[LIS_len];
    while (current_i != -1) {
        LIS.push_back(sequence[current_i]);
        current_i = parents[current_i];
    }
    std::reverse(LIS.begin(), LIS.end());

    return LIS;
}

int main() {
    long N;
    std::cin >> N;

    std::vector<long> a(N);
    for (long i = 0; i < N; ++i) {
        std::cin >> a[i];
    }

    auto LIS = find_LIS(a);
    std::cout << LIS.size() << std::endl;
    for (auto& elem : LIS) {
        std::cout << elem << " ";
    }
    return 0;
}
