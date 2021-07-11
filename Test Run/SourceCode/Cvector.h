/*
	HEADER FILE: Cvector.h

	Written by Cameron J. Turner
			   Ph.D. Candidate
			   The University of Texas at Austin

			   Graduate Research Assistant
			   Plutonium Operations Team
			   NMT-15
			   Los Alamos National Laboratory

    
	Copyright 2004

	Version 1.0	- 09/09/03
				Dynamic Vector Class obtained from
				Ford and Topp's website and modified for
				use with this software.
	Version 1.1 - 09/10/03
				Modifications to support dynamic allocation of
				4.3 billion elements tested and completed.
	Version 1.2 - 09/11/03
				Modifications completed to support matrix resizing.
				Functionality expanded to better match the capabilities
				of std::vector. Size warning added.
	Version 1.3 - 01/03/04
				Added function to sum the elements in a vector.
	Version 1.4 - 01/05/04
				Added function to sum the square of the elements in a vector.
				Added function to average the elements in a vector.
	Version 1.5	- 03/01/04
				Cleanup and comment 1D HyPerMaps Code
	Version 2.0 - 03/31/04
				Added maximum() and minimum() functions to find max and min 
				values of a vector of terms.
	Version 2.1 - 09/18/05
				Modified integers to be unsigned long integers whereever possible.
	Version 2.2 -10/08/05
				Corrected a bug in the Cvector reserve function - an int left unchanged 
				to an unsigned long int.

*/

#ifndef dVECTOR
#define dVECTOR

/*

	Include Files

*/


#include "Cexcept.h"	// include exception classes

using namespace std;

template <typename T>
class dVector
{
	public:
		dVector(unsigned long long int size = 0);
			// constructor.
			// Postconditions: allocates array with size number of elements
			// and capacity. elements are initialized to T(), the default
			// value for type T

		dVector(const dVector<T>& obj);
			// copy constructor
			// Postcondition: creates current vector as a copy of obj

		~dVector();
			// destructor
			// Postcondition: the dynamic array is destroyed

		dVector& operator= (const dVector<T>& rhs);
			// assignment operator.
			// Postcondition: current vector holds the same data
			// as rhs

		T& back();
			// return the element at the rear of the vector.
			// Precondition: the vector is not empty. if vector
			// is empty, throws the underflowError exception

		const T& back() const;
			// const version used when dVector object is a constant

		T& operator[] (unsigned long long int i);
			// provides general access to elements using an index.
			// Precondition: 0 <= i < vSize. if the index is out
			// of range, throws the indexRangeError exception

		const T& operator[] (unsigned long long int i) const;
			// const version used when dVector object is a constant

		void push_back(const T& item);
			// insert item at the rear of the vector.
			// Postcondition: the vector size is increased by 1

		void resize(unsigned long long int num);
			// resize the vector to size num

		void pop_back();
			// remove element at the rear of the vector.
			// Precondition: vector is not empty. if the vector is
			// empty, throws the underflowError exception

		unsigned long long int size() const;
			// return current list size

		T& front();
			// return the element at the front of the vector.
			// Precondition: the vector is not empty. if vector
			// is empty, throws the underflowError exception

		const T& front() const;
			// return first element in vector in a constant case

		bool empty() const;
			// return true if vector is empty and false otherwise

		unsigned long long int capacity() const;
			// return the current capacity of the vector

		double sum() const;
			// return the sum of the elements in the vector

		double sqr() const;
			// return the sum of the squares of the elements in the vector

		double avg() const;
			// return the average of the elements in the vector

		double maximum() const;
			// return the maximum of the elements in the vector 

		double minimum() const;
			// return the minimum of the elements in the vector 

		void swap(unsigned long long int pos1, unsigned long long int pos2);
			// swap two elements in a vector

		void insert(unsigned long long int pos, const T& item);
			// insert an element at position pos

		void join(dVector<T> &vA,dVector<T> &vB);
			// join vector vB to the tail of vA

		void erase();
			// erase contents of the vector

   private:
		unsigned long long int vCapacity;	// amount of available space
		unsigned long long int vSize;		// number of elements in the list
		T *vArr;							// the dynamic array

		void reserve(unsigned long long int n, bool copy);
			// called by public functions only if n > vCapacity. expands
			// the vector capacity to n elements, copies the existing
			// elements to the new space if copy == true, and deletes
			// the old dynamic array. throws the memoryAllocationError
			// exception if memory allocation fails
};

// set the capacity to n elements
template <typename T>
void dVector<T>::reserve(unsigned long long int n, bool copy)
{
	T *newArr;
	unsigned long long int i;

	// allocate a new dynamic array with n elements
	newArr = new T[n];
	if (newArr == NULL)
		throw memoryAllocationError(
			"dVector reserve(): memory allocation failure");

	// if copy is true, copy elements from the old list to the new list
	if (copy)
		for(i = 0; i < vSize; i++)
			newArr[i] = vArr[i];

	// delete original dynamic array. if vArr is NULL, the vector was
	// originally empty and there is no memory to delete
	if (vArr != NULL)
		delete [] vArr;

	// set vArr to the value newArr. update vCapacity
	vArr = newArr;
	vCapacity = n;
	
}

// constructor. initialize vSize and vCapacity.
// allocate a dynamic array of vSize integers
// and initialize the array with T()
template <typename T>
dVector<T>::dVector(unsigned long long int size):
	vSize(0), vCapacity(0), vArr(NULL)
{
	unsigned long int i;

	// if size is 0, vSize/vCapacity are 0 and vArr is NULL.
	// just return
	if (size == 0)
		return;

	// set capacity to size. since we are building the vector,
	// copy is false
	reserve(size, false);
	// assign size to vSize
	vSize = size;

	// copy T() into each vector element
	for (i=0;i < vSize;i++)
		vArr[i] = T();
}

// copy constructor. make the current object a copy of obj.
// for starters, use initialization list to create an empty
// vector
template <typename T>
dVector<T>::dVector (const dVector<T>& obj):
	vSize(0), vCapacity(0), vArr(NULL)
{
   unsigned long long int i;

	// if size is 0, vSize/vCapacity are 0 and vArr is NULL.
	// just return
	if (obj.vSize == 0)
		return;

	// set capacity to obj.vSize. since we are building the vector,
	// copy is false
	reserve(obj.vSize, false);
	// assign size to obj.vSize
	vSize = obj.vSize;

	// copy items from the obj.vArr to the newly allocated array
	for (i = 0; i < vSize; i++)
		vArr[i] = obj.vArr[i];
}

// destructor. deallocate the dynamic array
template <typename T>
dVector<T>::~dVector()
{
	if (vArr != NULL)
		// de-allocate memory for the array
		delete [] vArr;
}

// replace existing object (left-hand operand) by
// rhs (right-hand operand)
template <typename T>
dVector<T>& dVector<T>::operator= (const dVector<T>& rhs)
{
   unsigned long long int i;

   // check vCapacity to see if a new array must be allocated
   if (vCapacity < rhs.vSize)
		// make capacity of current object the size of rhs. don't
		// do a copy, since we will replace the old values
		reserve(rhs.vSize, false);

	// assign current object to have same size as rhs
	vSize = rhs.vSize;

   // copy items from rhs.vArr to vArr
   for (i = 0; i < vSize; i++)
      vArr[i] = rhs.vArr[i];

   return *this;
}

// check vSize and throw an underflowError exception if the
// value is 0; otherwise return the element vArr[vSize-1]
template <typename T>
T& dVector<T>::back()
{
	if (vSize == 0)
		throw underflowError(
			"dVector back(): vector empty");

	return vArr[vSize-1];
}

template <typename T>
const T& dVector<T>::back() const
{
	if (vSize == 0)
		throw underflowError(
			"dVector back(): vector empty");

	return vArr[vSize-1];
}

// provides general access to array elements
template <typename T>
T& dVector<T>::operator[] (unsigned long long int i)
{
	if (i < 0 || i >= vSize)
		throw indexRangeError(
			"dVector: index range error", i, vSize);

	return vArr[i];
}

// provides general access to array elements. constant version
template <typename T>
const T& dVector<T>::operator[] (unsigned long long int i) const
{
	if (i < 0 || i >= vSize)
		throw indexRangeError(
			"dVector: index range error", i, vSize);

	return vArr[i];
}

// insure that list has sufficient capacity,
// add the new item to the list, and increment vSize
template <typename T>
void dVector<T>::push_back(const T& item)
{
	// if space is full, allocate more capacity
	if (vSize == vCapacity)
	{
		if (vCapacity == 0)
			// if capacity is 0, set capacity to 1.
			// set copy to false because there are
			// no existing elements
			reserve(1,false);
		else
			// double the capacity
			reserve(2 * vCapacity, true);
	}

	// add item to the list, update vSize
	vArr[vSize] = item;
	vSize++;

	if (vSize == 25000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 50000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 75000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 100000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 125000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 150000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 175000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 200000000)
		cout << "dVector: vector oversize FINAL WARNING " 
		<< vSize << " elements" << endl;

	if (vSize == SIZELIM)
		throw VoversizeError(
			"dVector size limit exceeded");
}

// resize the vector,
// if the new size is less than previous, reduce vSize
// if the new size is greater than the previous, add to vSize
template <typename T>
void dVector<T>::resize(unsigned long long int num)
{
	if(num > vSize){
		
		// if space is full, allocate more capacity
		if (num >= vCapacity){
		
			if (vCapacity == 0)
				// if capacity is 0, set capacity to 1.
				// set copy to false because there are
				// no existing elements
				reserve(num,false);
			else
				// increase the capacity by the desired size
				reserve(num,true);
		}
	}
	
	// update vSize
	vSize = num;

	if (vSize == 25000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 50000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 75000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 100000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 125000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 150000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 175000000)
		cout << "dVector: vector oversize WARNING " 
		<< vSize << " elements" << endl;
	if (vSize == 200000000)
		cout << "dVector: vector oversize FINAL WARNING " 
		<< vSize << " elements" << endl;

	if (vSize == SIZELIM)
		throw VoversizeError(
			"dVector size limit exceeded");

	
}

// if not empty, just decrement the size
template <typename T>
void dVector<T>::pop_back()
{
	if (vSize == 0)
		throw underflowError(
			"dVector pop_back(): vector is empty");

	vSize--;
}

template <typename T>
unsigned long long int dVector<T>::size() const
{
	return vSize;
}

// check vSize and throw an underflowError exception if the
// value is 0; otherwise return the element vArr[0]
template <typename T>
T& dVector<T>::front()
{
	if (vSize == 0)
		throw underflowError(
			"dVector front(): vector empty");

	return vArr[0];
}

template <typename T>
const T& dVector<T>::front() const
{
	if (vSize == 0)
		throw underflowError(
			"dVector front(): vector empty");

	return vArr[0];
}

template <typename T>
bool dVector<T>::empty() const
{
	return vSize == 0;
}

template <typename T>
unsigned long long int dVector<T>:: capacity() const
{
	return vCapacity;
}

// sum vector elements
template <typename T>
double dVector<T>:: sum() const
{
	double sum = 0.0;
	for(int i=0;i<vSize;i++) sum += vArr[i];
	return sum;
}

// sum of the square of vector elements
template <typename T>
double dVector<T>:: sqr() const
{
	double sum = 0.0;
	for(unsigned long long int i=0;i<vSize;i++) sum += vArr[i]*vArr[i];
	return sum;
}

// average of vector elements
template <typename T>
double dVector<T>:: avg() const
{
	if (vSize == 0)
		return 0.0;
	double sum = 0.0;
	for(unsigned long long int i=0;i<vSize;i++) sum += vArr[i];
	return sum/vSize;
}

// maximum of vector elements
template <typename T>
double dVector<T>:: maximum() const
{
	if (vSize == 0)
		throw underflowError(
			"dVector front(): vector empty");
	double max = vArr[0];
	for(unsigned long long int i=1;i<vSize;i++){
		if(vArr[i] > max) max = vArr[i];
	}
	return max;
}

// minimum of vector elements
template <typename T>
double dVector<T>:: minimum() const
{
	if (vSize == 0)
		throw underflowError(
			"dVector front(): vector empty");
	double min = vArr[0];
	for(unsigned long long int i=1;i<vSize;i++){
		if(vArr[i] < min) min = vArr[i];
	}
	return min;
}

// swap elements
template <typename T>
void dVector<T>::swap(unsigned long long int pos1, unsigned long long int pos2)
{
	if (pos1 < 0 || pos1 >= vSize)
		throw indexRangeError(
			"dVector: index range error", pos1, vSize);

	if (pos2 < 0 || pos2 >= vSize)
		throw indexRangeError(
			"dVector: index range error", pos2, vSize);

	T value = vArr[pos1];
	vArr[pos1] = vArr[pos2];
	vArr[pos2] = value;

}

// insert element
template <typename T>
void dVector<T>::insert(unsigned long long int pos, const T& item)
{
	if (pos < 0 || pos >= vSize)
		throw indexRangeError(
			"dVector: index range error", pos, vSize);

	push_back(item);

	for(unsigned long long int i=vSize;i>pos;i--){
		vArr[i] = vArr[i-1];
	}
	vArr[pos] = item;

}

// join vectors
template <typename T>
void dVector<T>::join(dVector<T> &vA,dVector<T> &vB)
{
	// Capture the size of vB
	unsigned long long int i = 0;
	unsigned long long int sizeB = vB.size();

	// Append vB to vA with push_back
	for(i=0;i<sizeB;i++){
		vA.push_back(vB[i]);
	}

}

// erase vector
template <typename T>
void dVector<T>::erase()
{
	vSize = 0;
}



#endif   // dVECTOR