#pragma once
#include <iostream>
#include <vector>

namespace ArgumentParser {

struct flags_name {
    std::string short_name;
    std::string full_name;
    flags_name(std::string short_flag, std::string full) {

      short_name = short_flag;
      full_name = full;
    }
};

class ArgParser {
public:

    ArgParser(std::string str) {
      parser_name = str;
    }

    ArgParser& AddStringArgument (std::string flag);
    ArgParser& AddStringArgument (char short_flag, std::string flag);
    ArgParser& AddStringArgument (char short_flag, std::string flag, std::string input_string2);
    ArgParser& AddIntArgument(char short_flag, std::string flag);
    ArgParser& AddIntArgument(std::string flag);
    ArgParser& AddIntArgument(std::string str, std::string str2);
    ArgParser& Default(const char* input_string);
    ArgParser& MultiValue(size_t MinArgsCount = 0);
    ArgParser& AddFlag(char short_flag, std::string full_flag);
    ArgParser& AddFlag(char short_flag, std::string full_flag, std::string input_string2);
    ArgParser& AddFlag (std::string flag, std::string description);
    ArgParser& Positional();

    void AddHelp(char short_flag, std::string full_flag, std::string discription);
    bool Default(bool flag);
    void StoreValue(bool& flag);
    void StoreValue(std::string& value);
    void StoreValues(std::vector<int>& int_values);

    bool GetFlag(std::string flag);
    bool Help();
    bool Parse(int argc, char** argv);
    bool Parse(std::vector<std::string> array);

    int GetIntValue(std::string flag);
    int GetIntValue(std::string flag, int number);

    std::string HelpDescription();
    std::string GetStringValue(std::string flag);
    void Parser_v(int found, int i, int j, std::vector<std::string> array, bool flag_long);

private:
    std::vector<flags_name> flags;
    std::vector<std::string> values;
    std::vector<flags_name> flag_for_values;
    std::string* address_of_store_value;
    std::string Help_description;
    std::string parser_name;
    bool StoreValueFlag = false;
    bool StoreValuesFlag = false;
    std::vector<bool*> StoreValueMeaning;
    bool Help_flag = false;
    bool Position = false;
    int Multivalue_flag = -1000;
    std::vector<int>* link;
    std::vector<flags_name> bool_flag;

};

}