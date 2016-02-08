#include "default_allocator.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


class copyClass{
  private:
  	std::string* ptr; //just for testing
  	StevensDev::sgdm::DefaultAllocator<string> alloc;
  public:
  	copyClass();
  	copyClass(string* otherPtr);
  	copyClass(copyClass* other);
  	copyClass(const copyClass& other);
  	copyClass(copyClass&& other);
  	copyClass& operator=(const copyClass& other);
  	copyClass& operator=(copyClass&& other);
  	~copyClass();

  	void show();
};

