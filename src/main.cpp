#include <iostream>

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

    delete[](base_pairs);
    return 0;
}