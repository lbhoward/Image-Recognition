#include "BinaryMatrix.h"
#include <iostream>
#include <cmath>
using namespace std;

BinaryMatrix::BinaryMatrix(int M, int N) : Matrix(M, N)
{
}

BinaryMatrix::BinaryMatrix(int M, int N, double* input_data) : Matrix(M, N, input_data)
{
}

BinaryMatrix::BinaryMatrix(const BinaryMatrix& copy) : Matrix(copy)
{
}

double* BinaryMatrix::getData()
{
	return this->data;
}

double BinaryMatrix::Mean() const
{
	double mean = 0;
	int value = 0;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			mean += data[i*N+j];
			value++;
		}
	}

	return mean / value;
}

double BinaryMatrix::Max() const
{
	double max = data[0];

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (data[i*N+j] > max)
				max = data[i*N+j];
		}
	}

	return max;
}

BinaryMatrix BinaryMatrix::operator- (const BinaryMatrix& b)
{
	BinaryMatrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = 0;

			if (getRead(i,j) == 0 && b.getRead(i,j) == 0)
				k = 0;
			else if (getRead(i,j) == 0 && b.getRead(i,j) == 1)
				k = 1;
			else if (getRead(i,j) == 1 && b.getRead(i,j) == 1)
				k = 0;
			else if (getRead(i,j) == 1 && b.getRead(i,j) == 0)
				k = 1;

			c.data[i*N+j] = k;
		}
	}

	return c;
}

BinaryMatrix BinaryMatrix::operator* (const BinaryMatrix& b)
{
	BinaryMatrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = 0;

			if (getRead(i,j) == 0 && b.getRead(i,j) == 0)
				k = 0;
			else if (getRead(i,j) == 0 && b.getRead(i,j) == 1)
				k = 0;
			else if (getRead(i,j) == 1 && b.getRead(i,j) == 1)
				k = 1;
			else if (getRead(i,j) == 1 && b.getRead(i,j) == 0)
				k = 0;

			c.data[i*N+j] = k;
		}
	}

	return c;
}

BinaryMatrix BinaryMatrix::operator/ (const BinaryMatrix& b)
{
	BinaryMatrix c(M,N);

	double k = 0;

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			if (getRead(i,j) == 0 && b.getRead(i,j) == 0)
				k = 0;
			else if (getRead(i,j) == 0 && b.getRead(i,j) == 1)
				k = 0;
			else if (getRead(i,j) == 1 && b.getRead(i,j) == 1)
				k = 1;
			else if (getRead(i,j) == 1 && b.getRead(i,j) == 0)
				k = 0;

			c.data[i*N+j] = k;
		}
	}

	return c;
}

BinaryMatrix BinaryMatrix::operator+ (const BinaryMatrix& b)
{
	BinaryMatrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = 0;

			if (getRead(i,j) == 1 && b.getRead(i,j) == 1)
				k = 1;
			else if (getRead(i,j) == 0 && b.getRead(i,j) == 1)
				k = 1;
			else if (getRead(i,j) == 1 && b.getRead(i,j) == 0)
				k = 1;
			else if (getRead(i,j) == 0 && b.getRead(i,j) == 0)
				k = 0;

			c.data[i*N+j] = k;
		}
	}

	return c;
}

BinaryMatrix BinaryMatrix::operator= (const BinaryMatrix& copy)
{
	 M = copy.M;
	 N = copy.N;

	 delete [] data;

	 data = new double[M*N];

	 for (int i = 0; i < M; i++)
	 {
		 for (int j = 0; j < N; j++)
		 {
			 data[i*N+j] = copy.data[i*N+j];
		 }
	 }

	 return *this;
}

double BinaryMatrix::SSD(const BinaryMatrix& compare, int oM, int oN, int sM, int sN)
{
	BinaryMatrix temp2(sM, sN);

	for (int i = 0; i < sM; i++)
	{
		for (int j = 0; j < sN; j++)
		{
			temp2.data[i*temp2.N+j] = compare.data[(oM+i)*compare.N+(oN+j)];
		}
	}

	BinaryMatrix temp = *this;
	temp = temp - temp2;

	return temp.SumOf();
}

double BinaryMatrix::SSD(const BinaryMatrix& compare)
{
	BinaryMatrix temp = *this;
	BinaryMatrix temp2 = compare;
	temp = temp - temp2;

	return temp.SumOf();
}

double BinaryMatrix::CC(const BinaryMatrix& compare, int oM, int oN, int sM, int sN) const
{
	BinaryMatrix I(sM, sN);
	BinaryMatrix T(sM, sN);

	for (int i = 0; i < sM; i++)
	{
		for (int j = 0; j < sN; j++)
		{
			I.data[i*sN+j] = this->data[i*sN+j];
			T.data[i*sN+j] = compare.data[(i+oM)*compare.N+(j+oN)];
		}
	}

	I = I*T;

	return I.SumOf();
}