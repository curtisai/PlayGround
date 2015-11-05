#include "dynamic_array.h"
#include "gtest/gtest.h"
#include <string>

TEST(DynamicArrayTest, Test_pop_push_getLenth){
	sgdm::CountingAllocator<std::string> myAlloc;
	sgdc::DynamicArray<std::string> myArray(myAlloc);
	for(int i = 0; i < 100; i++){
		myArray.push(std::to_string(i));
	}
	EXPECT_EQ(100, myArray.getLength());

	for(int i = 0; i < myArray.getLength(); i++){
		EXPECT_EQ(std::to_string(i), myArray[i]);
	}

	for(int i = 0; i < myArray.getLength(); i++){
		EXPECT_EQ(std::to_string(99-i), myArray.pop());
	}
}


TEST(DynamicArrayTest, Test_pushFront_popFront){
	sgdm::CountingAllocator<std::string> myAlloc;
	sgdc::DynamicArray<std::string> myArray(myAlloc);
	for(int i = 0; i < 100; i++){
		myArray.pushFront(std::to_string(i));
	}
	//EXPECT_EQ(100, myArray.getLength());

	for(int i = 0; i < myArray.getLength(); i++){
		EXPECT_EQ(std::to_string(99 - i), myArray[i]);
	}

	for(int i = 0; i < myArray.getLength(); i++){
		EXPECT_EQ(std::to_string(99 - i), myArray.popFront());
	}
}

TEST(DynamicArrayTest, Test_at){
	sgdm::CountingAllocator<std::string> myAlloc;
	sgdc::DynamicArray<std::string> myArray(myAlloc);
	for(int i = 0; i < 100; i++){
		myArray.push(std::to_string(i));
	}
	//EXPECT_EQ(100, myArray.getLength());

	for(int i = 0; i < myArray.getLength(); i++){
		EXPECT_EQ(std::to_string(i), myArray.at(i));
	}
}




TEST(DynamicArrayTest, Test_insertAt){
	sgdm::CountingAllocator<std::string> myAlloc;
	sgdc::DynamicArray<std::string> myArray(myAlloc);
	for(int i = 0; i < 5; i++){
		myArray.push(std::to_string(i));
	}
	//EXPECT_EQ(100, myArray.getLength());

	for(int i = 0; i < 100; i++){
		myArray.insertAt(3, std::to_string(i));
	}
	EXPECT_EQ(105, myArray.getLength());

	for(int i = 3; i < 103 ; i++){
		EXPECT_EQ(std::to_string(99 - i + 3), myArray[i]);
	}
}

TEST(DynamicArrayTest, Test_removeAt){
	sgdm::CountingAllocator<std::string> myAlloc;
	sgdc::DynamicArray<std::string> myArray(myAlloc);
	for(int i = 0; i < 100; i++){
		myArray.push(std::to_string(i));
	}
	//EXPECT_EQ(100, myArray.getLength());

	for(int i = 1; i < 99; i++){
		EXPECT_EQ(std::to_string(i), myArray.removeAt(1));
	}
	EXPECT_EQ(2, myArray.getLength());
}



int main(int argc, char** argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}