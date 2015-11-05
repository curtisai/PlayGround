#include "counting_allocator.h"
#include "gtest/gtest.h"
#include <string>

TEST(countingAllocatorTest, testSet){
	sgdm::CountingAllocator<int> myIntAllocator;
	sgdm::CountingAllocator<std::string> myStrAllocator;

	using namespace sgdm;

	int* intPtr = myIntAllocator.get(100);
	std::string* strPtr = myStrAllocator.get(100);

	EXPECT_EQ(sizeof(*intPtr)*100, 100 * sizeof(int))<<"allocated memory size is "<<sizeof(*intPtr)<<", which doesn't equal to "<<sizeof(int)*100;
	EXPECT_EQ(sizeof(*strPtr)*100, 100 * sizeof(std::string))<<"allocated memory size is "<<sizeof(*strPtr)<<", which doesn't equal to "<<sizeof(std::string)*100;

	myIntAllocator.~CountingAllocator();
	myStrAllocator.~CountingAllocator();

	intPtr = NULL;
	strPtr = NULL;
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
