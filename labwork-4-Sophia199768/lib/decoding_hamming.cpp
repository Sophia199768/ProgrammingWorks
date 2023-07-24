#include "decoding_hamming.h"

int find_mistake(std::vector<int> array, int len) {
  int mistake = 0;
  for (int i = 0; i < len; i++) {
    if (array[i] == 1) {
      mistake ^= i + 1;
    }
  }
  return mistake;
}

int decode_hamming(std::vector<int> &hamming_decode, std::vector<int> &array) {
  int parity_bit = 1;
  int mistake;
  int len = hamming_decode.size();

  mistake = find_mistake(hamming_decode, len);

  if (mistake) {
    hamming_decode[mistake - 1] ^= '0' ^ '1';
    mistake = find_mistake(hamming_decode, len);

    if (mistake) {
      return -1;
    }
  }

  for (int k = 0; k < len; k++) {
    if (k + 1 == parity_bit) {
      parity_bit <<= 1;
    } else {
      if (hamming_decode[k] == 1) {
        array.push_back(1);
      } else {
        array.push_back(0);
      }
    }
  }
    return 0;
}