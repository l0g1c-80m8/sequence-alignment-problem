//
// Created by Rutvik Patel on 10/29/22.
//

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

#include "costs.h"


/**
 * Find the minimum-cost sequence alignment between two gene sequences.
 *
 * @param seq1 Gene sequence 1 as string.
 * @param seq2 Gene sequence 2 as string.
 * @return the minimum cost of an alignment with the aligned sequences as a 3-tuple.
 */
std::tuple<int, std::string, std::string> sequence_alignment_basic(std::string seq1, std::string seq2) {
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
    for (int i = 1; i <=m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = std::min({
                dp[i - 1][j - 1] + mismatch_penalties[{seq1.at(i - 1), seq2.at(j - 1)}],
                dp[i - 1][j] + gap_penalty,
                dp[i][j - 1] + gap_penalty
            });

    // Backtrack through the sub-problems and construct the solution strings
    auto i = m;
    auto j = n;
    std::vector<char> aligned_seq1;
    std::vector<char> aligned_seq2;

    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i - 1][j - 1] + mismatch_penalties[{seq1.at(i - 1), seq2.at(j - 1)}]) {
            aligned_seq1.insert(aligned_seq1.begin(), seq1.at(i - 1));
            aligned_seq2.insert(aligned_seq2.begin(), seq2.at(j - 1));
            i -= 1;
            j -= 1;
        } else if (dp[i][j] == dp[i - 1][j] + gap_penalty) {
            aligned_seq1.insert(aligned_seq1.begin(), seq1.at(i - 1));
            aligned_seq2.insert(aligned_seq2.begin(), '_');
            i -= 1;
        } else if (dp[i][j] == dp[i][j - 1] + gap_penalty) {
            aligned_seq1.insert(aligned_seq1.begin(), '_');
            aligned_seq2.insert(aligned_seq2.begin(), seq2.at(j - 1));
            j -= 1;
        }
    }

    // Fill the blanks at the beginning of the strings
    while (i > 0) {
        aligned_seq1.insert(aligned_seq1.begin(), seq1.at(i - 1));
        aligned_seq2.insert(aligned_seq2.begin(), '_');
        i -= 1;
    }
    while (j > 0) {
        aligned_seq1.insert(aligned_seq1.begin(), '_');
        aligned_seq2.insert(aligned_seq2.begin(), seq2.at(j - 1));
        j -= 1;
    }

    return {dp.back().back(), std::string(aligned_seq1.begin(), aligned_seq1.end()), std::string(aligned_seq2.begin(), aligned_seq2.end())};
}
