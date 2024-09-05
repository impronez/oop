#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	auto maxElemIt = arr.begin();
	for (auto it = arr.begin(); it != arr.end(); ++it)
	{
		if (less(*maxElemIt, *it))
		{
			maxElemIt = it;
		}
	}

	maxValue = *maxElemIt;

	return true;
}