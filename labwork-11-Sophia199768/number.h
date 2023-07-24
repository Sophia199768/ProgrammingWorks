#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

namespace stl_algorithms {
    template<typename Iterator, typename Predicate>
    bool all_of(Iterator begin, Iterator end, Predicate predicate);

    template<typename Iterator, typename Predicate>
    bool any_of(Iterator begin, Iterator end, Predicate predicate);

    template<typename Iterator, typename Predicate>
    bool none_of(Iterator begin, Iterator end, Predicate predicate);

    template<typename Iterator, typename Predicate>
    bool one_of(Iterator begin, Iterator end, Predicate predicate);

    template<typename Iterator, typename Predicate>
    bool is_sorted(Iterator begin, Iterator end, Predicate predicate);

    template<typename Iterator, typename Predicate>
    Iterator find_not(Iterator begin, Iterator end, Predicate predicate);

    template<typename Iterator, typename Predicate>
    Iterator find_backward(Iterator begin, Iterator end, Predicate predicate);

    template<typename Iterator, typename Predicate> // about end
    bool is_palindrome(Iterator begin, Iterator end, Predicate predicate);

    template<typename Iterator, typename Predicate>
    bool is_partitioned(Iterator begin, Iterator end, Predicate predicate);

    template<typename a, typename b, typename T1, typename T2>
    struct zip {

        class Iterator {
        public:
            Iterator(int current_, a *first_storage_, b *second_storage_);

            std::pair<T1, T2> operator*();

            Iterator &operator++();

            bool operator!=(Iterator const &other) const;
            bool operator==(Iterator const &other) const;

        private:
            int current;
            a *first_storage;
            b *second_storage;
        };

        zip(a &first_storage_, b &second_storage_);

        Iterator begin();

        Iterator end();

    private:
        int size_min;
        a *first_storage;
        b *second_storage;
    };

}

template<typename T>
struct xrange {

    class Iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using reference = T&;
        using value_type = T;
        using difference_type = T;

        Iterator(T current_, T step_ = 1);

        Iterator(const Iterator& other) = default; //

        T &operator*();

        T* operator->();

        Iterator &operator++();

        Iterator &operator--();

        Iterator &operator++(int);

        Iterator &operator--(int);

        bool operator!=(Iterator const &other) const; //object of class iterator

        bool operator==(Iterator const &other) const;

    private:
        T current;
        T step;
    };

    xrange(T start_, T end_);

    xrange(T end_);


    xrange(T start_, T end_, T step_);

    Iterator begin();

    Iterator end();

private:
    T start;
    T tail;
    T step;
};
