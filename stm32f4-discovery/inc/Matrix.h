/*
 * Matrix.h
 *
 *  Created on: 2015¦~5¤ë1¤é
 *      Author: YunKei
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <inttypes.h>

namespace Math{

	template <class T>
	class Matrix{

		public:
			Matrix(int row, int col);
			~Matrix();
			int getRowSize();
			int getColSize();
			void Assign(Matrix<T>& s);
			Matrix<T>& Add(Matrix<T>& s);
			Matrix<T>& Sub(Matrix<T>& s);
			Matrix<T>& Multiplication(Matrix<T>& s);
			Matrix<T>& Scale(const T scale);
			Matrix<T>& Transpose();
			void SetIdentity();
			void SetZero();
			double GetSum();

			class Proxy{
				public:
					Proxy(T* _vector) : _Vector(_vector){};
					T& operator [](int index){
						return _Vector[index];
					}
				private:
					T* _Vector;
			};

			void operator =(Matrix<T>& s);
			Matrix<T>& operator +(Matrix<T>& s);
			Matrix<T>& operator -(Matrix<T>& s);
			Matrix<T>& operator *(Matrix<T>& s);
			Matrix<T>& operator *(const T scale);
			void operator +=(Matrix<T>& s);
			void operator -=(Matrix<T>& s);
			void operator *=(Matrix<T>& s);
			void operator *=(const T scale);

			Proxy operator [](int index);

		private:
			int Row;
			int Col;
			Matrix<T>* _Matrix;
			Matrix<T>* _TMatrix;
			T** _matrix;
			Proxy* _Proxy;
	};
};

using namespace Math;

template <class T>
Matrix<T>::Matrix(int row, int col) : Row(row), Col(col), _Matrix(0), _TMatrix(0), _Proxy(0){
	_matrix = new T*[row];
	for(int i = 0; i < row; i++){
		_matrix[i] = new T[col];
	}
}

template <class T>
Matrix<T>::~Matrix(){
	for(int i = 0; i < Row; i++){
		delete [] _matrix[i];
	}
	delete [] _matrix;
	if(_Proxy){
		delete _Proxy;
	}
	if(_Matrix){
		delete _Matrix;
	}
	if(_TMatrix){
		delete _TMatrix;
	}
}

template <class T>
int Matrix<T>::getRowSize(){
	return Row;
}

template <class T>
int Matrix<T>::getColSize(){
	return Col;
}

template <class T>
void Matrix<T>::Assign(Matrix<T>& s){
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col; j++){
			_matrix[i][j] = s._matrix[i][j];
		}
	}
	return;
}

template <class T>
Matrix<T>& Matrix<T>::Add(Matrix<T>& s){
	if(_Matrix == 0){
		_Matrix = new Matrix(Row, Col);
	}
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col; j++){
			_Matrix->_matrix[i][j] = _matrix[i][j] + s._matrix[i][j];
		}
	}
	return *_Matrix;
}


template <class T>
Matrix<T>& Matrix<T>::Sub(Matrix<T>& s){
	if(_Matrix == 0){
		_Matrix = new Matrix(Row, Col);
	}
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col; j++){
			_Matrix->_matrix[i][j] = _matrix[i][j] - s._matrix[i][j];
		}
	}
	return *_Matrix;
}
template <class T>
Matrix<T>& Matrix<T>::Scale(const T scale){
	if(_Matrix == 0){
		_Matrix = new Matrix(Row, Col);
	}
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col; j++){
			_Matrix->_matrix[i][j] = _matrix[i][j] * scale;
		}
	}
	return *_Matrix;
}

template <class T>
Matrix<T>& Matrix<T>::Transpose(){
	if(_TMatrix == 0){
		_TMatrix = new Matrix(Col, Row);
	}
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col; j++){
			_TMatrix->_matrix[j][i] = _matrix[i][j];
		}
	}
	return *_TMatrix;
}


template <class T>
void Matrix<T>::SetIdentity(){
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col; j++){
			if(i == j){
				_matrix[i][j] = 1;
			}
			else{
				_matrix[i][j] = 0;
			}
		}
	}
}

template <class T>
void Matrix<T>::SetZero(){
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col; j++){
			_matrix[i][j] = 0;
		}
	}
}

template <class T>
double Matrix<T>::GetSum(){
	double value = 0;
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < Col; j++){
			value += _matrix[i][j];
		}
	}
	return value;
}

template <class T>
Matrix<T>& Matrix<T>::Multiplication(Matrix<T>& s){
	if(_Matrix){
		delete _Matrix;
	}
	_Matrix = new Matrix<T>(Row, s.Col);
	T v1[Col];
	T v2[s.Row];
	for(int i = 0; i < Row; i++){
		for(int j = 0; j < s.Col; j++){
			_Matrix->_matrix[i][j] = 0;
			for(int k = 0; k < Col; k++){
				v1[k] = _matrix[i][k];
			}
			for(int k = 0; k < s.Row; k++){
				v2[k] = s._matrix[k][j];
			}
			for(int k = 0; k < s.Row; k++){
				_Matrix->_matrix[i][j] += v1[k] * v2[k];
			}
		}
	}
	return *_Matrix;
}

template <class T>
void Matrix<T>::operator =(Matrix<T>& s){
	return Assign(s);
}

template <class T>
Matrix<T>& Matrix<T>::operator +(Matrix<T>& s){
	return Add(s);
}

template <class T>
Matrix<T>& Matrix<T>::operator -(Matrix<T>& s){
	return Sub(s);
}

template <class T>
Matrix<T>& Matrix<T>::operator *(Matrix<T>& s){
	return Multiplication(s);
}

template <class T>
Matrix<T>& Matrix<T>::operator *(const T scale){
	return Scale(scale);
}

template <class T>
void Matrix<T>::operator +=(Matrix<T>& s){
	return Assign(Add(s));
}

template <class T>
void Matrix<T>::operator -=(Matrix<T>& s){
	return Assign(Sub(s));
}

template <class T>
void Matrix<T>::operator *=(Matrix<T>& s){
	return Assign(Multiplication(s));
}

template <class T>
void Matrix<T>::operator *=(const T scale){
	return Assign(Scale(scale));
}


template <class T>
typename Matrix<T>::Proxy Matrix<T>::operator [](int index){
	if(_Proxy){
		delete _Proxy;
	}
	_Proxy = new Proxy(_matrix[index]);
	return *_Proxy;
}

#endif /* MATRIX_H_ */
