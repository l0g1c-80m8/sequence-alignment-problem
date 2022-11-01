#include <cstring>
#include <iostream>
#include <tuple>
#include <sys/time.h>

#include "basic.h"
#include "parse_file.h"
#include "perf_measure.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "Usage:\n - ./seq filename" << std::endl;
        return 1;
    }

    struct timeval begin, end; // store end and start time of execution
    gettimeofday(&begin, 0); // mark start time of execution

    auto base_pairs = new std::string[2];
    read_parse_file(argv[1], base_pairs);

    std::cout << "Base pair 1: " << base_pairs[0] << std::endl;
    std::cout << "Base pair 2: " << base_pairs[1] << std::endl;

    auto result = std::tuple<int, std::string, std::string>({0, "", ""}); // store result
    if (strcmp(argv[2], "basic") == 0)
        result = sequence_alignment_basic(base_pairs[0], base_pairs[1]);
    // TODO: add mode check for sequence_alignment_efficient and get result

    gettimeofday(&end, 0); // mark end time of execution
    double total_memory = getTotalMemory(); // get memory usage
    double total_time = getExecTime(begin, end);

    std::cout << std::get<0>(result) << std::endl; // Cost of a minimum cost alignment
    std::cout << std::get<1>(result) << std::endl; // Aligned sequence of string 1
    std::cout << std::get<2>(result) << std::endl; // Aligned sequence of string 2
    std::cout << total_time << std::endl; // Total execution time
    std::cout << total_memory << std::endl; // Total memory usage

    delete[](base_pairs);
    return 0;
}
