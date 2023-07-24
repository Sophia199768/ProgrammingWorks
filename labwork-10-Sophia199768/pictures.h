#pragma once
#include <iostream>
#include <locale.h>
#include <curses.h>
#include <unistd.h>

float averedge(float* array) {
    float sum = 0;
    for (int i = chet; i < chet + 6; i++) {
        sum += array[i];
    }
    return (sum/6);
}

int frequent_code(int* codes) {
    int max = 0;
    int max_code;
    std::unordered_map<int, int> weather_c;

    for (int i = chet; i < chet + 6; i++) {
        weather_c[codes[i]] += 1;
    }

    for (auto it = weather_c.begin(); it != weather_c.end(); it++) {
        if (it->second > max) {
            max = it->second;
            max_code = it->first;
        }
    }
    return max_code;
}

void quarter_day( float* tempreature, float* wind, float* direction, float& mid_temp, float& mid_win, float& mid_direct, int& code_max) {
    mid_temp = averedge(tempreature);
    mid_win = averedge(wind);
    mid_direct = averedge(direction);
    code_max = frequent_code(codes);
    chet += 6;
}

void code_of_weather(int code, float mid_temp, float mid_win, float mid_direct, WINDOW* in_win, int time) {

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

    if (code == 0 and time != 4) { // clear sky
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 1, 1, "   \\   /");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 1, 17, "Солнечно");
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 2, 1, "    .-. ");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 2, 17, "%.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 22, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 3, 1, " _ (   ) _");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 3, 17, "%.1f%s",    mid_win, "км/ч");
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 1, "    ._.");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 17, "%1.f",    mid_direct);
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 5, 1, "   /   \\ ");
        wattroff(in_win, COLOR_PAIR(2));

    } else if (code == 0 and time == 4) {
        mvwprintw(in_win, 1, 1, "   ☆ _/\\_   ☆     Ясно");
        mvwprintw(in_win, 2, 1, "   ☆\\    / ☆      %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 24, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1, "     \\/\\/         %.1f%s",    mid_win, "км/ч");
        mvwprintw(in_win, 4, 1,"  ☆   ☆      ☆    %1.f",    mid_direct);

    } else if (code >= 1 and code <= 2 and time!= 4) { //mainly cloudy
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 1, 1, "   \\  /");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 1, 14, "Переменная обл.");
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 2, 1, "   /\"\"");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 2, 7, "  .-.     %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 22, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 3, 2, "-- -_\\");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 3, 5, "  (    ).   %.1f%s", mid_win, "км/ч");
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 3, "/");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 6, "(___(__)   %1.f", mid_direct);
        mvwprintw(in_win, 5, 1, "           ");

    } else if (code >= 1 and code <= 2 and time == 4) {
        mvwprintw(in_win, 1, 14, "Переменная обл.");
        mvwprintw(in_win, 2, 7, " .-.     %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 22, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 5, "☆(    ).   %.1f%s", mid_win, "км/ч");
        mvwprintw(in_win, 4, 5, "(___(__)☆  %1.f", mid_direct);
        mvwprintw(in_win, 5, 1, "           ");

    } else if (code == 3) { // cloudy
        mvwprintw(in_win, 1, 1, "                Облачно");
        mvwprintw(in_win, 2, 1,"      .--.      %.1f  ",  mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 22, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1,"   .-(    ).    %.1f%s",    mid_win, "км/ч");
        mvwprintw(in_win, 4, 1,"  (___.__(__)   %1.f",    mid_direct);
        mvwprintw(in_win, 5, 1,"             ");

    } else if (code == 45 or code == 48) { // foggy or smog
        mvwprintw(in_win, 1, 1, "               %s", "Туман");
        mvwprintw(in_win, 2, 1, "  - - - -      %.1f", mid_temp);
        mvwprintw(in_win, 3, 1, " - - - -       %.1f", mid_win);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 20, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 4, 1, "  - - - -      %1.f", mid_direct);
        mvwprintw(in_win, 5, 1, " - - - - -");

    } else if (code == 51 or code == 53 or code == 55) {
        mvwprintw(in_win, 1, 1, "     .-.      Морось");
        mvwprintw(in_win, 2, 1, "   (    ).    %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 20, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1, "  (___(__)    %.1f", mid_win);
        wattron(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 4, 1, "  ,  , , ,    ");
        wattroff(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 4, 15, "%1.f", mid_direct);
        wattron(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 5, 1, " ,  , ,  ,   ");
        wattroff(in_win, COLOR_PAIR(3));

    } else if (code == 56 or code == 57) {
        mvwprintw(in_win, 1, 1, "    .-.  Моросящий дождь");
        mvwprintw(in_win, 2, 1, "  (    ).    %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 20, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1, " (___(__)   %.1f", mid_win);
        wattron(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 4, 1, "  ,  ,  , ,    %1.f", mid_direct);
        mvwprintw(in_win, 5, 1, " ,  ,  ,  ,   ");
        wattroff(in_win, COLOR_PAIR(3));

    } else if (code == 61 or code == 66 or code == 67) { // rain
        mvwprintw(in_win, 1, 1, "    .-.      Дождь");
        mvwprintw(in_win, 2, 1, "  (    ).    %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 20, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1, " (___(__)    %.1f", mid_win);
        wattron(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 4, 1, "  ' ' ' '    ");
        wattroff(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 4, 14, "%1.f", mid_direct);
        wattron(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 5, 1, " ' ' ' '  ");
        wattroff(in_win, COLOR_PAIR(3));

    } else if (code == 63 or code == 65 or code == 80 or code == 81 or code == 82) { //strong rain and showers rain
        mvwprintw(in_win, 1, 1, "     .-.      Ливень");
        mvwprintw(in_win, 2, 1, "   (    ).    %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 20, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1, "  (___(__)    %.1f", mid_win);
        wattron(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 4, 1, "   / / / /    ");
        wattroff(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 4, 15, "%1.f", mid_direct);
        wattron(in_win, COLOR_PAIR(3));
        mvwprintw(in_win, 5, 1, "  / / / / ");
        mvwprintw(in_win, 6, 1, " / / / / ");
        wattroff(in_win, COLOR_PAIR(3));

    } else if (code == 71) {
        mvwprintw(in_win, 1, 1, "     .-.     Снег");
        mvwprintw(in_win, 2, 1, "   (    ).   %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 18, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1, "  (___(__)    %.1f", mid_win);
        mvwprintw(in_win, 4, 1, "  * * * *     %1.f", mid_direct);
        mvwprintw(in_win, 5, 1, " * * * *");

    } else if (code == 73 or code == 75 or code == 85 or code == 86) {
        mvwprintw(in_win, 1, 1, "      .-.   Снегoпад");
        mvwprintw(in_win, 2, 1, "    (    ). %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 18, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1,"   (___(__) %.1f", mid_win);
        mvwprintw(in_win, 4, 1, "   * * * *  %1.f", mid_direct);
        mvwprintw(in_win, 5, 1, "  * * * *");
        mvwprintw(in_win, 6, 1, " * * * *");

    } else if (code == 77) {
        mvwprintw(in_win, 1, 1, "      .-.        Град");
        mvwprintw(in_win, 2, 1, "    (    ).      %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 22, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1,"   (___(__)      %.1f", mid_win);
        mvwprintw(in_win, 4, 1, "   . . . .   %1.f", mid_direct);
        mvwprintw(in_win, 5, 1, "  . . . .");
        mvwprintw(in_win, 6, 1, " . . . .");
    } else if (code == 95) {
        mvwprintw(in_win, 1, 1, "      .-.        Гроза");
        mvwprintw(in_win, 2, 1, "    (    ).      %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 22, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1,"   (___(__)      %.1f", mid_win);
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 1, "   ϟ  ϟ  ");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 1, " '   '   '%1.f", mid_direct);
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 1, "     ϟ   ");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 5, 1, "  ' '  '");
    } else if (code == 96 or code == 99) {
        mvwprintw(in_win, 1, 1, "      .-.        Гроза с градом");
        mvwprintw(in_win, 2, 1, "    (    ).      %.1f", mid_temp);
        wattron(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 2, 22, "°C");
        wattroff(in_win, COLOR_PAIR(1));
        mvwprintw(in_win, 3, 1,"   (___(__)      %.1f", mid_win);
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 1, "   ϟ  ϟ  ");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 1, " .   .   .%1.f", mid_direct);
        wattron(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 4, 1, "     ϟ   ");
        wattroff(in_win, COLOR_PAIR(2));
        mvwprintw(in_win, 5, 1, " .  .  .");
    }

}

void black_screen() {
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    WINDOW* black_screen = newwin(1000, 1000, 0, 0);
    wattron(black_screen, COLOR_PAIR(0));
    wrefresh(black_screen);
}

void data_of_day(int y, int v) {
    v = 51;
    WINDOW* data_win = newwin(3, 15, y - 2, 51);
    getmaxyx(data_win, y, v);
    box(data_win, 0, 0);
    mvwprintw(data_win, 1, 1, "  %s  ", which_day[curr_day].c_str());
    wrefresh(data_win);
}

void today() {
    int x = 0;
    int y = 0;
    WINDOW* today_win = newwin(10, 28, x, y);
    getmaxyx(today_win, x, y);
    mvwprintw(today_win, 1, 1, "%s", all_cities[chosen_city].c_str());
    wrefresh(today_win);
}

void time_of_day(int h, int w, int y, int x, int time, int code_max, float mid_temp, float mid_win, float mid_direct) {
    WINDOW* win = newwin(h, w, y, x);
    getmaxyx(win, y, x);
    WINDOW* in_win = derwin(win, y - 2, x, 2, 0); //win, h - 11, w , 0, 0

    box(win, 0, 0);
    box(in_win, 0, 0);

    switch(time) {
        case 1:
            mvwprintw(win, 1, 1, "%s", "         Утро            ");
            code_of_weather(code_max,  mid_temp, mid_win, mid_direct,  in_win, time);
            break;
        case 2:
            mvwprintw(win, 1, 1, "%s", "            День         ");
            code_of_weather( code_max, mid_temp, mid_win, mid_direct,  in_win, time);
            break;
        case 3:
            mvwprintw(win, 1, 1, "%s", "         Вечер            ");
            code_of_weather(code_max, mid_temp, mid_win, mid_direct,  in_win, time);
            break;
        case 4:
            mvwprintw(win, 1, 1, "%s", "            Ночь         ");
            code_of_weather(code_max, mid_temp, mid_win, mid_direct,  in_win, time);
            break;
    }
    wrefresh(win);
}

void days(float mid_temp, float mid_win, float mid_direct, int shift_oy) {
    int shift_ox;
    int code_max;
    data_of_day(shift_oy, 51);

    for (int it = 1; it < 5; it++) {
        if (it == 1) {
            shift_ox = 1;
        } else if (it == 2) {
            shift_ox = 29;
        } else if (it == 3) {
            shift_ox = 58;
        } else if (it == 4) {
            shift_ox = 87;
        }

        quarter_day(tempeature, wind, direction, mid_temp, mid_win, mid_direct, code_max);
        time_of_day(10, 30, shift_oy, shift_ox, it, code_max, mid_temp, mid_win, mid_direct);
    }
}

