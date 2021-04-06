#pragma once
#include "ObjGame.h"
#include "Checking.h"
#include "Factory.h"

class Controller;

class Pawn : public ObjGame
{
public:
	using Loc = std::pair<char, size_t>;
	Pawn() {};
	virtual ~Pawn() = default;
	virtual bool checkingLoc(std::pair<char, size_t> loc) override;
	void coronation(Loc loc);
	bool enPassant(std::pair<char, size_t> loc);
	bool isSecond() { return m_second; };
	void setSecond() { m_second = false; };
	virtual void initData(std::pair<bool, sf::Vector2f> pair);
	bool checkinCoronation(Loc loc, bool queue);

private:
	static bool m_registerit;
	sf::RenderWindow m_tempWin;
	bool m_second = true;
};
