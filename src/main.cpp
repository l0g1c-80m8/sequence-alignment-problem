#include <iostream>
#include <tuple>

#include "basic.h"
#include "parse_file.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "Usage:\n - ./seq filename" << std::endl;
        return 1;
    }

    auto base_pairs = new std::string[2];
    read_parse_file(argv[1], base_pairs);

    std::cout << "Base pair 1: " << base_pairs[0] << std::endl;
    std::cout << "Base pair 2: " << base_pairs[1] << std::endl;

    auto result = std::tuple<int, std::string, std::string>({0, "", ""});
    if (strcmp(argv[2], "basic") == 0)
        result = sequence_alignment_basic(base_pairs[0], base_pairs[1]);
    // TODO: add mode check for sequence_alignment_efficient and get result

    std::cout << std::get<0>(result) << std::endl; // Cost of a minimum cost alignment
    std::cout << std::get<1>(result) << std::endl; // Aligned sequence of string 1
    std::cout << std::get<2>(result) << std::endl; // Aligned sequence of string 2

    delete[](base_pairs);
    return 0;
}
