#include <lib/number.h>
#include <lib/number.tpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>

bool Predicate_1(int elem) {
    if (elem == 5) {
        return true;
    }
    return false;
}

bool Predicate_2(int elem) {
    if (elem < 15) {
        return true;
    }
    return false;
}

bool Predicate_3(int elem) {
    if (elem == 7) {
        return true;
    }
    return false;
}

bool Predicate_4(int elem1, int elem2) {
    if (elem1 < elem2) {
        return true;
    }
    return false;
}

bool Predicate_5(int elem1, int elem2) {
    if (elem1 == elem2) {
        return true;
    }
    return false;
}

TEST(STL, All_of) {
    std::vector<int> array = {5, 10, 7};
    auto start_it = array.begin();
    auto end_it = array.end();
    bool flag1;
    bool flag2;

    flag1 = stl_algorithms::all_of(start_it, end_it, Predicate_1);
    flag2 = stl_algorithms::all_of(start_it, end_it, Predicate_2);
    ASSERT_FALSE(flag1);
    ASSERT_TRUE(flag2);
}

TEST(STL, Any_of) {
    std::vector<int> array = {5, 10, 25};
    auto start_it = array.begin();
    auto end_it = array.end();
    bool flag;

    flag = stl_algorithms::any_of(start_it, end_it, Predicate_1);
    ASSERT_TRUE(flag);
}

TEST(STL, None_of) {
    std::vector<int> array = {40, 50, 25};
    auto start_it = array.begin();
    auto end_it = array.end();
    bool flag;

    flag = stl_algorithms::none_of(start_it, end_it, Predicate_1);
    ASSERT_TRUE(flag);
}

TEST(STL, One_of) {
    std::vector<int> array = {5, 7, 7};
    auto start_it = array.begin();
    auto end_it = array.end();
    bool flag1;
    bool flag2;

    flag1 = stl_algorithms::one_of(start_it, end_it, Predicate_1);
    flag2 = stl_algorithms::one_of(start_it, end_it, Predicate_3);
    ASSERT_TRUE(flag1);
    ASSERT_FALSE(flag2);
}

TEST(STL, Is_sorted) {
    std::vector<int> array = {1, 2, 3};
    std::vector<int> array2 = {1, 5, 2, 3, 4};
    auto start_it = array.begin();
    auto end_it = array.end();
    bool flag;

    flag = stl_algorithms::is_sorted(start_it, end_it, Predicate_4);
    ASSERT_TRUE(flag);
    start_it = array2.begin();
    end_it = array2.end();
    flag = stl_algorithms::is_sorted(start_it, end_it, Predicate_4);
    ASSERT_FALSE(flag);
}

TEST(STL, Find_not) {
    std::vector<int> array = {7, 3, 4, 2, 10};

    auto start_it = array.begin();
    auto end_it = array.end();
    auto fl = array.begin();

    fl = stl_algorithms::find_not(start_it, end_it, Predicate_1);

    ASSERT_EQ(7, *fl);
}

TEST(STL, Find_backward) {
    std::vector<int> array = {7, 3, 5, 4, 7};
    auto start_it = array.begin();
    auto end_it = array.end();
    auto fl = array.begin();

    fl = stl_algorithms::find_backward(start_it, end_it, Predicate_3);

    ASSERT_EQ(4, fl - start_it);
}

TEST(STL, Is_palindrome) {
    std::vector<int> array = {7, 3, 5, 5, 3, 7};
    auto start_it = array.begin();
    auto end_it = array.end();
    bool flag;

    flag = stl_algorithms::is_palindrome(start_it, end_it, Predicate_5);

    ASSERT_TRUE(flag);
}

TEST(STL, Is_partitioned) {
    std::vector<int> array = {7, 3, 5, 5, 3, 7};
    auto start_it = array.begin();
    auto end_it = array.end();
    bool flag;

    flag = stl_algorithms::is_partitioned(start_it, end_it, Predicate_1);

    ASSERT_TRUE(flag);
}

TEST(STL, Zip) {
    std::vector<int> array = {7, 3, 5, 5, 3, 7};
    std::vector<char> arr = {'a', 'b', 'c', 'd'};

    int chet = 0;
    for(auto value : stl_algorithms::zip<std::vector<int>, std::vector<char>, int, char>(array, arr)) {
        if (chet == 0) {
            ASSERT_EQ(7, value.first);
            ASSERT_EQ('a', value.second);
        }

        if (chet == 1) {
            ASSERT_EQ(3, value.first);
            ASSERT_EQ('b', value.second);
        }

        if (chet == 2) {
            ASSERT_EQ(5, value.first);
            ASSERT_EQ('c', value.second);
        }
        if (chet == 4) {
            ASSERT_EQ(5, value.first);
            ASSERT_EQ('d', value.second);
        }

        chet++;
    }
}

TEST(STL, Xrange) {
    auto x = xrange<double>(1.5, 5.5);
    std::vector<double> v {x.begin(), x.end()};


    auto x1 = xrange<int>(4);
    std::vector<int> v1 {x1.begin(), x1.end()};

    int answer[3];

    int chet = 0;
    for(auto i : xrange<int>(1, 6, 2)) {
        answer[chet] = i;
        chet++;
    }

    ASSERT_EQ(1, answer[0]);
    ASSERT_EQ(3, answer[1]);
    ASSERT_EQ(5, answer[2]);
}
int main() {
    return RUN_ALL_TESTS();
}