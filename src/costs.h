//
// Created by Rutvik Patel on 10/29/22.
//

#ifndef SEQ_COSTS_H
#define SEQ_COSTS_H

#include <map>
#include <tuple>

int gap_penalty = 30;

std::map<std::tuple<char, char>, int> mismatch_penalties = {
        {{'A', 'A'}, 0},
        {{'A', 'C'}, 110},
        {{'A', 'G'}, 48},
        {{'A', 'T'}, 94},

        {{'C', 'A'}, 110},
        {{'C', 'C'}, 0},
        {{'C', 'G'}, 118},
        {{'C', 'T'}, 48},

        {{'G', 'A'}, 48},
        {{'G', 'C'}, 118},
        {{'G', 'G'}, 0},
        {{'G', 'T'}, 110},

        {{'T', 'A'}, 94},
        {{'T', 'C'}, 48},
        {{'T', 'G'}, 110},
        {{'T', 'T'}, 0},
};

#endif //SEQ_COSTS_H
