/*
	HEADER FILE: Cexcept.h

	Written by Cameron J. Turner
			   Ph.D. Candidate
			   The University of Texas at Austin

			   Graduate Research Assistant
			   Plutonium Operations Team
			   NMT-15
			   Los Alamos National Laboratory

    
	Copyright 2004

	Version 1.0	- 09/09/03
				Exceptions handling Class obtained from
				Ford and Topp's website and modified for
				use with this software.
	Version 1.1 - 09/11/03
				Warning added to support size warnings.
	Version 1.2	- 03/01/04
				Cleanup and comment 1D HyPerMaps Code
	Version 1.3 - 09/18/05
				Modified integers to be unsigned long integers whereever possible.

*/

#ifndef EXCEPTION_CLASSES
#define EXCEPTION_CLASSES

#define SIZELIM 250000000	// Sets an upper limit on the number of 
							//  stored in the dMatrix and dVector classes


/*

	Include Files

*/

#include <iostream>
#include <vector>
#include <strstream>
#include <string>


using namespace std;

class baseException
{
	public:
		baseException(const string& str = ""):
			msgString(str)
		{
			if (msgString == "")
				msgString = "Unspecified exception";
		}

		string what() const
		{
			return msgString;
		}

	// protected allows a derived class to access msgString.
	// chapter 13 discusses protected in detail
	protected:
		string msgString;
};

// failure to allocate memory (new() returns NULL)
class memoryAllocationError: public baseException
{
	public:
		memoryAllocationError(const string& msg = ""):
			baseException(msg)
		{}
};

// function argument out of proper range
class rangeError: public baseException
{
	public:
		rangeError(const string& msg = ""):
			baseException(msg)
		{}
};

// index out of range
class indexRangeError: public baseException
{
	public:
		indexRangeError(const string& msg, unsigned long long int i, unsigned long long int size):
			baseException()
		{
			char indexString[80];
			ostrstream indexErr(indexString, 80);

			indexErr << msg << "  index " << i << "  size = " << size << ends;
			// indexRangeError can modify msgString, since it is in
			// the protected section of baseException
			msgString = indexString;
		}
};

// attempt to erase from an empty container
class underflowError: public baseException
{
	public:
		underflowError(const string& msg = ""):
			baseException(msg)
		{}
};

// attempt to insert into a full container
class overflowError: public baseException
{
	public:
		overflowError(const string& msg = ""):
			baseException(msg)
		{}
};

// matrix/vector oversize
class VoversizeError: public baseException
{
	public:
		VoversizeError(const string& msg = ""):
			baseException(msg)
		{}
};

// error in expression evaluation
class expressionError: public baseException
{
	public:
		expressionError(const string& msg = ""):
			baseException(msg)
		{}
};

// bad object reference
class referenceError: public baseException
{
	public:
		referenceError(const string& msg = ""):
			baseException(msg)
		{}
};

// feature not implemented
class notImplementedError: public baseException
{
	public:
		notImplementedError(const string& msg = ""):
			baseException(msg)
		{}
};

// date errors
class dateError: public baseException
{
	public:
		dateError(const string& first, unsigned long long int v, const string& last):
			baseException()
		{
			char dateStr[80];
			ostrstream dateErr(dateStr, 80);

			dateErr << first << ' ' << v << ' ' << last << ends;
			// dateError can modify msgString, since it is in
			// the protected section of baseException
			msgString = dateStr;
		}
};

// error in graph class
class graphError: public baseException
{
	public:
		graphError(const string& msg = ""):
			baseException(msg)
		{}
};

// file open error
class fileOpenError: public baseException
{
	public:
		fileOpenError(const string& fname):
			baseException()
		{
			char errorStr[80];
			ostrstream fileErr(errorStr, 80);

			fileErr << "Cannot open \"" << fname << "\"" << ends;
			// fileOpenError can modify msgString, since it is in
			// the protected section of baseException
			msgString = errorStr;
		}
};

// error in graph class
class fileError: public baseException
{
	public:
		fileError(const string& msg = ""):
			baseException(msg)
		{}
};

#endif	// EXCEPTION_CLASSES
