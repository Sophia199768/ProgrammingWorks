#pragma once
#include <iostream>
#include <algorithm>

template<typename T,  typename Allocator = std::allocator<T>>
class CCircularBuffer {
public:

    CCircularBuffer() = default;

    CCircularBuffer(int capacity) {
        capacity_ = capacity;
        buffer = Allocator().allocate(capacity);

    }

    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:

        bool flag;

        Iterator(T *p_start, int size, int pos, bool flag_ = false) {
            it = p_start;
            size_of_buff = size;
            position = pos;
            flag = flag_;
        }


        Iterator operator+(int n) { //return object
            bool flag_;
            if (position + n == size_of_buff) {
                flag_ = true;
            }
            int  position_ = (position + n) % size_of_buff;
            Iterator new_it = {it, size_of_buff, position_, flag_};
            return new_it;
        }

        Iterator operator-(int n) { //return object
            int position_ = position;
            position_ - n < 0 ? position_ = size_of_buff - position_ + n, flag = false : position_-= n;
            Iterator new_it = {it, size_of_buff, position_};
            return new_it;
        }

        Iterator &operator-=(int n) {
            position = (position + n) % size_of_buff;
            return *this;
        }

        Iterator &operator++() {
            if (position + 1 == size_of_buff) {
                flag = true;
            }
            position = (position + 1) % size_of_buff;

            return *this;
        }

        Iterator &operator--() {
            position - 1 < 0 ? position = size_of_buff - position + 1, flag = false : position--;
            return *this;
        }

        using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
         difference_type operator-(Iterator& other) {
             difference_type result = 1;
             while (*this != other) {
                 ++other;
                 result++;
             }
             return result;
        }

        Iterator &operator+=(difference_type n) {  //this - указатель on yourself
            if (position + n == size_of_buff) {
                flag = true;
            }
            position = (position + n) % size_of_buff;
            return *this;
        }


        T &operator*() {
            return it[position];
        }

        T object() {
            return it[position];
        }

        bool operator!=(Iterator const &other) const {
            return (position != other.position) or (flag != other.flag); //object of class iterator
        }

        bool operator==(Iterator const &other) const {
            return (position == other.position) and (flag == other.flag);
        }

        bool operator>(Iterator const &other) const {
            return (position > other.position) or (flag and !other.flag);
        }

         bool operator<(Iterator const &other) const {
            return (position < other.position) or (!flag and other.flag);
        }

        bool operator>=(Iterator const &other) const {
            return operator>(other) or operator==(other);
        }

        bool operator<=(Iterator const &other) const {
            return operator<(other) or operator==(other);
        }

        int position = 0;

    private:
        T *it;
        int size_of_buff = 0; // 0, 1, 2, 3, 4
    };

    Iterator begin_it() {
        return Iterator(buffer,  capacity_, start); // adress on first place of array
    }

    Iterator end_it() {
        bool flags = false;
        if (size_ == capacity_) {
            flags = true;
        }
        if (start > end) {
            flags = true;
        }

        return Iterator(buffer, capacity_, end, flags);
    }

    bool is_empty() {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }

    virtual void push_back(T value) {
        if (capacity_ == 1) {
            buffer[0] = value;
            return;
        }

        buffer[end++] = value;

        if (end > start and size_ == capacity_) {
            start++;
            start %= capacity_;
        }
        end %= capacity_;

        if (size_ < capacity_) {
            size_++;
        }
    }

    void push_front(T value) {
        if (capacity_ == 1) {
            buffer[0] = value;
            return;
        }

        if (size_ < capacity_) {
            size_++;
        }

        if (start == 0) {
            buffer[start] = value;
            start--;
            return;
        }

        if (--start > 0) {
            start %= capacity_;
            buffer[start] = value;
        } else {
            start = capacity_ - 1;
            buffer[start] = value;
        }

    }

    void pop_back() {
        if (--end >= 0) {
            end %= capacity_;
        } else {
            end = capacity_ - 1;
        }
        size_--;
    }

    void pop_front() {
        start++;
        start %= capacity_;
        size_--;
    }

    void clear() {
        std::memset(buffer, 0, sizeof(T) * capacity_);
        size_ = 0;
        end = 0;
        start = 0;
    }

    void insert(T value, Iterator iter) {
        T* buff;
        buff = (T*)malloc(capacity_ * sizeof(T));

        auto it1 = begin_it();
        auto it2 = end_it();
        int k = 0;

        for (; it1 != it2; ++it1) {
            if (it1 == iter) {
                buff[k] = value;
                k++;
            }
            buff[k] = *it1;
            k++;
        }

        int s = size_ + 1;
        clear();

        for (int i = 0; i < s; i++) {
            push_back(buff[i]);
        }

        if (size_ != capacity_) {
            size_++;
        }
    }

    void remove(Iterator it) {
        if (it == --end_it()) {
            pop_back();
            return;
        }
        if (it == begin_it()) {
            pop_front();
            return;
        }

        T* buff;
        buff = (T*)malloc(capacity_ * sizeof(T));

        auto it1 = begin_it();
        auto it2 = end_it();
        int k = 0;

        for (; it1 != it2; ++it1) {
            if (it1 == it) {
                continue;
            }
            buff[k] = *it1;
            k++;
        }

        clear();
        for (int i = 0; i < capacity_; i++) {
            push_back(buff[i]);
        }
    }

    int &front() {
        return buffer[start];
    }

    int &back() {
        return buffer[end];
    }

    T &operator[](int n) {
        return buffer[n];
    }

    virtual int capacity() {
        return capacity_;
    }

    int get_size() {
        return size_;
    }

    void print() {
        for (int i = start; i < capacity_; i++) {
            std::cout << buffer[i] << " ";
        }
        std::cout << '\n';
    }


private:
    T *buffer; // T* array of type T
    int start = 0;
    int capacity_ = 0;
    int end = 0;
    int size_ = 0;

};

template<typename T,  typename Allocator = std::allocator<T>>
class CCircularBufferExt : public CCircularBuffer<T> {
public:

    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:

        bool flag;

        Iterator(T *p_start, int size, int pos, bool flag_ = false) {
            it = p_start;
            size_of_buff = size;
            position = pos;
            flag = flag_;
        }

        Iterator &operator+=(int n) {  //this - указатель on yourself
            if (position + n == size_of_buff) {
                flag = true;
            }
            position = (position + n) % size_of_buff;
            return *this;
        }

        Iterator operator+(int n) { //return object
            bool flag_;
            if (position + n == size_of_buff) {
                flag_ = true;
            }
            int  position_ = (position + n) % size_of_buff;
            Iterator new_it = {it, size_of_buff, position_, flag_};
            return new_it;
        }

        Iterator operator-(int n) { //return object
            int position_ = position;
            position_ - n < 0 ? position_ = size_of_buff - position_ + n : position_-= n;
            Iterator new_it = {it, size_of_buff, position_};
            return new_it;
        }

        Iterator &operator-=(int n) {
            position = (position + n) % size_of_buff;
            return *this;
        }

        Iterator &operator++() {
            if (position + 1 == size_of_buff) {
                flag = true;
            }
            position = (position + 1) % size_of_buff;

            return *this;
        }

        Iterator &operator--() {
            position - 1 < 0 ? position = size_of_buff - position + 1 : position--;
            return *this;
        }

        using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
        difference_type operator-(const Iterator& rhs) const{
            return (it - rhs.it);
        }

        T &operator*() {
            return it[position];
        }

        bool operator!=(Iterator const &other) const {
            return (position != other.position) or (flag != other.flag); //object of class iterator
        }

        bool operator==(Iterator const &other) const {
            return (position == other.position) and (flag == other.flag);
        }

        bool operator>(Iterator const &other) const {
            return position > other.position;
        }

        bool operator<(Iterator const &other) const {
            return *this <= other && *this != other;
        }

        bool operator>=(Iterator const &other) const {
            return position >= other.position;
        }

        bool operator<=(Iterator const &other) const {
            return position <= other.position;
        }

        int position = 0;

        T object() {
            return it[position];
        }

    private:
        T *it;
        int size_of_buff = 0; // 0, 1, 2, 3, 4
    };

    Iterator begin_it() {
        return Iterator(buffer,  capacity_, start); // adress on first place of array
    }

    Iterator end_it() {
        bool flags = false;
        if (size_ == capacity_) {
            flags = true;
        }
        if (start > end) {
            flags = true;
        }

        return Iterator(buffer, capacity_, end, flags);
    }

    CCircularBufferExt(int size) {
        capacity_ = size;
        buffer = (T *) std::calloc(size, sizeof(T));
    }


    void Change_capasity() {
        T* buffer_new = Allocator().allocate(capacity_ * 2);
        auto it = begin_it();
        int i = 0;
        start = 0;
        for (it; it != end_it(); ++it) {
            buffer_new[i] = it.object();
        }
        end = i - 1;
        capacity_ = capacity_ * 2;
    }

    void push_back(T value) override {
        if (capasity_flag) {
            Change_capasity();
            capasity_flag = false;
            times = 1;
        }

        if (end + 1 == capacity_ and times == 2) {
            capasity_flag = true;
        }
        if (end + 1 == capacity_) {
            times += 1;
        }

        if (capacity_ == 1) {
            buffer[0] = value;
            return;
        }

        buffer[end++] = value;

        if (end > start and size_ == capacity_) {
            start++;
            start %= capacity_;
        }
        end %= capacity_;

        if (size_ < capacity_) {
            size_++;
        }
    }

    int capacity() override {
        return capacity_;
    }

private:
    T *buffer;
    int start = 0;
    int end = 0;
    int size_ = 0;
    bool capasity_flag = false;
    int capacity_ = 0;
    int times = 1;
};
