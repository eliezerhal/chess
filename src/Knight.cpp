#include "Knight.h"
#include "Controller.h"

bool Knight::m_registerit = Factory::registerit("Knight",
	[]() -> std::unique_ptr<ObjGame>
	{ return std::make_unique<Knight>(); });
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool Knight::checkingLoc(std::pair<char, size_t> loc)
{
	if (!ObjGame::checkingLoc(loc))
		return false;
	if ((loc.first == m_loc.first + 1 || loc.first == m_loc.first - 1) && (loc.second == (int)m_loc.second + 2 || loc.second == (int)m_loc.second - 2))
		return true;
	else if ((loc.first == m_loc.first + 2 || loc.first == m_loc.first - 2) && (loc.second == (int)m_loc.second + 1 || loc.second == (int)m_loc.second - 1))
		return true;
	return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Knight::initData(std::pair<bool, sf::Vector2f> pair)
{
	initLoc(pair);
	m_name = Obj::Knight;
	m_score = 3;
	if (pair.first)
		initTexture(Resources::instance().knightTexture());
	else
		initTexture(Resources::instance().knightBTexture());
}
