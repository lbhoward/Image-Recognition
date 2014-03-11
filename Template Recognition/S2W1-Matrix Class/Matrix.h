#pragma once

class Matrix{
public:
	Matrix(int M, int N);
	Matrix(int M, int N, double* input_data);
	Matrix(const Matrix& copy);
	~Matrix();
	double Matrix::getRead(int i, int j) const;
	double getReadWrite(int i, int j);
	void setNData(int i, int j, double value);

	int getWidth() { return N; };
	int getHeight() { return M; };

	Matrix operator+ (const Matrix& b);
	Matrix operator+ (const double scalar);
	Matrix operator- (const Matrix& b);
	Matrix operator- (const double scalar);
	Matrix operator* (const Matrix& b);
	Matrix operator* (const double scalar);
	Matrix operator/ (const Matrix& b);
	Matrix operator/ (const double scalar);
	Matrix operator= (const Matrix& b);
	double Matrix::operator[] (int i);
	double Matrix::operator() (int i, int j);

	double Matrix::SSD (Matrix compare);
	double Matrix::SumOf() const;
	double Matrix::CC(Matrix compare);
	double Matrix::NC(const Matrix& compare) const;
	virtual double Matrix::Mean() const;
	virtual double Matrix::Max() const;
	double Matrix::Min() const;

	virtual double Matrix::SSD (const Matrix& compare, int oM, int oN, int sM, int sN);
	double Matrix::SumOf(int oM, int oN, int sM, int sN) const;
	double Matrix::CC(const Matrix& compare, int oM, int oN, int sM, int sN);
	virtual double Matrix::Max(int oM, int oN, int sM, int sN) const;
	double Matrix::Min(int oM, int oN, int sM, int sN) const;

	void Matrix::SwapElements(int oM, int oN, int oMM, int oNN, int sM, int sN);
	void Matrix::InsertBlock(const Matrix& insert, int oM, int oN, int sM, int sN);

protected:
	int M;
	int N;
	double* data;
};

#include "BinaryMatrix.h"
#include "GreyscaleMatrix.h"