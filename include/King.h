#pragma once
#include "ObjGame.h"
#include "Factory.h"
#include "Checking.h"

class King : public ObjGame
{
public:
	King() = default;
	virtual ~King() = default;
	virtual bool checkingLoc(std::pair<char, size_t> loc) override;
	bool checkingCastling(std::pair<char, size_t> loc);
	bool isEmptyFromKing(std::pair<char, size_t> loc, King* k);
	void castling(std::pair<char, size_t> loc);
	void moveRook(std::pair<char, size_t> loc);
	void setCheck(bool val) { m_check = val; };
	bool getCheck() const { return m_check; };
	char getKey();
	virtual void initData(std::pair<bool, sf::Vector2f> pair);
private:
	static bool m_registerit;
	bool m_check = false;
};
