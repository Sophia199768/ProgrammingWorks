#include "parser.h"

void next(const std::string& str, int& j) {
    while (str[j] == ' ' or str[j] == '\n' or str[j] == '=') {
        j++;
    }
}

void pass_space(const std::string& str, int& j) {
    while (str[j] == ' ') {
        j++;
    }
}

void pass_comment(const std::string& str, int& k) {
    next(str, k);
    if (str[k] == '#') {
        while (str[k] != '\n' and k < str.size()) {
            k++;
        }
        k++;
    }
    next(str, k);
}

bool the_same_key(std::string key, std::vector<std::string> keys) {
    for (int i = 0; i < keys.size(); i++) {
        if (keys[i] == key) {
            return false;
        }
    }

    return true;
}

omfl::OmflParser omfl::parse(const std::string& str) {
    std::vector<std::string> keys;
    std::vector<std::string> values;
    std::vector<omfl::Sections> new_sections_;
    std::string section_name = "0";
    std::string key_name;
    std::string value;

    for (int i = 0; i < str.size(); i++) {
        next(str, i);

        if (str[i] == '[' or str[i - 1] == '[') {
            section_name.clear();
            i++;
            if (str[i - 2] == '[') {
                i -= 1;
            }
            while (str[i] != ']') {
                section_name += str[i];
                i++;
            }
            i++;
        }

        while(i < str.size() and str[i] != '[') {
            pass_comment(str, i);
            if (i >= str.size()) {
                break;
            }

            while (str[i] != ' ' and i < str.size()) {
                key_name += str[i];
                i++;
            }

            if (the_same_key(key_name, keys)) {
                keys.push_back(key_name);
            }

            key_name.clear();
            pass_comment(str, i);

            if (str[i] == '"') {

                if (str[i - 1] != '\n') {
                    value += '"';
                }

                i++;

                while (str[i] != '\n' and i < str.size()) {
                    value += str[i];
                    i++;
                    if (str[i] == ' ' and str[i - 1] == '"') {
                        pass_space(str, i);
                    }
                }

                values.push_back(value);
                value.clear();
                pass_comment(str, i);

            } else if (str[i] == '[') {
                value += '[';
                i++;
                while (str[i] != '\n' and i < str.size()) {
                    value += str[i];
                    i++;
                }
                values.push_back(value);
                value.clear();

                pass_comment(str, i);
            } else if ((str[i] >= '0' and str[i] <= '9') or str[i] == '+' or str[i] == '-') {
                while (str[i] != ' ' and str[i] != '\n' and i < str.size()) {
                    value += str[i];
                    i++;
                }
                values.push_back(value);
                value.clear();

                pass_comment(str, i);
            } else if (str[i] < '0' or str[i] > '9') {
                while (str[i] != ' ' and str[i] != '\n' and i < str.size()) {
                    value += str[i];
                    i++;
                }

                values.push_back(value);
                value.clear();
                pass_comment(str, i);
            }
        }

        if (new_sections_.size() > 0 and section_name == new_sections_[(new_sections_.size() - 1)].section_name) {
            for (int i = 0; i < keys.size(); i++) {
                new_sections_[new_sections_.size() - 1].keys.push_back(keys[i]);
                new_sections_[new_sections_.size() - 1].values.push_back(values[i]);
            }
        } else {

            Sections n = {section_name, keys, values};
            new_sections_.push_back(n);
        }
        section_name.clear();
        keys.clear();
        values.clear();
    }

    return OmflParser(new_sections_);
}

bool IsInt(std::string number) {
    int j = 0;
    while (number[j] == '+' or number[j] == '-') {
        j++;
    }
    for (int i = j; i < number.size(); i++) {
        if (number[i] < '0' or number[i] > '9') {
            return false;
        }
    }

    return true;
}

bool IsFloat(std::string value) {
    int j = 0;
    int number_of_dot = 0;
    while (value[j] == '+' or value[j] == '-' or value[j] == ' ') {
        j++;
    }

    for (int i = j; i < value.size(); i++) {
        if (value[i] == '.') {
            if (value[i - 1] < '0' or value[i - 1] > '9') {
                return false;
            }
            number_of_dot++;
            i++;
        }
        if (value[i] < '0' or value[i] > '9' or number_of_dot > 1) {
            return false;
        }
    }
    if (number_of_dot == 0) {
        return false;
    }
    return true;
}

bool IsString(std::string value) {
    int number_of_quotation_marks = 0;
    for (int i = 0; i < value.size(); i++) {
        if (value[i] == '"') {
            number_of_quotation_marks++;
        }
    }

    if (number_of_quotation_marks != 2) {
        return false;
    }

    if (value[0] != '"' or value[value.size() - 1] != '"') {
        return false;
    }

    return true;
}

bool IsBool(std::string value) {
    if (value == "true" or value == "false" or value == "\"true" or value == "\"false") {
        return true;
    } else {
        return false;
    }
}

bool IsArray(std::string value, int counter_iterations) {
    std::string buff;
    int count_l = 0;
    int count_r = 0;

    if (value[0] != '[' or value[value.size() - 1] != ']') {
        return false;
    }

    if (counter_iterations == 0) {
        for (int i = 0; i < value.size(); i++) {
            if (value[i] == '[') {
                count_l++;
            }
            if (value[i] == ']') {
                count_r++;
            }
        }
        if (count_l != count_r) {
            return false;
        }
    }
    counter_iterations++;

    for (int i = 1; i < value.size() - 1; i++) {
        if (value[i] == '"') {
            i++;
            buff += '"';
            while (value[i] != '"') {
                buff += value[i];
                i++;
            }
            buff += '"';
            if (!IsString(buff)) {
                return false;
            }
            buff.clear();
        }
        if (value[i] == '[') {
            i++;

            buff += '[';

            while (value[i] != ']') {
                buff += value[i];
                i++;

                if (i >= value.size()) {
                    return false;
                }
            }
            buff += ']';

            if (!IsArray(buff , counter_iterations)) {
                return false;
            }
            buff.clear();
        }
        if ((value[i] >= '0' and value[i] <= '9') or value[i] == '+' or value[i] == '-') {
            while (value[i] != ',' and i < value.size() - 1) {
                buff += value[i];
                i++;
            }
            if (!IsInt(buff) and !IsFloat(buff)) {
                return false;
            }
            buff.clear();
        }
        if (value[i] < '0' or value[i] > '9') {
            while (value[i] != ',' and value[i] != ']' and value[i] != ' ') {
                buff += value[i];
                i++;
            }
            if (buff == "true" or buff == "false") {
                if (!IsBool(buff)) {
                    return false;
                }
            }
            buff.clear();
        }
    }

    return true;
}

bool omfl::OmflParser::valid() const {
    for (int i = 0; i < sections.size(); i++) {
        if(sections[i].values.size() != sections[i].keys.size()) {
            return false;
        }
        if (sections[i].section_name.size() == 0 or sections[i].section_name[0] == '.'
            or sections[i].section_name[sections[i].section_name.size() - 1] == '.') {
            return false;
        }
        for (int j = 0; j < sections[i].keys.size(); j++) {
            if (sections[i].keys[j].size() == 0) {
                return false;
            }

            for (int k = 0; k < sections[i].keys[j].size(); k++) {
                if (sections[i].keys[j][k] != '-' and sections[i].keys[j][k] != '_' and sections[i].keys[j][k] != '=' ) {
                    if (sections[i].keys[j][k] < '0' or (sections[i].keys[j][k] > '9' and sections[i].keys[j][k] < 'A')
                        or sections[i].keys[j][k] > 'z') {
                        return false;
                    }
                }
            }

            if (sections[i].values[j][0] == '.') {
                return false;
            }
            if (sections[i].values[j].size() == 1 and
                (sections[i].values[j][0] == '+' or sections[i].values[j][0] == '-' or sections[i].values[j][0] == '[' or sections[i].values[j][0] == ']')) {
                return false;
            }

            if (sections[i].values[j].size() == 0) {
                return false;
            }

            if (!(IsInt(sections[i].values[j])) and !(IsFloat(sections[i].values[j]))
                and !(IsString(sections[i].values[j])) and !(IsBool(sections[i].values[j]))
                and !(IsArray(sections[i].values[j], 0))) {
                return false;
            }
        }


    }
    return true;
}

omfl::ForWork& omfl::ForWork::Get(std::string str) {
    for (int i = 0; i < sections_.size(); i++) {
        for (int j = 0; j < sections_[i].keys.size(); j++) {
            if (str == sections_[i].keys[j]) {
                value_get = sections_[i].values[j];
                return *this;
            }
        }
    }
    full_section_way = full_section_way + '.' + str;
    return *this;
}

omfl::ForWork omfl::OmflParser::Get(std::string str) const {
    std::string key_ = str;
    std::string section_name;
    int count_of_section = 0;

    if (str.find('.') != std::string::npos) {
        key_.clear();
        for (int i = str.size() - 1; i >= 0; i--) {

            if (str[i] == '.') {
                std::reverse(key_.begin(), key_.end());
                int j = 0;
                while (j < i) {
                    section_name += str[j];
                    j++;
                }
                break;
            }
            key_ += str[i];
        }

        for (int i = 0; i < sections.size(); i++) {
            if (section_name == sections[i].section_name) {
                count_of_section = i;
                break;
            }
        }
    }

    for (int i = 0; i < sections[count_of_section].keys[i].size(); i++) {
        if (sections[count_of_section].keys[i] == key_) {
            return ForWork(sections[count_of_section].values[i]);
        }
    }

    return ForWork(sections);
}

bool omfl::ForWork::IsInt() {
    int j = 0;

    while (value_get[j] == '+' or value_get[j] == '-') {
        j++;
    }

    for (int i = j; i < value_get.size(); i++) {
        if (value_get[i] < '0' or value_get[i] > '9') {
            return false;
        }
    }

    return true;
}

bool omfl::ForWork::IsFloat() {
    int j = 0;
    int number_of_dot = 0;
    while (value_get[j] == '+' or value_get[j] == '-' or value_get[j] == ' ') {
        j++;
    }

    for (int i = j; i < value_get.size(); i++) {
        if (value_get[i] == '.') {
            number_of_dot++;
            i++;
        }
        if (value_get[i] < '0' or value_get[i] > '9' or number_of_dot > 1) {
            return false;
        }
    }
    if (number_of_dot == 0) {
        return false;
    }
    return true;
}

bool omfl::ForWork::IsString() {
    int number_of_quotation_marks = 0;

    if (value_get[0] != '"' or value_get[value_get.size() - 1] != '"') {
        return false;
    }
    return true;
}

bool omfl::ForWork::IsArray() {
    std::string buff;

    for (int i = 1; i < value_get.size() - 1; i++) {
        if (value_get[i] == '"') {
            i++;
            buff += '"';

            while (value_get[i] != '"') {
                buff += value_get[i];
                i++;
            }

            buff += '"';
            array.push_back(buff);
            buff.clear();
        }
        if (value_get[i] == '[') {
            i++;
            buff += '[';
            while (value_get[i] != ']') {
                buff += value_get[i];
                i++;
            }
            buff += ']';
            array.push_back(buff);
            buff.clear();
        }
        if ((value_get[i] >= '0' and value_get[i] <= '9') or value_get[i] == '+' or value_get[i] == '-') {
            while (value_get[i] != ',' and i < value_get.size() - 1) {
                buff += value_get[i];
                i++;
            }
            array.push_back(buff);
            buff.clear();
        }
        if (value_get[i] < '0' or value_get[i] > '9') {
            while (value_get[i] != ',' and value_get[i] != ']' and value_get[i] != ' ') {
                buff += value_get[i];
                i++;
            }
            if (buff == "true" or buff == "false") {
                array.push_back(buff);
            }
            buff.clear();
        }
    }
    return true;
}

bool omfl::ForWork::IsBool() {
    if (value_get == "true" or value_get == "false") {
        return true;
    } else {
        return false;
    }
}

int omfl::ForWork::AsInt() {
    return atoi(value_get.c_str());
}

int omfl::ForWork::AsIntOrDefault(int perem) {
    if (IsInt()) {
        return AsInt();
    } else {
        return perem;
    }

}

float omfl::ForWork::AsFloat() {
    return atof(value_get.c_str());
}

float omfl::ForWork::AsFloatOrDefault(float perem) {
    if (IsFloat()) {
        return AsFloat();
    } else {
        return perem;
    }
}

std::string omfl::ForWork::AsString() {
    std::string str;
    int j = 0;

    for (int i = j; i < value_get.size(); i++) {
        if (value_get[i] != '\\' and value_get[i] != '\"') {
            str += value_get[i];
        }
    }
    return str;
}

std::string omfl::ForWork::AsStringOrDefault(std::string default_str) {
    if (IsString()) {
        return AsString();
    } else {
        return default_str;
    }
}

bool omfl::ForWork::AsBool() {
    if (value_get == "true") {
        return true;
    } else {
        return false;
    }
}