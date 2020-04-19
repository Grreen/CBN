#include "Ñonversion.h"
#include <algorithm>
#include <iomanip>

string Ñonversion::CalculationExponent(string intPart, string fractionalPart, int type)
{
	string exponent;

	if (intPart.size() > 0)
	{
		int exp = intPart.size() - 1;
		if (type == Float)
			exp += 127;
		else if (type == Double)
			exp += 1023;

		while (exp > 0)
		{
			exponent += (exp % 2 + '0');
			exp /= 2;
		}

		reverse(exponent.begin(), exponent.end());
		return exponent;
	}
	else
		CalculationExponent(fractionalPart, intPart, type);


}

string Ñonversion::CalculationMantissa(string intPart, string fractionalPart, int type)
{
	string mantissa;

	if (intPart.size() > 0)
	{
		mantissa += intPart.erase(0, 1);
		mantissa += fractionalPart;
	}
	else
	{
		mantissa += intPart;
		mantissa += fractionalPart.erase(0, 1);
	}
	if (type == Float || type == Double)
	{
		int beg = 23;
		if (type == Double)
			beg = 52;
		int temp = beg - mantissa.size();;
		for (unsigned int i = 0; i < temp; i++)
			mantissa += '0';
	}

	return mantissa;

}

void Ñonversion::EditWindow(string typeValue, string typeConvert, double value)
{
	wchar_t szTITLE[] = L"CONVERTER";

	int temp = 1;
	int _temp = 0;
	if (typeValue == "double")
	{
		temp = 2;
		_temp = 45;
	}
	
	SetConsoleTitle(szTITLE);
	Sleep(1.5);
	MoveWindow(FindWindow(NULL, szTITLE), 1, 1, 440 * temp - _temp, 220, false);

	for (int i = 0; i < 36 * temp; i++)
		cout << "-";
	cout << endl;
	system("cls");

	string _typeValue, _typeConvert;

	transform(typeValue.begin(), typeValue.end(), typeValue.begin(), toupper);
	transform(typeConvert.begin(), typeConvert.end(), typeConvert.begin(), toupper);

	cout << typeConvert << " conversionof a number" << endl;
	cout << "'" << value << "'" << endl;
	cout << "from " << typeValue << " to binary." << endl;

	for (int i = 0; i < 36 * temp; i++)
		cout << "-";
	cout << endl;
}

string Ñonversion::ConvertToBinary(int argc, char* argv[])
{
	string value, typeValue, typeConvert;

	for (int i = 0; i < argc; i++)
	{
		string temp = argv[i];
		if (temp.find("--number=") != string::npos)
			value =  temp.substr(temp.find('=') + 1, temp.length() - 1);
		else if (temp.find("--number") != string::npos && ++i < argc)
			value = string(argv[i]);

		if (temp.find("--method=") != string::npos)
			typeConvert = temp.substr(temp.find('=') + 1, temp.length() - 1);
		else if (temp.find("--method") != string::npos && ++i < argc)
			typeConvert = string(argv[i]);

		if (temp.find("--type=") != string::npos)
			typeValue = temp.substr(temp.find('=') + 1, temp.length() - 1);
		else if (temp.find("--type") != string::npos && ++i < argc)
			typeValue = string(argv[i]);
	}

	if ((typeValue != "double") && (typeValue != "float"))
	{
		cout << "Type Value:" << typeValue << "!" << endl;
		return "Error. Unknown value type.";
	}
	if ((typeConvert != "union") && (typeConvert != "classic"))
		return "Error. Unknown conversion type.";



	if (typeValue == "float")
		return ConvertToBinary(stof(value), typeConvert, typeValue);
	else if (typeValue == "double")
		return ConvertToBinary(stod(value), typeConvert, typeValue);


}
