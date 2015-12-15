// tests.cpp
#include "main.cpp"
#include <gtest/gtest.h>
 
TEST(ADDTEST, SinglePositive) { 

    BigInt a("1");
    BigInt b("1");
    BigInt c = a + b; 
    ASSERT_STREQ("2" , c.getNumber().c_str());
    a.setNumber("4");
   	b.setNumber("3");
    c = a + b;
    ASSERT_STREQ("7" , c.getNumber().c_str());

}

TEST(ADDTEST, DoublePositive) { 

    BigInt a("10");
    BigInt b("10");
    BigInt c = a + b; 
    ASSERT_STREQ("20" , c.getNumber().c_str());

    a.setNumber("25");
    b.setNumber("26");
    c = a + b;

    ASSERT_STREQ("51" , c.getNumber().c_str());

}

TEST(ADDTEST, DoubleSinglePositive) { 

    BigInt a("10");
    BigInt b("1");
    BigInt c = a + b; 
    ASSERT_STREQ("11" , c.getNumber().c_str());

    a.setNumber("19");
    b.setNumber("1");
    c = a + b;
    ASSERT_STREQ("20" , c.getNumber().c_str());

}

TEST(ADDTEST, LargePositive) { 

	// A is bigger
    BigInt a("1001010873782828282729401");
    BigInt b("82828377272727273730");
    BigInt c = a + b; 
    ASSERT_STREQ("1001093702160101010003131" , c.getNumber().c_str());
    
    // A is smaller
    a.setNumber("81817181727382");
    b.setNumber("820020283837372928478282849");
    c = a + b;
    ASSERT_STREQ("820020283837454745660010231", c.getNumber().c_str());
}
TEST(ADDTEST, smallNegative) {

	BigInt a("-1");
	BigInt b("2");

	BigInt c = a + b;

	ASSERT_STREQ("1", c.getNumber().c_str());
	}

TEST(DISABLE_SUBTEST, SinglePositive)
{
	//BigInt a("1");
	//BigInt b("1");
	//BigInt c = a - b;

	//ASSERT_STREQ("0", c.getNumber().c_str());
}

TEST(DISABLE_SUBTEST, NegativeResult)
{
	//BigInt a("2");
    //BigInt b("4");
    //BigInt c = a - b; 
   /// ASSERT_STREQ("-2", c.getNumber().c_str());
}

TEST(DISABLE_SUBTEST, LargePositive)
{
	//BigInt a("1001010873782828282729401");
    //BigInt b("82828377272727273730");
    //BigInt c = a - b; 
    //ASSERT_STREQ("1000928045405555555455671", c.getNumber().c_str());
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
