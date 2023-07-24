#pragma once
#include "number.h"

template<typename Iterator, typename Predicate>
bool stl_algorithms::all_of(Iterator begin, Iterator end, Predicate predicate) {

    for (Iterator it = begin; it != end; it++) {
        if (!predicate(*it)) {
            return false;
        }
    }
    return true;
}

template<typename Iterator, typename Predicate>
bool stl_algorithms::any_of(Iterator begin, Iterator end, Predicate predicate) {

    for (Iterator it = begin; it != end; it++) {
        if (predicate(*it)) {
            return true;
        }
    }
    return false;
}

template<typename Iterator, typename Predicate>
bool stl_algorithms::none_of(Iterator begin, Iterator end, Predicate predicate) {
    for (Iterator it = begin; it != end; it++) {
        if (predicate(*it)) {
            return false;
        }
    }
    return true;
}

template<typename Iterator, typename Predicate>
bool stl_algorithms::one_of(Iterator begin, Iterator end, Predicate predicate) {
    int chet = 0;

    for (Iterator it = begin; it != end; it++) {
        if (predicate(*it)) {
            chet++;
        }
        if (chet > 1) {
            return false;
        }
    }
    return true;
}

template<typename Iterator, typename Predicate>
bool stl_algorithms::is_sorted(Iterator begin, Iterator end, Predicate predicate) {

    for (Iterator it = begin; it != (end - 1); it++) {
        if (!predicate(*it, *(it + 1))) {
            return false;
        }
    }
    return true;
}

template<typename Iterator, typename Predicate>
Iterator stl_algorithms::find_not(Iterator begin, Iterator end, Predicate predicate) {

    for (Iterator it = begin; it != end; it++) {
        if (!predicate(*it)) {
            return it;
        }
    }
}

template<typename Iterator, typename Predicate>
Iterator stl_algorithms::find_backward(Iterator begin, Iterator end, Predicate predicate) { //const &

    for (Iterator it = end; it != begin; it--) {
        if (predicate(*it)) {
            return it;
        }
    }
}

template<typename Iterator, typename Predicate> // about end
bool stl_algorithms::is_palindrome(Iterator begin, Iterator end, Predicate predicate) {
    Iterator it1 = begin;
    Iterator it2 = end - 1;

    while (it1 != it2 and it1 < it2) {

        if (!predicate(*it1, *it2)) {
            return false;
        }
        it1++;
        it2--;
    }
    return true;
}

template<typename Iterator, typename Predicate>
bool stl_algorithms::is_partitioned(Iterator begin, Iterator end, Predicate predicate) {
    bool false_flag = false;
    bool true_flag = false;

    for (Iterator it = begin; it != end; it++) {
        if (predicate(*it)) {
            true_flag = true;
        } else {
            false_flag = true;
        }
    }

    if (true_flag and false_flag) {
        return true;
    }
    return false;
}

template<typename a, typename b, typename T1, typename T2>
stl_algorithms::zip<a, b, T1, T2>::Iterator::Iterator(int current_, a *first_storage_, b *second_storage_) {
    current = current_;
    first_storage = first_storage_;
    second_storage = second_storage_;
}

template<typename a, typename b, typename T1, typename T2>
std::pair<T1, T2>  stl_algorithms::zip<a, b, T1, T2>::Iterator::operator*() {
    return {*(first_storage->begin() + current), *(second_storage->begin() + current)};
}

template<typename a, typename b, typename T1, typename T2>
typename stl_algorithms::zip<a, b, T1, T2>::Iterator& stl_algorithms::zip<a, b, T1, T2>::Iterator::operator++() { //typename - type of data, not a class
    current += 1;
    return *this;
}

template<typename a, typename b, typename T1, typename T2>
bool stl_algorithms::zip<a, b, T1, T2>::Iterator::operator!=(Iterator const &other) const {
    return (current != other.current); //object of class iterator
}
template<typename a, typename b, typename T1, typename T2>
bool stl_algorithms::zip<a, b, T1, T2>::Iterator::operator==(Iterator const &other) const {
    return (current == other.current);
}


template<typename a, typename b, typename T1, typename T2>
stl_algorithms::zip<a, b, T1, T2>::zip(a &first_storage_, b &second_storage_) { // & reffer to not a copy an object
    first_storage = &first_storage_; // take address
    second_storage = &second_storage_;

    if (first_storage->size() < second_storage->size()) {
        size_min = first_storage->size();
    } else {
        size_min = second_storage->size();
    }
}

template<typename a, typename b, typename T1, typename T2>
typename stl_algorithms::zip<a, b, T1, T2>::Iterator stl_algorithms::zip<a, b, T1, T2>::begin() {
    return Iterator(0, first_storage, second_storage);
}
template<typename a, typename b, typename T1, typename T2>
typename stl_algorithms::zip<a, b, T1, T2>::Iterator stl_algorithms::zip<a, b, T1, T2>::end() {
    return Iterator(size_min, first_storage, second_storage);
}


template<typename T>
xrange<T>::Iterator::Iterator(T current_, T step_) {
    current  = current_;
    step = step_;
}

template<typename T>
T& xrange<T>::Iterator::operator*() {
        return current;
}

template<typename T>
T* xrange<T>::Iterator::operator->() {
    return &current;
}

template<typename T>
typename xrange<T>::Iterator& xrange<T>::Iterator::operator++() {
    current += step;
    return *this;
}

template<typename T>
typename xrange<T>::Iterator& xrange<T>::Iterator::operator--() {
    current -= step;
    return *this;
}

template<typename T>
typename xrange<T>::Iterator& xrange<T>::Iterator::operator++(int) { //
    Iterator obj = *this; // copy of this
    ++*this;
    return obj;
}

template<typename T>
typename xrange<T>::Iterator& xrange<T>::Iterator::operator--(int) { //
    Iterator obj = *this;
    --*this;
    return obj;
}

template<typename T>
bool xrange<T>::Iterator::operator!=(Iterator const &other) const { // ?
    return (current < other.current); //object of class iterator
}

template<typename T>
bool xrange<T>::Iterator::operator==(Iterator const &other) const {
    return (current == other.current);
}

template<typename T>
xrange<T>::xrange(T start_, T end_) {
    start = start_;
    tail = end_;
    step = 1;
}

template<typename T>
xrange<T>::xrange(T end_) {
    start = 0;
    tail = end_;
    step = 1;
}

template<typename T>
xrange<T>::xrange(T start_, T end_, T step_) {
    start = start_;
    tail = end_;
    step = step_;
}

template<typename T>
typename xrange<T>::Iterator xrange<T>::begin() {
    return Iterator(start, step);
}

template<typename T>
typename xrange<T>::Iterator xrange<T>::end() {
    return Iterator(tail, step);
}
