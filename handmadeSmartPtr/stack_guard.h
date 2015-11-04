//stack_guarded.h
#ifndef STACK_GUARD_H_
#define STACK_GUARD_H_

#include <cstddef>
namespace sgdm{
	template<typename T>
	class StackGuard{
	  private:
	  	T* thePtr;

	  public:
	  	StackGuard(T* guarded) throw();
	  	StackGuard(StackGuard<T>& newPtr) throw();
	  	~StackGuard();

	  	const T* operator->();

	  	StackGuard& operator=(StackGuard& rhs) throw();
	  	StackGuard& operator=(StackGuard&& rhs) throw();
	  	StackGuard& operator=(T* rhs) throw();
	  	const T& operator*();

	  	const bool operator==(const bool rhs);
	  	const bool operator!();
	  	const bool operator!=(StackGuard& rhs);
	  	const bool operator!=(const bool rhs);
	};

	template<typename T>
	StackGuard<T>::StackGuard(T* guarded = NULL) throw() {
		thePtr = guarded;
	}

	template<typename T>
	StackGuard<T>::StackGuard(StackGuard<T>& newPtr) throw(){
		thePtr = newPtr.thePtr;
		newPtr.thePtr = NULL;
	}

	template<typename T>
	StackGuard<T>::~StackGuard(){
		if(thePtr!=NULL)
			delete thePtr;
	}

	template<typename T>
	const T* StackGuard<T>::operator->(){
		return thePtr;
	}

	template<typename T>
	StackGuard<T>& StackGuard<T>::operator=(StackGuard<T>& rhs) throw(){
		if(this != rhs){
			delete thePtr;
			thePtr = rhs.thePtr;
			rhs.thePtr = NULL;
		}
		return *this;
	}

	template<typename T>
	StackGuard<T>& StackGuard<T>::operator=(StackGuard<T>&& rhs) throw(){
		if(this != &rhs){
			delete thePtr;
			thePtr = rhs.thePtr;
			rhs.thePtr = NULL;
		}
		return *this;
	}

	template<typename T>
	StackGuard<T>& StackGuard<T>::operator=(T* rhs) throw(){
		if(thePtr!=NULL)
			delete thePtr;
		thePtr = rhs;
		return *this;
	}

	template<typename T>
	const T& StackGuard<T>::operator*(){
		return *thePtr;
	}

	template<typename T>
	const bool StackGuard<T>::operator!=(const bool rhs){
		return thePtr^rhs;
	}

	template<typename T>
	const bool StackGuard<T>::operator==(const bool rhs){
		if(thePtr==NULL)
			return false==rhs;
		else
			return true==rhs;
	}

	template<typename T>
	const bool StackGuard<T>::operator!(){
		if(thePtr==NULL)
			return true;
		else
			return false;
	}
}

#endif