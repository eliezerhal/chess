#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Checking.h"
#include <array>
#include <memory>
#include <experimental/vector>

class Board;
class Controller;

class ObjGame
{
public:
	typedef std::pair<char, size_t> pair;
	typedef std::pair< ObjGame*, pair> movePieces;		
	enum class Obj { King, Queen, Rook, Bishop, Knight, Pawn, Non };
	enum class color { white, black };
	ObjGame() = default;
	virtual ~ObjGame() = default;
	void initTexture(const sf::Texture& picture);
	void move(sf::Vector2f& loc);
	virtual bool checkingLoc(std::pair<char, size_t> loc) ;
	void Draw(sf::RenderWindow& window);
	void setposition(sf::Vector2f position);
	void setLoc(std::pair<char, size_t> loc) { m_loc = loc; };
	sf::Vector2f getLocation() const { return m_location; };
	std::pair<char, size_t> getLoc() const { return m_loc; };
	sf::Sprite getSprite() const { return m_sprite; };
	Obj getName() const { return m_name; };
	bool isFirst() const { return m_first; };
	bool isDead() const { return m_dead; };
	void checkAllMovesLegal(ObjGame* og);
	bool isCheckCanceled(ObjGame* og, pair loc);
	bool checkingTemp(ObjGame* og, pair loc);
	std::vector< std::pair<char, size_t>> getMoves() { return allMovesLegal; };
	bool checkMat(ObjGame* pog, sf::Vector2f move, bool queue);
	void eatTheEnnemy(sf::Vector2f move, bool queue);
	void eatDemoTheEnnemy(sf::Vector2f move, bool queue);
	void initLoc(std::pair<bool, sf::Vector2f> pair);
	virtual void initData(std::pair<bool, sf::Vector2f> pair) = 0;

protected:
	Obj m_name;
	std::pair<char, size_t> m_loc;
	color m_color;
	sf::Vector2f m_location;
	unsigned int m_score;
	sf::Sprite m_sprite;
	bool m_first = true;
	bool m_dead = false;
	std::vector< std::pair<char, size_t>> allMovesLegal;
	Checking m_checking;
};
