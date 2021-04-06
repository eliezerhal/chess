#include "Bishop.h"
#include "Controller.h"

bool Bishop::m_registerit = Factory::registerit("Bishop",
	[]() -> std::unique_ptr<ObjGame>
	{ return std::make_unique<Bishop>(); });

bool Bishop::checkingLoc(std::pair<char, size_t> loc)
{
	if (!ObjGame::checkingLoc(loc))
		return false;
	return (std::abs(loc.first - m_loc.first) == std::abs((int)(loc.second - m_loc.second))) &&
		(m_checking.allEmpty(m_loc, loc));
}

void Bishop::initData(std::pair<bool, sf::Vector2f> pair)
{
	initLoc(pair);
	m_name = Obj::Bishop;
	m_score = 3;
	if (pair.first)
		initTexture(Resources::instance().bishopTexture());
	else
		initTexture(Resources::instance().bishopBTexture());
}