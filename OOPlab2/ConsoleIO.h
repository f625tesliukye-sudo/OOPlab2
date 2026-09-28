#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

class ConsoleIO
{
public:
	static int GetInt(const std::string& prompt, int minValue, int maxValue)
	{
		while (true)
		{
			std::cout << prompt;
			std::string line;
			if (!std::getline(std::cin, line))
			{
				std::cout << "\nВведення завершено.\n";
				std::exit(0);
			}
			try
			{
				size_t pos = 0;
				int value = std::stoi(line, &pos);
				while (pos < line.size() && std::isspace((unsigned char)line[pos]))
					pos++;
				if (pos == line.size() && value >= minValue && value <= maxValue)
					return value;
			}
			catch (...) {}

			std::cout << "\n\tНЕКОРЕКТНИЙ ВВІД! Очікується ціле число від "
			          << minValue << " до " << maxValue << ". Повторіть.\n";
		}
	}
};
