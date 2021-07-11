/*
	HEADER FILE: Cmatrix.h

	Written by Cameron J. Turner
			   Ph.D. Candidate
			   The University of Texas at Austin

			   Graduate Research Assistant
			   Plutonium Operations Team
			   NMT-15
			   Los Alamos National Laboratory

    
	Copyright 2004

	Version 1.0	- 09/09/03
				Dynamic Matrix Class obtained from
				Ford and Topp's website and modified for
				use with this software.
	Version 1.1 - 09/10/03
				Modifications to constructor to eliminate errors
	Version 1.2 - 09/11/03
				Modifications completed to support matrix resizing
	Version 1.3	- 03/01/04
				Cleanup and comment 1D HyPerMaps Code
	Version 1.4	- 03/23/04
				Eliminated call to "Cexcept.h" directly from Cmatrix.h
	Version 2.0 - 04/07/04
				Added SumCol() and SumRow() functions
	Version 2.1 - 04/16/04
				Added identity() function
	Version 2.2 - 04/27/04
				Added null() function
	Version 2.3 - 09/18/05
				Modified integers to be unsigned long long integers whereever possible.


*/

#ifndef dMATRIX_CLASS
#define dMATRIX_CLASS


/*

	Include Files

*/

#include <iostream>
#include "Cvector.h"
//#include "Cexcept.h"

using namespace std;

template <typename T>
class dMatrix
{
	public:
		dMatrix(unsigned long long int numRows = 0, unsigned long long int numCols = 0);
			// constructor.
			// Postcondition: create array having numRows x numCols elements
			// all of whose elements have value initVal

		dVector<T>& operator[] (unsigned long long int i);
			// index operator.
			// Precondition: 0 <= i < nRows. a violation of this
			// precondition throws the indexRangeError exception.
			// Postcondition: if the operator is used on the left-hand
			// side of an assignment statement, an element of row i 
			// is changed

		const dVector<T>& operator[](unsigned long long int i) const;
			// version for constant objects

		unsigned long long int rows() const;
			// return number of rows
		
		unsigned long long int cols() const;
			// return number of columns

		void resize(unsigned long long int numRows, unsigned long long int numCols);
			// modify the matrix size.
			// Postcondition: the matrix has size numRows x numCols.
			// any new elements are filled with the default value of type T

		void identity(unsigned long long int num);
			// define an identity matrix of size num by num

		void null(unsigned long long int numRows, unsigned long long int numCols);
			// define a null matrix of size numRows by numCols

		void rowswap(unsigned long long int row1,unsigned long long int row2);
			// swap two rows, row1 and row2.

		void colswap(unsigned long long int col1,unsigned long long int col2);
			// swap two rows, col1 and col2.

		void transpose();
			// transpose the matrix.

		void erase();
			// erase the matrix

		double SumCol(unsigned long long int ColNum);
			// sums the selected column

		double SumRow(unsigned long long int RowNum);
			// sums the selected row

	private:
		unsigned long long int nRows, nCols;
			// number of rows and columns

		dVector<dVector<T> > mat;
			// matrix is implemented as nRows vectors (rows),
			// each having nCols elements (columns)
};

template <typename T>
dMatrix<T>::dMatrix(unsigned long long int numRows, unsigned long long int numCols):
	nRows(numRows), nCols(numCols), mat(NULL)
{}

// non-constant version. provides general access to matrix
// elements
template <typename T>
dVector<T>& dMatrix<T>::operator[] (unsigned long long int i)
{
	if (i < 0 || i >= nRows)
		throw indexRangeError(
			"dMatrix: invalid row index", i, nRows);

   return mat[i];
}

// constant version.  can be used with a constant object.
// does not allow modification of a matrix element
template <typename T>
const dVector<T>& dMatrix<T>::operator[] (unsigned long long int i) const
{
	if (i < 0 || i >= nRows)
		throw indexRangeError(
			"dMatrix: invalid row index", i, nRows);

   return mat[i];
}

template <typename T>
unsigned long long int dMatrix<T>::rows() const
{
   return nRows;
}

template <typename T>
unsigned long long int dMatrix<T>::cols() const
{
   return nCols;
}

template <typename T>
void dMatrix<T>::resize(unsigned long long int numRows, unsigned long long int numCols)
{
    unsigned long long int i;
   
    // handle case of no size change with a return
    if (numRows == nRows && numCols == nCols)
      return;

	// assign the new matrix size
	nRows = numRows;
	nCols = numCols;

	// resize to nRows rows
	mat.resize(nRows);

	// resize each row to have nCols columns
	for (i=0; i < nRows; i++)
		mat[i].resize(nCols);

	if (nCols*nRows == 2500000)
		cout << "dMatrix: Matrix oversize WARNING " 
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 5000000)
		cout << "dMatrix: Matrix oversize WARNING " 
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 7500000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 10000000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 12500000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 15000000)
		cout << "dMatrix: Matrix oversize WARNING " 
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 17500000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 20000000)
		cout << "dMatrix: Matrix oversize FINAL WARNING " 
		<< nCols*nRows << " elements" << endl;

	if (nCols*nRows == SIZELIM)
		throw VoversizeError(
			"dMatrix size limit exceeded");

	return;
}

template <typename T>
void dMatrix<T>::identity(unsigned long long int num)
{
	unsigned long long int i,j;
   
    // handle case of no size change with a return
    if (num == nRows && num == nCols){
		for(i=0; i < nRows; i++){
			for(j=0; j < nCols; j++) mat[i][j] = 0.0;
			mat[i][i] = 1.0;
		}
		return;
    }

	// assign the new matrix size
	nRows = num;
	nCols = num;

	// resize to nRows rows
	mat.resize(nRows);

	// resize each row to have nCols columns
	for (i=0; i < nRows; i++)
		mat[i].resize(nCols);

	if (nCols*nRows == 25000000)
		cout << "dMatrix: Matrix oversize WARNING " 
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 50000000)
		cout << "dMatrix: Matrix oversize WARNING " 
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 75000000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 100000000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 125000000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 150000000)
		cout << "dMatrix: Matrix oversize WARNING " 
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 175000000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 200000000)
		cout << "dMatrix: Matrix oversize FINAL WARNING " 
		<< nCols*nRows << " elements" << endl;

	if (nCols*nRows == SIZELIM)
		throw VoversizeError(
			"dMatrix size limit exceeded");

	for(i=0; i < nRows; i++){
		for(j=0; j < nCols; j++) mat[i][j] = 0.0;
		mat[i][i] = 1.0;
	}

	return;
}

template <typename T>
void dMatrix<T>::null(unsigned long long int numRows,unsigned long long int numCols)
{
	unsigned long long int i,j;
   
    // handle case of no size change with a return
    if (numRows == nRows && numRows == nCols){
		for(i=0; i < nRows; i++){
			for(j=0; j < nCols; j++) mat[i][j] = 0.0;
			mat[i][i] = 1.0;
		}
		return;
    }

	// assign the new matrix size
	nRows = numRows;
	nCols = numCols;

	// resize to nRows rows
	mat.resize(nRows);

	// resize each row to have nCols columns
	for (i=0; i < nRows; i++)
		mat[i].resize(nCols);

	if (nCols*nRows == 25000000)
		cout << "dMatrix: Matrix oversize WARNING " 
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 50000000)
		cout << "dMatrix: Matrix oversize WARNING " 
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 75000000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 100000000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 125000000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 150000000)
		cout << "dMatrix: Matrix oversize WARNING " 
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 175000000)
		cout << "dMatrix: Matrix oversize WARNING "  
		<< nCols*nRows << " elements" << endl;
	if (nCols*nRows == 200000000)
		cout << "dMatrix: Matrix oversize FINAL WARNING " 
		<< nCols*nRows << " elements" << endl;

	if (nCols*nRows == SIZELIM)
		throw VoversizeError(
			"dMatrix size limit exceeded");

	for(i=0; i < nRows; i++){
		for(j=0; j < nCols; j++) mat[i][j] = 0.0;
	}

	return;
}


template <typename T>
void dMatrix<T>::rowswap(unsigned long long int row1,unsigned long long int row2)
{
	T temp;
	unsigned long long int i;

	for(i=0;i<nCols;i++){
		temp = mat[row1][i];
		mat[row1][i] = mat[row2][i];
		mat[row2][i] = temp;
	}
}

template <typename T>
void dMatrix<T>::colswap(unsigned long long int col1,unsigned long long int col2)
{
	T temp;
	unsigned long long int i;

	for(i=0;i<nCols;i++){
		temp = mat[i][col1];
		mat[i][col1] = mat[i][col2];
		mat[i][col2] = temp;
	}
}

template <typename T>
void dMatrix<T>::transpose()
{
	dVector<T> mat2;
	
	unsigned long long int i, j;

	for(i=0;i<nRows;i++){
		for(j=0;j<nCols;j++){
			mat2.push_back(mat[i][j]);
		}
	}

	resize(nCols,nRows);

	for(i=0;i<nRows;i++){
		for(j=0;j<nCols;j++){
			mat[i][j] = mat2[i+nRows*j];
		}
	}
}

template <typename T>
void dMatrix<T>::erase()
{
	nRows = 0;
	nCols = 0;
}

template <typename T>
double dMatrix<T>::SumCol(unsigned long long int ColNum)
{
	double temp =0.0;

	for(unsigned long long int i=0;i<nRows;i++) temp += mat[i][ColNum];

	return temp;
}

template <typename T>
double dMatrix<T>::SumRow(unsigned long long int RowNum)
{
	double temp =0.0;

	for(unsigned long long int i=0;i<nCols;i++) temp += mat[RowNum][i];

	return temp;
}


#endif	// dMATRIX_CLASS
