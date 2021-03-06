// Copyright 2022, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>.
// Author: Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#ifndef ARRAY_H_
#define ARRAY_H_

#include <cstdlib>  // For size_t
#include <cstdint>  // For uint64_t

// A simple array that knows its size. Element type is an arbitrary type T
template<typename T>
class Array {
 private:
  // The elements of the array.
  T* elements_;
  // The number of elements.
  size_t size_;

 public:
  // Create array with given size. All elements will be zero.
  explicit Array(size_t size);

  // Destructor.
  ~Array() {delete[] elements_;}

  // Get the i-th element as a reference
  const T& operator[](int i) const { return elements_[i];}
  T& operator[](int i) { return elements_[i];}

  // Get the size of the array.
  size_t size() const {return size_;}

  // Copy constructor and assignment for the rule of three
  Array(const Array& other) = delete;
  Array& operator=(const Array& other) = delete;
};

// A specialization of Array for bools with bit packing
template<> class Array<bool> {
 private:
  uint64_t* elements_;
  size_t size_;

 public:
  explicit Array(size_t size) {
    size_ = size;
    // For n bits we need n / 64 uint64_ts, but we need to round up!
    elements_ = new uint64_t[(size_ + 63) / 64]{};
  }
  ~Array() {delete[] elements_;}

  size_t size() const {return size_;}

  // Get the i-th bool
  bool get(size_t i) const {
    // The bits 0..63 are in elements_[0]
    // The bits 64..127 are in elements_[1]
    // The bit i is in elements_[i / 64]
    // the division rounds towards zero.
    size_t elementIndex = i / 64;
    // The bit 23 is in elements_[0] at position 23;
    // The bit 64 is in elements_[1] at position 0;
    // The bit 74 is in elements_[1] at position 10;
    // The bit i is in elements_[i / 64] at position i modulo 64
    size_t bitIndex = i % 64;

    uint64_t element = elements_[elementIndex];

    // to extract the i-th bit, shift right by i and set all but the
    // 0-th bit to zero.
    uint64_t result = element >> bitIndex;
    // The bit we are interested in is now at position 0
    // Set all bits but the 0-th to zero
    result = result & uint64_t(1);
    return static_cast<bool>(result);
  }
  // Set the i-th bool to the value
  void set(size_t i, bool value) {
    // Same as in get(), see there for comments.
    size_t elementIndex = i / 64;
    size_t bitIndex = i % 64;
    uint64_t element = elements_[elementIndex];

    // a single 1 at the position of the bit
    uint64_t mask = uint64_t(1) << bitIndex;

    if (value) {
      // store "true"
      element = element | mask;
    } else {
      // store "false"
      element = element & (~mask);
    }
    elements_[elementIndex] = element;
  }
};

// A simple array that knows its size. Element type: int.
class ArrayInt {
 private:
  // The elements of the array.
  int* elements_;
  // The number of elements.
  size_t size_;

 public:
  // Create array with given size. All elements will be zero.
  explicit ArrayInt(size_t size);

  // Destructor.
  ~ArrayInt() {delete[] elements_;}

  // Get the i-th element as a reference
  const int& operator[](int i) const { return elements_[i];}
  int& operator[](int i) { return elements_[i];}

  // Get the size of the array.
  size_t size() const {return size_;}

  // Copy constructor and assignment for the rule of three
  ArrayInt(const ArrayInt& other) = delete;
  ArrayInt& operator=(const ArrayInt& other) = delete;
};

// A simple array that knows its size. Element type: float.
class ArrayFloat {
 private:
  // The elements of the array.
  float* elements_;
  // The number of elements.
  size_t size_;

 public:
  // Create array with given size. All elements will be zero.
  explicit ArrayFloat(size_t size);

  // Destructor.
  ~ArrayFloat() {delete[] elements_;}

  // Get the i-th element as a reference
  const float& operator[](int i) const { return elements_[i];}
  float& operator[](int i) { return elements_[i];}

  // Get the size of the array.
  size_t size() const {return size_;}

  // Copy constructor and assignment for the rule of three
  ArrayFloat(const ArrayFloat& other) = delete;
  ArrayFloat& operator=(const ArrayFloat& other) = delete;
};

#endif  // ARRAY_H_
