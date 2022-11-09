//
// Created by Rutvik Patel on 11/9/22.
//

#include "efficient.h"
#include "basic.h"
#include <algorithm>
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

/**
 * Find the minimum-cost sequence alignment between two gene sequences.
 *
 * @param seq1 Gene sequence 1 as string.
 * @param seq2 Gene sequence 2 as string.
 * @return the minimum cost of an alignment with the aligned sequences as a 3-tuple.
 */
std::tuple<int, std::string, std::string> sequence_alignment_efficient(std::string seq1, std::string seq2) {
    // Get sizes of the two string sequences
    auto m = seq1.length();
    auto n = seq2.length();

    if (m < 2 || n < 2) {
        return sequence_alignment_basic(seq1, seq2);
    }

    auto seq1_left = seq1.substr(0, (int) m / 2);
    auto seq1_right = seq1.substr((int) m / 2);

    std::vector<int> cost_left(n + 1, 0);
    std::vector<int> cost_right(n + 1, 0);

    auto dp1 = sequence_alignment(seq1_left, seq2);
    std::reverse(seq2.begin(), seq2.end());
    std::reverse(seq1_right.begin(), seq1_right.end());
    auto dp2 = sequence_alignment(seq1_right, seq2);
    std::reverse(seq2.begin(), seq2.end());

    // Find split point. We need to compare seq1_left with all variations of y and seq1_right with all variations of y
    // and then take the minimum of these to find our split point to recursively solve for the correct alignment.
    int min = INT_MAX;
    int idx = -1;
    for(int i = 0; i < n + 1; i++) {
        int cost = dp1[seq1_left.length()][i] + dp2[seq1_right.length()][n - i];
        if(cost < min) {
            min = cost;
            idx = i;
        }
    }

    auto left_alignment = sequence_alignment_efficient(seq1_left, seq2.substr(0, idx));
    auto right_alignment = sequence_alignment_efficient(seq1_right, seq2.substr(idx));

    auto right_alignment_seq_2 = std::get<2>(right_alignment);
//    std::reverse(right_alignment_seq_1.begin(), right_alignment_seq_1.end());
    std::reverse(right_alignment_seq_2.begin(), right_alignment_seq_2.end());


    return {
            min,
            std::get<1>(left_alignment) + std::get<1>(right_alignment),
            std::get<2>(left_alignment) + std::get<2>(right_alignment),
        };
}
