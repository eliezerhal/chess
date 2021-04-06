#pragma once
#include "ObjGame.h"
#include "Factory.h"
#include "Checking.h"

class Queen : public ObjGame
{
public:
	Queen() = default; 
	virtual ~Queen() = default;
	virtual bool checkingLoc(std::pair<char, size_t> loc) override;
	virtual void initData(std::pair<bool, sf::Vector2f> pair);

private:
	static bool m_registerit;
};
