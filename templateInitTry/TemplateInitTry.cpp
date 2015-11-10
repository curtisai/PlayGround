/*
This file is to try how to implement a template class
with a member variable who's also a class or struct

and what I've figured out is:
        the class/struct within a templata class is not 
        necessary to be a template
*/

#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class TemplateInit{
  private:
  	struct vectElement{
  		string eleString;
  		T value;
  		vectElement(T value);
  	};

  	vectElement theElement;
  	string theName; //what a silly variable name
  	
  public:
  	TemplateInit(string newName, T value);
  	void run();

};

template<typename T>
TemplateInit<T>::TemplateInit(string newName, T value):theName(newName), theElement(value){}

template<typename T>
TemplateInit<T>::vectElement::vectElement(T value):eleString(), value(value){}

template<typename T>
void TemplateInit<T>::run(){
	cout<<theName<<"     "<<theElement.eleString<<"   "<<theElement.value<<endl;
}



int main(){
	TemplateInit<int> myTry("hello",100);
	myTry.run();
	return 0;
}