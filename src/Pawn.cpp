#include "Pawn.h"
#include "Controller.h"
#include <iostream>

constexpr int MENU_WIDE = 840;
constexpr int MENU_HEIGHT = 1200;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Pawn::m_registerit = Factory::registerit("Pawn",
	[]() -> std::unique_ptr<ObjGame>
	{ return std::make_unique<Pawn>(); });
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Pawn::checkingLoc(std::pair<char, size_t> loc)
{
	bool test = Controller::getInstance().getTestOtherSide();
	if (!ObjGame::checkingLoc(loc))
		return false;
	int x;
	bool queue;
	if (Controller::getInstance().getRecursive())
		queue = Controller::getInstance().getTempQueue();
	else
		queue = Controller::getInstance().getQueue();
	if(!test)queue ? x = -1 : x = 1;
	else
		queue ? x = 1 : x = -1;
	if ((!test && !m_checking.isEmpty(loc, !queue)) || (test && !m_checking.isEmpty(loc, queue)))
	{
		if (std::abs(loc.first - m_loc.first) == 1 && loc.second == m_loc.second + x)
		{
			if (checkinCoronation(loc, queue) && !Controller::getInstance().getTest())
				coronation(loc);
			return true;
		}
		return false;
	}
	if ((std::abs(loc.first - m_loc.first) == 1 && loc.second == m_loc.second + x) && enPassant(loc))
	{
		if (checkinCoronation(loc, queue) && !Controller::getInstance().getTest())
			coronation(loc);
		return true;
	}
	if (loc.first == m_loc.first && loc.second == m_loc.second + x)
	{
		if (checkinCoronation(loc, queue) && !Controller::getInstance().getTest())
			coronation(loc);
		return true;
	}
	if (m_first && loc.first == m_loc.first && loc.second == m_loc.second + (x * 2))
	{
		Loc otherLoc = std::make_pair(loc.first, loc.second - x);
		if (m_checking.isEmpty(otherLoc, queue) && m_checking.isEmpty(otherLoc, !queue))
			return true;
	}
	return false;

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Pawn::checkinCoronation(Loc loc, bool queue)
{
	size_t line;
	queue ? line = 1 : line = 8;
	return loc.second == line;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Pawn::coronation(Loc loc)
{
	Board::getInstance().add(Menu::getInstance().coronation(),m_loc, loc);		
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Pawn::enPassant(std::pair<char, size_t> loc)
{
	int x, y;
	bool queue = Controller::getInstance().getQueue();
	if (Controller::getInstance().getRecursive())
		queue = Controller::getInstance().getAlgBoard().getQueue();
	queue ? (x = 1, y = 3) : (x = -1, y = 6);
	if (loc.second != y)
		return false;
	if (Controller::getInstance().whoIs(std::make_pair(loc.first, loc.second + x), !queue) != Obj::Pawn)
		return false;
	Pawn* p = dynamic_cast<Pawn*>(Board::getInstance().getObjects(!queue)[loc.first - 'a' + 8].get());
	if (p && !p->isSecond())
		return false;
	auto move = sf::Vector2f(((float)loc.first - 'a') * PLACE_PIECES, ((float)loc.second - 1 + x) * PLACE_PIECES);
	if (!Controller::getInstance().getTest())
		eatTheEnnemy(move, queue);
	return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Pawn::initData(std::pair<bool, sf::Vector2f> pair)
{
	initLoc(pair);
	m_name = Obj::Pawn;
	m_score = 1;
	if (pair.first)
		initTexture(Resources::instance().pawnTexture());
	else
		initTexture(Resources::instance().pawnBTexture());
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~