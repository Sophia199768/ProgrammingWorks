#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<std::string> all_cities = {"Moscow", "Saint_Petersburg", "New_York", "Seoul", "Beijing", "London"}; // "Saint Petersburg", "NewYork"
std::string api_key = "9355ef9c13bdee55edb74a344059e920";
std::string api_key_coord = "+SKhjHthbrByDKBW643OiQ==wejblvaamLNg6z60";
int amount_of_days = 3;
int frequency = 60;
int exit_key;
int chosen_city = 0;
int chet = 0;
int curr_day = 0;

int codes[24 * 7];
float tempeature[24 * 7];
float wind[24 * 7];
float direction[24 * 7];
std::string which_day[24 * 7];
std::unordered_map<int, std::string> month = {{1, "Января"}, {2, "Февраля"}, {3, "Марта"},
                                              {4, "Апреля"}, {5, "Мая"}, {6, "Июня"},
                                              {7, "Июля"}, {8, "Августа"}, {9, "Сентября"},
                                              {10, "Октября"}, {11, "Ноября"}, {12,"Декабря"}};

