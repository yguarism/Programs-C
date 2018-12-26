//SafeMatrix.cpp

#include <iostream>
#include <math.h>
#include "SafeMatrix.h"
using namespace std;

// Methods
void SafeMatrix::transpose() {
	SafeMatrix copyMatrix(_numCols, _numRows);
	
	for (int i = 0; i < _numCols; i++) {
		for (int j = 0; j < _numRows; j++) {
			copyMatrix(i, j) = (*this)(j, i);
		}
	}
	
	int temp = _numRows;
	_numRows = _numCols;
	_numCols = temp;
	_dataSpaceAllocated = _numRows * _numCols;
	
	for (int i = 0; i < _dataSpaceAllocated; i++) {
		_data[i] = copyMatrix._data[i];
	}
}

bool SafeMatrix::appendRow(const int cols, const float data[]) {
	if (_data == 0 || cols != _numCols || cols < 0 || data == 0) {
		return false;
	}
	
	/*
	if (_data == 0) {
		_numRows = 1;
		_numCols = cols;
		_dataSpaceAllocated = cols;
		
		_data = new (std::nothrow) float[_dataSpaceAllocated];
		
		for (int i = 0; i < _dataSpaceAllocated; i++) {
			_data[i] = data[i];
		}
		
		return true;
	} else {*/
	SafeMatrix newMatrix(_numRows + 1, cols);
	int j = 0;
	
	for (int i = 0; i < newMatrix._dataSpaceAllocated; i++) {
		if (i < _dataSpaceAllocated) {
			newMatrix._data[i] = _data[i];
		} else {
			newMatrix._data[i] = data[j];
			j++;
		}
	}
	
	_numRows = newMatrix._numRows;
	_numCols = newMatrix._numCols;
	_dataSpaceAllocated = newMatrix._dataSpaceAllocated;
	
	delete[] _data;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	
	if (_data == 0) {
		return false;
	}
	
	for (int i = 0; i < _dataSpaceAllocated; i++) {
		_data[i] = newMatrix._data[i];
	}
	
	return true;
}

bool SafeMatrix::appendColumn(const int rows, const float data[]) {
	if (_data == 0 || rows != _numRows || rows < 0 || data == 0) {
		return false;
	}
	
	_numCols = _numCols + 1;
	transpose();
	appendRow(rows, data);
	transpose();
	
	return true;
	
	/*
	if (_data == 0) {
		_numRows = rows;
		_numCols = 1;
		_dataSpaceAllocated = rows;
		
		_data = new (std::nothrow) float[_dataSpaceAllocated];
		
		for (int i = 0; i < _dataSpaceAllocated; i++) {
			_data[i] = data[i];
		}
		
		return true;
	} else {
		SafeMatrix newMatrix(rows, _numCols + 1);
		int k = 0;

		for (int i = 0; i < _numRows; i++) {
			for (int j = 0; j < newMatrix._numCols; j++) {
				if (j == _numCols) {
					newMatrix(i, j) = data[k];
					k++;
				} else {
					newMatrix(i, j) = (*this)(i, j);
				}
			}
		}
		
		_numCols = newMatrix._numCols;
		_dataSpaceAllocated = newMatrix._dataSpaceAllocated;
		
		delete[] _data;
		_data = new (std::nothrow) float[_dataSpaceAllocated];
		
		for (int i = 0; i < _dataSpaceAllocated; i++) {
			_data[i] = newMatrix._data[i];
		}
		
		return true;
	}*/
}

Dimensions SafeMatrix::dimensions() const {
	Dimensions newDim;
	newDim.rows = _numRows;
	newDim.cols = _numCols;
	
	return newDim;
}

// Operators
float& SafeMatrix::operator()(int i, int j) {
	if (i > _numRows || j > _numCols || i < 0 || j < 0) {
		return _nan;
	}
	
	int location = 0;
	
	for (int m = 0; m < i; m++) {
		for (int n = 0; n < j; n++) {
			location++;
		}
	}
	
	return _data[location];
}  

SafeMatrix SafeMatrix::operator+(const SafeMatrix& m) const {
	if ((_numRows != m._numRows) || (_numCols != m._numCols)) {
		SafeMatrix badMatrix(-1, -1);
		
		return badMatrix;
	}
	
	SafeMatrix sumMatrix(_numRows, _numCols);
	
	for (int i = 0; i < _dataSpaceAllocated; i++) {
		sumMatrix._data[i] = m._data[i] + _data[i];
	}
	
	return sumMatrix;
}

SafeMatrix SafeMatrix::operator*(const SafeMatrix& m) const {
	if (_numCols != m._numRows) {
		SafeMatrix badMatrix(-1, -1);
		
		return badMatrix;
	} else {
		SafeMatrix thisCopy(_numRows, _numCols);
		SafeMatrix mCopy(m._numRows, m._numCols);
		SafeMatrix product(_numRows, m._numCols);
		
		for (int i = 0; i < _dataSpaceAllocated; i++) {
			thisCopy._data[i] = _data[i];
		}
		
		for (int i = 0; i < m._dataSpaceAllocated; i++) {
			mCopy._data[i] = m._data[i];
		}
		
		for (int i = 0; i < _numRows; i++) {
			for (int j = 0; j < m._numCols; j++) {
				int num = 0;
				for (int k = 0; k < _numCols; k++) {
					num += thisCopy(i, k) * mCopy(k, j);
				}
				product(i, j) = num;
			}
		}
		
		return product;
	}
}

void SafeMatrix::operator=(const SafeMatrix& m) {
	_dataSpaceAllocated = m._dataSpaceAllocated;

	if (_data != 0) 
		delete[] _data;
	
	if (_numRows > 0) {
		_data = new (std::nothrow) float[_dataSpaceAllocated];
		if (!_data) {
			_numRows = NOT_A_MATRIX;
		}
	}
	for (int i = 0; i < _dataSpaceAllocated; i++) {
		_data[i] = m._data[i];
	}
}

// Constructors/Destructor
SafeMatrix::SafeMatrix() {  //size 0 matrix
	_numRows = 0;
	_numCols = 0;
	_dataSpaceAllocated = 0;
	_data = 0;
}
 /* // Constructors/Destructor
SafeMatrix::SafeMatrix() {
  _numRows = 0;
  _numCols = 0;
  _dataSpaceAllocated = 0;
  _data = new (std::nothrow) float[1];
  if(!_data){
    return;
  }
  _data[0] = 0;

};*/

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
  _dataSpaceAllocated = rows*cols;

  _data = new (std::nothrow) float[_dataSpaceAllocated];
  if(!_data){
    return;
  }

  for (int i = 0; i< _dataSpaceAllocated; i++){
    _data[i] = 0;
  }
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
 
  delete[] _data;
}

/*SafeMatrix::SafeMatrix(const SafeMatrix& m) {
	
}

SafeMatrix::SafeMatrix(const int rows, const int cols) {
	if (rows < 0 || cols < 0) {
		_numRows = NOT_A_MATRIX;
		_data = 0;
		return;
	} 
	
	_numRows = rows;
	_numCols = cols;
	
	if (_numRows == 0 || _numCols == 0) {
		_data = 0;
		return;
	}

	_dataSpaceAllocated = _numRows * _numCols;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
		
	if (!_data) {
		_numRows = NOT_A_MATRIX;
		return;
	}
	
	for (int i = 0; i < _dataSpaceAllocated; i++) {
		_data[i] = 0;
	}
	
	return;
}

SafeMatrix::SafeMatrix(const int rows, const int cols, const float initVal) {
	if (rows < 0 || cols < 0) {
		_numRows = NOT_A_MATRIX;
		_data = 0;
		return;
	} 
	
	_numRows = rows;
	_numCols = cols;
	
	if (_numRows == 0 || _numCols == 0) {
		_data = 0;
		return;
	}
	
	_dataSpaceAllocated = _numRows * _numCols;
	_data = new (std::nothrow) float[_dataSpaceAllocated];
	
	if (!_data) {
		_numRows = NOT_A_MATRIX;
		return;
	}
	
	for (int i = 0; i < _dataSpaceAllocated; i++) {
		_data[i] = initVal;
	}
	
	return;
}

SafeMatrix::~SafeMatrix() {
	_numRows = -2;
	if (_data != 0) {
		delete[] _data;
	}
	_data = 0;
}*/

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
			if (j < (m._numCols - 1)) {
				os << ", ";
			}
			os << "]";
			if (i < (m._numRows - 1)) {
				os << std::endl;
			}
		}
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
  SafeMatrix m2(4,4,8);
  SafeMatrix h = m+m2;
  float data[] = {1,2,3,4,5};
  cout << m+m2 << " HI " << endl;
  cout << h._numCols << "and" << h._numRows << endl;

  cout << "Matrix m:\n" << m << endl;
  //cout << "Matrix m1:\n" << m1 << endl;
  m.appendRow(4, data);
  cout << "Matrix m:\n" << m << endl;
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