#include "stack.h"
#include "gtest/gtest.h"

TEST(StackTest, Size){
	Stack s = {1,2,3,4,5};
	ASSERT_EQ(5,s.size());
}

TEST(StackTest, Pop){
	Stack s = {1,2,3,4,5};
	ASSERT_EQ(5,s.pop());
	ASSERT_EQ(4,s.size());
}

TEST(StackTest, Push){
	Stack s = {1,2,3,4,5};
	s.push(7);
	ASSERT_EQ(6,s.size());
}

TEST(StackTest, Peek){
	Stack s = {1,2,3,4,5};
	ASSERT_EQ(5,s.peek());
	ASSERT_EQ(5,s.size());
}


int main(int argc, char **argv){
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

