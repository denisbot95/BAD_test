#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>
#include "NumbersCollection.h"

using namespace std;

bool isNumber(string s);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	
	if (argc == 1)
	{
		cerr << "Файл не задан." << endl;
		return 0;
	}

	auto beginTime = chrono::system_clock::now();
	
	ifstream file(argv[1]);

	string line;
	NumbersCollection nc;

	while (!file.eof())
	{
		getline(file, line);
		if (!isNumber(line))
		{
			if (file.eof())
				break;

			cerr << "Ошибка. " << line << " не число." << endl;
			system("pause");
			return 0;
		}
		nc.push(atoi(line.c_str()));
	}
	
	file.close();

	cout.precision(10);

	cout << "min = " << nc.getMin() << endl
		<< "max = " << nc.getMax() << endl
		<< "avg = " << nc.getAverage() << endl
		<< "med = " << nc.getMedian() << endl;

	auto endTime = chrono::system_clock::now();
	auto time = chrono::duration_cast<chrono::seconds>(endTime - beginTime).count();
	cout << "Затраченное время: " << time << "секунд" << endl;
	
	system("pause");
}

bool isNumber(string s) 
{
	tr1::regex regex("^[-]?\\d+$");
	return tr1::regex_match(s, regex);
}
