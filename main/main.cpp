#include "../Calculator_lib/Calculator.h"
#include <windows.h>

int main()
{
	std::string mw_string = { "MW" };

	for (;;)
	{
		std::string input_string = GettingString();

		if (input_string == "end")
			break;

		try
		{
			float result = RunCalculator(input_string);
			if (std::search(input_string.begin(), input_string.end(),
				mw_string.begin(), mw_string.end()) == input_string.end())
			{
				std::cout << "ans \n \n" << result << std::endl;
			}
		}
		catch (char *exception)
		{
			std::cout << exception << std::endl;
			std::cout << "Try again." << std::endl;
			return -1;
		}
		catch (std::exception &e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
			return -1;
		}
	}
    return 0;
}