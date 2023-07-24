#include <iostream>
#include <ncurses.h>
#include <curl/curl.h>
#include "config.h"
#include <unordered_map>
#include "pictures.h"

CURL *curl = curl_easy_init();
CURL *curl_ = curl_easy_init();

size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    std::string* response = static_cast<std::string*>(userdata);
    response->append(ptr, size * nmemb);
    return size * nmemb;
}

void coordinates(std::string& str, std::string & latitude, std::string& longitude) {
    latitude = "";
    longitude = "";

    int i = str.find("latitude") + 11;

    while (str[i] != ',') {
        latitude += str[i];
        i++;
    }

    i = str.find("longitude") + 12;

    while (str[i] != ',') {
        longitude += str[i];
        i++;
    }
}

void api_coordinates(std::string& response, std::string& latitude, std::string& longitude) {
    std::string url_coord = "https://api.api-ninjas.com/v1/city?name=" + all_cities[chosen_city];
    response = "";
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url_coord.c_str());
        curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-Api-Key: +SKhjHthbrByDKBW643OiQ==wejblvaamLNg6z60");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            coordinates(response, latitude, longitude);
         //   printw("%s %s \n", latitude.c_str(), longitude.c_str());
        } else {
            printw("%s Error \n", res);
        }
    }
}

void weather_code_(std::string str, int& weather_code) {
    std::string answer;
    int i = str.find("weathercode\":[") + 14;
    chet = 0;
    int j = 0;
    while (str[i] != ']') {
        while (str[i] != ',' and str[i] != ']') {
            answer += str[i];
            i++;
        }
        if (str[i] == ']') {
            break;
        }
        i++;
        if (answer != "") {
            codes[j] = std::stoi(answer);
        }
        j++;
        answer = "";
    }

    i = str.find("temperature_2m\":[") + 17;
    j = 0;

    answer = "";
    while (str[i] != ']') {
        while (str[i] != ',' and str[i] != ']') {
            answer += str[i];
            i++;
        }
        if (str[i] == ']') {
            break;
        }
        i++;
        if (answer != "") {
            tempeature[j] = std::stof(answer);
        }
        j++;
        answer = "";
    }

    i = str.find("windspeed_80m\":[") + 16;
    j = 0;

    answer = "";
    while (str[i] != ']') {
        while (str[i] != ',' and str[i] != ']') {
            answer += str[i];
            i++;
        }
        if (str[i] == ']') {
            break;
        }
        i++;
        if (answer != "") {
            wind[j] = std::stof(answer);
        }
        j++;
        answer = "";
    }

    i = str.find("winddirection_80m\":[") + 20;
    j = 0;

    answer = "";
    while (str[i] != ']') {
        while (str[i] != ',' and str[i] != ']') {
            answer += str[i];
            i++;
        }
        if (str[i] == ']') {
            break;
        }
        i++;
        if (answer != "") {
            direction[j] = std::stof(answer);
        }
        j++;
        answer = "";
    }


    i = str.find("time\":[") + 8;
    j = 0;
    answer = "";

    while (str[i] != ']') {
        while (str[i] != ',' and str[i] != ']') {
            answer += str[i];
            i++;
        }
        if (str[i] == ']') {
            break;
        }
        i++;

        std::string month_ = "";
        int m_;
        std::string number_of_day = "";

        if (answer != "") {

            if (answer[5] == '-') {
                for (int f = 6; f <= 7; f++) {
                    month_ += answer[f];
                }

                for (int f = 9; f < 11; f++) {
                    number_of_day += answer[f];
                }

            } else {
                for (int f = 5; f < 7; f++) {
                    month_ += answer[f];
                }

                for (int f = 8; f < 10; f++) {
                    number_of_day += answer[f];
                }
            }

            m_ = std::stoi(month_);
            month_ = month[m_];
            which_day[j / 24] = number_of_day + " " + month_;
        }
        j++;
        answer = "";
    }

    int shift_oy = 10;

    //printw("%s", all_cities[chosen_city].c_str()); // where?
    black_screen();
    today();

    for (int i = 0; i < amount_of_days; i++) {
        float mid_temp = 0;
        float mid_win = 0;
        float mid_direct = 0;
        curr_day  = i;

        days(mid_temp, mid_win, mid_direct, shift_oy);
        shift_oy += 15;
    }

    chet = 0;
}

void api_weather(std::string& latitude, std::string& longitude) {
    int weather_code = 0;

    std::string url = "https://api.open-meteo.com/v1/forecast?latitude=" + latitude + "&longitude=" + longitude
            + "&hourly=temperature_2m,weathercode,windspeed_80m,winddirection_80m,temperature_120m" +
                                  "&forecast_days=" + std::to_string(amount_of_days) + "&key=" + api_key;

    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    std::string response_weather;
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response_weather);

    CURLcode res = curl_easy_perform(curl_);

    latitude = "";
    longitude = "";

    std::string r = ((response_weather.c_str())); // to string something made with this
    weather_code_(r, weather_code);
}

int main() {
    char* locale = setlocale(LC_ALL, "");
    const int ESC = 27;
    std::string latitude;
    std::string longitude;
    initscr(); //turn on getch and another
    start_color();
    std::string response;

    while(true) {
        api_coordinates(response, latitude, longitude);
        api_weather(latitude, longitude);

        exit_key = getch();

        switch (exit_key) {
            case (int)'+':
                amount_of_days++;
                break;
            case (int)'-':
                amount_of_days--;
                break;
            case (int)'p':
                chosen_city--;
                break;
            case (int)'n':
                chosen_city++;
                break;
            case ESC:
                std::cout << "ECS, EXIT";
                endwin(); // help to make clear all
                curl_easy_cleanup(curl);
                curl_easy_cleanup(curl_);
                exit(0);
            default:
                continue;
        }
    }

}