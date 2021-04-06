#include "Checking.h"
#include "Controller.h"
bool Checking::checkCol(Loc from, Loc to, bool queue)
{
	int x;
	from.second < to.second ? x = 1 : x = -1;
	int length = std::abs((int)from.second - (int)to.second);
	Loc loc = from;
	for (size_t i = 0; i < length; i++)
	{
		loc.second += x;
		if (!checkLoc(loc, to, queue))
			return false;
	}
	return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Checking::checkRow(Loc from, Loc to, bool queue)
{
	int x;
	from.first < to.first ? x = 1 : x = -1;
	int length = std::abs((int)from.first - (int)to.first);
	Loc loc = from;
	for (size_t i = 0; i < length; i++)
	{
		loc.first += x;
		if (!checkLoc(loc, to, queue))
			return false;
	}
	return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Checking::checkDiagonal(Loc from, Loc to, bool queue)
{
	int x, y;
	from.first < to.first ? x = 1 : x = -1;
	from.second < to.second ? y = 1 : y = -1;
	int length = std::abs((int)from.first - (int)to.first);
	Loc loc = from;
	for (size_t i = 0; i < length; i++)
	{
		loc.first += x;
		loc.second += y;
		if (!checkLoc(loc, to, queue))
			return false;
	}
	return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Checking::checkLoc(Loc loc, Loc to, bool queue)
{
	if (Controller::getInstance().getTest())
		if (loc != to && !isEmpty(loc, queue))
			return false;
	if (!Controller::getInstance().getTest())
		if (!isEmpty(loc, queue))
			return false;
	if (loc != to && !isEmpty(loc, !queue))
		return false;
	return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Checking::allEmpty(Loc from, Loc to)
{
	bool queue;
	!Controller::getInstance().getRecursive() ? queue = Controller::getInstance().getQueue() : queue = Controller::getInstance().getTempQueue();
	if (!Controller::getInstance().getOwner(from))
		queue = !queue;
	if (from == to)
		return false;
	if (from.second == to.second)
		return checkRow(from, to, queue);
	if (from.first == to.first)
		return checkCol(from, to, queue);
	return checkDiagonal(from, to, queue);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Checking::isEmpty(std::pair<char, size_t>& loc, bool queue)
{
	if (!Controller::getInstance().getRecursive())
		return Board::getInstance().isEmpty(loc, queue);
	else
		return Controller::getInstance().getAlgBoard().isEmpty(loc, queue);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Checking::isArrEmpty()
{
	size_t count = 0;
	for (auto& i : Board::getInstance().getObjects(Controller::getInstance().getQueue()))
		if (!i)
			count++;
	return count == 15;
}
