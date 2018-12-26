////////////////////////////////////////////////////////////////////////////////
//
// SafeArray.cpp
// Implements class SafeArray
// This is an array that
// (a) Does array-bounds checking
// (b) Does deleted-array checking
//
// Change History:
// 21 Nov 2018: Initial Code Created; PASW
//

#include "invariant.h"
#include "SafeArray.h"

float& SafeArray::operator()(const int i) {
  INVARIANT_TEST(_size < -1, "operator()");
  RESET_NAN;
  if (i < 0 || i > _size-1) {
    errorMsg("Method operator(): Out of bounds access error");
    return _nan;
  }
  return _data[i];
}

void SafeArray::operator=(const SafeArray& a) {
  INVARIANT_TEST(_size < -1, "operator=");
  INVARIANT_TEST(a._size < -1, "operator=(a)");
  RESET_NAN;
  if (_data)
    delete[] _data;
  _data = 0;
  _size = a._size;
  if (_size > 0) {
    _data = new (std::nothrow) float[_size];
    if (!_data) {
      _size = NOT_AN_ARRAY;
      errorMsg("Method operator=: out of memory");
    }
  }
  for (int i = 0; i < _size; ++i)
    _data[i] = a._data[i];
}

SafeArray::SafeArray() {
  _size = 0;
  _data = 0;
}

SafeArray::SafeArray(const SafeArray& a) {
  *this = a;
}

SafeArray::SafeArray(const int size) {
  if (size < 0) {
    _size = NOT_AN_ARRAY;
    _data = 0;
    return;
  }
  _size = size;
  if (_size == 0) {
    _data = 0;
    return;
  }
  _data = new (std::nothrow) float[_size];
  if (!_data)                                 // Failed to allocate space
    _size = NOT_AN_ARRAY;
  return;
}

SafeArray::SafeArray(const int size, const float initVal) {
  if (size < 0) {
    _size = NOT_AN_ARRAY;
    _data = 0;
    return;
  }
  _size = size;
  if (_size == 0) {
    _data = 0;
    return;
  }
  _data = new (std::nothrow) float[_size];
  if (!_data)                                 // Failed to allocate space
    _size = NOT_AN_ARRAY;
  for (int i = 0; i < _size; ++i)
    _data[i] = initVal;
  return;
}

SafeArray::SafeArray(const int size, const float data[]) {
  if (size < 0) {
    _size = NOT_AN_ARRAY;
    _data = 0;
    return;
  }
  _size = size;
  if (_size == 0) {
    _data = 0;
    return;
  }
  _data = new (std::nothrow) float[_size];
  if (!_data)                                 // Failed to allocate space
    _size = NOT_AN_ARRAY;
  for (int i = 0; i < _size; ++i)
    _data[i] = data[i];
  return;
}

SafeArray::~SafeArray() {
  _size = -2;           // Unset the invariant
  if (_data)
    delete[] _data;
  _data = 0;
}

// Private Methods
 
std::ostream& operator<<(std::ostream& os, SafeArray& a) {
  if (a._size < NOT_AN_ARRAY) {
    a.errorMsg("Method ostream::operator<<: attempting to output deleted SafeArray");
    abort();
  }
  if (a._size == NOT_AN_ARRAY) {
    os << "Not-an-Array";
    return os;
  }
  os << "[";
  for (int i = 0; i < a._size; ++i) {
    os << a(i);
    if (i < (a._size - 1))
      os << ", ";
  }
  os << "]";
  return os;
}

void SafeArray::errorMsg(const char msg[]) const {
  std::cerr << msg << std::endl;
}
