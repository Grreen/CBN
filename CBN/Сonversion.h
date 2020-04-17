#pragma once

#include <string>
#include <iostream>
#include <math.h>
#include <Windows.h>

using namespace std;

class Ñonversion
{
	template <class T>
	static string IntPart(T value);

	template <class T>
	static string FractionalPart(T value);

	static string CalculationExponent(string intPart, string fractionalPart, int type);
	static string CalculationMantissa(string intPart, string fractionalPart, int type);

	template <class T>
	static string StandartConvert(T value);
	template <class T>
	static string UnionConvert(T value);

	static void EditWindow(string typeValue, string typeConvert, double value);

public:
	template <class T>
	static string ConvertToBinary(T value, string typeConvert, string typeValue);
	static string ConvertToBinary(int argc, char* argv[]);
};

//-------------------------------------------------------------------------------------------------------------------//
template <class T>
string Ñonversion::ConvertToBinary(T value, string typeConvert, string typeValue)
{
	if ((typeValue != "double") && (typeValue != "float"))
		return "Error. Unknown value type.";

	if (typeConvert == "classic")
	{
		if (typeValue == "float")
			return StandartConvert((float)value);
		else if (typeValue == "double")
			return StandartConvert((double)value);
	}
	else if (typeConvert == "union")
	{
		if (typeValue == "float")
			return UnionConvert((float)value);
		else if (typeValue == "double")
			return UnionConvert((double)value);
	}
	else
		return "Error. Unknown conversion type.";
}

template <class T>
string Ñonversion::StandartConvert(T value)
{

	EditWindow(string(typeid(T).name()), "classic", (double)value);


	string result;
	
	if (value > 0)
		result += "0";
	else
		result += "1";

	int type = 0;
	if (string(typeid(value).name()) == "double")
		type = 1;

	result += CalculationExponent(IntPart(value), FractionalPart(value), type);
	result += CalculationMantissa(IntPart(value), FractionalPart(value), type);		

	int temp = 0;
	for (int i = 0; i < result.length(); i++)
	{
		temp++;
		if (temp == 9)
		{
			result.insert(i," ");
			temp = 0;
		}
	}

	return result;
}

template <class T>
string Ñonversion::UnionConvert(T value)
{
	EditWindow(string(typeid(T).name()), "union", (double)value);


	union
	{
		T value;
		char bytes[sizeof(T)];
	}temp;

	bool fl = false;

	temp.value = value;
	string str;

	if ((string(typeid(value).name()) == "float") || (string(typeid(value).name()) == "double"))
	{
		for (int i = sizeof(T) - 1; i >= 0; i--)
		{
			for (int j = 7; j >= 0; j--)
				str += to_string(((temp.bytes[i] >> j) & 1));
			str += " ";
		}
		return str;
	}
	return "Error";
}

enum types { Float = 0, Double };

template <class T>
string Ñonversion::IntPart(T value)
{
	int intPart = floor(abs(value));
	string result;

	if (intPart != 0)
		while (intPart > 0)
		{
			int temp = intPart % 2;
			if (temp == -1)
				temp = 1;
			result += (temp + '0');
			intPart /= 2;
		}
	else
		result = "0";


	reverse(result.begin(), result.end());

	return result;
}

template <class T>
string Ñonversion::FractionalPart(T value)
{
	string result;
	double intPart, fractionalPart;

	fractionalPart = modf(abs(value), &intPart);

	if (fractionalPart != 0)
	{
		int temp = 23;
		if (string(typeid(value).name()) == "double")
			temp = 52;
		for (;;)
		{
			while (fractionalPart != 1 && result.length() < temp)
			{
				fractionalPart *= 2;
				result += (int)(fractionalPart) + '0';
				if (fractionalPart > 1)
					fractionalPart = modf(fractionalPart, &intPart);
			}
			return result;
		}
	}
	else
	{
		result = "0";
		return result;
	}

}

