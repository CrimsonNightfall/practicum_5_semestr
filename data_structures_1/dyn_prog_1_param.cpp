#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> nails(n);
    for (int &nail : nails) {
        std::cin >> nail;
    }

    std::sort(nails.begin(), nails.end());
    std::vector<int> dp(n);
    dp[0] = dp[1] = nails[1] - nails[0];

    for (int i = 2; i < n; ++i) {
        dp[i] = nails[i] - nails[i - 1] + std::min(dp[i - 1], dp[i - 2]);
    }
    std::cout << dp[n - 1] << std::endl;

    return 0;
}