#include <vector>
#include <iostream>
#include <math.h>

class Matrix {
private:
	int degree;
public:
	int getDegree()
	{
		return degree;
	}
	void setDegree(int degree)
	{
		this->degree = degree;
	}
private:
	double** element;
public:
	double** getElements()
	{
		return element;
	}
	void setElements(double** elements)
	{
		this->element = elements;
	}
public:
	Matrix()
	{
		this->degree = 3;
		this->element = new double* [3] {
			new double[3] {0, 0, 0},
				new double[3] {0, 0, 0},
				new double[3] {0, 0, 0}
		};
	}
	Matrix(int degree, double** element) {
		this->degree = degree;
		double** newelement = new double* [degree];
		for (int i = 0; i < degree; i++)
		{
			newelement[i] = new double[degree];
			for (int i2 = 0; i2 < degree; i2++)
			{
				newelement[i][i2] = element[i][i2];
			}
		}
		this->element = newelement;
	}
	Matrix(Matrix* copy)
	{
		this->degree = copy->degree;
		double** newelement = new double* [degree];
		for (int i = 0; i < degree; i++)
		{
			newelement[i] = new double[degree];
			for (int i2 = 0; i2 < degree; i2++)
			{
				newelement[i][i2] = copy->element[i][i2];
			}
		}
		this->element = newelement;
	}
	~Matrix()
	{
		for (int i = 0; i < degree; i++)
		{
			delete[] element[i];
		}
	}

	void View()
	{
		for (int i = 0; i < degree; i++)
		{
			for (int i2 = 0; i2 < degree; i2++)
			{
				std::cout << element[i][i2] << " ";
			}
			std::cout << std::endl;
		}
	}
	Matrix Transponse()
	{
		double** transposedElement = new double* [degree];
		for (int i = 0; i < degree; i++)
		{
			transposedElement[i] = new double[degree];
		}
		for (int i = 0; i < degree; i++)
		{
			for (int i2 = 0; i2 < degree; i2++)
			{
				int reverseIndex = abs(degree - 1 - i);
				transposedElement[reverseIndex][i2] = element[i2][reverseIndex];
			}
		}
		return new Matrix(degree, transposedElement);
	}
	//I died here
	void Inverse()
	{
		double** A = element;
		int N = degree;
		double temp;

		double** E = new double* [N];

		for (int i = 0; i < N; i++)
			E[i] = new double[N];

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				E[i][j] = 0.0;

				if (i == j)
					E[i][j] = 1.0;
			}

		for (int k = 0; k < N; k++)
		{
			temp = A[k][k];

			for (int j = 0; j < N; j++)
			{
				A[k][j] /= temp;
				E[k][j] /= temp;
			}

			for (int i = k + 1; i < N; i++)
			{
				temp = A[i][k];

				for (int j = 0; j < N; j++)
				{
					A[i][j] -= A[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}
		}

		for (int k = N - 1; k > 0; k--)
		{
			for (int i = k - 1; i >= 0; i--)
			{
				temp = A[i][k];

				for (int j = 0; j < N; j++)
				{
					A[i][j] -= A[k][j] * temp;
					E[i][j] -= E[k][j] * temp;
				}
			}
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				A[i][j] = E[i][j];

		for (int i = 0; i < N; i++)
			delete[] E[i];
		delete[] E;
	}
	//Find Det for matrix
	double Det()
	{
		int row = 0;
		double det = 0;
		//Left to right
		while (row < degree)
		{
			double _det = 1;
			for (int i = 0; i < degree; i++)
			{
				int offset = row;
				if (i + offset >= degree)
				{
					offset -= degree;
				}
				_det *= element[i + offset][i];
			}
			det += _det;
			row++;
		}
		//right to left
		while (row > 0)
		{
			double _det = 1;
			for (int i2 = 0, i = degree - 1; i >= 0; i--, i2++)
			{
				int offset = row - degree;
				if (i + offset < 0)
				{
					offset += degree;
				}
				double el = element[i + offset][i2];
				_det *= el;
			}
			det -= _det;
			row--;
		}
		return det;
	}
};