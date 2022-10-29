//
// Created by Rutvik Patel on 10/29/22.
//

#include <iostream>
#include <string>
#include <vector>

#include "costs.h"

int sequence_alignment_basic(std::string seq1, std::string seq2) {
    auto m = seq1.length();
    auto n = seq2.length();

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++)
        dp[i][0] = i * 30;
    for (int i = 0; i <= n; i++)
        dp[0][i] = i * 30;

    for (int i = 1; i <=m; i++) {
        for (int j = 1; j <= n; j++) {
            if (seq1.at(i - 1) == seq2.at(j - 1))
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = std::min({
                    dp[i - 1][j - 1] + mismatch_penalties[{seq1.at(i - 1), seq2.at(j - 1)}],
                    dp[i - 1][j] + gap_penalty,
                    dp[i][j - 1] + gap_penalty
                });
        }
    }
    return dp.back().back();
}
