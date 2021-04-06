#pragma once
#include "ObjGame.h"
#include "Menu.h"
#include "Algorithm.h"
#include "Checking.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <ctime>
#include <chrono>
const unsigned int SIZE_BOARD = 1000;
const unsigned int SIZE_WIDTH = 1625;
const unsigned int SIZE_WINDOW_WIDTH = 625;
const unsigned int SIZE_TEXT = 425;
class AlgBoard;

class Controller
{
public:	
	using Loc = std::pair<char, size_t>;
	using movePieces = std::pair< ObjGame*, Loc>;
	static Controller& getInstance();
	~Controller() {};
	void run();
	void printScreen();
	void printVictory();
	void draw();
	void drawCheck(Loc loc);
	void drawTimer();
	void caseOfEvent(sf::Event event);
	void play(movePieces move);
	bool checkingMove(movePieces& move);
	ObjGame::Obj whoIs(Loc loc, bool val) const;
	void check(bool check);
	bool isCheck(bool queue);
	bool isPat();
	bool isMat();
	bool isThreatEliminated();
	void resetRectCheck() { m_recChek.setOutlineColor(sf::Color::Transparent); };
	void resetData();
	void resetPawns();
	void gameing();
	std::pair<std::pair< std::string, std::string>, std::string> getColor() const { return m_color; }
	bool getQueue() const { return m_queue; };
	bool getTempQueue() const { return m_tempQueue; };
	void setCheck(bool val, bool check);
	void setMat(bool val, bool queue);
	void setAlgBoard(AlgBoard& other, bool val);
	AlgBoard& getAlgBoard() { return m_algBoard; };
	Loc getLocOfTreatening() const { return m_locOfTreatening; };
	void setRecursive(bool val) { m_recursive = val; };
	bool getRecursive() const { return m_recursive; };
	bool getTest() const { return m_test; };
	void setTest(bool val) { m_test = val; };
	sf::RectangleShape& getRecChek() { return m_recChek; };
	bool getOwner(Loc loc) const;
	bool getTestOtherSide() const { return m_testOtherSide; };
	void setPat() { m_pat = true; };
	void initTimer();

private:
	Controller();
	Controller(const Controller&);
	bool m_mat1 = false;
	bool m_mat2 = false;
	bool m_mat = false;
	bool m_pat = false;
	bool m_queue = false;
	bool m_tempQueue;
	bool m_gamer = false;
	bool m_recursive = false;
	sf::RenderWindow m_window;
	std::pair<std::pair< std::string, std::string>, std::string> m_color;
	AlgBoard m_algBoard;
	Checking m_checking;
	bool m_check = false;
	bool m_test = false;
	bool m_testOtherSide = false;
	Loc m_locOfTreatening;
	sf::RectangleShape m_recChek;
	sf::RectangleShape m_recPieces;
	std::array<sf::Clock, 2 > clock;
	int m_time = 0;
	sf::Time deltaTime[2];
	sf::Text m_timer[2];
};
