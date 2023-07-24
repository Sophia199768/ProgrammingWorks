#include "ArgParser.h"

ArgumentParser::ArgParser &ArgumentParser::ArgParser::AddStringArgument(std::string flag) {
    flags_name cur = {"0", "--" + flag};
    flags.push_back(cur);
    return *this;
}

ArgumentParser::ArgParser &ArgumentParser::ArgParser::AddStringArgument(char short_flag, std::string flag) {
    std::string short_flag_(1, short_flag);
    flags_name cur = {"-" + short_flag_, "--" + flag};
    flags.push_back(cur);
    return *this;
}

ArgumentParser::ArgParser &
ArgumentParser::ArgParser::AddStringArgument(char short_flag, std::string flag, std::string input_string2) { //
    std::string short_flag_(1, short_flag);
    flags_name cur = {"-" + short_flag_, "--" + flag};
    flags.push_back(cur);
    Help_description += input_string2;
    return *this;
}

ArgumentParser::ArgParser &ArgumentParser::ArgParser::AddIntArgument(char short_flag, std::string flag) {
    std::string short_flag_(1, short_flag);
    flags_name cur = {"-" + short_flag_, "--" + flag};
    flags.push_back(cur);
    return *this;
}

ArgumentParser::ArgParser &ArgumentParser::ArgParser::AddIntArgument(std::string flag) {
    flags_name cur = {"0", "--" + flag};
    flags.push_back(cur);
    return *this;
}

ArgumentParser::ArgParser &ArgumentParser::ArgParser::AddIntArgument(std::string flag, std::string description) {
    flags_name cur = {"0", "--" + flag};
    flags.push_back(cur);
    Help_description += description;
    return *this;
}

ArgumentParser::ArgParser &ArgumentParser::ArgParser::MultiValue(size_t MinArgsCount) {
    Multivalue_flag = MinArgsCount;
    if (Help_flag) {
        Help_description += "[repeated, min args = " + (std::to_string(MinArgsCount)) + "]";
    }
    return *this;
}

ArgumentParser::ArgParser &ArgumentParser::ArgParser::AddFlag(char short_flag, std::string full_flag) {
    std::string short_flag_(1, short_flag);
    flags_name cur = {"-" + short_flag_, "--" + full_flag};
    flags.push_back(cur);
    return *this;
}

ArgumentParser::ArgParser &
ArgumentParser::ArgParser::AddFlag(char short_flag, std::string full_flag, std::string input_string2) {
    std::string short_flag_(1, short_flag);
    flags_name cur = {"-" + short_flag_, "--" + full_flag};
    flags.push_back(cur);
    Help_description += input_string2;
    return *this;
}

ArgumentParser::ArgParser &ArgumentParser::ArgParser::AddFlag(std::string full_flag, std::string str2) {
    flags_name cur = {"0", "--" + full_flag};
    flags.push_back(cur);
    Help_description += str2;
    return *this;
}

ArgumentParser::ArgParser &ArgumentParser::ArgParser::Positional() {
    Position = true;
    return *this;
}

void ArgumentParser::ArgParser::AddHelp(char short_flag, std::string full_flag, std::string description) {
    Help_flag = true;
    Help_description = parser_name;
    std::string short_flag_(1, short_flag);
    flags_name cur = {"-" + short_flag_, "--" + full_flag};
    flags.push_back(cur);
    Help_description += description;
}

ArgumentParser::ArgParser &ArgumentParser::ArgParser::Default(const char *input_string) {
    values.push_back(input_string);
    flag_for_values.push_back(flags[flags.size() - 1]);
    flags.pop_back();
    if (Help_flag) {
        Help_description = (input_string);
    }
    return *this;
}

bool ArgumentParser::ArgParser::Default(bool flag) {
    std::string bool_flag;
    if (flag == true) {
        bool_flag = true;
    } else {
        bool_flag = false;
    }
    values.push_back(bool_flag);
    flag_for_values.push_back(flags[flags.size() - 1]);
    flags.pop_back();
    return false;
}

void ArgumentParser::ArgParser::StoreValue(std::string &value) {
    StoreValueFlag = true;
    address_of_store_value = &value;
    value = flags[flags.size() - 1].full_name;
}

void ArgumentParser::ArgParser::StoreValue(bool &flag) {
    StoreValueMeaning.push_back(&flag);
    bool_flag.push_back(flags[flags.size() - 1]);
}

void ArgumentParser::ArgParser::StoreValues(std::vector<int> &int_values) {
    StoreValuesFlag = true;
    link = &int_values;

}

bool ArgumentParser::ArgParser::Help() {
    return Help_flag;
}

bool ArgumentParser::ArgParser::Parse(int argc, char **argv) {
    std::vector<std::string> array;
    for (int i = 0; i < argc; i++) {
        array.push_back(argv[i]);
    }
    return Parse(array);
}

std::string FoundValue(int found_pos, std::string search_string) {
    std::string our_value;
    for (int i = found_pos; i < search_string.size(); i++) {
        our_value += search_string[i];
    }
    if (our_value.empty()) {
        our_value = " ";
    }
    return our_value;
}

void ArgumentParser::ArgParser::Parser_v(int found, int i, int j, std::vector<std::string> array, bool flag_long) {
    for (int q = 0; q < StoreValueMeaning.size(); q++) {
        if (bool_flag[q].full_name == flags[i].full_name and bool_flag[q].short_name == flags[i].short_name) {
            *StoreValueMeaning[q] = true;
        }
    }
    if (StoreValueFlag && (*address_of_store_value == flags[i].full_name)) {
        *address_of_store_value = FoundValue(found + flags[i].full_name.size() + 1, array[j]);
    }

    if (StoreValueFlag && (*address_of_store_value == flags[i].short_name)) {
        *address_of_store_value = FoundValue(found + flags[i].short_name.size() + 1, array[j]);
        flag_long = false;
    }

    if (flag_long) {
        values.push_back(FoundValue(found + flags[i].full_name.size() + 1, array[j]));
        if (StoreValuesFlag) {
            link->push_back(atoi(FoundValue(found + flags[i].full_name.size() + 1, array[j]).c_str()));
        }
    } else {
        values.push_back(FoundValue(found + flags[i].short_name.size() + 1, array[j]));
        if (StoreValuesFlag) {
            link->push_back(atoi(FoundValue(found + flags[i].short_name.size() + 1, array[j]).c_str()));
        }
    }

    flag_for_values.push_back(flags[i]);
}

bool Type_data(std::string str) {

    for (int i = 0; i < str.size(); i++) {
        if (str[i] < '0' or str[i] > '9') {
            return false;
        }
    }
    return true;
}


bool ArgumentParser::ArgParser::Parse(std::vector<std::string> array) {
    bool flag = false;
    bool flag_long = true;

    if (flags.size() == 0 and array.size() != 0) {
        return true;
    }

    for (int j = 0; j < array.size(); j++) {

        for (int i = 0; i < flags.size(); i++) {

            int found = array[j].find(flags[i].full_name);

            if (found == std::string::npos) {
                found = array[j].find(flags[i].short_name);
                if (found != std::string::npos) {
                    flag_long = false;
                }
            }

            if (found != std::string::npos) {
                flag = true;

                int found_next_flag;
                bool flag_ = false;

                while (array[j].size() > 1 and array[j].find('=') == std::string::npos and !flag_long) {

                    flag_ = true;
                    for (int k = 0; k < flags.size(); k++) {

                        found_next_flag = array[j].find(flags[k].short_name);
                        if (found_next_flag != std::string::npos) {
                            array[j].erase(found_next_flag + 1, found_next_flag + 1);
                            Parser_v(found, k, j, array, flag_long);
                        }
                    }
                }

                if (!flag_) {
                    Parser_v(found, i, j, array, flag_long);
                }

            }
        }
    }

    int size_ = (flag_for_values.size());

    if (Position) {
        for (int i = 1; i < array.size(); i++) {
            if (array[i][0] != '-') {
                if (Type_data(array[i])) {
                    link->push_back(atoi(array[i].c_str()));
                }
            }
        }
        return true;
    }

    if (Multivalue_flag > size_) {
        return false;
    }

    return flag;
}

bool ArgumentParser::ArgParser::GetFlag(std::string flag) {

    flag = "--" + flag;
    for (int i = 0; i < flag_for_values.size(); i++) {
        if (flag_for_values[i].full_name == flag) {
            return true;
        }
    }
    return false;
}

int ArgumentParser::ArgParser::GetIntValue(std::string flag) {
    flag = "--" + flag;
    for (int i = 0; i < flag_for_values.size(); i++) {
        if (flag == flag_for_values[i].short_name) {
            int val = atoi(values[i].c_str());
            return val;
        }
        if (flag == flag_for_values[i].full_name) {
            int val = atoi(values[i].c_str());
            return val;
        }
    }
}

int ArgumentParser::ArgParser::GetIntValue(std::string flag, int number) {
    flag = "--" + flag;
    int counter = 0;
    for (int i = 0; i < flag_for_values.size(); i++) {
        if (flag == flag_for_values[i].short_name and counter == number) {
            int val = atoi(values[i].c_str());
            return val;
        }
        if (flag == flag_for_values[i].full_name and counter == number) {
            int val = atoi(values[i].c_str());
            return val;
        }
        counter++;
    }
}

std::string ArgumentParser::ArgParser::HelpDescription() {
    return Help_description;
}

std::string ArgumentParser::ArgParser::GetStringValue(std::string flag) {
    flag = "--" + flag;
    for (int i = 0; i < flag_for_values.size(); i++) {
        if (flag == flag_for_values[i].short_name) {
            return values[i];
        }
        if (flag == flag_for_values[i].full_name) {
            return values[i];
        }
    }
}
