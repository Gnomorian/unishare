#pragma once

typedef unsigned char BYTE;

#include <string>

using ByteArray = std::basic_string<BYTE, std::char_traits<BYTE>, std::allocator<BYTE>>;

template<class T>
class HeapGuard
{
	T* pType;
public:
	HeapGuard(T* pType) : pType(pType) {}
	~HeapGuard() 
	{ 
		delete pType; 
		pType = nullptr;
	}

	void unassign() { pType = nullptr; }
	void assign(T* pType) { this->pType = pType; }
};

template<class T>
class ArrayHeapGuard
{
	T* pType;
public:
	ArrayHeapGuard(T* pType) : pType(pType) {}
	~ArrayHeapGuard() 
	{
		delete[] pType;
		pType = nullptr;
	}

	void unassign() { pType = nullptr; }
	void assign(T* pType) { this->pType = pType; }
};