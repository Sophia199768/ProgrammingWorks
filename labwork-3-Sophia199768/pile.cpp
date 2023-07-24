#include "pile.h"
#include "color.h"

void SavePicture(std::string picture, uint16_t height, uint16_t width, uint64_t** pile) {

    Image image(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color color_pixel = {0, 0, 0};
            switch (pile[y][x]) {
            case 0:
                color_pixel = { 255, 255, 255 };
                break;
            case 1:
                color_pixel = { 68, 148, 74 };
                break;
            case 2:
                color_pixel = { 128, 0, 255 };
                break;
            case 3:
                color_pixel = { 255, 215, 0 };
                break;
            default:
                color_pixel = { 24, 21, 19 };
                break;
            }

            image.SetColor(color_pixel, x, y);
        }
    }
    image.Export(picture.c_str());
}

void TheMatrix(uint16_t height, uint16_t width, uint64_t max_iter,uint64_t frequent, const std::string& input_string,
    const std::string& link, const std::string& way_out, bool max_it, bool flag_out) {

    uint16_t number_of_iteration = 0;
    uint64_t** pile;

    std::string name_of_picture;

    bool saving_picture = false;

    pile = (unsigned long long**)malloc(width * sizeof(unsigned long long*));
    std::vector<long long> parametres(0);

    for (int i = 0; i < width; i++) { // Creating a matrix
        pile[i] = (unsigned long long*) calloc(height, sizeof(unsigned long long));
    } 

    std::ifstream file;
    file.open(link);

    if (!file.is_open()) {
        std::cout << "File couldn't be open";
        return;
    }

    std::string str;


    while (std::getline(file, str)) {  // Filling in the matrix
        std::istringstream iss(str);
        std::string token;

        while (std::getline(iss, token, '\t')) {  
            parametres.push_back(atoll(token.c_str()));
        }
        pile[parametres[0]][parametres[1]] = parametres[2];
        parametres.clear();
    }

    while (true) { // Imitating the scattering of grains of sand
        if (max_it) {
            if (number_of_iteration % frequent == 0 and number_of_iteration / frequent != 0) {
                saving_picture = true;
                name_of_picture = std::to_string(number_of_iteration / frequent);
                std::string picture = way_out + name_of_picture + '_' + "image.bmp";
                SavePicture(picture, height, width, pile);
                picture.clear();
            }
        }

        flag_out = true;

        if (max_it) {
            if (number_of_iteration >= max_iter) {
                break;
            }
        }

        number_of_iteration++;
        for (uint16_t i = 0; i < height; i++) {
            for (uint16_t j = 0; j < width; j++) {
                if (pile[i][j] >= 4) {
                    flag_out = false;
                    j > 0 ? pile[i][j - 1] += 1 : 0;
                    i > 0 ? pile[i - 1][j] += 1 : 0;
                    j < width - 1 ? pile[i][j + 1] += 1 : 0;
                    i < height - 1 ? pile[i + 1][j] += 1 : 0;
                    pile[i][j] = (pile[i][j] - 4);
                }
            }
        }

        if (flag_out) {
            if (!max_it || !saving_picture) {
                name_of_picture = "last";
                std::string picture = way_out + name_of_picture + '_' + "image.bmp";
                SavePicture(picture, height, width, pile);
                picture.clear();
            }
            break;
        }
    }

    for (int i = 0; i < width; i++) {  // Then we delete the array of pointers
        free(pile[i]);
    }

    free(pile);
}
