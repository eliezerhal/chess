#include "Controller.h"
#include "King.h"
#include "Pawn.h"
#include <algorithm>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Controller::getOwner(Loc loc) const
{
	for (auto& i : Board::getInstance().getObjects(m_queue))
		if (i && i->getLoc() == loc)
			return true;
	return false;
}
void Controller::initTimer()
{
	int j = 0;
	for (auto& i : m_timer)
	{
		i.setCharacterSize(2);
		i = sf::Text(std::to_string(deltaTime[j].asSeconds()), Resources::instance().getFontTexture());
		i.setColor(sf::Color::Black);
		i.setStyle(sf::Text::Bold);
		i.setPosition(sf::Vector2f(SIZE_BOARD, SIZE_TEXT + (((float)j++) * PLACE_PIECES)));
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Controller::Controller() :m_recChek(sf::Vector2f(PLACE_PIECES, PLACE_PIECES))
{
	initTimer();
	m_recChek.setFillColor(sf::Color::Transparent);
	m_recPieces.setFillColor(sf::Color::White);
	m_recPieces.setSize(sf::Vector2f(SIZE_WINDOW_WIDTH, SIZE_BOARD));
	m_recPieces.setPosition(sf::Vector2f(SIZE_BOARD, 0));
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::resetData()
{
	m_queue = !m_queue;
	Board::getInstance().resetObj();
	m_gamer = false;
}
void Controller::resetPawns()
{
	for (auto& i : Board::getInstance().getObjects(!m_queue))
		if (Pawn* p = dynamic_cast<Pawn*>(i.get()))
			if (!p->isFirst())
				p->setSecond();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::gameing()
{
	while (!m_gamer)
	{
		clock[m_queue].restart();
		if (auto event = sf::Event{}; m_window.waitEvent(event))
			caseOfEvent(event);
		draw();
		deltaTime[m_queue] += clock[m_queue].getElapsedTime();
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Controller::checkingMove(movePieces& move)
{
	std::pair<char, size_t> temp;
	if (!move.first->checkingLoc(move.second))
		return false;
	if (isPat())
	{
		setPat();
		return false;
	}
	// checking if the check is canceled
	temp = move.first->getLoc();
	move.first->setLoc(move.second);
	bool val = !isCheck(m_queue);
	move.first->setLoc(temp);
	if (!val)
		return isThreatEliminated();
	return val;
}

bool Controller::isThreatEliminated()
{
	auto locOfTreatening = getLocOfTreatening();
	for (auto& i : Board::getInstance().getObjects(Controller::getInstance().getQueue()))
		if (i && i->checkingLoc(locOfTreatening))
			return true;
	return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::draw()
{
	m_window.clear();
	m_window.draw(m_recPieces);
	Board::getInstance().drawable(m_window);
	for (auto& i : Board::getInstance().getVecRect())
		m_window.draw(i);
	drawTimer();
	m_window.draw(m_recChek);
	m_window.display();
}

void Controller::drawTimer()
{
	int j = 0;
	for (auto& i : m_timer)
	{
		auto minute = std::to_string((int)deltaTime[j].asSeconds() / 60);
		auto second = std::to_string((int)deltaTime[j++].asSeconds() % 60);
		i.setString(minute + ":" + second);
		m_window.draw(i);
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::drawCheck(Loc loc)
{
	float x = (loc.first - 'a') * PLACE_PIECES;
	float y = (loc.second - 1) * PLACE_PIECES;
	auto pos = sf::Vector2f(x, y);
	m_recChek.setPosition(pos);
	m_recChek.setOutlineThickness(-5);
	m_recChek.setOutlineColor(sf::Color::Red);
	draw();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Controller& Controller::getInstance()
{
	static Controller instance;
	return instance;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::run()
{
	do {
		m_color = Menu::getInstance().initTheMenu();
		printScreen();
		printVictory();
	} while (!m_mat && !m_pat);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::printScreen()
{
	m_window.create(sf::VideoMode(SIZE_WIDTH, SIZE_BOARD), "Chess Game");
	if (m_color.first.first == "black")
		m_queue = !m_queue;
	while (m_window.isOpen())
	{
		draw();
		clock[!m_queue].restart();
		resetData();
		setMat(isMat(), m_queue);
		if (m_mat || m_pat)
			return;
		if (!m_queue && m_color.second == "Computer")
		{
			auto move = Algorithm::getInstance().getMoving();
			play(move);
		}
		else
			gameing();
	}
}
void Controller::printVictory()
{
	if (m_mat1)
		Menu::getInstance().printWinning(Resources::instance().lose());
	else if (m_mat2)
		Menu::getInstance().printWinning(Resources::instance().winner());
	else if (m_pat)
		Menu::getInstance().printWinning(Resources::instance().tie());
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::caseOfEvent(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		m_window.close();
		exit(0);
	case sf::Event::MouseButtonPressed:
		const auto location = m_window.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
		switch (event.mouseButton.button)
		{
		case sf::Mouse::Button::Left:
			Board::getInstance().getMoving(location);
			break;
		}
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::play(movePieces move)
{
	if (checkingMove(move))
	{
		Board::getInstance().setBoard(move);
		check(true);
		resetPawns();
		m_gamer = true;
	}
	return;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ObjGame::Obj Controller::whoIs(Loc loc, bool val) const
{
	if (!getRecursive())
		return Board::getInstance().getObj(loc, val);
	return Controller::getInstance().getAlgBoard().getObj(loc, val);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::check(bool check)
{
	m_test = true;
	bool queue;
	if(!check)
		m_testOtherSide = true;
	check ? queue = m_queue : queue = !m_queue;
	Loc loc;
	for (auto it = Board::getInstance().getObjects(!queue).begin(); it != Board::getInstance().getObjects(!queue).end(); it++)
		if (King* k = dynamic_cast<King*>(it->get()))
			loc = k->getLoc();
	for (auto& i : Board::getInstance().getObjects(queue))
	{
		if (i && i->checkingLoc(loc))
		{
			setCheck(true, queue);
			drawCheck(loc);
			m_locOfTreatening = i->getLoc();
			m_testOtherSide = false;
			return;
		}
		setCheck(false, queue);
	}
	m_testOtherSide = false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::setCheck(bool val, bool check)
{
	for (auto it = Board::getInstance().getObjects(!check).begin(); it != Board::getInstance().getObjects(!check).end(); it++)
		if (King* k = dynamic_cast<King*>(it->get()))
			k->setCheck(val);
}
void Controller::setMat(bool val, bool queue)
{
	m_mat = val;
	if (queue)
		m_mat1 = val;
	else
		m_mat2 = val;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Controller::isCheck(bool queue)
{
	check(false);
	for (auto it = Board::getInstance().getObjects(queue).begin(); it != Board::getInstance().getObjects(queue).end(); it++)
		if (King* k = dynamic_cast<King*>(it->get()))
			return k->getCheck();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Controller::isPat()
{
	for (auto& i : Board::getInstance().getObjects(m_queue))
		if (King* k = dynamic_cast<King*>(i.get()))
			if (!isCheck(m_queue) && m_checking.isArrEmpty() && i->getMoves().size() == 0)
				return true;
	return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Controller::isMat()
{
	King* k;
	size_t moves = 0;
	for (auto& i : Board::getInstance().getObjects(m_queue))
	{
		if(i) i->checkAllMovesLegal(i.get());
		if (i && i->getMoves().size() != 0)
			moves++;
	}
	if (isCheck(m_queue) && !moves)
		return true;
	return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Controller::setAlgBoard(AlgBoard& other, bool val)
{
	m_algBoard = other;
	m_algBoard.setQueue(val);
	m_tempQueue = val;
}