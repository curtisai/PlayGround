#include "gtest/gtest.h"

#include "Factorial.h"
TEST(FactorialTest, Negative){
	EXCEPT_EQ(1, Factorial(-5));
	EXCEPT_EQ(1, Factorial(-1));
	EXCEPT_GT(Factorial(-10), 0);
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALLTESTS();
}
