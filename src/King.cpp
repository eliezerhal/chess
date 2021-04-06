#include "King.h"
#include "Controller.h"

bool King::m_registerit = Factory::registerit("King",
	[]() -> std::unique_ptr<ObjGame>
	{ return std::make_unique<King>(); });


bool King::checkingLoc(std::pair<char, size_t> loc)
{
	bool queue = Controller::getInstance().getQueue();
	if (Controller::getInstance().getRecursive())
		queue = Controller::getInstance().getTempQueue();
	if(!(Board::getInstance().getObj(loc, queue) == ObjGame::Obj::Non || Board::getInstance().getObj(loc, queue) == ObjGame::Obj::King))
		return false;
	if (loc != m_loc || Controller::getInstance().getTest())
		for (auto& i : Board::getInstance().getObjects(!queue))
		{
			if (King* k = dynamic_cast<King*>(i.get()))
			{
				if (!isEmptyFromKing(loc, k))
					return false;
				continue;
			}
			if (i && i->checkingLoc(loc))
				return false;
		}
	if (checkingCastling(loc))
	{
		if (!Controller::getInstance().getTest())
			castling(loc);
		return true;
	}
	return (std::abs(loc.first - m_loc.first) <= 1 && std::abs((int)(loc.second - m_loc.second)) <= 1);
}

bool King::isEmptyFromKing(std::pair<char, size_t> loc, King* k)
{
	if (std::abs(loc.first - k->getLoc().first) <= 1 && std::abs((int)(loc.second - k->getLoc().second)) <= 1)
		return false;
	return true;
}

bool King::checkingCastling(std::pair<char, size_t> loc)
{
	if (m_check)
		return false;
	if (!m_first)
		return false;
	char key = getKey();
	key == 'b' ? (loc.first == key ? loc.first -= 1 : loc.first += 2) : (loc.first == key ? loc.first -= 2 : loc.first += 1);
	int x = 1;
	if (m_loc.first < loc.first)
		x = -1;
	auto checkLoc = std::make_pair(loc.first + x, loc.second);
	if (!m_checking.allEmpty(this->m_loc, checkLoc))
		return false;
	if (Controller::getInstance().whoIs(loc, Controller::getInstance().getQueue()) != Obj::Rook)
		return false;
	if (!Board::getInstance().getObjects(Controller::getInstance().getQueue())[loc.first - 'a']->isFirst())
		return false;
	if (!Controller::getInstance().getRecursive())
		if (!Board::getInstance().getObjects(Controller::getInstance().getQueue())[loc.first - 'a']->isFirst())
			return false;
	if (Controller::getInstance().getRecursive())
		if (!Controller::getInstance().getAlgBoard().getObjects(Controller::getInstance().getTempQueue())[loc.first - 'a']->isFirst())
			return false;
	return true;
}

void King::castling(std::pair<char, size_t> loc)
{
	setLoc(loc);
	auto temp = sf::Vector2f(((float)loc.first - 'a') * PLACE_PIECES, ((float)loc.second - 1) * PLACE_PIECES);
	move(temp);
	char key = getKey();
	loc.first == key ? moveRook(std::make_pair(key + 1, loc.second)) : moveRook(std::make_pair(key + 3, loc.second));
}

void King::moveRook(std::pair<char, size_t> loc)
{
	char key = getKey() + 1;
	int y;
	loc.first == key ? y = 0 : y = 7;
	Board::getInstance().getObjects(Controller::getInstance().getQueue())[y]->setLoc(loc);
	auto temp = sf::Vector2f(((float)loc.first - 'a') * PLACE_PIECES, ((float)loc.second - 1) * PLACE_PIECES);
	Board::getInstance().getObjects(Controller::getInstance().getQueue())[y]->move(temp);
}

char King::getKey()
{
	if (Controller::getInstance().getColor().first.first == "white")
		return 'b';
	return 'c';
}

void King::initData(std::pair<bool, sf::Vector2f> pair)
{
	initLoc(pair);
	m_name = Obj::King;
	m_score = 2;
	if (pair.first)
		initTexture(Resources::instance().kingTexture());
	else
		initTexture(Resources::instance().kingBTexture());
}