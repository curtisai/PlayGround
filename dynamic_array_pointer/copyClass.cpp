#include "copyClass.h"
#include <iostream>


copyClass::copyClass()
: alloc(){
	ptr = alloc.get(1);
	alloc.construct(ptr, "hello");
	cout << "default constructor called \n";
}

copyClass::copyClass(string* otherPtr)
: alloc(){
	ptr = alloc.get(1);
	alloc.construct(ptr, *otherPtr);
	cout << "string ptr construcor called \n";
}

copyClass::copyClass(copyClass* other)
: alloc(){
	ptr = alloc.get(1);
	alloc.construct(ptr, *(other->ptr));
	cout << "copyClass ptr constructor called \n";
}

copyClass::copyClass(const copyClass& other)
: alloc(){
	ptr = alloc.get(1);
	alloc.construct(ptr, *(other.ptr));
	cout << "copy constructor called \n";
}
copyClass::copyClass(copyClass&& other)
: alloc(){
	ptr = alloc.get(1);
	ptr = other.ptr;
	other.ptr = nullptr;
	cout << "move constructor called \n";
}

copyClass& copyClass::operator=(const copyClass& other){
	ptr = alloc.get(1);
	alloc.construct(ptr, *(other.ptr));
	return *this;
}

copyClass& copyClass::operator=(copyClass&& other){
	ptr = other.ptr;
	other.ptr = nullptr;
	return *this;
}
copyClass::~copyClass(){
	if(ptr != nullptr)
		alloc.destruct(ptr);
	alloc.release(ptr);
	ptr = nullptr;
	cout << "destructor called \n";
}

void copyClass::show(){
	std::cout << *ptr << "\n";
}
