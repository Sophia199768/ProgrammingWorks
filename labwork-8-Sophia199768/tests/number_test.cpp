#include <lib/buff.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(CCircularBufferTest, EmptyTest) { //buffer is empty
    CCircularBuffer<int> buffer(10);
    ASSERT_TRUE(buffer.is_empty());
}

TEST(CCircularBufferTest, NotEmptyTest) { //buffer is not empty
    CCircularBuffer<int> buffer(10);
    for (int i = 0; i < 10; ++i) {
        buffer.push_back(i);
    }
    ASSERT_FALSE(buffer.is_empty());
}

TEST(CCircularBufferTest, PushBack) { //push back test
    CCircularBuffer<int> buffer(10);
    for (int i = 0; i < 10; ++i) {
        buffer.push_back(i);
    }

    ASSERT_EQ(buffer.capacity(), 10);
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(buffer[i], i);
    }
}

TEST(CCircularBufferTest, PushBackCircul) { //push back test
    CCircularBuffer<int> buffer(5);
    for (int i = 0; i < 10; ++i) {
        buffer.push_back(i);
    }

    ASSERT_EQ(buffer.capacity(), 5);

    ASSERT_EQ(buffer[0], 5);
    ASSERT_EQ(buffer[1], 6);
    ASSERT_EQ(buffer[2], 7);
    ASSERT_EQ(buffer[3], 8);
    ASSERT_EQ(buffer[4], 9);

}

TEST(CCircularBufferTest, PushFront) { //push front test
    CCircularBuffer<int> buffer(10);

    for (int i = 0; i < 10; ++i) {
        buffer.push_front(i);
    }

    ASSERT_EQ(buffer.capacity(), 10);

    ASSERT_EQ(buffer[0], 0);
    ASSERT_EQ(buffer[1], 9);
    ASSERT_EQ(buffer[2], 8);
    ASSERT_EQ(buffer[3], 7);
    ASSERT_EQ(buffer[4], 6);
    ASSERT_EQ(buffer[5], 5);
    ASSERT_EQ(buffer[6], 4);
    ASSERT_EQ(buffer[7], 3);
    ASSERT_EQ(buffer[8], 2);
    ASSERT_EQ(buffer[9], 1);

}

TEST(CCircularBufferTest, PopFront) {
    CCircularBuffer<int> buffer(3);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    ASSERT_EQ(buffer.capacity(), 3);
    ASSERT_EQ(*buffer.begin_it(), 1);

    buffer.pop_front();
    buffer.pop_front();

    auto it = buffer.begin_it();
    auto it2 = buffer.end_it();

    ASSERT_EQ(*(buffer.begin_it()), 3);

}

TEST(CCircularBufferTest, PopBack1) { //
    CCircularBuffer<int> buffer(3);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);

    ASSERT_EQ(buffer.get_size(), 3);

    buffer.pop_back();

    ASSERT_EQ(*(--buffer.end_it()), 2);
}

TEST(CCircularBufferTest, PopBack2) { //
    CCircularBuffer<int> buffer(5);
    buffer.push_back(0);
    buffer.push_back(2);
    buffer.push_back(7);
    buffer.push_back(3);
    ASSERT_EQ(buffer.capacity(), 5);
    buffer.pop_back();
    ASSERT_EQ(*buffer.end_it(), 3);
}

TEST(CCircularBuffer, Clear) {
    CCircularBuffer<int> buffer(3);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    ASSERT_EQ(buffer.capacity(), 3);
    buffer.clear();
    ASSERT_EQ(buffer.get_size(), 0);
}

TEST(CCircularBuffer, Overwrite) {
    CCircularBuffer<int> buffer(2);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    buffer.push_back(4);
    ASSERT_EQ(buffer.capacity(), 2);
    ASSERT_EQ(buffer[0], 3);
    ASSERT_EQ(buffer[1], 4);
}

TEST(CCircularBuffer, IteratorTestBegin) {
    CCircularBuffer<int> buffer(10);
    CCircularBuffer<int>::Iterator it = buffer.begin_it();
    ASSERT_EQ(*it, 0);
}


TEST(CСircularBuffer, Iterator) {
    CCircularBuffer<int> buffer(3);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
     int i = 0;
     for (auto it = buffer.begin_it(); it != buffer.end_it(); ++it) {
         ASSERT_EQ(*it, ++i);
      }
}

TEST(CCircularBufferExt, MaxSize) {
    CCircularBufferExt<int> buffer(3);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    ASSERT_EQ(buffer.capacity(), 3);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(6);
    buffer.push_back(7);
    buffer.push_back(8);
    buffer.push_back(9);

    ASSERT_EQ(buffer.capacity(), 6);
}

TEST(CCircularBuffer, MaxSize) {
    CCircularBuffer<int> buffer(3);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    ASSERT_EQ(buffer.capacity(), 3);
}

bool h(int a) {
    return a > 0;
}

TEST(CCircularBuffer, All_of_Test) {
    CCircularBuffer<int> buffer(3);
    buffer.push_back(3);
    buffer.push_back(1);
    buffer.push_back(3);
    ASSERT_TRUE(std::all_of(buffer.begin_it(), buffer.end_it(), h));
    buffer.push_back(-6);
    ASSERT_FALSE(std::all_of(++buffer.begin_it(), buffer.end_it(), h));
}

TEST(CCircularBuffer, All_of_Test1) {
    CCircularBuffer<int> buffer(5);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(4);
    buffer.push_back(5);

    ASSERT_TRUE(std::all_of(buffer.begin_it(), buffer.end_it(), h));

    buffer.push_back(-6);

    ASSERT_FALSE(std::all_of(++buffer.begin_it(), buffer.end_it(), h));
}

TEST(CCircularBuffer, Swap) {
    CCircularBuffer<int> buffer(2);
    buffer.push_back(4);
    buffer.push_back(5);
    std::swap(buffer[0], buffer[1]);

    ASSERT_EQ(buffer[0], 5);
    ASSERT_EQ(buffer[1], 4);
}

TEST(CCircular, IteratorValids) { //Проверка итератора на правильность получения значения из контейнера
    CCircularBuffer<int> buffer(4);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(8);
    auto it = buffer.begin_it();
    ASSERT_EQ(*it, 4);
}

TEST(CCircular, IteratorValidsAlot) { //Проверка итератора на правильность получения значения из контейнера при многократном добавлении
    CCircularBuffer<int> buffer(4);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(8);
    buffer.push_back(1);
    buffer.push_back(2);
    buffer.push_back(3);
    buffer.push_back(7);
    buffer.push_back(9);
    buffer.push_back(86);
    buffer.push_back(4);
    buffer.push_back(54);
    buffer.push_back(81);
    auto it = buffer.begin_it();
    ASSERT_EQ(*it, 86);
}

TEST(CCircularBuffer, IteratorMovement) {
    CCircularBuffer<int> buffer(3);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(8);
    auto it = buffer.begin_it() + 1;
    auto it_copy = it;
    --it;
    ASSERT_TRUE(it != it_copy);
    ++it;
    ASSERT_TRUE(it == it_copy);
}

TEST(CCirularBuffer, IterratoMov) {
    CCircularBuffer<int> buffer(4); // smth th
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(8);
    buffer.push_back(9);
    auto it = buffer.begin_it();
    auto value = *it;
    *it = value + 1;
    ASSERT_TRUE(*it == value + 1);
}

TEST(CCircularBuffer, IterratorСompare) { // Проверка итератора на правильность применения операторов сравнения
    CCircularBuffer<int> buffer(4); // smth th
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(8);

    auto it1 = buffer.begin_it();
    auto it2 = buffer.begin_it();

    ASSERT_TRUE(it1 == it2);
    ASSERT_TRUE(it1 <= it2);

    ++it1;
    ASSERT_TRUE(it1 > it2);
    --it1;
    ++it2;
    ASSERT_TRUE(it1 <= it2);
    ASSERT_FALSE(it1 == it2);
}

TEST(CCircularBuffer, IteratorInc) {
    CCircularBuffer<int> buffer(4);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(8);
    auto it1 = buffer.begin_it();
    auto it2 = it1;
    ++it1;
    ASSERT_TRUE(it1 != it2);
    --it1;
    ASSERT_TRUE(it1 == it2);
}

TEST(CCircularBuffer, IteratorEqual) { // Проверка итератора на правильность применения операторов присваивания
    CCircularBuffer<int> buffer(4);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(8);
    auto it1 = buffer.begin_it();
    auto it2 = it1;
    ASSERT_TRUE(it1 == it2);
}

TEST(CCircularBuffer, Sort) { // Проверка итератора на правильность применения операторов присваивания
    CCircularBuffer<int> buffer(6);
    buffer.push_back(1);
    buffer.push_back(0);
    buffer.push_back(8);
    buffer.push_back(6);
    buffer.push_back(9);
    buffer.push_back(10);

    auto it1 = buffer.begin_it();
    auto it2 = buffer.end_it();
    std::sort(it1, it2);

   ASSERT_EQ(buffer[0], 0);
   ASSERT_EQ(buffer[1], 1);
   ASSERT_EQ(buffer[2], 6);
   ASSERT_EQ(buffer[3], 8);
   ASSERT_EQ(buffer[4], 9);
   ASSERT_EQ(buffer[5], 10);
}


TEST(CCircularBuffer, IteratorInsert) { // Проверка итератора на правильность применения операторов присваивания
    CCircularBuffer<int> buffer(4);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(8);
    auto it = buffer.begin_it() + 1;

    buffer.insert(4, it);

    auto it1 = buffer.begin_it();
    auto it2 = buffer.end_it();

    std::cout << '\n';
    for (; it1 != it2; ++it1) {
        std::cout << *it1 << " ";
    }
}


TEST(CCircularBuffer, IteratorRemove) { // Проверка итератора на правильность применения операторов присваивания
    CCircularBuffer<int> buffer(4);
    buffer.push_back(4);
    buffer.push_back(5);
    buffer.push_back(8);
    auto it = buffer.begin_it() + 1;
    buffer.remove( it);

    auto it1 = buffer.begin_it();
    auto it2 = buffer.end_it();


    ASSERT_EQ(*it1, 4);

    std::cout << '\n';
    for (; it1 != it2; ++it1) {
        std::cout << *it1 << " ";
    }

}


int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
