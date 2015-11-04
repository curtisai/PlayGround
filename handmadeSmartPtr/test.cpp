#include "stack_guard.h"
#include "gtest/gtest.h"
#include <string>


TEST(StackGuardTest, TheTest){
	
	std::string* mptr = new std::string("this is the test string A");
	sgdm::StackGuard<std::string> strPtrA(mptr);
	//sgdm::StackGuard<std::string> strPtrB = new std::string("this is the test string B");

	EXPECT_EQ("this is the test string A",*strPtrA);
	//EXPECT_EQ("this is the test string B",*strPtrB);
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}