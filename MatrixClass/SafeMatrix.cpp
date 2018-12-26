#include <iostream>
#include "SafeMatrix.h"
#include <math.h>

using namespace std;


// Methods
bool  SafeMatrix::invert(){// Invert Matrix
  if(_numRows != _numCols)
    return false;

  this -> append(identity(_numRows));

  for(int i = 0; i < _numRows; i++) {
    if(!_data[i * _numCols + i])
      return false;

    for(int j = _numCols - 1; j >= i; j--)
      _data[i * _numCols + j] /= _data[i * _numCols + i];
    
    for(int j = i + 1; j < _numRows; j++) {
      if(_data[j * _numCols + i]) {
        for(int k = _numCols - 1; k >= i; k--)
          _data[j * _numCols + k] -= (_data[j * _numCols + i] / _data[i * _numCols + i]) * _data[i *_numCols + k];
      }
    }
  }

  for(int i = 0; i < _numCols; i++)
    this -> deleteColumn(i);

  return true;
}                    

SafeMatrix SafeMatrix::solve(const SafeMatrix& A){// Solve MX = A
  if(A._numCols != 1)
    return A;

  this -> invert();
  SafeMatrix r = *this * A;
  this -> invert();
  return r;
}    

bool SafeMatrix::deleteRow(const int rowNumber){
  INVARIANT_TEST(_numRows < -1, "deleteRow");
  if(rowNumber < 0 || rowNumber > _numRows || !_data) {
    return false;
  }
// SafeMatrix delRoe(_numRows-1,_numCols);
// _numRows = _numRows -1;
// _numCols = _numCols;
// for(int i = 0; i < _numRows; i++){
//   if(i == rowNumber){
//     for(int j = 0; j<_numCols; j++){
//       delRoe._data[j] = _data[j+_numCols];
//     }
//   }
//   else{
//     for(int j = 0; j<_numCols; j++){
//       delRoe._data[j] = _data[j];
//     }
//   }
// }
// _dataSpaceAllocated=_numRows*_numCols;

  float tempData[(_numRows - 1) * _numCols];
  for(int i = 0; i < _numRows; i++) {
    if(i != rowNumber)  {
      if(i < rowNumber) {
        for(int j = 0; j < _numCols; j++)
          tempData[i * _numCols + j] = _data[i * _numCols + j]; 
      }
      else if(i > rowNumber)  {
        for(int j = 0; j < _numCols; j++)
          tempData[(i - 1) * _numCols + j] = _data[ i * _numCols + j];
      }
    }
  }

  _numRows--;
  _dataSpaceAllocated = _numRows * _numCols;
  delete[] _data;

  _data = new (std::nothrow) float[_dataSpaceAllocated];

  for(int i = 0; i < _dataSpaceAllocated; i++)  
    _data[i] = tempData[i];

  return true;
}
bool SafeMatrix::deleteColumn(const int columnNumber){
  INVARIANT_TEST(_numRows < -1, "deleteColumn");
  if (columnNumber < 0){
    return false;
  }
  this -> transpose();
  this -> deleteRow(columnNumber);
  this -> transpose();
  return true;
}
bool SafeMatrix::swapRow(const int row1, const int row2){
  INVARIANT_TEST(_numRows < -1, "swapRow");
// SafeMatrix tempRow1(1,_numCols);
// SafeMatrix tempRow2(1,_numCols);
  if(row1 == row2){
    return true;
  }
  if(row1 < 0 || row2 < 0 || !_data){
    return false;
  }

  for(int i = 0; i < _numCols; i++) {
    float temp = _data[row1 * _numCols + i];
    _data[row1 * _numCols + i] = _data[row2 * _numCols + i];
    _data[row2 * _numCols + i] = temp;
  }

// for(int i = 0; i < _numRows; i++){
//   if(i == row1){
//     tempRow1 = (*this).row(i);
//   } 
//   if(i == row2) {
//     tempRow2 = (*this).row(i);
//   }
// }
// int count1 = 0;
// int count2 = 0;

// for (int i = _numCols*row1; i < (_numCols*row1+_numCols); i++){
//   _data[i] = tempRow2._data[count1];
//   count1++;
// }
// for (int i = _numCols*row2; i < (_numCols*row2+_numCols); i++){
//   _data[i] = tempRow1._data[count2];
//   count2++;
// }
// /*for(int i = 0; i < _numRows; i++){
//   for(int j = 0; j < _numCols; j++){
//     if(i == row1){
//       _data[j] = tempRow2._data[j- j*i];
//     }
//     if(i == row2){
//       _data[j] = tempRow1._data[j- j*i];
//     }
//   }
// }*/

  return true;
}

bool SafeMatrix::swapColumn(const int column1, const int column2){
  INVARIANT_TEST(_numRows < -1, "swapColumn");
  if(column1 == column2){
    return true;
  }
  if(column1 < 0 || column2 < 0){
    return false;
  }

  transpose();
  (*this).swapRow(column1, column2);
  transpose();

  return true;
}
bool SafeMatrix::append(const SafeMatrix& m){
  INVARIANT_TEST(_numRows < -1, "append");
  if(m._numCols<=0 || m._numRows <=0){
    return false;
  }
  if(!_data || !m._data){
    return false;
  }

  SafeMatrix mCopy(m._numRows, m._numCols);

  for(int i = 0; i < m._dataSpaceAllocated; i++){
    mCopy._data[i] = m._data[i];
  }

  SafeMatrix mAppend(_numRows, m._numCols+_numCols);
  SafeMatrix mAppend1(m._numRows + _numRows, _numCols);

  if(_numRows == m._numRows){// ATTACH ON RIGHT
    for(int i = 0; i < m._numCols; i++) {
      float tempColumn[m._numRows];
      for(int j = 0; j < m._numRows; j++)
        tempColumn[j] = m._data[j * m._numCols + i];
      this -> appendColumn(_numRows, tempColumn);
    }

    // mCopy.transpose();
    // (*this).transpose();

    // for(int i = 0; i < _dataSpaceAllocated; i++){
    //   mAppend._data[i] = _data[i];
    // }
    
    // for(int i = _numRows*_numCols; i< mAppend._dataSpaceAllocated; i++){
    //   mAppend._data[i] = mCopy._data[i - (_numRows*_numCols)];
    // }
    // _numCols = mAppend._numCols;
    // _numRows = mAppend._numRows;
    // _dataSpaceAllocated = mAppend._dataSpaceAllocated;
    // delete[] _data;
    // _data = new (std::nothrow) float[_dataSpaceAllocated];
    // if(!_data){
    //   return false;
    // }

    // for(int i=0; i < _dataSpaceAllocated; i++){
    //   _data[i] = mAppend._data[i];
    // }
    
    // return true;
  }

  else if(_numCols == m._numCols){ // ATTACH ON BOTTOM 

    for(int i = 0; i < m._numRows; i++) {
      float tempRow[m._numCols];
      for(int j = 0; j < m._numCols; j++)
        tempRow[j] = m._data[i * _numCols + j];
      this -> appendRow(_numCols, tempRow);
    }
    // for(int i = 0; i < _dataSpaceAllocated; i++){
    //   mAppend1._data[i] = _data[i];
    // }
    
    // for(int i = _numRows*_numCols; i< mAppend1._dataSpaceAllocated; i++){
    //   mAppend1._data[i] = mCopy._data[i - (_numRows*_numCols)];
    // }
    // _numCols = mAppend1._numCols;
    // _numRows = mAppend1._numRows;
    // _dataSpaceAllocated = mAppend1._dataSpaceAllocated;
    // delete[] _data;
    // _data = new (std::nothrow) float[_dataSpaceAllocated];
    // if(!_data){
    //   return false;
    // }

    // for(int i=0; i < _dataSpaceAllocated; i++){
    //   _data[i] = mAppend1._data[i];
    //}
  }



  return true;
}

bool SafeMatrix::isNaM() const{ // Is Not-a-Matri
  INVARIANT_TEST(_numRows < -1, "isNAM");
  if(_numRows == NOT_A_MATRIX){
    return true;
  }
  return false;
}                 

SafeMatrix SafeMatrix::row(const int rowNumber) const{
  INVARIANT_TEST(_numRows < -1, "row");
  if(rowNumber<0 || rowNumber > _numRows){
    return SafeMatrix(-1,-1);
  }

  SafeMatrix mRow(1, _numCols);

  for(int i = 0; i < _numCols; i++){
    mRow._data[i] = _data[rowNumber*_numCols+i];
  } 

  return mRow;
}
SafeMatrix SafeMatrix::column(const int columnNumber) const{
  INVARIANT_TEST(_numRows < -1, "column");
  if(columnNumber<0){
    return SafeMatrix(-1,-1);
  }

  SafeMatrix mTran(*this);
  SafeMatrix jk(_numRows,1);
  mTran.transpose();
  jk = mTran.row(columnNumber);
//jk.transpose();
  return jk;

/*SafeMatrix mCol (_numRows,1);
for(int i = 0; i< mCol._dataSpaceAllocated; i++){
  mCol._data[i] = mTran._data[i];
}
return mCol;*/
}

void SafeMatrix::transpose() {
  INVARIANT_TEST(_numRows < -1, "transpose");

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

  for(int i=0; i< _dataSpaceAllocated; ++i){
    _data[i] = m._data[i];
  }
  int temp = _numRows;
  _numRows = _numCols;
  _numCols = temp;
}

bool SafeMatrix::appendRow(const int cols, const float data[]) {
  INVARIANT_TEST(_numRows < -1, "appendRow");
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
  INVARIANT_TEST(_numRows < -1, "appendColumn");
  if(rows != _numRows || !data){
    return false;
  }
  transpose();
  appendRow(rows, data);
  transpose();

  return true;
}


Dimensions SafeMatrix::dimensions() const {
  INVARIANT_TEST(_numRows < -1, "dimensions");
  Dimensions Dim; //NOT EQUAL TO ZERO
  Dim.rows =_numRows;
  Dim.cols = _numCols;
  return Dim;
}

SafeMatrix SafeMatrix::identity(const int n){
  if(n<=0){
    return SafeMatrix(-1,-1);
  }
  int rowCount = 1;
  int colCount = 1;
  SafeMatrix mIdentity(n,n);
  for(int i = 0; i < n*n; i++){
    if(rowCount == colCount){
      mIdentity._data[i] = 1;
    } 
    else {
      mIdentity._data[i] = 0;
    }

    if (colCount == n){
      colCount = 1;
      rowCount++;
    }
    else{
      colCount++;
    }
  }
  return mIdentity;
}

// Operators
float& SafeMatrix::operator()(int i, int j) {
  INVARIANT_TEST(_numRows < -1, "operator()");
  if (i>_numRows || j > _numCols || i < 0 || j < 0){
    return _nan;
  }
  return _data[(i)*_numCols + (j)];
}  

SafeMatrix SafeMatrix::operator+(const SafeMatrix& m) const {
  INVARIANT_TEST(_numRows < -1, "operator+");
  if(_numCols != m._numCols || _numRows != m._numRows || _dataSpaceAllocated != m._dataSpaceAllocated){
    return SafeMatrix(-1,-1);
  }  
  SafeMatrix mAdd(m._numRows, m._numCols);
  for(int i = 0; i<_dataSpaceAllocated; i++){
    mAdd._data[i]= m._data[i]+_data[i];
  }
  return mAdd;
}
SafeMatrix SafeMatrix::operator- (const SafeMatrix& m) const{
  INVARIANT_TEST(_numRows < -1, "operator-");
  if(_numCols != m._numCols || _numRows != m._numRows || _dataSpaceAllocated != m._dataSpaceAllocated){
    return SafeMatrix(-1,-1);
  }  
  SafeMatrix mSub(m._numRows, m._numCols);
  for(int i = 0; i<_dataSpaceAllocated; i++){
    mSub._data[i]= _data[i] - m._data[i];
  }
  return mSub;
}

SafeMatrix SafeMatrix::operator*(const SafeMatrix& m) const {
  INVARIANT_TEST(_numRows < -1, "operator*");
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
  INVARIANT_TEST(_numRows < -1, "operator=");
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
bool SafeMatrix::operator==(const SafeMatrix& m) const {
  INVARIANT_TEST(_numRows < -1, "operator==");
  if (m._numRows < 0 || _numRows < 0){
    return false;
  } 
  if(_dataSpaceAllocated != m._dataSpaceAllocated){
    return false;
  }
  else{
    for(int i=0; i< _dataSpaceAllocated; ++i){
      if(fabs(_data[i]-m._data[i])>pow(10,-5)){
        return false;
      }
    }
  }

  return true;

}
bool SafeMatrix::operator!=(const SafeMatrix& m) const{
  INVARIANT_TEST(_numRows < -1, "operator!=");
  if (m._numRows < 0 || _numRows < 0){
    return false;
  } 
  if(_dataSpaceAllocated != m._dataSpaceAllocated){
    return true;
  }
  else{
    for(int i=0; i< _dataSpaceAllocated; ++i){
      if(fabs(_data[i] - m._data[i])>pow(10,-5)){
        return true;
      }
    }
  }
  return false;
}
// Constructors/Destructor
SafeMatrix::SafeMatrix() {
  _numRows = 1;
  _numCols = 1;
  _dataSpaceAllocated = 1;
  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data){
    return;
  }
    _data[0] = 0;

};

SafeMatrix::SafeMatrix(const SafeMatrix& m) {
  if(m._numRows < 0 || m._numCols < 0){
    _numRows = NOT_A_MATRIX;
    return;
  }
  if(m._numRows == 0|| m._numCols == 0){
    _numRows= m._numRows;
    _numCols = m._numCols;
    _dataSpaceAllocated = 0;
    _data = 0;
    return;
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
  
  if(cols == 0 && rows ==0){
    _numRows = 1;
    _numCols = 1;
    _dataSpaceAllocated = 1;
    _data = new (std::nothrow) float[_dataSpaceAllocated];
    if(!_data){
      return;
    }
    _data[0] = 0;
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
    _numRows= rows;
    _numCols = cols;
    _dataSpaceAllocated = 0;
    _data = 0;
    return;;
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
SafeMatrix::SafeMatrix(const Dimensions& d){
  if(d.rows < 0 || d.cols < 0){
    _numRows = NOT_A_MATRIX;
    return;
  }
  if(d.rows == 0|| d.cols == 0){
    _numRows= d.rows;
    _numCols = d.cols;
    _dataSpaceAllocated = 0;
    _data = 0;
    return;
  }

  _numRows = d.rows;
  _numCols = d.cols;
  _dataSpaceAllocated = _numRows*_numCols;
  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data){
    return;
  }
  for (int i = 0; i< _dataSpaceAllocated; i++){
    _data[i] = 0;
  }
}                                  // Uninitialized matrix                        // Uninitialized matrix
SafeMatrix::SafeMatrix(const Dimensions& d, const float initVal){
  if(d.rows < 0 || d.cols < 0){
    _numRows = NOT_A_MATRIX;
    return;
  }
  if(d.rows == 0|| d.cols == 0){
    _numRows= d.rows;
    _numCols = d.cols;
    _dataSpaceAllocated = 0;
    _data = 0;
    return;
  }

  _numRows = d.rows;
  _numCols = d.cols;
  _dataSpaceAllocated = _numRows*_numCols;
  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data){
    return;
  }
  for (int i = 0; i< _dataSpaceAllocated; i++){
    _data[i] = initVal;
  }
} 
SafeMatrix::SafeMatrix(const int rows, const float data[]){ //A VECTOR
  if(rows < 0){
    _numRows = NOT_A_MATRIX;
    return;
  }

  _numCols = 1;
  _numRows = rows;
  _dataSpaceAllocated = _numRows*_numCols;
  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data){
    return;
  }
  for (int i = 0; i< _dataSpaceAllocated; i++){
    _data[i] = data[i];
  }

}

SafeMatrix::~SafeMatrix() {
  if(_numRows == NOT_A_MATRIX){
    _numRows = 0;
    _numCols = 0;
    _dataSpaceAllocated = _numRows*_numCols;
    return;
  }
  _numRows = MATRIX_DELETED;
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

/*#ifndef MARMOSET_TESTING

int main() {
  SafeMatrix m(3,4,1.2);
  
  SafeMatrix m5();
  float data6[]={1.1,2.2,3.3};

  m5.appendRow(3,data6);
  cout << m5 <<" HEIS" << endl;
  SafeMatrix m2(4,4,8);
  float bData[] = {1,2,3,4};
  SafeMatrix b(4, bData);
  
  cout << m.appendRow(4,bData) << "what happened man" << endl;
  cout << m << "LKm" <<  endl;
  SafeMatrix i = m.identity(4);

  cout << i.invert() << "\n";
  cout << i << "\n\n";
  cout << i.solve(b);



  cout <<  m2.invert();

  cout << m2 << "\n\n";


  // m2.append(m);

  // m2 (0,1) = 0;
  // m2 (2,1) = 0;

  // m2.deleteRow(1);


  // cout << m2 << "LMAKS O\n\n" << endl;

  // m2.deleteColumn(0);

  // cout << m2 << "\n\n\n";

  // m2.swapColumn(0,1);

  // cout << m2 << "\n\n\n";



  //SafeMatrix h = m3;
  //cout << m << "jk" << endl;
  //cout << h << " HI " << endl;
  //cout << h._numCols << "and" << h._numRows << endl; THIS IS PRIVATE INFO DONT TOUCH

  //cout << "Matrix m:\n" << m << endl;
  //cout << "Matrix m1:\n" << m1 << endl;
  //m.appendRow(4, data);
  //cout << "Matrix m:\n" << m << endl;
  
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

  cout << "data1:\n" << data1 << endl;
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
  


  return 0;
}

#endif*/