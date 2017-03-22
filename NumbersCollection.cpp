#include "NumbersCollection.h"
#include <algorithm>

void NumbersCollection::push(int value)
{
	std::lock_guard<std::mutex> g(m);

	if (cur < data.size())
		data[cur] = value;
	else
		data.push_back(value);

	cur++;
}

double NumbersCollection::getMedian()
{
	/* »спользуетс€ что бы не вычисл€ть медиану при каждом обращении.
	 ≈сли медиана была рассчитана раньше и коллекци€ не мен€лась то
	 возвращаетс€ старое значение.
	*/
	static int lastCount{ 0 };

	if (lastCount != cur)
	{
		std::lock_guard<std::mutex> g(m);

		if (cur != data.size())
			data.resize(cur);
		
		std::sort(data.begin(), data.end());

		int middle = data.size() / 2 - 1;

		if (data.size() % 2 == 0)
			median = (data[middle] + data[middle + 1]) / 2.0;
		else
			median = data[middle];

		lastCount = cur;
	}

	return median;
}

double NumbersCollection::getAverage()
{
	/* »спользуетс€ что бы не вычисл€ть среднее значение при каждом обращении.
	≈сли медиана была рассчитана раньше и коллекци€ не мен€лась то
	возвращаетс€ старое значение.
	*/
	static int lastCount{ 0 };

	if (lastCount != cur)
	{
		std::lock_guard<std::mutex> g(m);

		if (cur != data.size())
			data.resize(cur);

		average = 0;
		auto size = data.size();

		for (auto val : data)
			average += val / (float) size;

		lastCount = cur;
	}

	return average;
}

double NumbersCollection::getMax()
{
	/* »спользуетс€ что бы не вычисл€ть максимальный элемент при каждом обращении.
	≈сли медиана была рассчитана раньше и коллекци€ не мен€лась то
	возвращаетс€ старое значение.
	*/
	static int lastCount{ 0 };

	if (lastCount != cur)
	{
		std::lock_guard<std::mutex> g(m);

		if (cur != data.size())
			data.resize(cur);

		max = *std::max_element(data.begin(), data.end());

		lastCount = cur;
	}

	return max;
}

double NumbersCollection::getMin()
{
	/* »спользуетс€ что бы не вычисл€ть минимальный элемент при каждом обращении.
	≈сли медиана была рассчитана раньше и коллекци€ не мен€лась то
	возвращаетс€ старое значение.
	*/
	static int lastCount{ 0 };

	if (lastCount != cur)
	{
		std::lock_guard<std::mutex> g(m);

		if (cur != data.size())
			data.resize(cur);

		min = *std::min_element(data.begin(), data.end());
		lastCount = cur;
	}

	return min;
}
