#pragma once
#pragma once
#include "Resources.h"
static bool play = false;
class Menu;// "Menu.h"
class Command {
public:
	virtual bool execute(sf::Vector2f loc) = 0;
	virtual  void getTexture(sf::RenderWindow& window) = 0;
	//virtual std::string getColor() = 0;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class choiceColor : public Command {
public:
	choiceColor(const sf::Texture& buttom, sf::Vector2f loc) { m_color.setTexture(buttom); m_color.setPosition(loc); }
	virtual bool execute(sf::Vector2f loc);
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_color); }
	//virtual std::string getColor() { return "none"; };
private:
	sf::Sprite m_color;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Exit : public Command {
public:
	Exit(const sf::Texture& buttom, sf::Vector2f loc) { m_exit.setTexture(buttom); m_exit.setPosition(loc); }
	virtual bool execute(sf::Vector2f loc) {
		if (m_exit.getGlobalBounds().contains(loc))
			exit(0);
		return false;
	}
	//virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_exit); }
private:
	sf::Sprite m_exit;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Play : public Command {
public:
	Play(const sf::Texture& buttom, sf::Vector2f loc) { m_play.setTexture(buttom), m_play.setPosition(loc); }
	virtual bool execute(sf::Vector2f loc);
	//virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_play); }
private:
	sf::Sprite m_play;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class ColorBlack : public Command {
public:
	ColorBlack(const sf::Texture& buttom, sf::Vector2f loc) { m_black.setTexture(buttom), m_black.setPosition(loc); }
	virtual bool execute(sf::Vector2f loc);
	//virtual std::string getColor() { return "black"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_black); }
private:
	sf::Sprite m_black;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class ColorWhite : public Command {
public:
	ColorWhite(const sf::Texture& buttom, sf::Vector2f loc) { m_white.setTexture(buttom), m_white.setPosition(loc); }
	virtual bool execute(sf::Vector2f loc);
	//virtual std::string getColor() { return "white"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_white); }
private:
	sf::Sprite m_white;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Player : public Command {
public:
	Player(const sf::Texture& buttom, sf::Vector2f loc) { m_play.setTexture(buttom), m_play.setPosition(loc); }
	virtual bool execute(sf::Vector2f loc);
	//virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_play); }
private:
	sf::Sprite m_play;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Computer : public Command {
public:
	Computer(const sf::Texture& buttom, sf::Vector2f loc) { m_play.setTexture(buttom), m_play.setPosition(loc); }
	virtual bool execute(sf::Vector2f loc);
	virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_play); }
private:
	sf::Sprite m_play;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class knight : public Command {
public:
	knight(const sf::Texture& buttom, sf::Vector2f loc) { m_play.setTexture(buttom), m_play.setPosition(loc), m_play.setScale(sf::Vector2f(1, 1));
	}
	virtual bool execute(sf::Vector2f loc);
	virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_play); }
private:
	sf::Sprite m_play;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class queen : public Command {
public:
	queen(const sf::Texture& buttom, sf::Vector2f loc) { m_play.setTexture(buttom), m_play.setPosition(loc), m_play.setScale(sf::Vector2f(1,1));
	}
	virtual bool execute(sf::Vector2f loc);
	virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_play); }
private:
	sf::Sprite m_play;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class rook : public Command {
public:
	rook(const sf::Texture& buttom, sf::Vector2f loc) { m_play.setTexture(buttom), m_play.setPosition(loc), m_play.setScale(sf::Vector2f(1, 1));
	}
	virtual bool execute(sf::Vector2f loc);
	virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_play); }
private:
	sf::Sprite m_play;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class bishop : public Command {
public:
	bishop(const sf::Texture& buttom, sf::Vector2f loc) { m_play.setTexture(buttom), m_play.setPosition(loc), m_play.setScale(sf::Vector2f(1,1)); }
	virtual bool execute(sf::Vector2f loc);
	virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_play); }
private:
	sf::Sprite m_play;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class help : public Command {
public:
	help(const sf::Texture& buttom, sf::Vector2f loc) { m_play.setTexture(buttom), m_play.setPosition(loc), m_play.setScale(sf::Vector2f(1,1)); }
	virtual bool execute(sf::Vector2f loc);
	virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_play); }
private:
	sf::Sprite m_play;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class helpbuttom : public Command {
public:
	helpbuttom(const sf::Texture& buttom, sf::Vector2f loc) { m_play.setTexture(buttom), m_play.setPosition(loc), m_play.setScale(sf::Vector2f(1,1)); }
	virtual bool execute(sf::Vector2f loc);
	virtual std::string getColor() { return "none"; };
	virtual void getTexture(sf::RenderWindow& window) { window.draw(m_play); }
private:
	sf::Sprite m_play;
};