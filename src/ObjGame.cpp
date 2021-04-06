#include "ObjGame.h"
#include "King.h"
#include "Controller.h"
#include <iterator>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ObjGame::move(sf::Vector2f& loc)
{
	if (isFirst())
		m_first = false;
	m_sprite.setPosition(loc);
	m_location = loc;
}
bool ObjGame::checkingLoc(std::pair<char, size_t> loc)
{
	bool test = Controller::getInstance().getTestOtherSide();
	bool val = Controller::getInstance().getQueue();
	if (!test)
		if (!m_checking.isEmpty(loc, val))
			return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ObjGame::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ObjGame::setposition(sf::Vector2f position)
{
	m_sprite.setPosition(m_location);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ObjGame::initTexture(const sf::Texture& picture)
{
	m_sprite.setTexture(picture);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ObjGame::checkAllMovesLegal(ObjGame* og)
{
	allMovesLegal.clear();
	for(int i = 0; i < 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			auto loc = std::pair<char, size_t>(i + 'a', j);
			if (loc == og->getLoc())
				continue;
			if (Controller::getInstance().isCheck(Controller::getInstance().getQueue()))
			{
				if (checkingLoc(loc) && isCheckCanceled(og, loc))
					allMovesLegal.push_back(loc);
				continue;
			}
			if (checkingLoc(loc))
				allMovesLegal.push_back(loc);				
		}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool ObjGame::isCheckCanceled(ObjGame* og, pair loc)
{
	auto locOfTreatening = Controller::getInstance().getLocOfTreatening();
	if (og->checkingLoc(locOfTreatening))
	{
		if (King* k = dynamic_cast<King*>(og))
			return checkingTemp(og, loc);
		return true;
	}
	return checkingTemp(og, loc);
}

bool ObjGame::checkingTemp(ObjGame* og, pair loc)
{
	bool val = false;
	std::pair<char, size_t> temp;
	temp = og->getLoc();
	Controller::getInstance().setTest(true);
	og->setLoc(loc);
	if (King* k = dynamic_cast<King*>(og))
		if (!k->checkingLoc(loc))
		{
			og->setLoc(temp);
			return false;
		}
	if (!Controller::getInstance().isCheck(Controller::getInstance().getQueue()))
		val = true;
	og->setLoc(temp);
	Controller::getInstance().setTest(false);
	return val;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool ObjGame::checkMat(ObjGame* pog, sf::Vector2f move, bool queue)
{
	King* k = dynamic_cast<King*>(pog);
	if (pog && pog->getLocation() == move)
	{
		if (k)
			Controller::getInstance().setMat(true, queue);
		return true;
	}
	return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ObjGame::eatTheEnnemy(sf::Vector2f move, bool queue)
{
	auto& arr = Board::getInstance().getObjects(!queue);
	for (auto it = arr.begin(); it != arr.end(); it++)
		if (*it && checkMat(it->get(), move, !queue))
			Board::getInstance().initTheEating(std::move(*it));
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ObjGame::eatDemoTheEnnemy(sf::Vector2f move, bool queue)
{
	auto& arr = Controller::getInstance().getAlgBoard().getObjects(!queue);
	for (auto it = arr.begin(); it != arr.end(); it++)
		checkMat(*it, move, !queue);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ObjGame::initLoc(std::pair<bool, sf::Vector2f> pair)
{
		m_location = pair.second;
		m_loc = std::pair<char, size_t>{ (pair.second.x / (int)PLACE_PIECES) + 'a', pair.second.y / PLACE_PIECES + 1 };
		m_sprite.setPosition(m_location);
		m_sprite.setOrigin(0, 0);
		m_sprite.scale(1, 1);
}