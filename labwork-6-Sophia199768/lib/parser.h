#pragma once

#include <filesystem>
#include <istream>
#include <vector>

namespace omfl {

class Sections {
public:

    Sections(std::string name, std::vector<std::string> keys_, std::vector<std::string> values_) {
        section_name = name;
        keys = keys_;
        values = values_;
    }

    std::string section_name;
    std::vector<std::string> keys;
    std::vector<std::string> values;
};

class ForWork {
public:

    ForWork(std::string str) {
        value_get = str;
    }

    ForWork(std::vector<Sections> section_f) {
        sections_ = section_f;
    }

    ForWork operator[] (int value_number) {
        IsArray();
        if (value_number > array.size()) {
            value_get = "none";
        } else {
            value_get = array[value_number];
        }
        return ForWork(value_get);
    }

    bool IsInt();
    bool IsFloat();
    bool IsString();
    bool IsArray();
    bool IsBool();
    bool AsBool();
    int AsInt();
    int AsIntOrDefault(int perem);
    float AsFloat();
    float AsFloatOrDefault(float perem);
    std::string AsString();
    std::string AsStringOrDefault(std::string default_str);
    ForWork& Get(std::string str); // retrurn *this

    std::string value_get;
    std::vector<std::string> array;
    std::vector<Sections> sections_;
    std::string full_section_way;
    bool part_section = false;
};

class OmflParser {
public:

    OmflParser(std::vector<Sections> section) {
        sections = section;
    }

    ForWork Get(std::string str) const;
    bool valid() const;
    std::vector<Sections> sections;
};

OmflParser parse(const std::filesystem::path &path);
OmflParser parse(const std::string &str);


}// namespace

// {[{key, key, key}, {2, 4, 6}], [{key, key, key}, {2, 4, 6}]}