#include "number.h"
#include <iostream>
#include <iomanip>

const int osnovanie = 1000000000;

uint2022_t from_uint(uint32_t i) {
    std::vector<unsigned int> arr(0);

    do {
        if (sizeof(arr) + sizeof(arr[0]) * arr.size() >= 300) {
            return uint2022_t(arr);
        }
        arr.push_back(i % osnovanie);
        i = i / osnovanie;
    } while (i != 0);

    return uint2022_t(arr);
}

uint2022_t from_string(const char* buff) {
    std::string buff1 = buff;
    std::vector<unsigned int> arr(0);

    for (int i = buff1.length(); i > 0; i -= 9) {
        if (sizeof(arr) + sizeof(arr[0]) * arr.size() >= 300) {
            return uint2022_t(arr);
        }
        if (i < 9) {
            arr.push_back(atoi(buff1.substr(0, i).c_str())); // ��� ��������� �����
        } else {
            arr.push_back(atoi(buff1.substr(i - 9, 9).c_str())); // string � int
        }
    }
    return uint2022_t(arr);
}


uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    int peremennay_perepolneniy = 0;
    int maxlenght = std::max(lhs.array.size(), rhs.array.size());
    uint2022_t sum = lhs;

    for (int i = 0; i < maxlenght || peremennay_perepolneniy != 0; ++i) {
        if (sizeof(sum.array) + sizeof(sum.array[0]) * sum.array.size() >= 300) {
            sum.array.clear();
            return sum;
        }

        if (i == lhs.array.size()) {
            sum.array.push_back(0);
        }
        if (i < rhs.array.size()) {
            sum.array[i] += rhs.array[i] + peremennay_perepolneniy;
        } else {
            sum.array[i] += peremennay_perepolneniy;
        }
        peremennay_perepolneniy = sum.array[i] >= osnovanie;

        if (peremennay_perepolneniy != 0) {
            sum.array[i] -= osnovanie;
        }

    }
    return sum;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t raznosti = lhs;
    int peremennay_raznosti = 0;

    for (int i = 0; i < rhs.array.size() || peremennay_raznosti != 0; ++i) {
        raznosti.array[i] -= peremennay_raznosti + (i < rhs.array.size() ? rhs.array[i] : 0);
        peremennay_raznosti = lhs.array[i] < 0;
        if (peremennay_raznosti != 0) {
            raznosti.array[i] += osnovanie;
        }
    }


    return raznosti;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    std::vector<unsigned int> arr;
    if (sizeof(arr) + sizeof(arr[0]) * rhs.array.size() + sizeof(arr[0]) * lhs.array.size() >= 300) {
        return uint2022_t(arr);
    }
    arr.resize(lhs.array.size() + rhs.array.size()); // �����
    for (size_t i = 0; i < lhs.array.size(); ++i) {
        int peremennay_perepolnenia = 0;

        for (size_t j = 0; j < rhs.array.size() || peremennay_perepolnenia != 0; ++j) {
            long long cur = arr[i + j] + lhs.array[i] * 1LL * (j < rhs.array.size() ? rhs.array[j] : 0) + peremennay_perepolnenia; //1LL ����� ��������������
            arr[i + j] = static_cast<int>(cur % osnovanie); // ����� ����������� ������������ ��������������
            peremennay_perepolnenia = static_cast<int>(cur / osnovanie);
        }
    }
    return uint2022_t(arr);
}


uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    std::vector<unsigned int> arr;
    return uint2022_t(arr);
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int i = 0; i < rhs.array.size(); i++) {
        if (lhs.array[i] != rhs.array[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    int maxlenght = std::max(lhs.array.size(), rhs.array.size());
    for (int i = 0; i < maxlenght; i++) {
        if (lhs.array[i] != rhs.array[i]) {
            return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    if (value.array.empty()) {
        stream << 0;
    } else {
        stream << value.array.back();

        char old_fill = stream.fill('0');
        for (long long i = static_cast<long long>(value.array.size()) - 2; i >= 0; --i) {
            stream << std::setw(9) << value.array[i]; // setw ������� �� 9
        }

        stream.fill(old_fill);
    }
    return stream;
}