#include "MyCoolDB.h"
#include "Tabl.h"

int main() {
    MyCoolDB bd;
    std::string q = "CREATE TABLE FIRST (GH INT, e BOOL, r VARCHAR(255));";
    bd.parse(q);
    std::string second = "INSERT INTO FIRST VALUES (10, true, \"fvhjior\");";
    bd.parse(second);
    std::string third = "INSERT INTO FIRST VALUES (20, true, \"cow\");";
    bd.parse(third);
    std::string eight = "INSERT INTO FIRST (GH, e) VALUES (221, true);";
    bd.parse(eight);
    //std::string  five = "SELECT * FROM FIRST;";
    //bd.parse(five);
    std::string q1 = "CREATE TABLE SECOND (some BOOL, SOMETHING INT, WHAT INT);";
    bd.parse(q1);
    std::string second1 = "INSERT INTO SECOND VALUES (false, 1, 25);";
    bd.parse(second1);
    std::string third1 = "INSERT INTO SECOND VALUES (false, 2, 34);";
    bd.parse(third1);
    std::string fiveff = "SELECT * FROM SECOND;";
    bd.parse(fiveff);

    // std::string join = "SELECT r, WHAT FROM FIRST RIGHT JOIN SECOND ON FIRST.GH > SECOND.SOMETHING;";
    // bd.parse(join);

    //std::string fourth = "UPDATE FIRST SET e = false WHERE GH = 1;";
    //std::string fourth = "UPDATE FIRST SET GH = 34;";
    //  bd.parse(fourth);
    // std::string six = "DELETE FROM FIRST WHERE GH = 1;";
    // bd.parse(six);

    //std::string seven = "DROP TABLE FIRST;";
    // bd.parse(seven);
    // bd.parse(second);
    // std::string  five = "SELECT * FROM FIRST;";
    //  bd.parse(five);
    //std::string th = "SAVE first;";
    //bd.parse(th);
    //"SELECT e, r FROM FIRST WHERE GH > 0 AND e != true OR GH = 1 AND e = true;";
    //std::string e = "LOAD first.txt;";
    // bd.parse(e);

    return 0;
}