#include <iostream>
#include "SafeMatrix.h"

// Methods
void SafeMatrix::transpose() {
  SafeMatrix m = SafeMatrix(_numRows,_numCols);
  SafeMatrix m1 = SafeMatrix(_numRows,_numCols);
  
  for (int i = 0; i < _numCols; i++){
      for (int j = 0; j < _numRows; j++){
        m(i,j) = m1(j,i);
    }
  }
  int temp = _numRows;
  _numRows = _numCols;
  _numCols = temp;
  for(int i=0; i< _dataSpaceAllocated; ++i){
    _data[i] = m._data[i];
  }
}
bool SafeMatrix::appendRow(const int cols, const float data[]) {
  if(cols != _numCols){
    return false;
  }
  SafeMatrix m = SafeMatrix(_numRows, cols);
  for(int i = 0; i < m._dataSpaceAllocated; i++){
    m._data[i] = _data[i];
  }
  int i = _dataSpaceAllocated;
  int j = 0;
  while (i < m._dataSpaceAllocated && j < cols){
    m._data[i] = data[j];
    i++;
    j++;
  }
  return true;
}

bool SafeMatrix::appendColumn(const int rows, const float data[]) {
  //SafeMatrix m = SafeMatrix(rows, _numCols);


}


Dimensions SafeMatrix::dimensions() const {
  Dimensions Dim; //NOT EQUAL TO ZERO
  Dim.rows =_numRows;
  Dim.cols = _numCols;
  return Dim;
}

// Operators
float& SafeMatrix::operator()(int i, int j) {
 int loc = 0;

 for(int m = 0; m<i; m++){
  for(int n = 0; n< j; n++){
    loc++;
  }
 }
 return _data[loc];
}  

SafeMatrix SafeMatrix::operator+(const SafeMatrix& m) const {
  if(m._numCols != _numCols && m._numRows != _numRows){
    return SafeMatrix();
  }
  int cols = m._numCols;
  int row = m._numRows;
  float data[m._dataSpaceAllocated];
  for(int i = 0; i<_dataSpaceAllocated; i++){
    data[i]= m._data[i]+_data[i];
  }

}

SafeMatrix SafeMatrix::operator*(const SafeMatrix& m) const {
  if(m._numCols != _numCols && m._numRows != _numRows){
    return SafeMatrix();
  }

}

void SafeMatrix::operator=(const SafeMatrix& m) {

  _dataSpaceAllocated = m._dataSpaceAllocated;
  delete[] _data;
  
  _data = new float[_dataSpaceAllocated];

  for(int i=0; i< _dataSpaceAllocated; ++i){
    _data[i] = m._data[i];
  }
}

  // Constructors/Destructor
SafeMatrix::SafeMatrix() {
  _numRows = -1;
  _numCols = -1;
  _dataSpaceAllocated = 0;
  _data = new float[_dataSpaceAllocated];
};

SafeMatrix::SafeMatrix(const SafeMatrix& m) {
  _numRows = m._numRows;
  _numCols = m._numCols;
  _dataSpaceAllocated = m._numRows*m._numCols;
}

SafeMatrix::SafeMatrix(const int rows, const int cols) {
   _numRows = rows;
   _numCols = cols;
   _dataSpaceAllocated = rows*cols;
   _data = new float[_dataSpaceAllocated];
   for (int i = 0; i<= _numRows*_numCols; i++){
    _data[i] = 0;
  }

}

SafeMatrix::SafeMatrix(const int rows, const int cols, const float initVal) {
  _numRows = rows;
  _numCols = cols;
  _dataSpaceAllocated = rows*cols;
  _data = new float[_dataSpaceAllocated];
   for (int i = 0; i<= _dataSpaceAllocated; i++){
    _data[i] = initVal;
  }
}

SafeMatrix::~SafeMatrix() {
  _numRows = 0;
  _numCols = 0;
  _dataSpaceAllocated = _numRows*_numCols;
  for (int i = 0; i<= _dataSpaceAllocated; i++){
    _data[i] = 0;
  }
  delete[] _data;
}

std::ostream& operator<<(std::ostream& os, const SafeMatrix& m) {
  INVARIANT_TEST(m._numRows < NOT_A_MATRIX, "ostream::operator<<()");
  if (m._numRows < NOT_A_MATRIX) {
    m.errorMsg("Method ostream::operator<<: attempting to output deleted SafeMatrix");
    abort();
  }
  if (m._numRows == NOT_A_MATRIX) {
    os << "Not-a-Matrix";
    return os;
  }
  if (m._numRows == 0)
    os << "[]";
  for (int i = 0; i < m._numRows; ++i) {
    os << "[";
    for (int j = 0; j < m._numCols; ++j) {
      os << MATRIX(m,i,j);
      if (j < (m._numCols - 1))
        os << ", ";
    }
    os << "]";
    if (i < (m._numRows - 1))
      os << std::endl;
  }
  return os;
}

void SafeMatrix::errorMsg(const char msg[]) const {
  std::cerr << msg << std::endl;
}
