#include "../Calculator_lib/Calculator.h"
#include <windows.h>
#include <gtest/gtest.h>

TEST(TestCalculator, OperationsTest)
{
	Calculator calculator;
	std::vector<std::string> input_strings{"1 + 1", "5 - 9", "8 * 6", "15/4", "-(-5)", "6^2"};
	std::vector<float> expected_results{ 2, -4, 48, 3.75, 5, 36 };
	std::vector<float> actual_results(expected_results.size());

	for (int i = 0; i < input_strings.size(); i++)
	{
		actual_results.at(i) = calculator.RunCalculator(input_strings.at(i));
	}
		ASSERT_EQ(actual_results, expected_results);
}

TEST(TestCalculator, ModAndSqrtTest)
{
	Calculator calculator;
	std::vector<std::string> input_strings{ "sqrt(16)", "mod(5,2)" };
	std::vector<float> expected_results{ 4, 1 };
	std::vector<float> actual_results(expected_results.size());

	for (int i = 0; i < input_strings.size(); i++)
	{
		actual_results.at(i) = calculator.RunCalculator(input_strings.at(i));
	}
	ASSERT_EQ(actual_results, expected_results);
}


TEST(TestCalculator, MWAndMRTest)
{
	Calculator calculator;
	std::vector<std::string> input_strings{ "1 + 5", "MW", "MR", "6 + 5", "MW[1]", "MR + MR[1] + 1" };
	std::vector<float> expected_results{ 6, 6, 6, 11, 11, 18 };
	std::vector<float> actual_results(expected_results.size());

	for (int i = 0; i < input_strings.size(); i++)
	{
		actual_results.at(i) = calculator.RunCalculator(input_strings.at(i));
	}
	ASSERT_EQ(actual_results, expected_results);
}

TEST(TestCalculator, ExpressionTest)
{
	Calculator calculator;
	std::vector<std::string> input_strings{ "((5.2^2+45.6)*(58.6+99.001))^(0.5)-98/17.2---89-+mod(--55,1)*sqrt(sqrt(18^2))",
					"------8+-+-+-+-9*sqrt(2568)*(mod(mod(156,56.5),45.4)-  99/4.1)="};
	std::vector<float> expected_results{ 12.2983f, 8606.7509f };
	std::vector<float> actual_results(expected_results.size());

	for (int i = 0; i < input_strings.size(); i++)
	{
		actual_results.at(i) = calculator.RunCalculator(input_strings.at(i));
		ASSERT_NEAR(actual_results.at(i), expected_results.at(i), 1e-4);
	}
	
}

TEST(TestCalculator, ExceptionTest)
{
	Calculator calculator;
	std::vector<std::string> input_strings{ "(1+2", "abc", "sqrt(-1)", "1/0", "mod(2,0)", "5+*1"};

	for (int i = 0; i < input_strings.size(); i++)
	{
		ASSERT_THROW(calculator.RunCalculator(input_strings.at(i)), const char*);
	}
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}