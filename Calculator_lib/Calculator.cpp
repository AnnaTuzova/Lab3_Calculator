#include "Calculator.h"

Calculator::Calculator()
{
	mw_elements.resize(kNumOfElements);
	for (int i = 0; i < mw_elements.size(); i++)
	{
		mw_elements.at(i) = std::numeric_limits<float>::quiet_NaN();
	}
}

Calculator::~Calculator()
{

}

float Calculator::RunCalculator(std::string &input_string)
{
	std::string mw_string = { "MW" };
	
	if (std::search(input_string.begin(), input_string.end(),
		mw_string.begin(), mw_string.end()) != input_string.end())
	{
		MemoryWriting(input_string, mw_elements, result);
	}
	else
	{
		result = Calculation(input_string);
	}

	return result;
}

std::string Calculator::GettingString()
{
	std::string input_string;
	std::getline(std::cin, input_string);

	return input_string;
}

float Calculator::Calculation(std::string &input_string)
{
	FormatString(input_string);
	CheckMultipleOperators(input_string);

	ModCalculation(input_string);
	SqrtCalculation(input_string);

	MemoryReading(input_string, mw_elements, result);

	NegateFormation(input_string);
	NegateRecursion(input_string);

	std::string RPN_string = ReversePolishNotation(input_string);
	result = CalculationRPN(RPN_string);

	return result;
}


void Calculator::SpaceDelete(std::string &input_string)
{
	input_string.erase(std::remove_if(input_string.begin(), input_string.end(), isspace), input_string.end());
}

void Calculator::AddBracket(std::string &input_string)
{
	input_string.push_back(')');
	input_string.insert(0, "(");
}

void Calculator::BracketCheck(std::string &input_string)
{
	int count_open_bracket = 0;
	int count_close_bracket = 0;

	for (int i = 0; i < input_string.size(); i++)
	{
		if (input_string.at(i) == '(')
		{
			count_open_bracket++;
		}
		else if (input_string.at(i) == ')')
		{
			count_close_bracket++;
		}
	}

	if (count_close_bracket != count_open_bracket)
	{
		throw "Error: invalid expression.";
	}
}

void Calculator::FormatString(std::string &input_string)
{	
	if (input_string.back() == '=')
	{
		input_string.pop_back();
	}

	AddBracket(input_string);
	SpaceDelete(input_string);
	BracketCheck(input_string);
}

void Calculator::CheckMultipleOperators(std::string &input_string)
{
	std::vector<std::string> serch_multiple_operators =
	{ "+*" , "+/", "+^", "+=",
		"-*", "-/", "-^", "-=" ,
		"*+" , "*-" , "**" , "*/" , "*^" , "*=" ,
		"/+" , "/-" , "/*" , "//" , "/^" , "/=" ,
		"^+" , "^-" , "^*" , "^/" , "^^", "^=",
		"=+", "=-", "=*", "=/", "=^", "==",
		"(*", "(/", "(^", "(=", "()",
		"+)", "-)", "*)", "/)", "^)", "=)" };

	std::string::iterator it;

	for (int i = 0; i < serch_multiple_operators.size(); i++)
	{
		it = std::search(input_string.begin(), input_string.end(), serch_multiple_operators.at(i).begin(), serch_multiple_operators.at(i).end());
		if (it != input_string.end())
			throw "Error: invalid expression.";
	}
}

bool Calculator::DigitCheck(std::string &input_string)
{
	int i = 0;
	for (i = 0; i < input_string.size(); i++)
	{
		if (isdigit(input_string.at(i)) || input_string.at(i) == '.')
			continue;
		else
			break;
	}

	if (i == input_string.size())
		return true;
	else
		return false;
}

void Calculator::CommaCheck(std::string &input_string)
{
	std::vector<char> comma = { ',' };
	std::vector<char>::iterator it;

	for (int i = 0; i < input_string.size(); i++)
	{
		it = std::find(comma.begin(), comma.end(), input_string.at(i));
		if (it != comma.end())
		{
			throw "Error: invalid expression.";
		}
	}
}


void Calculator::NegateFormation(std::string &input_string)
{
	std::vector<char> operators = { '+', '-' };
	std::vector<char>::iterator it;

	for (int i = 0; i < input_string.size(); i++)
	{
		it = std::find(operators.begin(), operators.end(), input_string.at(i));
		if (it != operators.end())
		{
			if ((input_string.at(i - 1) == '-' || input_string.at(i - 1) == '+'
				|| input_string.at(i - 1) == '(' || input_string.at(i - 1) == ',')
				&& isdigit(input_string.at(i + 1)))
			{
				Negate(i, input_string, it);
			}

			else if (((input_string.at(i - 1) == '-' || input_string.at(i - 1) == '+') &&
				(input_string.at(i + 1) == '-' || input_string.at(i + 1) == '+')) ||
				(isdigit(input_string.at(i - 1)) && (input_string.at(i + 1) == '-' ||
					input_string.at(i + 1) == '+')))
			{
				continue;
			}

			else if ((input_string.at(i - 1) == '-' || input_string.at(i - 1) == '+' ||
				input_string.at(i - 1) == '(' || input_string.at(i - 1) == ',') &&
				input_string.at(i + 1) == '(')
			{
				ArgumentNegateFormation(i, input_string, it);
			}

		}
		else
		{
			continue;
		}
	}
}

void Calculator::Negate(int &i, std::string &input_string, std::vector<char>::iterator &it)
{
	std::string number_string;

	size_t begin_position = i;
	i++;  //Pass +/-

	while (isdigit(input_string.at(i)) || input_string.at(i) == '.')
	{
		number_string.push_back(input_string.at(i));

		if (i != input_string.size() - 1)
			i++;
		else
			break;
	}

	InsertString(input_string, number_string, number_string, begin_position, it);
	i += 2; // add size of '(' + '0' + ')' and subtract 1 in the next 'for' loop 
}

void Calculator::ArgumentNegateFormation(int &i, std::string &input_string, std::vector<char>::iterator it)
{
	std::string negative_argument;

	size_t begin_position = i;
	size_t negative_string_size = 1;
	size_t end_position = FindingEndOfArgument(begin_position, negative_string_size, input_string);

	negative_argument = input_string.substr(begin_position + negative_string_size, end_position - (begin_position + negative_string_size));
	std::string negative_argument_primordial = negative_argument;

	NegateFormation(negative_argument);

	size_t insert_string_size = InsertString(input_string, negative_argument_primordial, negative_argument, begin_position, it);

	i += insert_string_size;
}

void Calculator::NegateRecursion(std::string &input_string)
{
	std::vector<std::string> serch_double_operators = { "++" , "+-", "-+", "--", ",-(", ",+(", "(-(", "(+(" };
	std::string::iterator it;

	for (int i = 0; i < serch_double_operators.size(); i++)
	{
		it = std::search(input_string.begin(), input_string.end(), serch_double_operators.at(i).begin(), serch_double_operators.at(i).end());
		if (it != input_string.end())
		{
			NegateFormation(input_string);
			NegateRecursion(input_string);
		}
		else
		{
			continue;
		}
	}
}

size_t Calculator::InsertString(std::string &input_string, std::string &delete_string, std::string &add_string, size_t begin_position, std::vector<char>::iterator &it)
{
	std::string insert_string;

	input_string.erase(begin_position, delete_string.size() + 1);

	if (*it == '-')
		insert_string = "(0-";
	else
		insert_string = "(0+";

	insert_string.append(add_string);
	insert_string.append(")");

	input_string.insert(begin_position, insert_string);

	return insert_string.size();
}


void Calculator::SqrtCalculation(std::string &input_string)
{
	std::string sqrt_string = { "sqrt" };
	std::string::iterator it;
	std::string sqrt_argument;
	std::string calculation_result_string;

	size_t begin_position = 0;
	size_t end_position = 0;

	float float_result;

	for (int i = 0; i < input_string.size(); i++)
	{
		it = std::search(input_string.begin(), input_string.end(), sqrt_string.begin(), sqrt_string.end());
		if (it != input_string.end())
		{
			begin_position = std::distance(input_string.begin(), it);
			end_position = FindingEndOfArgument(begin_position, sqrt_string.size(), input_string);

			sqrt_argument = input_string.substr(begin_position + sqrt_string.size(), end_position - (begin_position + sqrt_string.size()));
			MemoryReading(sqrt_argument, mw_elements, result);
			SqrtCalculation(sqrt_argument);

			NegateFormation(sqrt_argument);
			NegateRecursion(sqrt_argument);

			sqrt_argument = ReversePolishNotation(sqrt_argument);
			float_result = CalculationRPN(sqrt_argument);

			if (float_result < 0)
			{
				throw "Error: invalid expression. Impossible to take the root of a negative number.";
			}

			float_result = std::sqrt(float_result);

			FloatToString(float_result, calculation_result_string);

			input_string.erase(begin_position, end_position - begin_position);
			input_string.insert(begin_position, calculation_result_string);
		}
		else
		{
			break;
		}
	}
}

void Calculator::ModCalculation(std::string &input_string)
{
	std::string mod_string = { "mod" };
	std::string mod_argument;
	std::string::iterator it;
	std::string calculation_result_string;

	std::string first_argument;
	std::string second_argument;

	size_t begin_position = 0;
	size_t end_position = 0;

	float float_result, first_argument_float, second_argument_float;

	for (int j = 0; j < input_string.size(); j++)
	{
		it = std::search(input_string.begin(), input_string.end(), mod_string.begin(), mod_string.end());
		if (it != input_string.end())
		{
			begin_position = std::distance(input_string.begin(), it);
			end_position = FindingEndOfArgument(begin_position, mod_string.size(), input_string);

			mod_argument = input_string.substr(begin_position + mod_string.size(), end_position - (begin_position + mod_string.size()));
			ModCalculation(mod_argument);

			NegateFormation(mod_argument);
			NegateRecursion(mod_argument);

			SelectionModArguments(mod_argument, first_argument, second_argument, mod_argument.size());
			MemoryReading(first_argument, mw_elements, result);
			MemoryReading(second_argument, mw_elements, result);

			first_argument = ReversePolishNotation(first_argument);
			second_argument = ReversePolishNotation(second_argument);

			first_argument_float = CalculationRPN(first_argument);
			second_argument_float = CalculationRPN(second_argument);

			if (second_argument_float == 0)
			{
				throw "Error: invalid expression. Impossible to divide by zero.";
			}

			float_result = std::fmod(first_argument_float, second_argument_float);

			FloatToString(float_result, calculation_result_string);

			if (float_result <= 0)
			{
				AddBracket(calculation_result_string);
				NegateFormation(calculation_result_string);
			}

			input_string.erase(begin_position, end_position - begin_position);
			input_string.insert(begin_position, calculation_result_string);
		}
		else
		{
			break;
		}
	}
}


void Calculator::SelectionModArguments(std::string match_string, std::string &first_argument, std::string &second_argument, size_t match_string_size)
{
	for (int i = 1; i < match_string.size(); i++) //Pass '('
	{
		while (match_string.at(i) != ',')
		{
			first_argument.push_back(match_string.at(i));

			if (i != match_string.size() - 1)
				i++;
			else
				throw "Error: invalid expression.";
		}

		if (first_argument.empty())
			throw "Error: invalid expression.";

		i++; //Pass ','

		CommaCheck(match_string.substr(i, match_string.size() - i));

		for (int j = i; i < match_string_size - 1; j++) //Pass ')'
		{
			second_argument.push_back(match_string.at(j));
			i++;
		}

		if (second_argument.empty())
			throw "Error: invalid expression.";

		break;
	}
}

size_t Calculator::FindingEndOfArgument(size_t begin_position, size_t skipped_string_size, std::string search_string)
{
	size_t end_position = 0;
	std::stack<char> bracket_stack;

	for (int i = begin_position + skipped_string_size; i <= search_string.size(); i++)
	{
		while (search_string.at(i) != ')')
		{
			if (search_string.at(i) == '(')
			{
				bracket_stack.push(search_string.at(i));
			}
			i++;
		}

		if (search_string.at(i) == ')')
		{
			if (!bracket_stack.empty())
				bracket_stack.pop();
			else
				throw "Error: invalid expression.";
		}

		if (bracket_stack.empty())
		{
			end_position = ++i;
			break;
		}
	}

	return end_position;
}

void Calculator::FloatToString(float &float_result, std::string &calculation_result_string)
{
	std::stringstream result_stream;
	result_stream << float_result;
	result_stream >> calculation_result_string;
	result_stream.clear();
}


int Calculator::Prioritization(char symbol)
{
	switch (symbol)
	{
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	case '(':
		return 0;
	case ')':
		return 1;
	case '^':
		return 4;
	}
}

std::string Calculator::ReversePolishNotation(std::string input_string)
{
	std::vector<char> operators = { '+','-', '(', ')', '*', '/', '^', '=' };
	std::vector<char>::iterator it;
	std::stack<char> operators_stack;
	std::string out_string;

	for (int i = 0; i < input_string.size(); i++)
	{
		it = std::find(operators.begin(), operators.end(), input_string.at(i));
		if (it != operators.end())
		{
			if (i != 0 && isdigit(input_string.at(i - 1)))
			{
				out_string.append(" "); //???????? ?????????? ????? ??? ????????
			}

			if (*it == '(')
			{
				operators_stack.push(*it);
			}

			if (*it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '^')
			{
				if (operators_stack.empty())
				{
					operators_stack.push(*it);
				}
				else
				{
					if (Prioritization(*it) > Prioritization(operators_stack.top()))
					{
						operators_stack.push(*it);
					}
					else
					{
						while (!operators_stack.empty() && Prioritization(operators_stack.top()) >= Prioritization(*it))
						{
							out_string.push_back(operators_stack.top());
							operators_stack.pop();
						}
						operators_stack.push(*it);
					}
				}
			}

			if (*it == ')')
			{
				while (operators_stack.top() != '(')
				{
					out_string.push_back(operators_stack.top());
					operators_stack.pop();
				}
				operators_stack.pop();
			}
		}
		else
		{
			if (isdigit(input_string.at(i)) || input_string.at(i) == '.')
			{
				out_string.push_back(input_string.at(i));
			}
			else
			{
				throw "Error: invalid expression.";
			}
		}
	}

	while (!operators_stack.empty())
	{
		out_string.push_back(operators_stack.top());
		operators_stack.pop();
	}

	return out_string;
}

float Calculator::CalculationRPN(std::string input_string)
{
	std::stack<float> number_stack;

	float right_operand, left_operand;
	float calculation_result;
	float number_float;

	if (DigitCheck(input_string) == true)
	{
		std::istringstream number_stream(input_string);
		number_stream >> number_float;
		return number_float;
	}

	int i = 0;
	while (i != input_string.size())
	{
		std::string number_string;

		while (isdigit(input_string.at(i)) || input_string.at(i) == '.')
		{
			number_string.push_back(input_string.at(i));
			++i;
		}

		if (isdigit(input_string.at(i - 1)))
		{
			std::istringstream number_stream(number_string);
			number_stream >> number_float;
			number_stack.push(number_float);
		}

		if (isspace(input_string.at(i)))
		{
			i++;
		}

		if (i == input_string.size())
		{
			return number_stack.top();
		}

		if (input_string.at(i) == '+' || input_string.at(i) == '-' ||
			input_string.at(i) == '*' || input_string.at(i) == '/' ||
			input_string.at(i) == '^')
		{
			CalculationOperators(input_string.at(i), right_operand, left_operand, calculation_result, number_stack);
			i++;
		}
	}
	return number_stack.top();
}

void Calculator::CalculationOperators(char input_string_element, float &right_operand, float &left_operand, float &calculation_result, std::stack<float> &number_stack)
{
	switch (input_string_element)
	{
	case '+':
		right_operand = number_stack.top(); number_stack.pop();
		left_operand = number_stack.top(); number_stack.pop();
		calculation_result = left_operand + right_operand;
		number_stack.push(calculation_result);
		break;
	case '-':
		right_operand = number_stack.top(); number_stack.pop();
		left_operand = number_stack.top(); number_stack.pop();
		calculation_result = left_operand - right_operand;
		number_stack.push(calculation_result);
		break;
	case '*':
		right_operand = number_stack.top(); number_stack.pop();
		left_operand = number_stack.top(); number_stack.pop();
		calculation_result = left_operand * right_operand;
		number_stack.push(calculation_result);
		break;
	case '/':
		right_operand = number_stack.top(); number_stack.pop();

		if (right_operand == 0)
		{
			throw "Error: invalid expression. Impossible to divide by zero.";
		}

		left_operand = number_stack.top(); number_stack.pop();
		calculation_result = left_operand / right_operand;
		number_stack.push(calculation_result);
		break;
	case '^':
		right_operand = number_stack.top(); number_stack.pop();
		left_operand = number_stack.top(); number_stack.pop();
		calculation_result = std::pow(left_operand, right_operand);
		number_stack.push(calculation_result);
		break;
	}
}


void Calculator::StringToFloat(std::string input_string, float &n, size_t substr_begin_position)
{
	std::istringstream number_stream(input_string.substr(substr_begin_position, input_string.size()));
	number_stream >> n;
	number_stream.clear();
}

void Calculator::MemoryWriting(std::string input_string, std::vector<float> &mw_elements, float result)
{
	if (isnan(result))
		throw "Error: You cannot use the MW operation without having the result of the calculation.";

	SpaceDelete(input_string);

	std::string mw_string = { "MW" };

	if (input_string.size() > 2 && input_string.at(mw_string.size()) == '[')
	{
		float n;
		size_t substr_begin_position = mw_string.size() + 1;

		StringToFloat(input_string, n, substr_begin_position);
		if (n <= mw_elements.size())
			mw_elements.at(n) = result;
		else
			throw "Error: exceeding the limit. The maximum number of elements is 20.";
	}
	else if (input_string == "MW")
	{
		mw_elements.at(0) = result;
	}
	else
	{
		throw "Error: invalid expression.";
	}
}

void Calculator::MemoryReading(std::string &input_string, std::vector<float> &mw_elements, float result)
{
	std::string mr_string = { "MR" };
	std::string::iterator it;
	std::string mr_insert_string;
	
	size_t begin_position = 0;
	size_t end_position = 0;

	float mr;

	for (int i = 0; i < input_string.size(); i++)
	{
		it = std::search(input_string.begin(), input_string.end(), mr_string.begin(), mr_string.end());
		if (it != input_string.end())
		{
			if (isnan(result))
				throw "Error: You cannot use the MR operation without having the result of the calculation.";

			begin_position = std::distance(input_string.begin(), it);
						
			if (input_string.size() > 2 && input_string.at(begin_position + mr_string.size()) == '[')
			{
				float n;
				size_t substr_begin_position = begin_position + mr_string.size() + 1; //Pass '['
				
				StringToFloat(input_string, n, substr_begin_position);
				if (n <= mw_elements.size())
				{
					mr = mw_elements.at(n);
		
					if (isnan(mr))
						throw "Error: You are trying to call an empty cell in MR operation.";

					if (input_string.size() >= 6 && input_string.at(begin_position + 5) == ']') //n = 10 to 20
						end_position = begin_position + 5;
					else if (input_string.size() >= 5 && input_string.at(begin_position + 4) == ']') //n = 0 to 9
						end_position = begin_position + 4;
					else
						throw "Error: invalid expression.";

					input_string.erase(begin_position, end_position - begin_position + 1);
					FloatToString(mr, mr_insert_string);
					input_string.insert(begin_position, mr_insert_string);
				}	
				else
				{
					throw "Error: exceeding the limit. The maximum number of elements is 20.";
				}	
			}
			else
			{
				mr = mw_elements.at(0);
				if (isnan(mr))
					throw "Error: You are trying to call an empty cell in MR operation.";
				
				input_string.erase(begin_position, mr_string.size());
				FloatToString(mr, mr_insert_string);
				input_string.insert(begin_position, mr_insert_string);
			}
		}
		else
		{
			break;
		}
	}
}
