#pragma once

#include <string>;
#include <vector>;
class StringUtils
{
public:

	static int len(std::string str)
	{
		int length = 1;
		for (int i = 0; str[i] != '\0'; i++)
		{
			length++;

		}
		return length;
	}

	static std::vector<std::string> split(std::string str, char seperator)
	{
		int currIndex = 0, i = 0;
		int startIndex = 0, endIndex = 0;
		std::vector<std::string> strings;

		for (int i = 0; i < len(str); i++) {
			if (str[i] == seperator || i == len(str))
			{
				endIndex = i;
				std::string subStr = "";
				subStr.append(str, startIndex, endIndex - startIndex);
				if (subStr != "$") {
					strings.push_back(subStr);
				}
				startIndex = endIndex + 1;
			}
		}
		std::string subStr = "";
		subStr.append(str, startIndex, endIndex - startIndex);
		strings.push_back(subStr);
		return strings;
	}
};

