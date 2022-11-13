//
// Created by Jordan Bettencourt on 10/27/2022.
//

#ifndef SEQ_FILE_UTILS_H
#define SEQ_FILE_UTILS_H
#include <iostream>

void read_parse_file(const std::string& path, std::string base_pairs[2]);
void write_file(const std::string& out_path, std::tuple<int, std::string, std::string> result, long total_memory, double total_time);

#endif //SEQ_FILE_UTILS_H
