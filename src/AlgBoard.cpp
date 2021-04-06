#include "AlgBoard.h"
#include "Board.h"
#include "King.h"
#include "Controller.h"
void AlgBoard::init()
{
	int i = 0;
	int j = 0;
	for (auto& og : Board::getInstance().getObjComputer())
	{
		m_objComputer[i] = og.get();
		i++;
	}
	for (auto& og : Board::getInstance().getObjGamer())
	{
		m_objGamer[j] = og.get();
		j++;
	}
}

AlgBoard::AlgBoard(const AlgBoard& other)
{
	m_objComputer = other.m_objComputer;
	m_objGamer = other.m_objGamer;
}

AlgBoard& AlgBoard::operator=(AlgBoard& other) 
{
	m_objComputer = other.m_objComputer;
	m_objGamer = other.m_objGamer;
	return *this;
}

array& AlgBoard::getObjects(bool queue)
{
	if (queue)
		return getObjGamer();
	return getObjComputer();
}

void AlgBoard::play(movePieces move, bool queue)
{
	if (Controller::getInstance().checkingMove(move))
	{
		*this = Controller::getInstance().getAlgBoard();
		setBoard(move, queue);
		check(queue);
	}
	return;
}

void AlgBoard::setBoard(movePieces move, bool queue)
{
	move.first->setLoc(move.second);
	auto temp = sf::Vector2f(((float)move.second.first - 'a') * 125, ((float)move.second.second - 1) * 125);
	//auto temp = std::make_pair(move.second.first, move.second.second - 1);
	move.first->eatDemoTheEnnemy(temp, queue);
	move.first->move(temp);
}

void AlgBoard::check(bool queue)
{ 
	printVector();
	std::pair<char, size_t> loc;
	for (auto it = getObjects(!queue).begin(); it != getObjects(!queue).end(); it++)
		if (King* k = dynamic_cast<King*>(*it))
			loc = k->getLoc();
	for (auto& i : getObjects(queue))
		if (i && i->checkingLoc(loc))
		{
			setCheck(true, queue);
			return;
		}
	setCheck(false, queue);
}

void AlgBoard::setCheck(bool val, bool queue)
{
	for (auto it = getObjects(!queue).begin(); it != getObjects(!queue).end(); it++)
		if (King* k = dynamic_cast<King*>(*it))
			k->setCheck(val);
}

ObjGame::Obj AlgBoard::getObj(std::pair<char, size_t>& loc, bool queue)
{
	if (queue)
		for (auto& i : m_objGamer)
			if (i && i->getLoc() == loc)
				return i->getName();
	if (!queue)
		for (auto& i : m_objComputer)
			if (i && i->getLoc() == loc)
				return i->getName();
	return ObjGame::Obj::Non;
}

bool AlgBoard::isEmpty(std::pair<char, size_t>& loc, bool queue)
{
	if (getObj(loc, queue) == ObjGame::Obj::Non)
		return true;
	return false;
}

void AlgBoard::printVector()
{
	for (auto& i : m_objComputer)
	{
		std::cout << "m_objComputer" << "        "<<i->getLoc().first << " " << i->getLoc().second <<" "
		 << "        "<<i->getLocation().x << " " << i->getLocation().y << std::endl;
		
	}
	/*for (auto& i : m_objGamer)
	{
		std::cout << "m_objGamer" << i->getLoc().first << " " << i->getLoc().second << std::endl;
	}*/
}
