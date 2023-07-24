#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "color.h"
#include "pile.h"

int main(int argc, char* argv[]) {
    uint16_t height = 0;
    uint16_t width = 0;
    uint16_t number_of_iteration = 0;
    uint64_t chet = 0;
    uint64_t max_iter = 1;
    uint64_t frequent = 0;
    uint64_t** pile;

    std::string input_string;
    std::string link;
    std::string way_out;
    std::string name_of_picture;
    std::string comparison;

    int correct_parametrs = 0;
    bool flag_out = false;
    bool correct_way = false;
    bool correct_link = false;
    bool max_it = false;

    for (int i = 0; i < argc - 1; i++) { // Entering all necessary flags
        comparison = argv[i];
        if (comparison == "-l" or comparison == "--length") {
            height = atoll(argv[i + 1]);
            correct_parametrs += 1;
        }
        if (comparison == "-w" or comparison == "--width") {
            correct_parametrs += 1;
            width = atoll(argv[i + 1]);
        }
        if (comparison == "-i" or comparison == "--input") {
            link = (argv[i + 1]);
            correct_link = true;
        }
        if (comparison == "-o" or comparison == "--output") {
            way_out = (argv[i + 1]);
            correct_way = true;
        }
        if (comparison == "-m" or comparison == "--max-iter") {
            max_iter = atoll(argv[i + 1]);
            max_it = true;
        }
        if (comparison == "-f" or comparison == "--freq") {
            frequent = atoll(argv[i + 1]);
            if (frequent == 0) {
                frequent = max_iter;
            }
        }
    }

    if (correct_parametrs < 2) {
        std::cout << "You didn't write length or width, check it" << std::endl;
    }
    if (correct_way = false) {
        std::cout << "You didn't specify the path where to save the images" << std::endl;
    }
    if (correct_link = false) {
        std::cout << "You didn't specify the path where to take the link" << std::endl;
    }

    TheMatrix(height, width, max_iter, frequent, input_string, link, way_out, max_it, flag_out);

    return 0;
}
