/* Copyright 2022 */
//  Set.cpp
//  Clang
//
//  Created by Paramie Willmann on 22.06.22.
//

#include "./Set.h"
#include <utility>

template<typename T>
Set<T>::Set() {
    size_ = 0;
    head_ = new Node;
    head_->next_ = nullptr;
    head_->_element = nullptr;
}

template<typename T>
Set<T>::~Set() {
    Node *temp;
    // free all nodes.
    while (head_->next_ != nullptr) {
        temp = head_;
        head_ = head_->next_;
        delete temp;
    }
    // free last node.
    delete head_;
}

template<typename T>
bool Set<T>::lookup(T new_element) {
    if (head_->_element == nullptr) {
        return false;
    }
    Node *temp;
    temp = head_;
    while (temp->next_ != nullptr) {
        if (*temp->_element == new_element) {
            return true;
        }
        temp = temp->next_;
    }
    // check last node.
    if (*temp->_element == new_element) {return true;}
    return false;
}

template<typename T>
void Set<T>::insert(T new_element) {
    // if Set is empty then insert first element.
    if (head_->_element == nullptr) {
        size_++;
        head_->_element = new T(new_element);
        head_->next_ = nullptr;
    } else {
            // insert next element at head position.
            if (lookup(new_element) == 0) {
                Node *prev_head;
                size_++;
                // save current head to prev_head.
                prev_head = head_;
                // assign new head and put in data.
                head_ = new Node;
                head_->_element = new T(new_element);
                // assign next node to prev_head.
                head_->next_ = prev_head;
            }
    }
}

template<typename T>
void Set<T>::erase(T target) {
    if (lookup(target) == 0) {
        return;
    }
    size_--;
    Node *temp;
    Node *prev;
    temp = head_;
    prev = nullptr;
    if (*head_->_element == target) {
        head_ = temp->next_;
    } else {
        while (*temp->_element!= target) {
            prev = temp;
            temp = temp->next_;
        }
        if (temp->_element == nullptr) {
            return;
        }
        prev->next_ = temp->next_;
    }
    delete temp;
}

Set<unsigned char>::Set() {
    size_ = 0;
    // create Table with 256 empty slots marked as -1.
    Table_ = new int[256];
    for (int i = 0; i < 256; i++) {
        Table_[i] = -1;
    }
}

Set<unsigned char>::~Set() {
    delete[] Table_;
}

void Set<unsigned char>::insert(unsigned char x) {
    if (!lookup(x)) {
        size_++;
        Table_[x] = x;
    }
}

bool Set<unsigned char>::lookup(unsigned char x) {
    if (Table_[x] == -1) {
        return false;
    } else {
        return true;
    }
}

void Set<unsigned char>::erase(unsigned char x) {
    if (lookup(x)) {
        size_--;
        Table_[x] = -1;
    }
}

template class Set<int>;
template class Set<float>;
