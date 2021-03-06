/* Copyright 2022 */
//  Set.h
//  Clang
//
//  Created by Paramie Willmann on 22.06.22.
//


#ifndef SET_H_
#define SET_H_

#include <cstdio>

// Implementation of Dynamic Array using Linked List.
template<typename T>
class Set {
 public:
        // Constructor.
        Set();
        // Destructor:: free all node.
        ~Set();
        // Method to insert a element to set.
        void insert(T x);
        // Method that erase a given element.
        void erase(T x);
        // Method that check if element in set.
        bool lookup(T x);
        // return size of set.
        size_t size() {return size_;}
 private:
        class Node {
         public:
                ~Node() {delete _element;}
                T* _element;
                Node* next_;
        };
        Node* head_;
        size_t size_;
};

// A specialization of static Array for unsigned char,
// which holds 0-255 values.
template<> class Set<unsigned char> {
 public:
        // Constructor.
        Set();
        // Destructor:: free the Table.
        ~Set();
        // Method to insert a element to set.
        void insert(unsigned char x);
        // Method that erase a given element.
        void erase(unsigned char x);
        // Method that check if element in set.
        bool lookup(unsigned char x);
        // return size of set.
        size_t size() {return size_;}
 private:
        size_t size_;
        int *Table_;
};

#endif  // SET_H_
