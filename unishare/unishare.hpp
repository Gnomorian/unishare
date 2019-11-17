#pragma once

enum USError
{
	OK,
	ApplicationDone,
	Timeout,
	Unknown
};

#define CHECK_RESULT if(result != OK) return result

template <class T>
class HeapGuard
{
	T* ptr;
public:
	HeapGuard(T* ptr) { protect(ptr); }
	void protect(T* ptr) { this->ptr = ptr; }
	void emancipate() { ptr = nullptr; }
	~HeapGuard() { delete ptr; }
};

template <class T>
class HeapGuardArray
{
	T* ptr;
public:
	HeapGuardArray(T* ptr) { protect(ptr); }
	void protect(T* ptr) { this->ptr = ptr; }
	void emancipate() { ptr = nullptr; }
	~HeapGuardArray() { delete[] ptr; }
};