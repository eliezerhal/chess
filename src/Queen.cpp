#include "Queen.h"
#include "Controller.h"

bool Queen::m_registerit = Factory::registerit("Queen",
	[]() -> std::unique_ptr<ObjGame>
	{ return std::make_unique<Queen>(); });
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Queen::checkingLoc(std::pair<char, size_t> loc)
{
	/*bool test = Controller::getInstance().getTestOtherSide();
	bool val = Controller::getInstance().getQueue();
	if (!test)
		if (!m_checking.isEmpty(loc, val))
			return false;*/
	if (!ObjGame::checkingLoc(loc))
		return false;
	return ((loc.first == m_loc.first || loc.second == m_loc.second) && m_checking.allEmpty(m_loc, loc)) ||
		((std::abs(loc.first - m_loc.first) == std::abs((int)(loc.second - m_loc.second))) && m_checking.allEmpty(m_loc, loc));
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Queen::initData(std::pair<bool, sf::Vector2f> pair)
{
	initLoc(pair);
	m_name = Obj::Queen;
	m_score = 9;
	if (pair.first)
		initTexture(Resources::instance().queenTexture());
	else
		initTexture(Resources::instance().queenBTexture());
}