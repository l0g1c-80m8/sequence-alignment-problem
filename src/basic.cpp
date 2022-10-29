//
// Created by Rutvik Patel on 10/29/22.
//

#include <iostream>
#include <string>
#include <vector>

#include "costs.h"


/**
 * Find the minimum-cost sequence alignment between two gene sequences.
 *
 * @param seq1 Gene sequence 1 as string.
 * @param seq2 Gene sequence 2 as string.
 * @return the minimum cost of an alignment.
 */
int sequence_alignment_basic(std::string seq1, std::string seq2) {
    // Get sizes of the two string sequences
    auto m = seq1.length();
    auto n = seq2.length();

    // Initialize an all zero dp table
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    // Initialize values for trivial solution - string of size 0 mismatches all chars from other string
    for (int i = 0; i <= m; i++)
        dp[i][0] = i * gap_penalty;
    for (int i = 0; i <= n; i++)
        dp[0][i] = i * gap_penalty;

    // Incrementally solve the sub-problems. Final solution at dp[m][n].
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
