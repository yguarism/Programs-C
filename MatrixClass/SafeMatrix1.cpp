#include <iostream>
#include "SafeMatrix.h"

using namespace std;


// Methods
void SafeMatrix::transpose() {
  if(_numCols<= 0|| _numRows <=0 || !_data){
    return;
  }
  SafeMatrix m = SafeMatrix(_numCols, _numRows);
  SafeMatrix m1 = SafeMatrix(*this);

  for(int i=0; i< _dataSpaceAllocated; ++i){
    m._data[i] = m1._data[i];
  }

  
  for (int i = 0; i < _numCols; i++){
    for (int j = 0; j < _numRows; j++){
      float temp = m1(j,i);
      m1(j,i) = m(i,j);
      m(i,j) = temp;
    }
  }
  /*SafeMatrix n = SafeMatrix(_numCols, _numRows);
  for(int i=0; i< _dataSpaceAllocated; ++i){
    n._data[i] = m._data[i];
  }
  for(int i=0; i< _dataSpaceAllocated; ++i){
    _data[i] = n._data[i];
  }*/
  for(int i=0; i< _dataSpaceAllocated; ++i){
    _data[i] = m._data[i];
  }
  int temp = _numRows;
  _numRows = _numCols;
  _numCols = temp;
}
bool SafeMatrix::appendRow(const int cols, const float data[]) {
  if(cols<=0){
    return false;
  }
  if(cols != _numCols || !_data || !data){
    return false;
  }
  SafeMatrix m(_numRows + 1, cols);
  
  for(int i = 0; i < _dataSpaceAllocated; i++){
    m._data[i] = _data[i];
  }
  int i = 0;

  while (i < _numCols){
    m._data[i+_dataSpaceAllocated] = data[i];
    i++;
  }
  _numCols = m._numCols;
  _numRows = m._numRows;
  _dataSpaceAllocated = m._dataSpaceAllocated;
  delete[] _data;
  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data){
    return false;
  }
  
  for(int i=0; i < m._dataSpaceAllocated; i++){
    _data[i] = m._data[i];
  }

  return true;
}

bool SafeMatrix::appendColumn(const int rows, const float data[]) {
  if(rows != _numRows || !data){
    return false;
  }
  transpose();
  appendRow(rows, data);
  transpose();
 
  return true;
}


Dimensions SafeMatrix::dimensions() const {
  Dimensions Dim; //NOT EQUAL TO ZERO
  Dim.rows =_numRows;
  Dim.cols = _numCols;
  return Dim;
}

// Operators
float& SafeMatrix::operator()(int i, int j) {
  if (i>_numRows || j > _numCols || i < 0 || j < 0){
    return _nan;
  }
 /*int loc = 0;

 for(int m = 0; m<i; m++){
  for(int n = 0; n< j; n++){
    loc++;
  }
 }*/
  return _data[(i)*_numCols + (j)];
}  

SafeMatrix SafeMatrix::operator+(const SafeMatrix& m) const {
  if(_numCols != m._numCols || _numRows != m._numRows || _dataSpaceAllocated != m._dataSpaceAllocated){
    return SafeMatrix(-1,-1);
  }  
  SafeMatrix mAdd(m._numRows, m._numCols);
  for(int i = 0; i<_dataSpaceAllocated; i++){
    mAdd._data[i]= m._data[i]+_data[i];
  }
  return mAdd;
}

SafeMatrix SafeMatrix::operator*(const SafeMatrix& m) const {
  if(_numCols != m._numRows){
    return SafeMatrix(-1,-1);
  }
  if(!_data || !m._data){
    return SafeMatrix(-1,-1);
  }
  else{
    SafeMatrix _copied(_numRows,_numCols);
    SafeMatrix m_copied(m._numRows, m._numCols);
    SafeMatrix mC(_numRows, m._numCols);
    for(int i = 0; i < _dataSpaceAllocated; i++){
      _copied._data[i] =_data[i];
    }

    for(int i = 0; i < m._dataSpaceAllocated; i++){
      m_copied._data[i] = m._data[i];
    }

    for (int i = 0; i < _numRows; i++) {
      for (int j = 0; j < m._numCols; j++) {
        float sum = 0.0;
        for (int k = 0; k < _numCols; k++){
          sum += _copied(i,k)*m_copied(k,j);
        }
        mC(i,j) = sum;
      }
    }
    return mC;  
  }
}

void SafeMatrix::operator=(const SafeMatrix& m) {
  if(m._numRows < 0 || m._numCols < 0){
    SafeMatrix(-1,-1);
    return;
  }
  _dataSpaceAllocated = m._dataSpaceAllocated;

  if(_data != 0)
    delete[] _data;
  
  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data){
    return;
  }


  for(int i=0; i < _dataSpaceAllocated; i++){
    _data[i] = m._data[i];
  }
}

  // Constructors/Destructor
SafeMatrix::SafeMatrix() {
  _numRows = 0;
  _numCols = 0;
  _dataSpaceAllocated = 0;
  _data = 0;

};

SafeMatrix::SafeMatrix(const SafeMatrix& m) {
  if(m._numRows < 0 || m._numCols < 0){
    _numRows = NOT_A_MATRIX;
    return;
  }
  if(m._numRows == 0|| m._numCols == 0){
    SafeMatrix();
  }
  _numRows = m._numRows;
  _numCols = m._numCols;

  _dataSpaceAllocated = m._dataSpaceAllocated;
  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data || !m._data){
    return;
  }

  for (int i = 0; i< _dataSpaceAllocated; i++){
    _data[i] = m._data[i];
  }
}

SafeMatrix::SafeMatrix(const int rows, const int cols) {
  if(rows < 0 || cols < 0){
    _numRows = NOT_A_MATRIX;
    return;
  }
  if(rows == 0|| cols == 0){
    SafeMatrix();
  }
  _numRows = rows;
  _numCols = cols;
  _dataSpaceAllocated = _numRows*_numCols;

  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data){
    return;
  }

  for (int i = 0; i< _dataSpaceAllocated; i++){
    _data[i] = 0;
  }

  return;
}

SafeMatrix::SafeMatrix(const int rows, const int cols, const float initVal) {
  if(rows < 0 || cols < 0){
    _numRows = NOT_A_MATRIX;
    return;
  }
  if(rows == 0|| cols == 0){
    SafeMatrix();
  }
  _numRows = rows;
  _numCols = cols;
  _dataSpaceAllocated = _numRows*_numCols;
  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data){
    return;
  }
  for (int i = 0; i< _dataSpaceAllocated; i++){
    _data[i] = initVal;
  }
}

SafeMatrix::~SafeMatrix() {
  if(_numRows == NOT_A_MATRIX){
    _numRows = 0;
    _numCols = 0;
    _dataSpaceAllocated = _numRows*_numCols;
    return;
  }
  _numRows = 0;
  _numCols = 0;
  _dataSpaceAllocated = _numRows*_numCols;
  if(_data != 0){
    delete[] _data;
  }
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

#ifndef MARMOSET_TESTING

int main() {
  SafeMatrix m(4,4,1.2);
  m.transpose();
  SafeMatrix m2(3,3,8);
  SafeMatrix h = m+m2;
  float data[] = {1,2,3,4,5};
  cout << m+m2 << " HI " << endl;
  cout << h._numCols << "and" << h._numRows << endl;

 

  //float data1[] = {1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1}

  /*cout << "Matrix m:\n" << m << endl;
  //cout << "Matrix m1:\n" << m1 << endl;
  m.appendRow(4, data);
  cout << "Matrix m:\n" << m << endl;
  */
  /*SafeMatrix data1;
  SafeMatrix data2(1,1);
  data2.appendRow(1,data);
  data2.appendRow(1,data+1);
  data2.appendRow(1,data+2);
  data2.appendRow(1,data+3);
  SafeMatrix data3(5,4,1.3);
  SafeMatrix data4;
  data4 = data3;
  data4.appendRow(5,data);*/

  /*cout << "data1:\n" << data1 << endl;
  cout << "data2:\n" << data2 << endl;
  cout << "data3:\n" << data3 << endl;
  cout << "data4:\n" << data4 << endl;

  SafeMatrix data5(data3);
  cout << "data5:\n" << data5 << endl;
  data5(2,3) = 4.6;
  cout << "data5:\n" << data5 << endl;
  data5(6,2) = 7.2;
  cout << "data5:\n" << data5 << endl;
  float x = data5(2,2);
  cout << "x: " << x << endl;
  x = data5(6,2);
  cout << "x: " << x << endl;
  */


  return 0;
}

#endif