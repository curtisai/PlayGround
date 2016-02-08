#include "counting_allocator.h"
#include "gtest/gtest.h"
#include "stack_guard.h"
#include <string>

TEST(countingAllocatorTest, testSet){
	using namespace sgdm;
	using std::string;
	string test = "length = 11";
	StackGuard<string> guardedStr(new string("length = 11"));

	EXPECT_EQ(11, guardedStr->size());
	EXPECT_EQ(test.size(), guardedStr->size());
	EXPECT_TRUE("length = 11" == *guardedStr);
	EXPECT_TRUE(test == *guardedStr);
	EXPECT_FALSE(!guardedStr);
	EXPECT_FALSE(guardedStr != true);
	EXPECT_TRUE(guardedStr == true);

	StackGuard<string> newStr(std::move(guardedStr));
	EXPECT_EQ(11, newStr->size());
	EXPECT_EQ(test.size(), newStr->size());
	EXPECT_TRUE("length = 11" == *newStr);
	EXPECT_TRUE(test == *newStr);
	EXPECT_FALSE(!newStr);
	EXPECT_FALSE(newStr!=true);
	EXPECT_TRUE(newStr == true);

	EXPECT_TRUE(!guardedStr);
	EXPECT_TRUE(guardedStr!=true);
	EXPECT_TRUE(guardedStr == false);
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
