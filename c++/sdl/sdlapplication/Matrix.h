#ifndef GENERICMATRIX_H
#define GENERICMATRIX_H

#include "Vector.h"

// Просто матрица NxN, с умножением на себя и вектор, без особых конструкторов
template<int N>
class GenericMatrix
{
public:
	static const int Size = N;
	typedef double Element;

private:
	typedef Element MatrixRow[N];
	typedef MatrixRow MatrixData[N];

	MatrixData A;

	friend class RowAccessor;
	friend class ConstRowAccessor;
	template<int M>
	friend GenericMatrix<M> operator *(const GenericMatrix<M>&, const GenericMatrix<M>&);
	template<int M>
	friend GenericVector<double, M> operator *(const GenericMatrix<M>&, const GenericVector<double, M>&);
    
public:
	// экземпляры этого класса содержат ссылку на матрицу,
	// поэтому ими нельзя пользоваться после того как матрица будет удалена, но хз как это запретить
	class RowAccessor
	{
	private:
		GenericMatrix& matrix;
		const int row;

		inline RowAccessor(GenericMatrix& _matrix, const int _row) : matrix(_matrix), row(_row) {};

		friend class GenericMatrix;

		RowAccessor operator=(const RowAccessor& );

	public:
		inline Element& operator [](const int index) const
		{
			if(index >= 0 && index < N)
				return matrix.A[row][index];
			else
				throw std::out_of_range("second matrix index is out of range (RowAccessor)");
		}
	};

	class ConstRowAccessor
	{
	private:
		const GenericMatrix& matrix;
		const int row;

		inline ConstRowAccessor(const GenericMatrix& _matrix, const int _row) : matrix(_matrix), row(_row) {};

		friend class GenericMatrix;

	public:
		inline const Element& operator [](const int index) const
		{
			if(index >= 0 && index < N)
				return matrix.A[row][index];
			else
				throw std::out_of_range("second matrix index is out of range (ConstRowAccessor)");
		}
	};

public:
	// конструктор по умолчанию, матрица, заполненная нулями
    inline GenericMatrix()
	{
		mset(A, 0);
	}

	// матрица, с заданным значением на диагонали, и нулями в остальных клетках
    inline GenericMatrix(const Element& m)
    {
		mset(A, 0);
 
		for(int i = 0; i < N; ++i)
			A[i][i] = m;
    }

	// индексация, не const
    inline RowAccessor operator [](const int index)
    {
        if(index >= 0 || index < N)
			return RowAccessor(*this, index);
		else
			throw std::out_of_range("first matrix index is out of range (operator [])");
    }

    inline ConstRowAccessor operator [](const int index) const
    {
        if(index >= 0 || index < N)
			return ConstRowAccessor(*this, index);
		else
			throw std::out_of_range("first matrix index is out of range (operator [] const)");
    }
};

// умножение матрицы на матрицу
template<int N>
GenericMatrix<N> operator *(const GenericMatrix<N>& A, const GenericMatrix<N>& B)
{
	GenericMatrix<N> C;

	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
		{
			C.A[i][j] = 0;

			for(int k = 0; k < N; ++k)
				C.A[i][j] += A.A[i][k] * B.A[k][j];
		}

	return C;
}

// умножение матрицы на вектор
template<int N>
GenericVector<double, N> operator *(const GenericMatrix<N>& A, const GenericVector<double, N>& v)
{
	GenericVector<double, N> x;

	for(int i = 0; i < N; ++i)
	{
		x[i] = 0;

		for(int j = 0; j < N; ++j)
			x[i] += A.A[i][j] * v[j];
	}

	return x;
}

// умножение матрицы на вектор, предварительно преобразуя вектор в однородный, и после умножения преобразовав обратно
template<int N>
GenericVector<double, N> operator *(const GenericMatrix<N+1>& A, const GenericVector<double, N>& v)
{
	// 1)
	GenericVector<double, N+1> homo;

	for(int i = 0; i < N; ++i)
		homo[i] = v[i];

	homo[N] = 1.0;

	// 2)
	homo = A * homo;

	// 3)
	GenericVector<double, N> ans;

	for(int i = 0; i < N; ++i)
		ans[i] = homo[i] / homo[N];

	return ans;
}

#endif
