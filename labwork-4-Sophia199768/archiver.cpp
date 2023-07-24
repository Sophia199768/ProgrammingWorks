#include"lib/arc.h"

int main(int argc, char* argv[]) {
  std::string main_archive;
  std::string create;
  std::string file;
  std::string list;
  std::string extract;
  std::string append;
  std::string delete_file;
  std::string concatenate;
  std::string flag;
  std::string flag_next;
  std::string archive_name;
  std::string archive_name_2;
  std::string path;

  bool flag_path = false;
  bool flag_create = false;
  bool flag_file = false;
  bool flag_list = false;
  bool flag_extract = false;
  bool flag_append = false;
  bool flag_delete_file = false;
  bool flag_concatenate = false;

  int len_of_coding_word = 0;
  std::vector <std::string> names_of_files;

  for (int i = 1; i < argc; i++) { // ввод всех необходимых флагов
    flag = argv[i];

    if (i + 1 == argc) {
      flag_next = argv[i];
    } else {
      flag_next = argv[i + 1];
    }

    if (flag == "-L" or flag == "--word") {
      len_of_coding_word = atoi(argv[i + 1]);
    }

    if (flag == "-p" or flag == "--path") {
      path = argv[i + 1];
      flag_path = true;
    }

    if (flag == "-c" or flag == "--create") {
      flag_create = true;

      if (flag_next == "-f" or flag_next == "--file=") {
        main_archive = argv[i + 2];
        for (int j = i + 3; j < argc; j++) {
          names_of_files.push_back(argv[j]);
        }
      }
    }

    if (flag == "-f" or flag == "--file=") {
      main_archive = argv[i + 1];
      flag_file = true;
    }

    if (flag == "-l" or flag == "--list") {
      flag_list = true;
    }

    if (flag == "-x" or flag == "--extract") {
      flag_extract = true;
      if (flag_next.find('-') == std::string::npos) {
        for (int j = i + 1; j < argc; j++) {
          names_of_files.push_back(argv[j]);
        }
      }
    }

    if (flag == "-a" or flag == "--append") {
      flag_append = true;
      file = argv[i + 1];
    }

    if (flag == "-d" or flag == "--delete") {
      flag_delete_file = true;
      file = argv[i + 1];
    }

    if (flag == "-A" or flag == "--concatenate") {
      flag_concatenate = true;
      archive_name = (argv[i + 1]);
      archive_name_2 = (argv[i + 2]);
    }
  }

  if (!flag_path) {
    std::cout << "You don't give a path" << '\n';
    return 1;
  }

  Archiver archive = {names_of_files, path, main_archive, len_of_coding_word};

  if (flag_create) {
    archive.CreateArchive();
    return 0;
  }

  if (flag_list) {
    archive.ListOfNames();
    return 0;
  }

  if (flag_append) {
    archive.Append(file);
    return 0;
  }

  if (flag_extract) {
    archive.Extract(names_of_files);
    return 0;
  }

  if (flag_delete_file) {
    archive.DeleteFile(file);
    return 0;
  }

  if (flag_concatenate) {
    std::vector<std::string> names = {archive_name, archive_name_2};
    archive.Concatenate(names);
    return 0;
  }
}