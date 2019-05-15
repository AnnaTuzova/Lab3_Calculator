#pragma once 

#include <iostream>
#include <algorithm>   
#include <vector>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>

class Calculator {
private:
	const float kNumOfElements = 20;
	std::vector<float> mw_elements;
	float result = std::numeric_limits<float>::quiet_NaN();


	float Calculation(std::string &input_string);

	void SpaceDelete(std::string &input_string);
	void AddBracket(std::string &input_string);
	void BracketCheck(std::string &input_string);
	void FormatString(std::string &input_string);
	void CheckMultipleOperators(std::string &input_string);
	bool DigitCheck(const std::string input_string);
	void ÑommaCheck(std::string &input_string);

	void NegateFormation(std::string &input_string);
	void Negate(int &i, std::string &input_string, std::vector<char>::iterator &it);
	void ArgumentNegateFormation(int &i, std::string &input_string, std::vector<char>::iterator it);
	void NegateRecursion(std::string &input_string);
	size_t InsertString(std::string &input_string, std::string &delete_string, std::string &add_string, const size_t begin_position, std::vector<char>::iterator &it);

	void SqrtCalculation(std::string &input_string);
	void ModCalculation(std::string &input_string);
	void ReplaceInString(const size_t begin_position, const size_t end_position, const float float_result, std::string &input_string);
	void SelectionModArguments(const std::string match_string, std::string &first_argument, std::string &second_argument, const size_t match_string_size);
	size_t FindingEndOfArgument(const size_t begin_position, const size_t skipped_string_size, const std::string search_string);
	void FloatToString(const float float_result, std::string &calculation_result_string);

	int Prioritization(const char symbol);
	std::string ReversePolishNotation(const std::string input_string);
	void RPNOperators(std::stack<char> &operators_stack, std::string &out_string, std::vector<char>::iterator it);
	float CalculationRPN(const std::string input_string); //RPN - Reverse Polish Notation
	void CalculationOperators(const char input_string_element, float &right_operand, float &left_operand, float &calculation_result, std::stack<float> &number_stack);

	void StringToFloat(const std::string input_string, float &n, const size_t substr_begin_position);
	void MemoryWriting(std::string &input_string, std::vector<float> &MW_elements, const float result);
	void MemoryReading(std::string &input_string, std::vector<float> &MW_elements, const float result);
	void MRReplaceInString(const size_t begin_position, std::string &input_string, const float mr);

public:
	Calculator();
	~Calculator();
	
	float RunCalculator(std::string &input_string);
	std::string GettingString();
};
