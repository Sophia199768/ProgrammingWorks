#include "arc.h"
#include "haffman.h"

Archiver::Archiver(std::vector<std::string>& input, std::string& path, std::string& archive_name, int len_of_coding) {
  for (std::string i: input) {
    names_of_files.push_back(i); // rewrite all names of files
  }

  coding_words.push_back(len_of_coding);
  path_of_archive = path;
  link = path + '\\';
  link = link + archive_name + ".haf";
  archiver_name = archive_name;
}

void Archiver::GetInfo() {
  coding_words.clear();
  char byte;
  int counter;
  long long head = 0;
  int name_number = 0;
  std::string size_of_header;
  std::string info;
  std::string add;
  std::fstream archive;
  archive.open(link, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
  
  while (!(archive.eof())) {
    archive.read(&byte, 1);
    
    if (archive.eof()) {
      break;
    }
    
    if (byte == '<') {
      counter = 0;
      while (byte != '>') {
        archive.read(&byte, 1);
        if (byte == '|' or byte == '>') {
          switch (counter) {
            case 0:
              names_of_files.push_back(info);
              counter++;
              info.clear();
              break;
            case 1:
              size_of_files.push_back(atoll(info.c_str()));
              counter++;
              info.clear();
              break;
            case 2:
              int len_of_word = atoi(info.c_str());
              coding_words.push_back(len_of_word);
              info.clear();
              break;
          }
        }

        if (byte != '|' and byte != '<' and byte != '>') {
          info += byte;
        }

      }
      positions.push_back(archive.tellg());
      archive.seekg(size_of_files[size_of_files.size() - 1], std::ios::cur);
    }
  }

}

long long Archiver::CountLen(long long size_of_current, int number_bit) {
  return (long long)ceil((ceil((size_of_current * 8.0) / (coding_words[0])) * (coding_words[0] + number_bit)) / 8);
}

void Archiver::CreateArchive() {
  char byte;
  std::ifstream current_file;
  std::ofstream archive;
 // std::ofstream small_archive; // new


  std::string len;

  archive.open(link, std::ios_base::binary | std::ios_base::out);
  //archive.open(path_of_archive + "small_archive.haf" , std::ios_base::binary | std::ios_base::out); // new

  for (long long i = 0; i < names_of_files.size(); i++) {
    current_file.open(path_of_archive + '\\' + names_of_files[i], std::ios_base::binary | std::ios_base::in);
    byte = '<';
    archive.write(&byte, 1);

    archive << names_of_files[i];
    byte = '|';
    archive.write(&byte, 1);

    current_file.seekg(0, std::ios::end); //size
    int number_bit = 1;

    while (pow(2, number_bit) < (coding_words[0] + number_bit + 1)) { // find count of bit_chet for know len of word
      number_bit++; // len of coded word
    }

    long long size_of_current = current_file.tellg();

    archive << CountLen(size_of_current, number_bit); // len coded file
    current_file.close();
    byte = '|';
    archive.write(&byte, 1);

    archive << coding_words[0];
    byte = '>';
    archive.write(&byte, 1);

    archive.close();
    Coding(coding_words[0], names_of_files[i]);
    archive.open(link, std::ios_base::binary | std::ios_base::app);
  }
  archive.close();
}

void Archiver::Append(std::string& new_file) {
  std::ifstream current_file;
  std::ofstream archive;
  char byte;
  archive.open(link, std::ios_base::binary | std::ios_base::app);
  current_file.open(path_of_archive + '\\' + new_file, std::ios_base::binary | std::ios_base::in);

  byte = '<';
  archive.write(&byte, 1);

  archive << new_file;
  byte = '|';
  archive.write(&byte, 1);

  current_file.seekg(0, std::ios::end);

  int number_bit = 1;
  while (pow(2, number_bit) < (coding_words[0] + number_bit + 1)) {
    number_bit++; // len of coded word
  }

  long long size_of_current = current_file.tellg();

  archive << CountLen(size_of_current, number_bit);
  current_file.close();
  byte = '|';
  archive.write(&byte, 1);

  archive << coding_words[0];
  byte = '>';
  archive.write(&byte, 1);

  archive.close();
  Coding(coding_words[0], new_file);

}

void Archiver::ListOfNames() {
  GetInfo(); // to know all information about archive

  for (int i = 0; i < names_of_files.size(); i++) {
    std::cout << names_of_files[i] << "\n";
  }

}

void Archiver::Extract(std::vector<std::string> names) {
  GetInfo();

  if (names.empty()) {
    names = names_of_files;
  }

  for (long long i = 0; i < names.size(); i++) {
    std::string file_name = path_of_archive + '\\' + names[i];
    auto it = find(names_of_files.begin(), names_of_files.end(), names[i]);
    long long index = it - names_of_files.begin(); // calculating the index
    Decode(coding_words[index], names[i], positions[index], size_of_files[index]);
  }

}

void Archiver::DeleteFile(std::string& name_of_delete_file) {
  std::ofstream new_archive;
  std::ifstream old_archive;
  std::string name_of_new_archive = path_of_archive + '\\' + "new.haf";
  char byte;
  long long counter = 0;
  bool flag = true;
  GetInfo();

  new_archive.open(name_of_new_archive, std::ios_base::binary | std::ios_base::out);
  old_archive.open(link, std::ios_base::binary | std::ios_base::in);

  auto it = find(names_of_files.begin(), names_of_files.end(), name_of_delete_file);
  int index = it - names_of_files.begin();

  if (index == 0) {
    flag = false;
    old_archive.seekg(size_of_files[index] + positions[index], std::ios_base::beg);
  }

  while (!(old_archive.eof())) {
    counter++;
    old_archive.read(&byte, 1);

    if (old_archive.eof()) {
      break;
    }

    new_archive.write(&byte, 1);

    if (flag && positions[index - 1] + size_of_files[index - 1] == counter) {
      old_archive.seekg(positions[index] + size_of_files[index], std::ios_base::beg);
    }
  }

  new_archive.close();
  old_archive.close();
  std::remove(link.c_str());
  std::rename(name_of_new_archive.c_str(), link.c_str());

}

void Archiver::Concatenate(std::vector<std::string>& names_of_archives) {
  std::ofstream archive_concatenate;
  std::ifstream archive_1;
  std::ifstream archive_2;
  char byte;

  archive_concatenate.open(link, std::ios_base::binary | std::ios_base::out);
  archive_1.open(path_of_archive + '\\' + names_of_archives[0], std::ios_base::binary | std::ios_base::in);
  archive_2.open(path_of_archive + '\\' + names_of_archives[1], std::ios_base::binary | std::ios_base::in);
   while (!(archive_1.eof())) {
     archive_1.read(&byte, 1);
     if (archive_1.eof()) {
       break;
     }
     archive_concatenate.write(&byte, 1);
   }
   archive_1.close();

   while (!(archive_2.eof())) {
     archive_2.read(&byte, 1);
     if (archive_2.eof()) {
       break;
     }
     archive_concatenate.write(&byte, 1);
   }
   archive_2.close();
   archive_concatenate.close();

 }

void Archiver::ToBinary(char byte, std::vector<int>& arr) {
  for (int j = 0; j < 8; j++) {
    if (byte & 1) {
      arr.push_back(1);
    } else {
      arr.push_back(0);
    }
    byte = byte >> 1;
  }
}

int Archiver::FromBinary(std::vector<int>& arr) {
  int number = 0;

  for (int i = 7; i >= 0; ) {
    if (arr[i] == 1) {
      number += int(pow(2, i));
    }
    i--;
  }

  return number;
}

void Archiver::Coding(int len_of_word, std::string& file_name) {
  char byte;
  char byte_for_read;
  char byte_for_write;

  std::vector<int> to_char(8);
  std::vector<int> save_bits;
  std::vector<int> word;
  std::vector<int> answer;
  std::vector<int> word_to_hemming(len_of_word);
  std::ofstream archiver_file;
  std::ifstream encode_file;
  std::string name_of_file = path_of_archive + '\\' + file_name;

  archiver_file.open(link, std::ios_base::app | std::ios_base::binary);
  encode_file.open(name_of_file, std::ios_base::in | std::ios_base::binary);

  while (!(encode_file.eof())) {
    encode_file.read(&byte_for_read, 1);

    if (encode_file.eof()) {
      break;
    }

    byte = byte_for_read;
    ToBinary(byte, word);

    while (word.size() >= len_of_word) {
      for (int i = 0; i < word_to_hemming.size(); i++) {
        word_to_hemming[i] = word[i];
      }
      word.erase(word.begin(), word.begin() + word_to_hemming.size());
      answer = findHammingCode(word_to_hemming);
      for (int k = 0; k < answer.size(); k++) {
        save_bits.push_back(answer[k]);
      }
      answer.clear();
      while (save_bits.size() >= 8) {
        for (int o = 0; o < 8; o++) {
          to_char[o] = save_bits[o];
        }
        byte_for_write = (char) FromBinary(to_char);

        save_bits.erase(save_bits.begin(), save_bits.begin() + 8);
        archiver_file.write(&byte_for_write, 1);
      }
    }
  }

  if (word.size() != 0) { // a special case
      int size = len_of_word - word.size();
      for (int i = 0; i < size; i++) {
          word.push_back(0);
      }
      answer = findHammingCode(word);
  }
  for (int k = 0; k < answer.size(); k++) {
      save_bits.push_back(answer[k]);
  }
  while (save_bits.size() >= 8) {
      for (int o = 0; o < 8; o++) {
          to_char[o] = save_bits[o];
      }

      byte_for_write = (char)FromBinary(to_char);
      save_bits.erase(save_bits.begin(), save_bits.begin() + 8);
      archiver_file.write(&byte_for_write, 1);
    }

  if (save_bits.size() < 8) {
      for (int o = 0; o < 8 - save_bits.size(); o++) {
          save_bits.push_back(0);
      }

      byte_for_write = (char)FromBinary(save_bits);
      archiver_file.write(&byte_for_write, 1);
    }


  encode_file.close();
  archiver_file.close();
}

void Archiver::Decode(int len_of_word, std::string& name_of_file, long long pos, long long size_of_file) {
  std::ifstream archiver_file;
  std::ofstream unencode_file;
  std::vector<int> answer;
  std::vector<int> buffer;
  std::vector<int> decoder;
  std::vector<int> write_buff;
  std::vector<int> to_char(8);
  std::string file_name = path_of_archive + '\\' + name_of_file;

  int len_of_hamming_word;
  int number_parity_bit = 1;
  char byte;
  char byte_for_write;

  archiver_file.open(link, std::ios_base::in | std::ios_base::binary);
  unencode_file.open(file_name, std::ios_base::out | std::ios_base::binary);
  archiver_file.seekg(pos, std::ios::beg);

  while (pow(2, number_parity_bit) < (len_of_word + number_parity_bit + 1)) {
    number_parity_bit++; // len of coded word
  }

  len_of_hamming_word = len_of_word + number_parity_bit;

  std::vector<int> for_hamming(len_of_hamming_word);

  for (long long h = 0; h < size_of_file; h++) {
    archiver_file.read(&byte, 1);

    ToBinary(byte, answer);
    for (int j = 0; j < 8; j++) {
      buffer.push_back(answer[j]);
    }
    answer.clear();

    while(buffer.size() >=  len_of_hamming_word) {
      for (int j = 0; j <  len_of_hamming_word; j++) {
        for_hamming[j] = buffer[j];
      }

      int res = decode_hamming(for_hamming, decoder);

      if (res == -1) { //have more than one mistakes
          std::cout << "More than one mistakes" << '\n';
          return;
      }

      buffer.erase(buffer.begin(), buffer.begin() +  len_of_hamming_word);

      for (int i = 0; i < decoder.size(); i++) {
        write_buff.push_back(decoder[i]);
      }
      decoder.clear();

      while (write_buff.size() >= 8) {

        for (int i = 0; i < 8; i++) {
          to_char[i] = write_buff[i];
        }

        byte_for_write = (char)FromBinary(to_char);
        unencode_file.write(&byte_for_write, 1);
        write_buff.erase(write_buff.begin(), write_buff.begin() + 8);
      }
    }
  }
  archiver_file.close();
  unencode_file.close();

}
