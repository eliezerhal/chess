#pragma once
#include "ObjGame.h"
#include "Checking.h"
#include "Factory.h"

class Knight : public ObjGame
{
public:
	Knight() = default; 
	virtual ~Knight() = default ;
	virtual bool checkingLoc(std::pair<char, size_t> loc) override;
	virtual void initData(std::pair<bool, sf::Vector2f> pair);

private:
	static bool m_registerit;
	Checking m_checking;
};
