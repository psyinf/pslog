#include <gtest/gtest.h>
#include <gmock/gmock.h>


#include <LoggerRegistry.h>
#include <Logger.h>
#include <MultiSink.h>
#include <DefaultLogFormatter.h>


namespace
{
	class SimpleLoggerTest : public ::testing::Test
	{
	protected:
	
		SimpleLoggerTest() 
		{}

		virtual ~SimpleLoggerTest() 
		{}

		
	};

	using namespace ::testing;
	TEST_F(SimpleLoggerTest, CreateLogger)
	{
		static auto l = pslog::LoggerRegistry::make<pslog::Logger>("b1");
		testing::internal::CaptureStdout();
		pslog::LogObject logObj = l->log(pslog::Level::LVL_INFO, "Hello123");
		std::string output = testing::internal::GetCapturedStdout();
		ASSERT_THAT(output, HasSubstr("Hello123"));
		ASSERT_THAT(output, HasSubstr(" INFO "));
		ASSERT_THAT(logObj,Field(&pslog::LogObject::msg, StrEq("Hello123")));
		ASSERT_THAT(logObj, Field(&pslog::LogObject::context, StrEq("b1")));
		ASSERT_THAT(logObj, Field(&pslog::LogObject::level, Eq(pslog::Level::LVL_INFO)));
	}

	TEST_F(SimpleLoggerTest, CreateSpecializedLogger)
	{
		static auto l = pslog::LoggerRegistry::make<pslog::Logger, pslog::DefaultLogFormatter, pslog::MultiSink >("b1");
		testing::internal::CaptureStdout();
		pslog::LogObject logObj = l->log(pslog::Level::LVL_INFO, "Hello123");
		std::string output = testing::internal::GetCapturedStdout();
		ASSERT_THAT(output, HasSubstr("Hello123"));
		ASSERT_THAT(output, HasSubstr(" INFO "));
		ASSERT_THAT(logObj, Field(&pslog::LogObject::msg, StrEq("Hello123")));
		ASSERT_THAT(logObj, Field(&pslog::LogObject::context, StrEq("b1")));
		ASSERT_THAT(logObj, Field(&pslog::LogObject::level, Eq(pslog::Level::LVL_INFO)));
		//CHECK file content
	}

} // Namespace




int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}