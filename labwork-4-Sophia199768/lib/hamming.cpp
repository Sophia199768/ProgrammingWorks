#include "hamming.h"

std::vector<int> generateHammingCode(std::vector<int> bits, int size, int number_parity_bit) {
  long long size_of_vector = number_parity_bit + size;
  int j = 0;
  std::vector<int> hamming_code(size_of_vector);

  for (int i = 0; i < number_parity_bit; ++i) {
    hamming_code[pow(2, i) - 1] = -1;
  }

  for (int i = 0; i < size_of_vector; i++) {
    if (hamming_code[i] != -1) {
      hamming_code[i] = bits[j];
      j++;
    }
  }

  for (int i = 0; i < size_of_vector; i++) {
    if (hamming_code[i] != -1) {
      continue;
    }

    int x = log2(i + 1);
    int one_count = 0;

    for (int j = i + 2; j <= size_of_vector; ++j) {
      if (j & (1 << x)) {
        if (hamming_code[j - 1] == 1) {
          one_count++;
        }
      }
    }

    if (one_count % 2 == 0) {
      hamming_code[i] = 0;
    } else {
      hamming_code[i] = 1;
    }
  }
  return hamming_code;

}

std::vector<int> findHammingCode(std::vector<int> &bits) {
  int size = bits.size();
  int number_parity_bit = 1;
  while (pow(2, number_parity_bit) < (size + number_parity_bit + 1)) {
    number_parity_bit++;
  }

  return generateHammingCode(bits, size, number_parity_bit);
}

