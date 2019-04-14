#pragma once 

#include <iostream>
#include <algorithm>   
#include <vector>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>

float RunCalculator(std::string &input_string);
std::string GettingString();
float Calculation(std::string &input_string);

void SpaceDelete(std::string &input_string);
void AddBracket(std::string &input_string);
void BracketCheck(std::string &input_string);
void FormatString(std::string &input_string);
void CheckMultipleOperators(std::string &input_string);
bool DigitCheck(std::string &input_string);
void ÑommaCheck(std::string &input_string);

void NegateFormation(std::string &input_string);
void Negate(int &i, std::string &input_string, std::vector<char>::iterator &it);
void ArgumentNegateFormation(int &i, std::string &input_string, std::vector<char>::iterator it);
void NegateRecursion(std::string &input_string);
size_t InsertString(std::string &input_string, std::string &delete_string, std::string &add_string, size_t begin_position, std::vector<char>::iterator &it);

void SqrtCalculation(std::string &input_string);
void ModCalculation(std::string &input_string);
void SelectionModArguments(std::string match_string, std::string &first_argument, std::string &second_argument, size_t match_string_size);
size_t FindingEndOfArgument(size_t begin_position, size_t skipped_string_size, std::string search_string);
void FloatToString(float &float_result, std::string &calculation_result_string);

int Prioritization(char symbol);
std::string ReversePolishNotation(std::string input_string);
float CalculationRPN(std::string input_string); //RPN - Reverse Polish Notation

void MemoryWriting(std::string input_string, std::vector<float> &MW_elements, float result);
void MemoryReading(std::string &input_string, std::vector<float> &MW_elements, float result);