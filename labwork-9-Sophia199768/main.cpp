#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <ctime>
#include <stdlib.h>
template<class T>
struct list {

    struct Node {
        T element;
        Node* next;

        Node(T str) {
            element = str;
            next = nullptr;
        }
    };

    Node* first;
    Node* last;

    list() {
        first = nullptr;
        last = nullptr;
    }

    bool is_empty() const {
        return (first == nullptr);
    }

    void push(T str) {
        Node* p = new Node(str);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

};

template<class T>
struct Pool_Allocator {
    typedef T value_type;
    typedef T* pointer;
    typedef void* allocator_type;

    template <typename T1>
    struct rebind {
        using other = Pool_Allocator<T1>;
    };

    Pool_Allocator() {

        std::vector<std::pair<size_t, size_t>> pools = {{5000, 1000}, {500, 100}, {50, 10}};

        amount_of_pool = pools.size();
        size_t size_ = 0;

        for (size_t i = 0; i < pools.size(); i++) {
            size_ += pools[i].first * pools[i].second;
        }

        size = size_;
        alloc_pointer = malloc(size);
        start_ = (char*) alloc_pointer;
        end_ = start_ + size;
        next = start_;

        for (size_t i = 0; i < pools.size(); i++) {
            new_pools(pools[i].first, pools[i].second);
        }

    }

    Pool_Allocator(std::vector<std::pair<size_t, size_t>> pools) { // fisrt - size_of_blocks, second - amount_of_blocks
        amount_of_pool = pools.size();
        size_t size_ = 0;

        for (int i = 0; i < pools.size(); i++) {
            size_ += pools[i].first * pools[i].second;
        }

        size = size_;
        alloc_pointer = malloc(size);
        start_ = (char*) alloc_pointer;
        end_ = start_ + size;
        next = start_;

        for (size_t i = 0; i < pools.size(); i++) {
            new_pools(pools[i].first, pools[i].second);
        }
    }

    Pool_Allocator(const Pool_Allocator& refer) { // copy - constructor
        amount_of_pool = refer.amount_of_pool;
        size = refer.size;
        alloc_pointer = malloc(size);
        start_ = (char*) alloc_pointer;
        end_ = start_ + size;
        next = start_;
    }

    void new_pools(size_t size_of_block, size_t amount_of_blocks) {
        Pool new_pool(size_of_block, amount_of_blocks, next);
        all_pools.push(new_pool);
    }

    pointer& best_pool(size_t n, size_t& sizer_) {
        size_t min_block = UINT64_MAX;
        T* point = nullptr;
        auto k = all_pools.first;
        size_t l = 0;
        bool flag = false;
        auto it = all_pools.first;

        for (size_t i = 0; it != nullptr; i++, it = it->next) {
            if (n <= it->element.size_of_block and n < min_block) {

                for (size_t j = 0; j < it->element.amount_of_block; j++) {
                    if (it->element.free_blocks[j]) {
                        l = j;
                        flag = true;
                        break;
                    }

                }

                if (flag) {
                    min_block = it->element.size_of_block;
                    sizer_ = min_block;
                    point = (T*)(it->element.start + (it->element.size_of_block * l));
                    k = it;
                }
            }
        }

        if (point != nullptr) {
            k->element.free_blocks[l] = false;
            return point;
        } else {
            throw std::bad_alloc{};
        }
    }

    pointer& allocate(size_t n) {
        size_t sizer_;
        pointer point = best_pool(n * sizeof(value_type), sizer_); //how many bytes we need
        report( point, sizer_);
        return point;
    }

    void deallocate(T* p, size_t n_ = 0) {
        size_t n = 0;
        auto it = all_pools.first;
        for (int i = 0; it != nullptr; i++, it = it->next) {
            if ((char*)p >= it->element.start and (char*)p <= it->element.end) {
                for (int j = 0; j < it->element.amount_of_block; j++) {
                    if ((char*)p == it->element.start + (it->element.size_of_block * j)) {
                        it->element.free_blocks[j] = true;
                        n = it->element.size_of_block;
                    }
                }
            }
        }
        report(p, n, false);
    }

    void free_pool(size_t number_of_pool) {
        for (int i = 0; i < all_pools[number_of_pool].amount_of_block; i++) {
            all_pools[number_of_pool].free_blocks = true;
        }
    }

    int size_of() {
        return size;
    }

    void destroy(T* p) {
        size_t n = 0;
        auto it = all_pools.first;
        for (int i = 0; it == nullptr; i++, it = it->next) {
            if ((char*)p >= it->element.start and (char*)p <= it->element.end) {
                for (int j = 0; j < it->element.amount_of_block; j++) {
                    if ((char*)p == it->element.start + (it->element.size_of_block * j)) {
                        it->element.free_blocks[j] = true;
                        n = it->element.size_of_block;
                    }
                }
            }
            p->~T();
        }

    }

    struct Pool {

        Pool() = default;

        Pool(size_t size_of_block_, size_t amount_of_block_, char*& next_) { //*& url on pointer that change pointer
            free_blocks = (bool*)malloc(amount_of_block_ * sizeof(bool));

            for (int i = 0; i < amount_of_block_; i++) {
                free_blocks[i] = true;
            }

            size_of_block = size_of_block_;
            amount_of_block = amount_of_block_;
            start = next_;
            end = start + (size_of_block_ * amount_of_block_);
            next_ = end + 1;
        }

        bool* free_blocks; // econom memory
        size_t size_of_block;
        size_t amount_of_block;
        char* start;
        char* end;
    };


private:

    void report(T* p, std::size_t size_of_block, bool alloc = true) const {
        std::cout << (alloc ? "Alloc: " : "Dealloc: ") << size_of_block << " bytes at " << std::hex << std::showbase
                  << reinterpret_cast<void*>(p) << std::dec << '\n';
    }

    size_t  size;
    allocator_type alloc_pointer; //void* because we want to converse in which type of date
    size_t amount_of_pool;
    size_t  pool_size;
    list<Pool> all_pools;
    char* start_;
    char* end_;
    char* next;
};

template <typename T1, typename T2>
bool operator==(const Pool_Allocator<T1>& other1, const Pool_Allocator<T2>& other2) {
    return &other1 == &other2;
}

template <typename T1, typename T2>
bool operator!=(const Pool_Allocator<T1>& other1, const Pool_Allocator<T2>& other2) {
    return &other1 != &other2;
}

int main() {
    std::vector<std::pair<size_t, size_t>> pools = {{1200, 125}, {60,170}};

    std::unordered_map<int, int, std::hash<int>, std::equal_to<int>, Pool_Allocator<std::pair<const int, int>>> un_map;

    std::vector<int, Pool_Allocator<int>> array;

    un_map[0] = 1;
    un_map[1] = 2;
    un_map[2] = 3;

    for (int i = 0; i < 3; i++) {
        std::cout << un_map[i] << " ";
    }

    std::cout << '\n' << "............................................................." << '\n';

    std::list<int, Pool_Allocator<int>> l;


    Pool_Allocator<int> my_alloc(pools);

    clock_t start_1 = clock();
    int* pointer = my_alloc.allocate(8); //5, 6, 7, 8, 9, 10...?
    clock_t end_1 = clock();
    double seconds_1 = (double)(end_1 - start_1) / CLOCKS_PER_SEC;
    std::cout << "The time of working allocate from my allocator: " << seconds_1 << " seconds" <<  "\n";

    clock_t start_2 = clock();
    std::allocator<int> real_alloc;
    int* point  = real_alloc.allocate(8);
    clock_t end_2 = clock();
    double seconds_2 = (double)(end_2 - start_2) / CLOCKS_PER_SEC;
    std::cout << "The time of working allocate from library allocator: " << seconds_2 << " seconds" <<  "\n";

   // std::cout << *pointer;

    clock_t deallocate_start_1 = clock();
    my_alloc.deallocate(pointer);
    clock_t deallocate_end_1 = clock();
    double seconds_deallocate_1 = (double)(deallocate_end_1 - deallocate_start_1) / CLOCKS_PER_SEC;
    std::cout << "The time of working allocate from my allocator: " << seconds_deallocate_1 << " seconds" <<  "\n";

    clock_t deallocate_start_2 = clock();
    real_alloc.deallocate(point, 8);
    clock_t deallocate_end_2 = clock();
    double seconds_deallocate_2 = (double)(deallocate_end_2 - deallocate_start_2) / CLOCKS_PER_SEC;
    std::cout << "The time of working allocate from library allocator: " << seconds_deallocate_2 << " seconds" <<  "\n";

    std::cout << ".............................................................................." << '\n';

    int* point_1 = my_alloc.allocate(5);
    my_alloc.deallocate(point_1);
    point_1 = my_alloc.allocate(5);
    std::cout << " " << *point_1 << '\n';

    std::cout << ".............................................................................." << '\n';

    std::vector<int, Pool_Allocator<int>> vec;
    vec.push_back(5);
    vec.push_back(1);
    std::cout << ".............................................................................." << '\n';

    std::cout << "Why my allocator is better" << " ";

    std::vector<std::pair<size_t, size_t>> pools_s = {{100000000000000, 1}};
    Pool_Allocator<long long> my_allocs(pools_s);

    clock_t start_big = clock();
    my_allocs.allocate(10000000000000); //5, 6, 7, 8, 9, 10...?
    clock_t end_big = clock();
    double seconds_big = (double)(end_big - start_big) / CLOCKS_PER_SEC;

    std::cout << "The time of working allocate from my allocator: " << seconds_big << " seconds" <<  "\n";

   // real_alloc.allocate(10000000000000);



    std::cout << ".............................................................................." << '\n';

    std::vector<std::pair<size_t, size_t>> pools_new = {{1200, 125}, {60,170}};
    clock_t start_12 = clock();
    int* pointer12 = my_alloc.allocate(8); //5, 6, 7, 8, 9, 10...?
    clock_t end_12 = clock();
    double seconds_12 = (double)(end_12 - start_12) / CLOCKS_PER_SEC;
    std::cout << "The time of working allocate from my allocator: " << seconds_12 << " seconds" <<  "\n";

    std::cout << ".............................................................................." << '\n';


    clock_t start_121 = clock();
    for (int i = 0; i < 10; i++) {
        pointer12 = my_alloc.allocate(i);
    }
    std::cout << ".............................................................................." << '\n';
    clock_t end_121 = clock();
    double seconds_121 = (double)(end_121 - start_121) / CLOCKS_PER_SEC;
    std::cout << "The time of working allocate from my allocator: " << seconds_121 << " seconds" <<  "\n";

    std::cout << ".............................................................................." << '\n';


    return 0;
}

