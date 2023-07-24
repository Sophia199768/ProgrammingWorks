#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include "hamming.h"
#include "decoding_hamming.h"

class Archiver {

private:
    std::string link;
    std::string path_of_archive;
    std::string archiver_name;
    std::vector<std::string> names_of_files;
    std::vector<long long> size_of_files;
    std::vector<int> coding_words;
    std::vector<long long> positions;
public:
    Archiver(std::vector<std::string>& input, std::string& path, std::string& archive_name, int len_of_coding);
    void GetInfo();
    void CreateArchive();
    void Append(std::string& new_file);
    void ListOfNames();
    void Extract(std::vector<std::string> names = {});
    void DeleteFile(std::string& name_of_delete_file);
    void Concatenate(std::vector<std::string>& names_of_archives);
    void ToBinary(char byte, std::vector<int>& arr);
    int FromBinary(std::vector<int>& arr);
    long long CountLen(long long size_of_current, int number_bit);
    void Coding(int len_of_word, std::string& file_name);
    void Decode(int len_of_word, std::string& name_of_file, long long pos, long long size_file);
};