#include "Tabl.h"

bool More(std::string &q, double condition) { // 0
    double num = std::stod(q);
    return num > condition;
}

bool Less(std::string &q, double condition) { // 1
    double num = std::stod(q);
    return num < condition;
}

bool EqualString(std::string &q, std::string &condition) { // 4
    return q == condition;
}

bool NotEqualString(std::string &q, std::string &condition) { // 5
    return q != condition;
}

bool MoreOrEqual(std::string &q, double condition) { // 8
    double num = std::stod(q);
    return num >= condition;
}

bool LessOrEqual(std::string &q, double condition) { // 9
    double num = std::stod(q);
    return num <= condition;
}


void print::save(std::string str) {
    std::string h = str;
    answer.push_back(str);
}

void print::cout(int colomns) {
    int count = 0;
    for (int i = 0; i < answer.size(); i++) {
        count++;
        std::cout << answer[i];
        if (count == colomns) {
            std::cout << '\n';
            count = 0;
        } else {
            std::cout << ',';
        }
    }
}


Tabl::Colomn::Colomn(std::vector<std::string> &inf_, char type_, char primary_) {
    primary = primary_;
    type = type_;
    inf = inf_;
}

Tabl::Colomn::Colomn(const Colomn &colomn) {
    inf = colomn.inf;
    type = colomn.type;
    primary = colomn.primary;
}

Tabl::Tabl(std::vector<std::pair<std::string, char>> &inform, std::vector<int> &special) {
    std::vector<std::string> a;
    amount_of_line = 0;
    for (int it = 0; it < inform.size(); it++) {
        index_data[inform[it].first] = it;
        data.emplace_back(inform[it].first, Colomn(a, inform[it].second, (char) special[it]));
    }
}

bool Tabl::IsInt(std::string &value_get) {
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

bool Tabl::IsFloat(std::string &value_get) {
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

bool Tabl::IsVarChar(std::string &value_get) {

    if (value_get[0] != '"' or value_get[value_get.size() - 1] != '"') {
        return false;
    }
    return true;
}

bool Tabl::IsBool(std::string &value_get) {
    if (value_get == "true" or value_get == "false") {
        return true;
    } else {
        return false;
    }
}

bool Tabl::Type(std::string &inf, char it) {
    if (IsBool(inf) and it == 0) {
        return true;
    }
    if (IsInt(inf) and it == 1) {
        return true;
    }
    if (IsFloat(inf) and it == 2) {
        return true;
    }
    if (IsVarChar(inf) and it == 3) {
        return true;
    }
    return false;
}

Tabl::Exeption::Exeption(int num) {
    switch (num) {
        case 0:
            error = "Uncorrect type";
            break;
        case 1:
            error = "Key is Primary, you can't repeat value";
            break;
        default:
            error = "Unknown mistake";
            break;
    }
}

void Tabl::INSERT(std::vector<std::string> &info) {
    try {
        int chet = 0;
        amount_of_line++;
        for (auto it = data.begin(); it != data.end(); it++) {
            if (!Type(info[chet], it->second.type)) {
                throw (Exeption(0));
                return;
            }
            if (it->second.primary == 1 and find(it->second.inf.begin(), it->second.inf.end(), info[chet])) {
                throw (Exeption(1));
                return;
            }
            it->second.inf.push_back(info[chet]);
            chet++;
        }
    } catch (Exeption &mistake) {
        std::cout << mistake.error;
        exit(1);
    }
}

void Tabl::INSERT(std::vector<std::string> &names, std::vector<std::string> &info) {
    try {
        int chet = 0;
        amount_of_line++;
        for (auto it = data.begin(); it != data.end(); it++) {
            if (it->second.primary == 1 and find(it->second.inf.begin(), it->second.inf.end(), info[chet])) {
                throw (Exeption(0));
                return;
            }
            if (names[chet] == it->first and Type(info[chet], it->second.type)) {
                it->second.inf.push_back(info[chet]);
                chet++;
            } else {
                it->second.inf.push_back("NULL");
            }
        }
    } catch (Exeption &mistake) {
        std::cout << mistake.error;
        exit(1);
    }
}

void Tabl::UPDATE(std::vector<std::pair<std::string, std::string>> &info) { //
    try {
        for (int line = 0; line < amount_of_line; line++) {
            for (auto &it: info) {
                if (data[index_data[it.first]].second.primary == 1 and
                    find(data[index_data[it.first]].second.inf.begin(), data[index_data[it.first]].second.inf.end(),
                         it.second)) {
                    throw (Exeption(1));
                    return;
                }
                data[index_data[it.first]].second.inf[line] = it.second;
            }
        }
    } catch (Exeption &mistake) {
        std::cout << mistake.error;
        exit(1);
    }
}

void Tabl::UPDATE(std::vector<std::pair<std::string, std::string>> &info, std::string &condition) { //
    try {
        std::vector<Node *> roots;
        build_tree(condition, roots);

        for (int line = 0; line < amount_of_line; line++) {
            for (auto &cond: roots) {
                if (Preorder(cond, line)) {
                    for (auto &it: info) {
                        if (data[index_data[it.first]].second.primary == 1 and
                            find(data[index_data[it.first]].second.inf.begin(),
                                 data[index_data[it.first]].second.inf.end(), it.second)) {
                            throw (Exeption(1));
                            return;
                        }
                        data[index_data[it.first]].second.inf[line] = it.second;
                    }
                    break;
                }
            }
        }
    } catch (Exeption &mistake) {
        std::cout << mistake.error;
        exit(1);
    }
}

void Tabl::DELETE() {
    for (auto &&it: data) {
        it.second.inf.clear();
    }
    amount_of_line = 0;
}

void Tabl::DELETE(std::string &condition) {
    std::vector<Node *> roots;
    build_tree(condition, roots);

    for (int line = 0; line < amount_of_line; line++) {
        for (auto &cond: roots) {
            if (Preorder(cond, line)) {
                amount_of_line--;
                for (auto &&it: data) { // && delete for object
                    it.second.inf.erase(it.second.inf.begin() + line);
                }
                break;
            }
        }
    }
}


Tabl::Node::Node() {
        left = nullptr;
        right = nullptr;
    }

Tabl::Node::Node(std::string &oper, std::string &cond, std::string &colomn_name_) {
    operator_ = oper;
    condition = cond;
    colomn_name = colomn_name_;
    left = nullptr;
    right = nullptr;
}


bool Tabl::isTrue(Node *node, int i) {
    if (node->operator_ == "<") {
        double num = std::stod(node->condition);
        return Less(data[index_data[node->colomn_name]].second.inf[i], num);
    } else if (node->operator_ == ">") {
        double num = std::stod(node->condition);
        return More(data[index_data[node->colomn_name]].second.inf[i], num);
    } else if (node->operator_ == "<=") {
        double num = std::stod(node->condition);
        return LessOrEqual(data[index_data[node->colomn_name]].second.inf[i], num);
    } else if (node->operator_ == ">=") {
        double num = std::stod(node->condition);
        return MoreOrEqual(data[index_data[node->colomn_name]].second.inf[i], num);
    } else if (node->operator_ == "=") {
        return EqualString(data[index_data[node->colomn_name]].second.inf[i], node->condition);
    } else if (node->operator_ == "<>") {
        return NotEqualString(data[index_data[node->colomn_name]].second.inf[i], node->condition);
    }
    return false;
}

bool Tabl::Preorder(Node *node, int i) { // * ?
    if (node == nullptr) {
        return true;
    }
    if (!isTrue(node, i)) {
        return false;
    }
    bool x = Preorder(node->left, i);
    bool y = Preorder(node->right, i);
    return x and y;
}

void Tabl::connection(Node *&root, Node &key) {
    if (root == nullptr) {
        root = new Node;
        root->operator_ = key.operator_;
        root->colomn_name = key.colomn_name;
        root->condition = key.condition;
        return;
    }
    connection(root->left, key);
}

void Tabl::build_tree(std::string &question, std::vector<Node *> &roots) {
    std::string field_name;
    std::string cond;
    std::string tmp;
    bool flag_NOT = false;

    roots.push_back(nullptr);
    for (int i = 0; i < question.size(); i++) {

        while (question[i] == ' ') {
            i++;
        }
        if (question.size() >= 3) {
            std::string str;
            str += question[i];
            str += question[i + 1];
            str += question[i + 2];
            if (str == "NOT") {
                flag_NOT = true;
                i += 3;
            }
        }

        while (question[i] == ' ') {
            i++;
        }

        while (question[i] != ' ') {
            field_name += question[i];
            i++;
        }

        while (question[i] == ' ') {
            i++;
        }

        std::string sign;
        while (question[i] != ' ') {
            sign += question[i];
            i++;
        }

        if (flag_NOT) {
            if (sign == "=") {
                sign = "<>";
            } else if (sign == "<>") {
                sign = "=";
            } else if (sign == ">") {
                sign = "<=";
            } else if (sign == "<") {
                sign = ">=";
            } else if (sign == "<=") {
                sign = ">";
            } else if (sign == ">=") {
                sign = "<";
            }
            flag_NOT = false;
        }

        while (question[i] == ' ') {
            i++;
        }

        while (question[i] != ' ' and i < question.size()) {
            cond += question[i];
            i++;
        }

        while (question[i] == ' ') {
            i++;
        }

        while (tmp != "AND" and tmp != "OR" and i < question.size()) {
            tmp += question[i];
            i++;
        }

        Node object(sign, cond, field_name);
        connection(roots[roots.size() - 1], object);

        if (tmp == "OR") {
            roots.push_back(nullptr);
        }

        tmp = "";
        field_name = "";
        cond = "";
    }
}

void Tabl::SELECT(std::vector<std::string> &fields) {
    print Print;
    for (auto &i: fields) {
        Print.save(i);
    }

    for (int line = 0; line < amount_of_line; line++) {
        for (auto &it: fields) {
            Print.save(data[index_data[it]].second.inf[line]);
        }
    }
    Print.cout(fields.size());
}

void Tabl::SELECTWHERE(std::vector<std::string> &fields, std::string &question) { // fields - colomns in answer
    std::vector<Node *> roots;
    print Print;

    for (auto &i: fields) {
        Print.save(i);
    }

    build_tree(question, roots);

    for (int line = 0; line < amount_of_line; line++) {

        for (auto &condition: roots) {
            if (Preorder(condition, line)) {
                for (auto &it: fields) {
                    Print.save(data[index_data[it]].second.inf[line]);
                }
                break;
            }
        }
    }

    Print.cout(fields.size());
}

Tabl::~Tabl() {
    data.clear();
}

