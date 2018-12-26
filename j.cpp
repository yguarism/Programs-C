
#include <iostream>
#include "SafeMatrix.h"

using namespace std;
// Methods
void SafeMatrix::transpose() {
    if (_dataSpaceAllocated < 1 || !_data) {
        return;
    }
    int row = _numCols;
    int col = _numRows;

    float * T = new(std::nothrow) float[_dataSpaceAllocated];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            T[j * _numCols + i] = operator()(i, j);
        }
    }
    _numRows = row;
    _numCols = col;
    _dataSpaceAllocated = row * col;
    for (int i = 0; i < _dataSpaceAllocated; i++) {
        _data[i] = T[i];
    }
}

bool SafeMatrix::appendRow(const int cols,
    const float data[]) {
    if (cols != _numCols || _dataSpaceAllocated < 1 || !_data) {
        return false;
    }

    int i = 0; //index
    SafeMatrix matrix(_numRows + 1, cols);

    for (i = 0; i < _dataSpaceAllocated; i++) { //elements from the original
        matrix._data[i] = _data[i];     
    }
    for (i = 0; i < cols; i++) { //adding the new ones
        matrix._data[i + _dataSpaceAllocated] = data[i];
    }

    _numCols = matrix._numCols;
    _numRows = matrix._numRows;
    _dataSpaceAllocated = matrix._dataSpaceAllocated;
    delete[] _data;
    _data = new(std::nothrow) float[_dataSpaceAllocated];
    if(!_data){
        return false;
    }
    for (i = 0; i < _dataSpaceAllocated; i++) {
        _data[i] = matrix._data[i];
    }
    
    return true;
}

bool SafeMatrix::appendColumn(const int rows,
    const float data[]) {
    if (rows != _numRows || _dataSpaceAllocated < 1 || !_data) {
        return false;
    }

    transpose();
    appendRow(rows, data);
    transpose();
    
    return true;
}

Dimensions SafeMatrix::dimensions() const {
    Dimensions d;
    d.rows = _numRows;
    d.cols = _numCols;
    return d;
}

// Operators
float & SafeMatrix::operator()(int i, int j) {
    if (i < 0 || j < 0 || _data == NULL) { //when it is invalid
        return _nan;
    }
    int index = i * _numCols + j;

    return _data[index];
}

SafeMatrix SafeMatrix::operator+(const SafeMatrix & m) const {
    if (_numCols != m._numCols || _numRows != m._numRows||!_data || !m._data) { //whent they are not the same size
        return SafeMatrix(-1,-1);
    }

    SafeMatrix matrix(_numRows, _numCols, 0.0);

    for (int i = 0; i < _dataSpaceAllocated; i++) {
        matrix._data[i] = _data[i] + m._data[i];
    }

    return matrix;
}

SafeMatrix SafeMatrix::operator*(const SafeMatrix & m) const {
    if(_numCols!=m._numRows||!_data || !m._data){
        return SafeMatrix(-1,-1);      
    }
    
    SafeMatrix matrix(_numRows, m._numCols);
    
    for (int i = 0; i < _numRows; i++) {
        for (int j = 0; j < m._numCols; j++) {
            for (int k = 0; k < _numCols; k++)
                matrix._data[i * matrix._numCols + j] += _data[i * _numRows + k] * m._data[k * m._numCols + j];
        }
    }
    
    return matrix;
}

void SafeMatrix::operator = (const SafeMatrix & m) {
    _numRows = m._numRows;
    _numCols = m._numCols;
    _dataSpaceAllocated = m._dataSpaceAllocated;

    if(m._numRows<0|| m._numCols<0){
        SafeMatrix(-1,-1);
        return; 
    }
    if(_data != 0)
        delete[] _data;

    _data = new (std::nothrow) float[_dataSpaceAllocated];
    if(!_data){
        return;
    }

    for(int i = 0; i < _dataSpaceAllocated; i++){
        _data[i] = m._data[i];
    }
}

// Constructors/Destructor
SafeMatrix::SafeMatrix() {
    _numRows = 0;
    _numCols = 0;
    _dataSpaceAllocated = 0;
    _data = 0;
}

SafeMatrix::SafeMatrix(const SafeMatrix & m) {
    if(m._numCols<0||m._numRows<0){
        _numRows = NOT_A_MATRIX;
        return;
    }
    if(m._numCols == 0||m._numRows == 0){
        SafeMatrix();
    }
    _numCols = m._numCols;
    _numRows = m._numRows;
    _dataSpaceAllocated = _numCols * _numRows;
    _data = new(std::nothrow) float[_dataSpaceAllocated];
    
    if(!_data||!m._data){
        return;      
    }
    for (int i = 0; i < _dataSpaceAllocated; i++) {
        _data[i] = m._data[i];
    }

}

SafeMatrix::SafeMatrix(const int rows,
    const int cols) {

    if(rows<0||cols<0){
        _numRows = NOT_A_MATRIX;
        return;
    }
    if(rows==0||cols==0){
        SafeMatrix();
    }
    _numCols = cols;
    _numRows = rows;
    _dataSpaceAllocated = _numCols * _numRows;

    _data = new(std::nothrow) float[_dataSpaceAllocated];
    if(!_data){
        return;
    }
    for (int i = 0; i < _dataSpaceAllocated; i++) {
        _data[i] = 0;
    }
    return;
}

SafeMatrix::SafeMatrix(const int rows,
    const int cols,
        const float initVal) {
    
    if(rows<0||cols<0){
        _numRows = NOT_A_MATRIX;
        return;
    }
    if(rows==0||cols==0){
        SafeMatrix();
    }
    _numCols = cols;
    _numRows = rows;
    _dataSpaceAllocated = _numCols * _numRows;

    _data = new(std::nothrow) float[_dataSpaceAllocated];
    if(!_data){
        return;
    }
    for (int i = 0; i < _dataSpaceAllocated; i++) {
        _data[i] = initVal;
    }
}

SafeMatrix::~SafeMatrix() {
    if(_numRows == NOT_A_MATRIX){
        _numCols = 0;
        _numRows = 0;
        _dataSpaceAllocated = _numCols*_numRows;
        return;
    }
    _numCols = 0;
    _numRows = 0;
    _dataSpaceAllocated = _numCols*_numRows;
    if(_data!=0){
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
  SafeMatrix m2(5,5,8);
  SafeMatrix h = m+m2;
  float data[] = {1,2,3,4,5};
  cout << m+m2 << " HI " << endl;


 

  //float data1[] = {1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1}*/

  //cout << "Matrix m:\n" << m << endl;
  //cout << "Matrix m1:\n" << m1 << endl;
  /*m.appendRow(4, data);
  cout << "Matrix m:\n" << m << endl;
  
  SafeMatrix data1;
  SafeMatrix data2(1,1);
  data2.appendRow(1,data);
  data2.appendRow(1,data+1);
  data2.appendRow(1,data+2);
  data2.appendRow(1,data+3);
  SafeMatrix data3(5,4,1.3);
  SafeMatrix data4;
  data4 = data3;
  data4.appendRow(5,data);

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