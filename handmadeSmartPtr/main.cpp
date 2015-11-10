#include "stack_guard.h"



int main(){
	int k = 100;
	sgdm::StackGuard<int> intPtr(&k);

	return 0;
}