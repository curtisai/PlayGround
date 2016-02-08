#include <vector>

using std::vector;

void moveZeroes(vector<int>& nums){
	int zero_iter = 0;
	int non_zero_iter = 0;
	int size = nums.size();
	while(zero_iter < size && non_zero_iter < size){
		while(zero_iter < size && nums[zero_iter] != 0)
			zero_iter ++;
		while(non_zero_iter < size && nums[non_zero_iter] == 0)
			non_zero_iter ++;
		if(non_zero_iter < size && zero_iter < size && zero_iter < non_zero_iter){
			nums[zero_iter] = nums[non_zero_iter];
			nums[non_zero_iter] = 0;
			zero_iter ++;
			non_zero_iter ++;
		}
		else
			non_zero_iter ++; 
	}
}

int main(){
	vector<int> test = {4,2,4,0,0,3,0,5,1,0};
	moveZeroes(test);

	return 0;
}