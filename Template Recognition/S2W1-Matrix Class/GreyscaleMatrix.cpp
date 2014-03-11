#include "GreyscaleMatrix.h"
#include <iostream>
using namespace std;

GreyscaleMatrix::GreyscaleMatrix(int M, int N) : Matrix(M, N)
{
}

GreyscaleMatrix::GreyscaleMatrix(int M, int N, double* input_data) : Matrix(M, N, input_data)
{
	 //Normalise();
}

GreyscaleMatrix::GreyscaleMatrix(const GreyscaleMatrix& copy) : Matrix(copy)
{
}

double* GreyscaleMatrix::getData()
{
	return this->data;
}

GreyscaleMatrix GreyscaleMatrix::operator- (const GreyscaleMatrix& b)
{
	GreyscaleMatrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = getRead(i,j) - b.getRead(i,j);

			c.data[i*N+j] = k;
		}
	}

	//c.Normalise();

	return c;
}

GreyscaleMatrix GreyscaleMatrix::operator- (const double scalar)
{
	GreyscaleMatrix c(M,N);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double k = getRead(i,j) - scalar;

			c.data[i*N+j] = k;
		}
	}

	//c.Normalise();

	return c;
}

GreyscaleMatrix GreyscaleMatrix::operator* (const GreyscaleMatrix& b)
{
	GreyscaleMatrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = getRead(i,j) * b.getRead(i,j);

			c.data[i*N+j] = k;
		}
	}

	//c.Normalise();

	return c;
}

GreyscaleMatrix GreyscaleMatrix::operator* (const double scalar)
{
	GreyscaleMatrix c(M,N);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double k = getRead(i,j) * scalar;

			c.data[i*N+j] = k;
		}
	}

	//c.Normalise();

	return c;
}

GreyscaleMatrix GreyscaleMatrix::operator/ (const GreyscaleMatrix& b)
{
	GreyscaleMatrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = getRead(i,j) / b.getRead(i,j);

			c.data[i*N+j] = k;
		}
	}

	//c.Normalise();

	return c;
}

GreyscaleMatrix GreyscaleMatrix::operator/ (const double scalar)
{
	GreyscaleMatrix c(M,N);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double k = getRead(i,j) / scalar;

			c.data[i*N+j] = k;
		}
	}

	//c.Normalise();

	return c;
}

GreyscaleMatrix GreyscaleMatrix::operator= (const GreyscaleMatrix& copy)
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

double GreyscaleMatrix::Mean() const
{
	double mean = 0;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			mean += data[i*N+j];
		}
	}

	return floor((mean / (M*N)) + 0.5);
}

double GreyscaleMatrix::Max() const
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

void GreyscaleMatrix::Normalise()
{
	double min = this->Min();

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			data[i*N+j] -= min;
		}
	}

	double max = this->Max();

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (max != 0)
				data[i*N+j] /= max;
			data[i*N+j] *= 255;
			data[i*N+j] = floor(data[i*N+j] + 0.5);
		}
	}
}

double GreyscaleMatrix::SSD(const GreyscaleMatrix& compare)
{
	GreyscaleMatrix temp = *this;
	GreyscaleMatrix temp2 = compare;
	temp = temp - temp2;

	return temp.SumOf();
}