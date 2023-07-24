#include <iostream>
#include <vector>
#include "FramesHierarchy.h"

int main(int argc, char* argv[]) {
    std::string flag;
    std::string path;
    std::vector<std::string> name;
    bool flag_all = false;
    bool flag_path = false;
    bool flag_name = false;

    for (int i = 1; i < argc; i++) { // ввод всех необходимых флагов
        flag = argv[i];

        if (flag == "-n" or flag == "--name") {
            i++;
            while (i < argc and argv[i][0] != '-') {
                name.push_back(argv[i]);
                i++;
            }
            flag_name = true;
        }

        if (flag == "-p" or flag == "--path") {
            path = argv[i + 1];
            flag_path = true;
        }

        if (flag == "-a" or flag == "--all") {
            flag_all = true;
        }
    }

    Frame parse = path;

    if (!flag_path) {
        std::cout << "You don't give a path" << '\n';
        return 1;
    }

    if (flag_name) {
        read_frame(name, path);
        return 0;
    }


    if (flag_all) {
        frame_all(path);
        return 0;
    }
}
