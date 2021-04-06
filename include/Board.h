#pragma once
#include "Resources.h"
#include "ObjGame.h"
#include <array>
#include <SFML/Graphics.hpp>

const int SIZ = 16;
const float BOARD = 8;
const float PIECES_HEIGHT = 168;
const float PLACE_PIECES = 125;

class Controller;

class Board
{
public:
	using Loc = std::pair<char, size_t>;
	using gPair = std::pair<ObjGame*, std::pair<char, size_t>>;
	using pair = std::pair<char, size_t>;
	using movePieces = std::pair< ObjGame*, pair>;
	using dataPieces = std::array<std::pair<bool, sf::Vector2f>, SIZ>;
	using array = std::array<std::unique_ptr<ObjGame>, SIZ>;
	
private:
	Board();
	enum class color { white, black };
	ObjGame* m_obj;
	dataPieces m_whitePieces;
	dataPieces m_blackPieces;
	sf::RenderWindow m_window;
	array m_objGamer;
	array m_objComputer;
	sf::Sprite m_sprite;
	Resources m_res;
	gPair m_pair;
	std::map<std::string, dataPieces> m_Pieces;
	std::vector<sf::RectangleShape> m_temp;
	std::vector < std::unique_ptr<ObjGame> >m_eatingPieces;
	size_t size[2] = { 0 };
public:
	~Board() = default;
	static Board& getInstance();
	void initTheGame();
	void initThePieces();
	void drawable(sf::RenderWindow& window);
	bool getMoving(sf::Vector2f location);
	void setBoard(movePieces move);
	ObjGame::Obj getObj(std::pair<char, size_t>& loc, bool queue);
	array& getObjects(bool queue);
	array& getObjGamer() { return m_objGamer; };
	array& getObjComputer() { return m_objComputer; };
	sf::Sprite getSpriteBoard() { return m_sprite; };
	bool isEmpty(std::pair<char, size_t>& loc, bool queue);	
	void resetObj() { m_obj = nullptr; };
	void allLegal(ObjGame* og);
	void lightTheLoc(pair loc);
	void isCheckCanceled(ObjGame* og, pair loc);
	std::vector<sf::RectangleShape> getVecRect() { return m_temp; };
	sf::RectangleShape creatRect(std::pair<char, size_t> loc) { return sf::RectangleShape(sf::Vector2f(PLACE_PIECES, PLACE_PIECES)); };
	void resetTemp() { m_temp.clear(); }
	void add(std::unique_ptr<ObjGame> myChoice,Loc loc, Loc newloc);
	void initTheEating(std::unique_ptr<ObjGame> eat);
};