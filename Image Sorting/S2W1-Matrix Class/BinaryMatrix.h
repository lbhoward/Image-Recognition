#pragma once

#include "Matrix.h"

class BinaryMatrix : public Matrix
{
public:
	BinaryMatrix(int M, int N);
	BinaryMatrix(int M, int N, double* input_data);
	BinaryMatrix(const BinaryMatrix& copy);

	double* BinaryMatrix::getData();

	virtual double BinaryMatrix::Mean() const;
	virtual double BinaryMatrix::Max() const;

	BinaryMatrix operator- (const BinaryMatrix& b);
	BinaryMatrix operator* (const BinaryMatrix& b);
	BinaryMatrix operator/ (const BinaryMatrix& b);
	BinaryMatrix operator+ (const BinaryMatrix& b);
	BinaryMatrix operator= (const BinaryMatrix& copy);

	virtual double BinaryMatrix::SSD (const BinaryMatrix& compare, int oM, int oN, int sM, int sN);
	virtual double BinaryMatrix::SSD(const BinaryMatrix& compare);
	virtual double BinaryMatrix::CC(const BinaryMatrix& compare, int oM, int oN, int sM, int sN) const;
};