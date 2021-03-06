/* Copyright 2022 */
//  String.cpp
//  Clang
//
//  Created by Paramie Willmann on 06.06.22.
//

#include <utility>
#include <cstring>
#include "./String.h"

// ____________________________________________________________________________
String::String() {
    size_ = 0;
    data_ = new char[1];
    data_[0] = '\0';
}

// ____________________________________________________________________________
String::~String() {
    delete[] data_;
}

// ____________________________________________________________________________
String::String(const String& other) {
    size_ = other.size_;
    data_ = new char[other.size_ + 1];
    for (size_t i = 0; i < size_ + 1; i++) data_[i] = other.data_[i];
}

// ____________________________________________________________________________
String::String(String&& other) {
    delete[] data_;
    size_ = other.size_;
    data_ = other.data_;
    other.size_ = 0;
    other.data_ = nullptr;
}

// ____________________________________________________________________________
String& String::operator=(const char* other) {
    delete[] data_;
    size_ = strlen(other);
    // while (other[size_] != '\0') size_++;
    data_ = new char[size_ + 1];
    for (size_t i = 0; i < size_ + 1; ++i) data_[i] = other[i];
    return *this;
}

// ____________________________________________________________________________
String& String::operator=(const String& other) {
    if (this == &other) { return *this; }
    delete[] data_;
    size_ = other.size();
    // while (other.data_[size_] != '\0') size_++;
    data_ = new char[size_ + 1];
    for (size_t i = 0; i < size_ + 1; ++i) data_[i] = other.data_[i];
    return *this;
}

// ____________________________________________________________________________
String& String::operator=(String&& other) {
    if (this == &other) { return *this; }
    delete[] data_;
    size_ = other.size_;
    data_ = other.data_;
    other.data_ = nullptr;
    other.size_ = 0;
    return *this;
}

// ____________________________________________________________________________
size_t String::size() const {
    return size_;
}

// ____________________________________________________________________________
char* String::c_str() const {
    return data_;
}

// ____________________________________________________________________________
StringSorter::StringSorter(int size) {
    sizeSorter_ = size;
    dataSorter_ = new String[sizeSorter_];
}

// ____________________________________________________________________________
StringSorter::~StringSorter() {
    delete[] dataSorter_;
}

// ____________________________________________________________________________
String& StringSorter::operator[](size_t i) const {
    if (i < sizeSorter_) {
        return dataSorter_[i];
    } else {
        return dataSorter_[0];
    }
}

// ____________________________________________________________________________
size_t StringSorter::size() const {
    return sizeSorter_;
}

// ____________________________________________________________________________
void StringSorter::swap(int l, int r) {
    String t;
    t = dataSorter_[r].c_str();
    dataSorter_[r] = dataSorter_[l];
    dataSorter_[l] = t;
}

// ____________________________________________________________________________
void StringSorter::swapwithmove(int l, int r) {
    String t = dataSorter_[r];
    dataSorter_[r] = std::move(dataSorter_[l]);
    dataSorter_[l] = std::move(t);
}

// ____________________________________________________________________________
void StringSorter::q_sortwithmove() {
    // printf("start sorting...\n");
    quicksortwithmove(0, sizeSorter_ - 1);
}

// ____________________________________________________________________________
void StringSorter::q_sortwithcopy() {
    // printf("start sorting...\n");
    quicksort(0, sizeSorter_ - 1);
}

// ____________________________________________________________________________
void StringSorter::quicksort(int l, int r) {
        if (l >= r) {
            return;
        }
        int index = partition(l, r);
        quicksort(l, index - 1);
        quicksort(index + 1, r);
        return;
    }

// ____________________________________________________________________________
int StringSorter::partition(int l, int r) {
    String pivot = dataSorter_[l];
    int count = 0;
    for (int i = l + 1; i <= r; i++) {
        if (strcmp(dataSorter_[i].c_str(), pivot.c_str()) < 0) {
            count++;
        }
    }

    int PivotIndex = l + count;
    swap(l, PivotIndex); // NOLINT
    // printf("i: %d \n", i_);
    // printf("j: %d \n", j_);
    while (l < PivotIndex && r > PivotIndex) {
        while (strcmp(dataSorter_[r].c_str(), pivot.c_str()) > 0) {
            r--;
        }
        while (strcmp(dataSorter_[l].c_str(), pivot.c_str()) < 0) {
            l++;
        }
        if (l < PivotIndex && r > PivotIndex) {
            swap(l, r);  // NOLINT
        }
    }
    // printf("Finished Partition \n");
    // for (int i = 0; i < sizeSorter_; i++){
    //     printf("%s \n", dataSorter_[i].c_str());
    // }
    return PivotIndex;
}

// ____________________________________________________________________________
void StringSorter::quicksortwithmove(int l, int r) {
        if (l >= r) {
            return;
        }
        int index = partition(l, r);
        quicksort(l, index - 1);
        quicksort(index + 1, r);
        return;
    }

// ____________________________________________________________________________
int StringSorter::partitionwithmove(int l, int r) {
    String pivot = dataSorter_[l];
    int count = 0;
    for (int i = l + 1; i <= r; i++) {
        if (strcmp(dataSorter_[i].c_str(), pivot.c_str()) < 0) {
            count++;
        }
    }

    int PivotIndex = l + count;
    swapwithmove(l, PivotIndex); // NOLINT
    // printf("i: %d \n", i_);
    // printf("j: %d \n", j_);
    while (l < PivotIndex && r > PivotIndex) {
        while (strcmp(dataSorter_[r].c_str(), pivot.c_str()) > 0) {
            r--;
        }
        while (strcmp(dataSorter_[l].c_str(), pivot.c_str()) < 0) {
            l++;
        }
        if (l < PivotIndex && r > PivotIndex) {
            swapwithmove(l, r);  // NOLINT
        }
    }
    // printf("Finished Partition \n");
    // for (int i = 0; i < sizeSorter_; i++){
    //     printf("%s \n", dataSorter_[i].c_str());
    // }
    return PivotIndex;
}

// ____________________________________________________________________________
void StringSorter::bsortwithcopy() {
    for (size_t i = 0; i < sizeSorter_; ++i) {
        for (size_t j = 0; j + i + 1 < sizeSorter_; ++j) {
            if (strcmp(dataSorter_[j].c_str(),
                dataSorter_[j + 1].c_str()) > 0) {
                swap(j, j+1);
            }
        }
    }
}

// ____________________________________________________________________________
void StringSorter::bsortwithmove() {
    for (size_t i = 0; i < sizeSorter_; ++i) {
        for (size_t j = 0; j + i + 1 < sizeSorter_; ++j) {
            if (strcmp(dataSorter_[j].c_str(),
                dataSorter_[j + 1].c_str()) > 0) {
                swapwithmove(j, j+1);
            }
        }
    }
}
