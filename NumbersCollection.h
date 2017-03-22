#pragma once
#include <vector>
#include <limits>
#include <mutex>

class NumbersCollection {
public:
	
	NumbersCollection() = default;

	/*
		 онструктор принимающий начальное количество элементов в выборке.
		ѕозвол€ет избежать задержек при перераспределении пам€ти.
	*/
	NumbersCollection(int size) : data(size)
	{  }

	void push(int value);

	double getMedian();
	double getAverage();
	double getMax();
	double getMin();

private:
	std::vector<int> data;
	size_t cur{ 0 };

	int min{ INT_MAX }, max { INT_MIN };

	double median{ NAN }, average{ NAN };

	std::mutex m;
};