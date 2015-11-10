#include "stack_guard.h"
#include "gtest/gtest.h"
#include <string>


TEST(StackGuardTest, TheTest){
	
	//std::string* mptr = new std::string("this is the test string A");
	sgdm::StackGuard<std::string> strPtrA(new std::string("this is the test string A"));
	sgdm::StackGuard<std::string> strPtrB(new std::string("this is the test string B"));
	int intPtr = 100;
	sgdm::StackGuard<int>strPtrD(&intPtr);

	EXPECT_EQ("this is the test string A",*strPtrA);
	EXPECT_EQ("this is the test string B",*strPtrB);
	EXPECT_EQ(strPtrA->size(), strPtrB->size());
	EXPECT_EQ(!strPtrA, false);
	EXPECT_EQ(strPtrA!=false, true);
	sgdm::StackGuard<std::string> strPtrC(strPtrA);
	EXPECT_EQ(!strPtrA, true);
	EXPECT_EQ(strPtrA!=false, false);

}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}