//stack_guarded.h
#ifndef STACK_GUARD_H_
#define STACK_GUARD_H_
/*
	This is an unique_ptr-like class, for raw pointer management

	This is still under construction, may have unnecessary code

*/
//#include <cstddef>
namespace sgdm{
	template<typename T>
	class StackGuard{
	  private:
	  	T* thePtr;
	  	StackGuard(StackGuard<T>& newPtr) noexcept;          //Should use move constructor instead.
	  public:
	  	StackGuard(T* guarded = nullptr) noexcept;						//to disable throw()
	  	StackGuard(StackGuard<T>&& guarded) noexcept;

	  	 
	  	~StackGuard();

	  	T* operator->();

	  	//StackGuard& operator=(StackGuard& rhs) throw();
	  	StackGuard& operator=(StackGuard&& rhs) noexcept;
	  	//StackGuard& operator=(T* rhs) throw();            //This function for some unkown reasons, just doesn't work.
	  	                                                    //I intentionally leave it commented for solving it later
	  	const T& operator*();

	  	const bool operator==(const bool rhs);
	  	const bool operator!();
	  	//const bool operator!=(StackGuard& rhs);
	  	const bool operator!=(const bool rhs);
	};

	template<typename T>
	StackGuard<T>::StackGuard(T* guarded) noexcept{	//the default value could be discarded
		thePtr = guarded;
	}

	template<typename T>
	StackGuard<T>::StackGuard(StackGuard<T>&& newPtr) noexcept{//cannot be const so that the ownership could be handed over
		thePtr = newPtr.thePtr;                              //will be replaced later
		newPtr.thePtr = nullptr;
	}



	template<typename T>
	StackGuard<T>::~StackGuard(){
		if(thePtr!=nullptr)
			delete thePtr;
	}

	template<typename T>
	T* StackGuard<T>::operator->(){
		return thePtr;
	}
/*
	template<typename T>
	StackGuard<T>& StackGuard<T>::operator=(StackGuard<T>& rhs) throw(){
		if(this != rhs){
			delete thePtr;
			thePtr = rhs.thePtr;
			rhs.thePtr = nullptr;
		}
		return *this;
	}
	*/

	template<typename T>
	StackGuard<T>& StackGuard<T>::operator=(StackGuard<T>&& rhs) noexcept{
		if(this != &rhs){
			delete thePtr;
			thePtr = rhs.thePtr;
			rhs.thePtr = nullptr;
		}
		return *this;
	}

	template<typename T>
	const T& StackGuard<T>::operator*(){
		return *thePtr;
	}

	template<typename T>
	const bool StackGuard<T>::operator!=(const bool rhs){
		if(thePtr==nullptr)
			return false^rhs;
		else
			return true^rhs;
	}

	template<typename T>
	const bool StackGuard<T>::operator==(const bool rhs){
		if(thePtr==nullptr)
			return false==rhs;
		else
			return true==rhs;
	}

	template<typename T>
	const bool StackGuard<T>::operator!(){
		if(thePtr==nullptr)
			return true;
		else
			return false;
	}
}

#endif