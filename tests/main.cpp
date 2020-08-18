#include <gtest/gtest.h>
#include <LoggerRegistry.h>
TEST(Addition, CanAddTwoNumbers)
{
	EXPECT_EQ(4, 2 + 2);
}


TEST(pslog, CreateLogger)
{
	static auto l = pslog::LoggerRegistry::make<pslog::Logger>("b1");

}
int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}