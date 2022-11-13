#include "file_utils.h"
#include <fstream>

void read_parse_file(const std::string& path, std::string base_pairs[2]) {
    std::ifstream is;
    int currBasePairIdx = 0;
    int idx;
    is.open(path);
    if(!is) {
        std::cerr << "Error: file could not be opened" << std::endl;
        return;
    }

    is >> base_pairs[currBasePairIdx];
    std::string tmp;
    while(!is.eof()) {
        is >> tmp;
        if(tmp.empty()) {
            break;
        }

        if( tmp.find_first_not_of("0123456789") == std::string::npos) {
            // Line contains a valid number. Modify string.
            idx = std::stoi(tmp);
            base_pairs[currBasePairIdx] = base_pairs[currBasePairIdx].substr(0, idx + 1) + base_pairs[currBasePairIdx] + base_pairs[currBasePairIdx].substr(idx + 1, base_pairs[currBasePairIdx].length());
        } else {
            base_pairs[0] = base_pairs[currBasePairIdx];
            currBasePairIdx++;
            base_pairs[currBasePairIdx] = tmp;
        }
        tmp = "";
    }
    base_pairs[1] = base_pairs[currBasePairIdx];

    is.close();
}

void write_file(const std::string& out_path, std::tuple<int, std::string, std::string> result, long total_memory, double total_time) {
    std::ofstream os;
    os.open(out_path, std::fstream::out | std::fstream::trunc);
    if(os.fail()) {
        std::cerr << "Error: failed to write to file: " << out_path << std::endl;
        return;
    }

    os << std::get<0>(result) << std::endl; // Write cost
    os << std::get<1>(result) << std::endl; // Write aligned sequence 1
    os << std::get<2>(result) << std::endl; // Write aligned sequence 2
    os << total_time << std::endl; // Write execution time (ms)
    os << total_memory << std::endl; // Write total memory usage (bytes)

    os.close();
}