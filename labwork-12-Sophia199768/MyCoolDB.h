#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "Tabl.h"

class MyCoolDB {
public:
    MyCoolDB() {
    }

    void CREATE_TABLE(std::string name_, std::vector<std::pair<std::string, char>>& create, std::vector<int>& modif);
    void DROP_TABLE(std::string name_);
    bool check(std::string& cond, std::string& name1, std::string& name2, std::string& colomn1, std::string& colomn2, int line1, int line2);
    void InnerJoin(std::string& name1, std::string& name2, std::vector<std::string>& fields, std::string& cond, std::string& colomn1, std::string& colomn2);
    void LeftJoin(std::string& name1, std::string& name2, std::vector<std::string>& fields, std::string& cond, std::string& colomn1, std::string& colomn2);
    void RightJoin(std::string& name1, std::string& name2, std::vector<std::string>& fields, std::string& cond, std::string& colomn1, std::string& colomn2);
    void save(std::string& path);
    void load_file(std::string& path);
    void parse(std::string& query);

private:
    std::unordered_map<std::string, Tabl> DATABASE;

};