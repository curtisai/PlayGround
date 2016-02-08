#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
/*
class implicitCast{
  private:
  	int value;
  public:
  	implicitCast(){
  		value = 0;
  	}

  	implicitCast(implicitCast&& rval){
  		value = rval.value;
  		cout<<"move involved"<<endl;
  	}
  	implicitCast(const implicitCast& lval){
  		value = lval.value;
  		cout<<"copy involved"<<endl;
  	}
  	implicitCast(int integer):value(integer){
  		cout << "implicit cast involved"<<endl;
  	}
  	int getValue(){
  		return value;
  	}
};
implicitCast castTest(implicitCast x){
	int k = x.getValue();
	return k;
}
*/


class ReferenceMember{
  private:
  	string& strRef;
  public:
  	ReferenceMember(string& init){ //:strRef(init){
  		strRef = init;
  	}
};
int main(){
	//implicitCast fakePtr(std::move(castTest(100)));
	string fakePtr = "hello";
	ReferenceMember refTest(fakePtr);
	
	/*
	output:
	implicit cast involved
	implicit cast involved
	move involved
	*/
	//implicitCast ptr = castTest(100);
	/*
	output:
	implicit cast involved
	implicit cast involved
	*/
	//implicitCast ptr(castTest(100));
    /*
    implicit cast involved
    implicit cast involved
    */
	//implicitCast* ptr = &&castTest(100);
	//delete ptr;
	/*
	invalid conversion from ‘void*’ to ‘implicitCast*’ [-fpermissive]
	*/
	//implicitCast* ptr = (implicitCast*)(&&castTest(100));
	//delete ptr;
	/*
	expected ‘)’ before ‘(’ token
    implicitCast* ptr = (implicitCast*)(&&castTest(100));
                                                ^
    label ‘castTest’ used but not defined
    implicitCast* ptr = (implicitCast*)(&&castTest(100));
                                          ^
	*/

	return 0;
}


