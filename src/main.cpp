#include <cstring>
#include <iostream>
#include <tuple>
#include <sys/time.h>

#include "basic.h"
#include "efficient.h"
#include "file_utils.h"
#include "perf_measure.h"

int main(int argc, char *argv[]) {
    // Check input arg length
    if(argc < 3) {
        std::cout << "Usage:\n - ./seq input_path output_path" << std::endl;
        return 1;
    }

    // Initialize variables for calculating elapsed time
    struct timeval begin{}, end{};
    gettimeofday(&begin, nullptr);

    auto base_pairs = new std::string[2];
    // Parse the input file & create base pairs from this file
    read_parse_file(argv[1], base_pairs);

    // Run the correct algorithm based on input from sh file & store result
    auto result = std::tuple<int, std::string, std::string>({0, "", ""});
    if (strcmp(argv[3], "basic") == 0)
        result = sequence_alignment_basic(base_pairs[0], base_pairs[1]);
    else if(strcmp(argv[3], "efficient") == 0)
        result = sequence_alignment_efficient(base_pairs[0], base_pairs[1]);
    else
        return 0;

    // Calculate memory usage & total time elapsed
    gettimeofday(&end, nullptr); // mark end time of execution
    long total_memory = getTotalMemory(); // get memory usage
    double total_time = getExecTime(begin, end);

    // Write the resulting alignment & other info to file
    write_file(argv[2], result, total_memory, total_time);

    // Memory cleanup
    delete[](base_pairs);
    return 0;
}
