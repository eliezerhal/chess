#pragma once
#include <iostream>

class Checking
{
public:
	using Loc = std::pair<char, size_t>;
	Checking() = default;
	~Checking() = default;
	bool checkCol(Loc from, Loc to, bool queue);
	bool checkRow(Loc from, Loc to, bool queue);
	bool checkDiagonal(Loc from, Loc to, bool queue);
	bool checkLoc(Loc loc, Loc to, bool queue);
	bool allEmpty(Loc from, Loc to);
	bool isEmpty(std::pair<char, size_t>& loc, bool queue);
	bool isArrEmpty();
};