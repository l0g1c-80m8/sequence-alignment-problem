//
// Created by Rutvik Patel on 11/9/22.
//

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

#include "basic.h"
#include "costs.h"


/**
 * A dynamic programming based approach to find the value of sequence alignment between two sequences.
 *
 * @param seq1 Gene sequence 1 as string.
 * @param seq2 Gene sequence 2 as string.
 * @return the minimum cost of an alignment with the aligned sequences as a 3-tuple.
 */
std::vector<int> space_efficient_sequence_alignment(std::string seq1, std::string seq2, bool reverse = false) {
    // Reverse strings if required before further processing
    if (reverse) {
        std::reverse(seq1.begin(), seq1.end());
        std::reverse(seq2.begin(), seq2.end());
    }

    // Get sizes of the two string sequences
    auto m = seq1.length();
    auto n = seq2.length();

    // Initialize cost vectors to store alignment cost of seq 1 with all of seq 2
    std::vector<int> prev_costs(n + 1, 0);
    std::vector<int> costs(n + 1, 0);

    // Initialize values for trivial solution (none of seq 1 is matched with seq 2)
    for (int i = 0; i <= n; i++)
        prev_costs[i] = i * gap_penalty;

    // Find the costs of alignment of parts of seq 1 with all of seq 2
    for (int i = 1; i <= m; i++) {
        costs[0] = i * gap_penalty; // Required for trivial solution (seq 1 is matched with none of seq2)
        for (int j = 1; j <= n; j++)
            costs[j] = std::min({
                prev_costs[j - 1] + mismatch_penalties[{seq1.at(i - 1), seq2.at(j - 1)}],
                prev_costs[j] + gap_penalty,
                costs[j - 1] + gap_penalty
            });
        prev_costs.assign(costs.begin(), costs.end());
    }

    return costs;
}

/**
 * A divide and conquer based approach to find the minimum-cost sequence alignment between two gene sequences.
 *
 * @param seq1 Gene sequence 1 as string.
 * @param seq2 Gene sequence 2 as string.
 * @return the minimum cost of an alignment with the aligned sequences as a 3-tuple.
 */
std::tuple<int, std::string, std::string> sequence_alignment_efficient(std::string seq1, std::string seq2) {
    // Get sizes of the two string sequences
    auto m = seq1.length();
    auto n = seq2.length();

    // Solve small problems trivially
    if (m < 3 || n < 3)
        return sequence_alignment_basic(seq1, seq2);

    // (Divide step) Split seq 1 in two equal halves and find split point in seq 2
    auto left_alignment_costs = space_efficient_sequence_alignment(seq1.substr(0, m / 2), seq2, false);
    auto right_alignment_costs = space_efficient_sequence_alignment(seq1.substr(m / 2), seq2, true);

    // Find split point in seq 2 corresponding to index (m / 2) in seq 1
    int min_value = INT_MAX;
    int min_idx = -1;
    for(int i = 0; i <= n; i++) {
        int alignment_cost = left_alignment_costs[i] + right_alignment_costs[n - i];
        if (min_value > alignment_cost) {
            min_value = alignment_cost;
            min_idx = i;
        }
    }

    // (Conquer step) Solve the sub-problems recursively
    auto left_alignment = sequence_alignment_efficient(seq1.substr(0, m / 2), seq2.substr(0, min_idx));
    auto right_alignment = sequence_alignment_efficient(seq1.substr(m / 2), seq2.substr(min_idx));

    // (Combine step) Concatenate the strings to generate the full sequence
    return {
        std::get<0>(left_alignment) + std::get<0>(right_alignment),
        std::get<1>(left_alignment) + std::get<1>(right_alignment),
        std::get<2>(left_alignment) + std::get<2>(right_alignment),
    };
}
