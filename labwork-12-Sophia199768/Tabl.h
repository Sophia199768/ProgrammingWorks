#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

bool More(std::string& q, double condition);
bool Less(std::string& q, double condition);
bool EqualString(std::string& q, std::string& condition);
bool NotEqualString(std::string& q, std::string& condition);
bool MoreOrEqual(std::string& q, double condition);
bool LessOrEqual(std::string& q, double condition);

struct print {
    print() {

    }
    void save(std::string str);
    void cout(int colomns);
    std::vector<std::string> answer;
};

class Tabl {
public:
    struct Colomn {
        Colomn(std::vector<std::string>& inf_, char type_, char primary_ = 0);
        Colomn(const Colomn& colomn);
        Colomn() = default;

        std::vector<std::string> inf;
        char primary;
        char type;
    };

    Tabl() = default;
    Tabl(std::vector<std::pair<std::string, char>>& inform, std::vector<int>& special);
    static bool IsInt(std::string& value_get);
    static bool IsFloat(std::string& value_get);
    static bool IsVarChar(std::string& value_get);
    static bool IsBool(std::string& value_get);
    static bool Type(std::string& inf, char it);

    template<typename Iterator>
    bool find(Iterator begin, Iterator end, std::string& info) {
        for (Iterator it = begin; it != end; it++) {
            if (*it == info) {
                return true;
            }
        }
        return false;
    }

    class Exeption {
    public:
        Exeption(int num);
        std::string error;
    };

    void INSERT(std::vector<std::string>& info);
    void INSERT(std::vector<std::string> &names, std::vector<std::string> &info);
    void UPDATE(std::vector<std::pair<std::string, std::string>> &info);
    void UPDATE(std::vector<std::pair<std::string, std::string>> &info, std::string &condition);
    void DELETE();
    void DELETE(std::string &condition);

    struct Node {
        Node();
        Node(std::string &oper, std::string &cond, std::string &colomn_name_);
        Node *left;
        Node *right;
        std::string operator_;
        std::string condition;
        std::string colomn_name;
    };

    bool isTrue(Node *node, int i);
    bool Preorder(Node *node, int i);
    void connection(Node *&root, Node &key);
    void build_tree(std::string &question, std::vector<Node *> &roots);
    void SELECT(std::vector<std::string> &fields);
    void SELECTWHERE(std::vector<std::string> &fields, std::string &question);

    ~Tabl();

    std::vector<std::pair<std::string, Colomn>> data;
    std::unordered_map<std::string, int> index_data;
    int amount_of_line = 0;
};


