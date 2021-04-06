#include"Command.h"
#include "Menu.h"

bool Play::execute(sf::Vector2f loc)
{
	auto p = Menu::getInstance().getData();	
	if (m_play.getGlobalBounds().contains(loc))
		if (!p.first.first.empty() && !p.second.empty())
		{
			Menu::getInstance().setplay(true);
			return true;
		}
	return false;
}

bool Player::execute(sf::Vector2f loc)
{
	if (m_play.getGlobalBounds().contains(loc))
	{
		Menu::getInstance().setData("Player");
		return true;
	}
	return  false;
}
bool Computer::execute(sf::Vector2f loc)
{
	if (m_play.getGlobalBounds().contains(loc))
	{
		Menu::getInstance().setData("Computer");
		return true;
	}
	return  false;
}
 
bool ColorBlack:: execute(sf::Vector2f loc)
{
	if (m_black.getGlobalBounds().contains(loc))
	{
		Menu::getInstance().setColor("black");
		return true;
	}
	return false;
}

 bool ColorWhite::execute(sf::Vector2f loc)
 {
	 if (m_white.getGlobalBounds().contains(loc))
	 {
		 Menu::getInstance().setColor("white");
		 return true;
	 }
	 return false;
}

bool knight::execute(sf::Vector2f loc)
{
	 if (m_play.getGlobalBounds().contains(loc))
	 {
		 Menu::getInstance().setChoice("Knight");
		 return true;
	 }
	return false;
 }


bool queen:: execute(sf::Vector2f loc)
{
	if (m_play.getGlobalBounds().contains(loc))
	{
		Menu::getInstance().setChoice("Queen");
		return true;
	}
	return false;
}


 bool rook::execute(sf::Vector2f loc)
 {
	 if (m_play.getGlobalBounds().contains(loc))
	 {
		 Menu::getInstance().setChoice("Rook");
		 return true;
	 }
	return false;
}
bool bishop::execute(sf::Vector2f loc)
{
	 if (m_play.getGlobalBounds().contains(loc))
	 {
		 Menu::getInstance().setChoice("Bishop");
		 return true;
	 }
	return false;
 }

bool help::execute(sf::Vector2f loc)
{
	if (m_play.getGlobalBounds().contains(loc))
	{
		Menu::getInstance().setHelp();
		return true;
	}
	return false;
}

bool helpbuttom::execute(sf::Vector2f loc)
{
	if (m_play.getGlobalBounds().contains(loc))
	{		
		Menu::getInstance().drawHelp();
		return false;
	}
	return false;
}
