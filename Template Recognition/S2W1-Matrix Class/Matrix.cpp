// HOW10183346 - Lawrence Bradley Howard
// Matrix Class (Base)

#include <iostream>
using namespace std;
#include "Matrix.h"

Matrix::Matrix(int M, int N)
{
	this->M = M;
	this->N = N;

	//cout << "Matrix Constructor\n";
	data = new double[M*N];

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			data[i*N+j] = 0;
		}
	}
}

Matrix::Matrix(int M, int N, double* input_data)
{
	this->M = M;
	this->N = N;

	//cout << "Matrix Constructor\n";
	data = new double[M*N];
	
	for (int i = 0; i < M; i++)
	 {
		 for (int j = 0; j < N; j++)
		 {
			 data[i*N+j] = input_data[i*N+j];
		 }
	 }

	delete [] input_data;
}

Matrix::Matrix(const Matrix& copy)
{
	 //cout << "Copy Constructor\n";

	 M = copy.M;
	 N = copy.N;
	 
	 data = new double[M*N];

	 for (int i = 0; i < M; i++)
	 {
		 for (int j = 0; j < N; j++)
		 {
			 data[i*N+j] = copy.data[i*N+j];
		 }
	 }
}

Matrix::~Matrix()
{
	//cout << "Matrix Destructor\n";
	delete [] data;
}

double Matrix::getRead(int i, int j) const
{
	return data[i*N+j];
}

double Matrix::getReadWrite(int i, int j)
{
	return data[i*N+j];
}

void Matrix::setNData(int i, int j, double value)
{
	this->data[i*N+j] = value;
}

Matrix Matrix::operator+ (const Matrix& b)
{
	Matrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = getRead(i,j) + b.getRead(i,j);

			c.data[i*N+j] = k;
		}
	}

	return c;
}

Matrix Matrix::operator+ (const double scalar)
{
	Matrix c(M,N);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double k = getRead(i,j) + scalar;

			c.data[i*N+j] = k;
		}
	}

	return c;
}

Matrix Matrix::operator- (const Matrix& b)
{
	Matrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = getRead(i,j) - b.getRead(i,j);

			c.data[i*N+j] = k;
		}
	}

	return c;
}

Matrix Matrix::operator- (const double scalar)
{
	Matrix c(M,N);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double k = getRead(i,j) - scalar;

			c.data[i*N+j] = k;
		}
	}

	return c;
}

Matrix Matrix::operator* (const Matrix& b)
{
	if (M != b.N)
		return *this;

	Matrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = getRead(i,j) * b.getRead(i,j);

			c.data[i*N+j] = k;
		}
	}

	return c;
}

Matrix Matrix::operator* (const double scalar)
{
	Matrix c(M,N);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double k = getRead(i,j) * scalar;

			c.data[i*N+j] = k;
		}
	}

	return c;
}

Matrix Matrix::operator/ (const Matrix& b)
{
	if (M != b.N)
		return *this;

	Matrix c(M,N);

	for (int i = 0; i < b.M; i++)
	{
		for (int j = 0; j < b.N; j++)
		{
			double k = getRead(i,j) / b.getRead(i,j);

			c.data[i*N+j] = k;
		}
	}

	return c;
}

Matrix Matrix::operator/ (const double scalar)
{
	Matrix c(M,N);

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			double k = getRead(i,j) / scalar;

			c.data[i*N+j] = k;
		}
	}

	return c;
}

Matrix Matrix::operator= (const Matrix& copy)
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

double Matrix::operator[] (int i)
{
	return data[i];
}

double Matrix::operator() (int i, int j)
{
	return data[i*N+j];
}

double Matrix::SSD(Matrix compare)
{
	Matrix temp = *this - compare;

	temp = temp * temp;

	return temp.SumOf();
}

double Matrix::SumOf() const
{
	double k = 0;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			k += getRead(i,j);
		}
	}

	return k;
}

double Matrix::CC(Matrix compare)
{
	Matrix temp = *this * compare;

	return temp.SumOf();
}

double Matrix::Mean() const
{
	double mean = 0;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			mean += data[i*N+j];
		}
	}

	return mean / (M*N);
}

double Matrix::Max() const
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

double Matrix::Min() const
{
	double min = data[0];

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (data[i*N+j] < min)
				min = data[i*N+j];
		}
	}

	return min;
}





double Matrix::SSD(const Matrix& compare, int oM, int oN, int sM, int sN)
{
	Matrix temp2(sM, sN);

	for (int i = 0; i < sM; i++)
	{
		for (int j = 0; j < sN; j++)
		{
			temp2.data[i*N+j] = compare.data[(oM+i)*512+(oN+j)];
		}
	}

	Matrix temp = *this - temp2;

	temp = temp * temp;

	return temp.SumOf();
}

double Matrix::SumOf(int oM, int oN, int sM, int sN) const
{
	double k = 0;

	for (int i = 0; i < sM; i++)
	{
		for (int j = 0; j < sN; j++)
		{
			k += this->data[(oM+i)*N+(oN+j)];
		}
	}

	return k;
}

double Matrix::CC(const Matrix& compare, int oM, int oN, int sM, int sN)
{
	Matrix temp(sM, sN);
	Matrix comparetemp(sM, sN);

	for (int i = 0; i < sM; i++)
	{
		for (int j = 0; j < sN; j++)
		{
			temp.data[i*N+j] = this->data[(oM+i)*N+(oN+j)];
			comparetemp.data[i*N+j] = compare.data[(oM+i)*512+(oN+j)];
		}
	}

	temp = temp * comparetemp;

	return temp.SumOf();
}

double Matrix::Max(int oM, int oN, int sM, int sN) const
{
	double max = data[0];

	for (int i = 0; i < sM; i++)
	{
		for (int j = 0; j < sN; j++)
		{
			if (data[(oM+i)*N+(oN+j)] > max)
				max = data[(oM+i)*N+(oN+j)];
		}
	}

	return max;
}

double Matrix::Min(int oM, int oN, int sM, int sN) const
{
	double min = data[0];

	for (int i = 0; i < sM; i++)
	{
		for (int j = 0; j < sN; j++)
		{
			if (data[(oM+i)*N+(oN+j)] < min)
				min = data[(oM+i)*N+(oN+j)];
		}
	}

	return min;
}

void Matrix::SwapElements(int oM, int oN, int oMM, int oNN, int sM, int sN)
{
	Matrix temp(sM, sN);

	cout << "\n\nSwapping oM: " << oM << "-oN: " << oN << " -- with -- oMM: " << oNN << "-oNN: " << oMM;

	for (int i = 0; i < sM; i++)
	{
		for (int j = 0; j < sN; j++)
		{
			//Temporarilly store a 16x16 chunk of the matrix to be swapped
			temp.data[i*sN+j] = this->data[(oM+i)*N+(oN+j)];
			//Replace the chunk we just took (in the matrix) with a chunk elsewhere in the matrix
			this->data[(oM+i)*N+(oN+j)] = this->data[(oMM+i)*N+(oNN+j)];
			//And slot back the value we first took out - hey presto - a segment is unshuffled
			this->data[(oMM+i)*N+(oNN+j)] = temp.data[i*sN+j];
		}
	}
}

void Matrix::InsertBlock(const Matrix& insert, int oM, int oN, int sM, int sN)
{
	for (int i = 0; i < sM; i++)
	{
		for (int j = 0; j < sN; j++)
		{
			this->data[(oM+i)*N+(oN+j)] = insert.data[i*insert.N+j];
		}
	}
}

double Matrix::NC(const Matrix& compare) const
{
	Matrix tempA = *this, tempB = compare;
	Matrix temp1 = *this, temp2 = compare;

	//cout << "\n\ntempA Mean: " << tempA.Mean();
	//cout << "\n\ntempB Mean: " << tempB.Mean();

	//Find the mean value of both matrices; subtract each element of the matrices by its mean value
	tempA = tempA - tempA.Mean();
	temp1 = temp1 - temp1.Mean();
	tempB = tempB - tempB.Mean();
	temp2 = temp2 - temp2.Mean();

	//For the numerator, multiply matrices element by element; take the sum of the resultant matrix after multiplication
	Matrix toNum = tempA * tempB;
	double num = toNum.SumOf();

	//For the denominator, square each matrix element by element; take the sum of each squared matrix; multiply the sum; take the square root of the multiplied results
	Matrix toDenA = temp1 * temp1;
	Matrix toDenB = temp2 * temp2;
	double den = toDenA.SumOf() * toDenB.SumOf();
	//cout << "\n\ntoDenA: " << toDenA.SumOf();
	//cout << "\n\ntoDenB: " << toDenB.SumOf();
	//cout << "\n\nDen: " << den;
	den = sqrt(den);

	//cout << "\n\nNum: " << num << "  Den: " << den;

	//Divide the numerator by the denominator
	return num / den;
}