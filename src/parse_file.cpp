#include "parse_file.h"
#include <fstream>

void read_parse_file(std::string path, std::string base_pairs[2]) {
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