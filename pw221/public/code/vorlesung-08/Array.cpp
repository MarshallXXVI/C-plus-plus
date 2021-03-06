// Copyright 2022, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Author: Hannah Bast <bast@cs.uni-freiburg.de>.
// Author: Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#include "./Array.h"
#include <iostream>

template<typename T>
Array<T>::Array(size_t size) {
  size_ = size;
  elements_ = new T[size_]{};
}

template class Array<int>;
template class Array<float>;
// _________________________________________________
ArrayInt::ArrayInt(size_t size) {
  size_ = size;
  elements_ = new int[size_]{};
}

// _________________________________________________
ArrayFloat::ArrayFloat(size_t size) {
  size_ = size;
  elements_ = new float[size_]{};
}
// A very simple class for testing
class Dummy {
 private:
  int value_;

 public:
  explicit Dummy(int value) {value_ = value;}
};

// ________________________________
void doNothingButWrong() {
  // Error because Dummy has no default constructor.
  Array<Dummy> dummyArray(25);

  Dummy dummy(34);

  // Does not work, no operator<< for ostream (type of cout) and Dummy
  // std::cout << dummy;
}
