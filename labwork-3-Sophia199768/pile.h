#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>


void TheMatrix(uint16_t height, uint16_t width, uint64_t max_iter, uint64_t frequent, const std::string& input_string,
				const std::string& link, const std::string& way_out, bool max_it, bool flag_out);

void SavePicture(std::string picture, uint16_t height, uint16_t width, uint64_t** pile);
