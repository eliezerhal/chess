#pragma once
#include "ObjGame.h"
#include "Checking.h"
#include "Factory.h"

class Bishop : public ObjGame
{
public:
	Bishop()= default;
	virtual ~Bishop() = default;
	virtual bool checkingLoc(std::pair<char, size_t> loc) override;
	virtual void initData(std::pair<bool, sf::Vector2f> pair)override;

private:
	static bool m_registerit;
};
