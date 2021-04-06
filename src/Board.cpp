#include "Board.h"
#include "Controller.h"
#include "King.h"
#include "Factory.h"
#include <iterator>

Board::Board()
{	
	initThePieces();
	initTheGame();
	m_sprite.setTexture(m_res.getBoard());
	m_sprite.setPosition(0, 0);
	m_sprite.setScale(1, 1);	
}

Board& Board::getInstance()
{
	static Board instance; 
	return instance;
}

void Board::initTheGame()
{
	auto color = Controller::getInstance().getColor().first;
	auto i = 0;
	auto inNames = std::array<std::string, SIZ>
	{"Rook", "Knight", "Bishop", "King", "Queen", "Bishop", "Knight", "Rook"};
	if (color.first == "black") // For the purpose of initialization the Queen in her color
		std::swap(inNames[3], inNames[4]);
	for (size_t i = 8; i < 16; i++)
		inNames[i] = "Pawn";

	for (const auto& name : inNames)
	{
		auto p = m_Pieces;
		if (color.first == "black")
		{
			m_objComputer[i] = Factory::create(name);
			m_objComputer[i]->initData(m_whitePieces.at(i));
			m_objGamer[i] = Factory::create(name);
			m_objGamer[i]->initData(m_blackPieces.at(i++));
		}
		if (color.first == "white")
		{
			m_objComputer[i] = Factory::create(name);
			m_objComputer[i]->initData(m_blackPieces.at(i));
			m_objGamer[i] = Factory::create(name);
			m_objGamer[i]->initData(m_whitePieces.at(i++));
		}
	}
}
void Board::initThePieces()
{
	auto color = Controller::getInstance().getColor().first;
	int reset = 0, nextLigne = PLACE_PIECES;
	for (int i = 0; i < SIZE; i++) {
		if (i >= 8) {
			if (color.first == "white") {
				m_whitePieces[i] = { true,sf::Vector2f(((PLACE_PIECES * (i - 8))), (PLACE_PIECES * (BOARD - 2))) };
				m_blackPieces[i] = { false,sf::Vector2f(((PLACE_PIECES * (i - 8))), PLACE_PIECES) };
			}
			else {
				m_blackPieces[i] = { false,sf::Vector2f(((PLACE_PIECES * (i - 8))), (PLACE_PIECES * (BOARD - 2))) };
				m_whitePieces[i] = { true,sf::Vector2f(((PLACE_PIECES * (i - 8))), PLACE_PIECES) };
			}
		}
		else {
			if (color.first == "white") {
				m_whitePieces[i] = { true,sf::Vector2f((PLACE_PIECES * i) , PLACE_PIECES * (BOARD - 1)) };
				m_blackPieces[i] = { false,sf::Vector2f((PLACE_PIECES * i), 0) };
			}
			else {
				m_whitePieces[i] = { true,sf::Vector2f((PLACE_PIECES * i), 0) };
				m_blackPieces[i] = { false,sf::Vector2f((PLACE_PIECES * i) , PLACE_PIECES * (BOARD - 1)) };
			}
		}
	}
	if (color.first == "black") {
		m_Pieces.emplace(color.first, m_blackPieces);
		m_Pieces.emplace(color.second, m_whitePieces);
	}
	else {
		m_Pieces.emplace(color.first, m_whitePieces);
		m_Pieces.emplace(color.second, m_blackPieces);
	}
}
void Board::drawable(sf::RenderWindow& window)
{
	window.draw(getSpriteBoard());	
	for (auto& i : Board::getInstance().getObjGamer())
		if (i) i->Draw(window);
	for (auto& i : Board::getInstance().getObjComputer())
		if (i) i->Draw(window);
	for (auto& i : m_eatingPieces)
		if (i) i->Draw(window);
}

bool Board::isEmpty(std::pair<char, size_t>& loc, bool queue)
{
	if (Board::getInstance().getObj(loc, queue) == ObjGame::Obj::Non)
		return true;
	return false;
}

void Board::allLegal(ObjGame* og)
{
	for (int i = 0; i < 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			auto loc = std::pair<char, size_t>(i + 'a', j);
			if (loc == og->getLoc())
				continue;
			if (og->checkingLoc(loc))
				lightTheLoc(loc);
			if(King* k = dynamic_cast<King*>(og))
				continue;
			if (Controller::getInstance().isCheck(Controller::getInstance().getQueue()))
			{
				isCheckCanceled(og, loc);
				continue;
			}
		}
}

void Board::isCheckCanceled(ObjGame* og, pair loc)
{
	std::pair<char, size_t> temp;
	temp = og->getLoc();
	og->setLoc(loc);
	if (og->checkingLoc(loc) && !Controller::getInstance().isCheck(Controller::getInstance().getQueue()))
		lightTheLoc(loc);
	og->setLoc(temp);
}

void Board::lightTheLoc(pair loc)
{
	m_temp.push_back(creatRect(loc));
	float x = (loc.first - 'a') * PLACE_PIECES;
	float y = (loc.second - 1) * PLACE_PIECES;
	auto pos = sf::Vector2f(x, y);
	m_temp.back().setPosition(pos);
	m_temp.back().setOutlineThickness(-6);
	m_temp.back().setOutlineColor(sf::Color::Cyan);
	m_temp.back().setFillColor(sf::Color::Transparent);
}
void Board::add(std::unique_ptr<ObjGame> myChoice, Loc loc, Loc newloc)
{
	auto p = Controller::getInstance().getQueue();
	for (auto& i : getObjects(p))
		if (i && i->getLoc() == loc)
		{
			if (Controller::getInstance().getColor().first.first == "black")
				p = !p;
			auto location = i->getLocation();
			i = move(myChoice);
			i->initData(std::make_pair(p, sf::Vector2f(((float)((newloc.first - 'a') * PLACE_PIECES)), ((float)((newloc.second - 1) * PLACE_PIECES)))));
		}
}

bool Board::getMoving(sf::Vector2f location)
{
	for (auto& i : getObjects(Controller::getInstance().getQueue()))
		if (i && i->getSprite().getGlobalBounds().contains(location))
		{
			Controller::getInstance().setTest(true);
			resetTemp();
			Controller::getInstance().resetRectCheck();
			m_obj = i.get();
			allLegal(m_obj);
			return false;
		}
	if (!m_obj)
		return false;	
	else
	{
		m_pair.second.first = (location.x / (int)PLACE_PIECES) + 'a';
		m_pair.second.second = ((location.y / PLACE_PIECES) + 1);
		m_pair.first = m_obj;
	}
	Controller::getInstance().setTest(false);
	Controller::getInstance().play(m_pair);
	return true;
}

void Board::setBoard(movePieces move)
{
	move.first->setLoc(move.second);
	auto temp = sf::Vector2f(((float)move.second.first - 'a') * PLACE_PIECES, ((float)move.second.second - 1) * PLACE_PIECES);
	move.first->eatTheEnnemy(temp, Controller::getInstance().getQueue());
	move.first->move(temp);
	resetTemp();
}

ObjGame::Obj Board::getObj(std::pair<char, size_t>& loc, bool queue)
{
	for (auto& i : getObjects(queue))
		if(i && i->getLoc() == loc)
			return i->getName();
	return ObjGame::Obj::Non;
}

Board::array& Board::getObjects(bool queue)
{
	if (queue)
		return getObjGamer();
	return getObjComputer();
}

void Board::initTheEating(std::unique_ptr<ObjGame> eat)
{
	bool temp = !Controller::getInstance().getQueue();
	Controller::getInstance().getColor().first.first == "white" ? temp = !temp : temp = temp;
	size_t i;
	size_t j;
	size[!temp]++;
	size[!temp] <= 5 ? j = 0 : j = size[!temp] / 5;
	temp ? i = 0 : i = SIZE_WINDOW_WIDTH;
	m_eatingPieces.push_back(move(eat));
	m_eatingPieces.back()->initData(std::make_pair(!temp, sf::Vector2f(SIZE_BOARD + (PLACE_PIECES * ((float)((size[temp] - 1) % 5))), i + (PLACE_PIECES * ((float)(size[temp] / 6))))));
}
