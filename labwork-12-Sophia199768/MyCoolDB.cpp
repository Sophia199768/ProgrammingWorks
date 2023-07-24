#include "MyCoolDB.h"

void MyCoolDB::CREATE_TABLE(std::string name_, std::vector<std::pair<std::string, char>> &create, std::vector<int> &modif) {
    DATABASE[name_] = {create, modif};
}

void MyCoolDB::DROP_TABLE(std::string name_) {
    DATABASE[name_].~Tabl();
}

bool MyCoolDB::check(std::string &cond, std::string &name1, std::string &name2, std::string &colomn1, std::string &colomn2, int line1, int line2) {
    if (cond == ">") {
        return DATABASE[name1].data[DATABASE[name1].index_data[colomn1]].second.inf[line1] >
               DATABASE[name2].data[DATABASE[name2].index_data[colomn2]].second.inf[line2];
    } else if (cond == "<") {
        return DATABASE[name1].data[DATABASE[name1].index_data[colomn1]].second.inf[line1] <
               DATABASE[name2].data[DATABASE[name2].index_data[colomn2]].second.inf[line2];
    } else if (cond == ">=") {
        return DATABASE[name1].data[DATABASE[name1].index_data[colomn1]].second.inf[line1] >=
               DATABASE[name2].data[DATABASE[name2].index_data[colomn2]].second.inf[line2];
    } else if (cond == "<=") {
        return DATABASE[name1].data[DATABASE[name1].index_data[colomn1]].second.inf[line1] <=
               DATABASE[name2].data[DATABASE[name2].index_data[colomn2]].second.inf[line2];
    } else if (cond == "=") {
        return DATABASE[name1].data[DATABASE[name1].index_data[colomn1]].second.inf[line1] ==
               DATABASE[name2].data[DATABASE[name2].index_data[colomn2]].second.inf[line2];
    } else if (cond == "<>") {
        return DATABASE[name1].data[DATABASE[name1].index_data[colomn1]].second.inf[line1] !=
               DATABASE[name2].data[DATABASE[name2].index_data[colomn2]].second.inf[line2];
    }
    return false;
}

void MyCoolDB::InnerJoin(std::string &name1, std::string &name2, std::vector<std::string> &fields, std::string &cond,
               std::string &colomn1, std::string &colomn2) {
    print Print;
    for (auto &i: fields) {
        Print.save(i);
    }

    int size1 = DATABASE[name1].amount_of_line;
    int size2 = DATABASE[name2].amount_of_line;

    for (int line1 = 0; line1 < size1; line1++) {
        for (int line2 = 0; line2 < size2; line2++) {
            if (check(cond, name1, name2, colomn1, colomn2, line1, line2)) {
                for (auto &it: fields) {
                    if (DATABASE[name1].index_data.contains(it)) {
                        Print.save(DATABASE[name1].data[DATABASE[name1].index_data[it]].second.inf[line1]);
                    }
                }
                for (auto &it: fields) {
                    if (DATABASE[name2].index_data.contains(it)) {
                        Print.save(DATABASE[name2].data[DATABASE[name2].index_data[it]].second.inf[line2]);
                    }
                }
            }
        }
    }
    Print.cout(fields.size());
}

void MyCoolDB::LeftJoin(std::string &name1, std::string &name2, std::vector<std::string> &fields, std::string &cond,
              std::string &colomn1, std::string &colomn2) {
    print Print;
    for (auto &i: fields) {
        Print.save(i);
    }
    int size1 = DATABASE[name1].amount_of_line;
    int size2 = DATABASE[name2].amount_of_line;
    for (int line1 = 0; line1 < size1; line1++) {
        for (int line2 = 0; line2 < size2; line2++) {
            for (auto &it: fields) {
                if (DATABASE[name1].index_data.contains(it)) {
                    Print.save(DATABASE[name1].data[DATABASE[name1].index_data[it]].second.inf[line1]);
                }
            }
            if (check(cond, name1, name2, colomn1, colomn2, line1, line2)) {
                for (auto &it: fields) {
                    if (DATABASE[name2].index_data.contains(it)) {
                        Print.save(DATABASE[name2].data[DATABASE[name2].index_data[it]].second.inf[line2]);
                    }
                }
            } else {
                for (auto &it: fields) {
                    Print.save("NULL");
                }
            }
        }
    }
    Print.cout(fields.size());
}

void MyCoolDB::RightJoin(std::string &name1, std::string &name2, std::vector<std::string> &fields, std::string &cond,
               std::string &colomn1, std::string &colomn2) {
    print Print;
    for (auto &i: fields) {
        Print.save(i);
    }
    int size1 = DATABASE[name1].amount_of_line;
    int size2 = DATABASE[name2].amount_of_line;
    for (int line1 = 0; line1 < size1; line1++) {
        for (int line2 = 0; line2 < size2; line2++) {
            for (auto &it: fields) {
                if (DATABASE[name1].index_data.contains(it)) {
                    Print.save(DATABASE[name2].data[DATABASE[name2].index_data[it]].second.inf[line2]);
                }
            }
            if (check(cond, name1, name2, colomn1, colomn2, line1, line2)) {
                for (auto &it: fields) {
                    if (DATABASE[name2].index_data.contains(it)) {
                        Print.save(DATABASE[name1].data[DATABASE[name1].index_data[it]].second.inf[line1]);
                    }
                }
            } else {
                for (auto &it: fields) {
                    Print.save("NULL");
                }
            }
        }
    }
    Print.cout(fields.size());
}

void MyCoolDB::save(std::string &path) {
    std::ofstream save_table;
    save_table.open(path, std::ios_base::binary | std::ios_base::app);

    for (auto &&it: DATABASE) { //&& object not copy
        save_table << it.first << "!" << '\n';
        for (auto &&i: it.second.data) {
            save_table << i.first << "(" << i.second.type << ":" << i.second.primary << ")" << ' ';
        }
        save_table << "," << '\n';
        for (int lines = 0; lines < it.second.amount_of_line; lines++) {
            for (auto &&i: it.second.data) {
                save_table << i.second.inf[lines] << " ";
            }
            save_table << "," << '\n';
        }
    }
    save_table.close();
}

void MyCoolDB::load_file(std::string &path) {
    std::ifstream save_table;
    save_table.open(path, std::ios_base::binary | std::ios_base::in);
    std::string tmp;
    std::string name;
    std::vector<std::pair<std::string, char>> create;
    std::vector<int> modif;
    std::vector<std::string> info_insert;
    std::string name_of_colomn;
    std::string info;
    char type;
    char mod;
    int chet = 0;

    save_table >> tmp;
    while (!save_table.eof()) {

        int it = 0;
        while (tmp[it] != '!') {
            name += tmp[it];
            it++;
        }

        save_table >> tmp;
        while (tmp.find(',') == std::string::npos) {
            int i = 0;
            chet++;
            while (tmp[i] != '(') {
                name_of_colomn += tmp[i];
                i++;
            }
            i++;

            type = tmp[i];
            i += 2;
            mod = tmp[i];

            create.emplace_back(name_of_colomn, type);
            modif.push_back(mod);
            name_of_colomn = "";

            save_table >> tmp;
        }

        CREATE_TABLE(name, create, modif);

        save_table >> tmp;
        int counter = 0;
        while (tmp.find('!') == std::string::npos) {
            if (counter == chet) {
                DATABASE[name].INSERT(info_insert);
                info_insert.clear();
                counter = 0;
            } else {
                if (tmp != ",") {
                    info_insert.push_back(tmp);
                    counter++;
                }
            }

            save_table >> tmp;
            if (save_table.eof()) {
                save_table.close();
                return;
            }
        }

        name = "";
        create.clear();
        modif.clear();
        info_insert.clear();
        info = "";
        chet = 0;
    }
}

void MyCoolDB::parse(std::string &query) {
    char *locale = setlocale(LC_ALL, "");
    const int ESC = 27;
    std::string latitude;
    std::string longitude;

    std::string q_;
    std::vector<std::string> fields;

    if (query.find("CREATE TABLE") != std::string::npos) {
        std::string name;
        std::string tmp;
        std::string type;
        std::string name_colomn;
        std::vector<std::pair<std::string, char>> create;
        std::vector<int> modif;
        int i = 0;

        while (tmp != "CREATE TABLE") {
            tmp += query[i];
            i++;
        }
        i++;

        while (query[i] != '(') {
            if (query[i] != ' ') {
                name += query[i];
            }
            i++;
        }
        i++;
        tmp = "";

        while (query[i] != ')' and query[i + 1] != ';') {
            while (query[i] != ' ' and query[i] != ')') {
                name_colomn += query[i];
                i++;
            }
            i++;
            while (query[i] != ')' and query[i] != ',' and query[i] != ' ') {
                type += query[i];
                i++;
                if (type == "VARCHAR") {
                    while (query[i] != ')') {
                        i++;
                    }
                }
            }

            while (query[i] == ' ') {
                i++;
            }

            tmp = "";

            while (query[i] != ',' and query[i] != ')') {
                tmp += query[i];
                i++;
            }

            while (query[i] == ',' or query[i] == ' ') {
                i++;
            }

            char type_;
            if (type == "BOOL") {
                type_ = 0;
            } else if (type == "INT") {
                type_ = 1;
            } else if (type == "FLOAT" or type == "DOUBLE") {
                type_ = 2;
            } else if (type == "VARCHAR") {
                type_ = 3;
            }

            create.emplace_back(name_colomn, type_);
            name_colomn = "";
            type = "";
            if (tmp == "") {
                modif.push_back(0);
            } else if (tmp == "PRIMARY KEY") {
                modif.push_back(1);
            } else if (tmp == "FOREIGN KEY") {
                modif.push_back(2);
            } else if (tmp == "NULL") {
                modif.push_back(3);
            } else if (tmp == "NOT NULL") {
                modif.push_back(4);
            }
            tmp = "";
        }
        CREATE_TABLE(name, create, modif);
        return;
    }

    if (query.find("INSERT") != std::string::npos) {
        std::string tmp;
        int it = 0;

        while (query[it] == ' ') {
            it++;
        }

        while (tmp != "INSERT") {
            tmp += query[it];
            it++;
        }
        tmp = "";

        while (query[it] == ' ') {
            it++;
        }
        while (tmp != "INTO") {
            tmp += query[it];
            it++;
        }

        while (query[it] == ' ') {
            it++;
        }
        std::string table_name;

        while (query[it] != ' ') {
            table_name += query[it];
            it++;
        }

        while (query[it] == ' ') {
            it++;
        }

        std::vector<std::string> colomns_;
        tmp = "";
        if (query[it] == '(') {
            while (query[it] != ')') {
                if (query[it] != ',' and query[it] != '(' and query[it] != ' ') {
                    tmp += query[it];
                } else {
                    if (tmp != "") {
                        colomns_.push_back(tmp);
                        tmp = "";
                    }
                }
                it++;
            }
        }

        if (tmp != "") {
            colomns_.push_back(tmp);
        }

        tmp = "";
        if (query.find("VALUES") != std::string::npos) {
            std::vector<std::string> information;
            it = query.find("VALUES") + 8;

            while (query[it] != ')') {
                if (query[it] != ',' and query[it] != ' ') {
                    tmp += query[it];
                } else {
                    if (tmp != "") {
                        information.push_back(tmp);
                    }
                    tmp = "";
                }
                it++;
            }

            information.push_back(tmp);
            if (colomns_.size() != 0) {
                DATABASE[table_name].INSERT(colomns_, information);
                return;
            } else {
                DATABASE[table_name].INSERT(information);
                return;
            }
        } //else if (query.find("SELECT") != std::string::npos) {
        //
        // }
    }

    if (query.find("SELECT") != std::string::npos) {
        std::string table_name;
        std::string tmp;
        int it = 0;

        while (tmp != "SELECT") {
            tmp += query[it];
            it++;
        }
        tmp = "";

        while (query[it] == ' ') {
            it++;
        }

        while (tmp != "FROM") {

            if (query[it] == ',' or query[it] == ' ') {
                if (tmp != "*" and tmp != "") {
                    fields.push_back(tmp);
                }
                tmp = "";
                it++;
                continue;
            }

            tmp += query[it];
            it++;
        }

        while (query[it] == ' ') {
            it++;
        }

        while (query[it] != ' ' and query[it] != ';') {
            table_name += query[it];
            it++;
        }

        while (query[it] == ' ') {
            it++;
        }

        if (query.find('*') != std::string::npos) {

            for (auto &it_: DATABASE[table_name].data) {
                fields.push_back(it_.first);
            }
        }

        if (query.find("JOIN") != std::string::npos) {
            std::string which_join;
            std::string another_table;
            std::vector<std::pair<std::string, std::string>> answer;

            while (query[it] != ' ') {
                which_join += query[it];
                it++;
            }

            while (query[it] == ' ') {
                it++;
            }

            while (query[it] != ' ') {
                it++;
            }

            while (query[it] == ' ') {
                it++;
            }

            while (query[it] != ' ') {
                another_table += query[it];
                it++;
            }

            while (query[it] == ' ') {
                it++;
            }
            it += 2;

            while (query[it] == ' ') {
                it++;
            }

            int first;
            std::string first_table;
            std::string first_cond;

            while (query[it] != '.') {
                first_table += query[it];
                it++;
            }

            while (query[it] == ' ') {
                it++;
            }

            while (query[it] != ' ') {
                if (query[it] != '.') {
                    first_cond += query[it];
                }
                it++;
            }

            while (query[it] == ' ') {
                it++;
            }

            std::string sign;
            while (query[it] != ' ') {
                sign += query[it];
                it++;
            }

            while (query[it] == ' ') {
                it++;
            }

            std::string second_table;
            std::string second_cond;

            while (query[it] != '.') {
                second_table += query[it];
                it++;
            }

            while (query[it] == ' ') {
                it++;
            }

            while (query[it] != ' ' and query[it] != ';') {
                if (query[it] != '.') {
                    second_cond += query[it];
                }
                it++;
            }

            if (which_join == "INNER") {
                InnerJoin(first_table, second_table, fields, sign, first_cond, second_cond);
                return;
            }
            if (which_join == "LEFT") {
                LeftJoin(first_table, second_table, fields, sign, first_cond, second_cond);
                return;
            }
            if (which_join == "RIGHT") {
                RightJoin(first_table, second_table, fields, sign, first_cond, second_cond);
                return;
            }
        }

        if (query.find("WHERE") != std::string::npos) {
            it = query.find("WHERE") + 6;

            std::string condition;
            while (query[it] != ';') {
                if (query[it] == 'I' and query[it + 1] == 'S' and query[it + 2] == ' ') {
                    condition += '=';
                    condition += ' ';
                    it += 2;
                } else {
                    condition += query[it];
                    it++;
                }
            }
            DATABASE[table_name].SELECTWHERE(fields, condition);
            return;
        } else {
            DATABASE[table_name].SELECT(fields);
            return;
        }
    }

    if (query.find("UPDATE") != std::string::npos) {
        std::string tmp;
        std::string name_table;
        std::vector<std::pair<std::string, std::string>> update;
        int i = 0;

        while (tmp != "UPDATE") {
            tmp += query[i];
            i++;
        }

        while (query[i] == ' ') {
            i++;
        }

        while (query[i] != ' ') {
            name_table += query[i];
            i++;
        }
        while (query[i] == ' ') {
            i++;
        }

        tmp = "";

        while (tmp != "SET") {
            tmp += query[i];
            i++;
        }

        while (query[i] == ' ') {
            i++;
        }

        std::string colomn_;
        std::string inform;

        int where = query.find("WHERE");
        while (i != where and query[i] != ';' and query[i] != '\0') {
            while (query[i] != ' ') {
                colomn_ += query[i];
                i++;
            }
            i += 3;

            while (query[i] != ';' and query[i] != ',' and query[i] != '\n' and query[i] != ' ') {
                inform += query[i];
                i++;
            }

            while (query[i] == ' ') {
                i++;
            }

            update.emplace_back(colomn_, inform);
            colomn_ = "";
            inform = "";
        }

        if (where != -1) {
            i = query.find("WHERE") + 6;

            std::string condition;
            while (query[i] != ';') {
                if (query[i] == 'I' and query[i + 1] == 'S' and query[i + 2] == ' ') {
                    condition += '=';
                    condition += ' ';
                    i += 2;
                } else {
                    condition += query[i];
                    i++;
                }
            }
            DATABASE[name_table].UPDATE(update, condition);
        } else {
            DATABASE[name_table].UPDATE(update);
        }
    }

    if (query.find("DELETE") != std::string::npos) {
        std::string tmp;
        std::string name_table;
        int i = 0;

        while (query[i] == ' ') {
            i++;
        }

        while (tmp != "DELETE") {
            tmp += query[i];
            i++;
        }

        while (query[i] == ' ') {
            i++;
        }

        tmp = "";

        while (tmp != "FROM") {
            tmp += query[i];
            i++;
        }

        while (query[i] == ' ') {
            i++;
        }

        while (query[i] != ' ' and query[i] != ';') {
            name_table += query[i];
            i++;
        }

        int where = query.find("WHERE");

        if (where != -1) {
            i = query.find("WHERE") + 6;

            std::string condition;
            while (query[i] != ';') {
                if (query[i] == 'I' and query[i + 1] == 'S' and query[i + 2] == ' ') {
                    condition += '=';
                    condition += ' ';
                    i += 2;
                } else {
                    condition += query[i];
                    i++;
                }
            }

            DATABASE[name_table].DELETE(condition);
            return;
        } else {
            DATABASE[name_table].DELETE();
            return;
        }
    }

    if (query.find("DROP TABLE") != std::string::npos) {
        std::string tmp;
        std::string name_for_drop;
        int it = 0;

        while (query[it] == ' ') {
            it++;
        }

        while (tmp != "DROP TABLE") {
            tmp += query[it];
            it++;
        }

        while (query[it] == ' ') {
            it++;
        }

        while (query[it] != ' ' and query[it] != ';') {
            name_for_drop += query[it];
            it++;
        }
        DROP_TABLE(name_for_drop);
    }

    if (query.find("SAVE") != std::string::npos) {
        std::string path;
        std::string tmp;
        int it = 0;

        while (query[it] == ' ') {
            it++;
        }

        while (tmp != "SAVE") {
            tmp += query[it];
            it++;
        }

        while (query[it] == ' ') {
            it++;
        }

        while (query[it] != ' ' and query[it] != ';') {
            path += query[it];
            it++;
        }

        path += ".txt";
        save(path);
        return;
    }

    if (query.find("LOAD") != std::string::npos) {
        std::string path;
        std::string tmp;
        int it = 0;

        while (query[it] == ' ') {
            it++;
        }

        while (tmp != "LOAD") {
            tmp += query[it];
            it++;
        }

        while (query[it] == ' ') {
            it++;
        }
        while (query[it] != ' ' and query[it] != ';') {
            path += query[it];
            it++;
        }
        load_file(path);
        return;
    }
}
