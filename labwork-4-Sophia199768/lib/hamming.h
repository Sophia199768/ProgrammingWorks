#pragma once
#include <vector>
#include <cmath>

std::vector<int> generateHammingCode(std::vector<int> msgBits, int size, int number_parity_bit);
std::vector<int> findHammingCode(std::vector<int> &msgBit);