#pragma once

#include "Matrix.h"

class GreyscaleMatrix : public Matrix
{
	public:
	GreyscaleMatrix(int M, int N);
	GreyscaleMatrix(int M, int N, double* input_data);
	GreyscaleMatrix(const GreyscaleMatrix& copy);

	double* GreyscaleMatrix::getData();

	GreyscaleMatrix operator- (const GreyscaleMatrix& b);
	GreyscaleMatrix operator- (const double scalar);
	GreyscaleMatrix operator* (const GreyscaleMatrix& b);
	GreyscaleMatrix operator* (const double scalar);
	GreyscaleMatrix operator/ (const GreyscaleMatrix& b);
	GreyscaleMatrix operator/ (const double scalar);
	GreyscaleMatrix operator= (const GreyscaleMatrix& copy);

	virtual double GreyscaleMatrix::Mean() const;
	virtual double GreyscaleMatrix::Max() const;

	virtual double GreyscaleMatrix::SSD (const GreyscaleMatrix& compare);

	void Normalise();
};