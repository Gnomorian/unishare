#pragma once

#ifdef UNISHARE_COMMON
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif // UNISHARE_COMMON

#define API extern "C"

enum USError
{
	OK,
	ApplicationDone,
	Timeout,
	UnknownError
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