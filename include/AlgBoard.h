#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include "ObjGame.h"
class Controller;

const int SIZE = 16;
typedef std::pair<char, size_t> pair;
typedef std::pair< ObjGame*, pair> movePieces;
typedef std::array<ObjGame*, SIZE> array;

class AlgBoard
{
public:
	AlgBoard() = default;
	AlgBoard(const AlgBoard& other);
	~AlgBoard() {};
	AlgBoard& operator=( AlgBoard& other) ;
	void init();
	void play(movePieces move, bool queue);
	array& getObjects(bool queue);
	array& getObjGamer() { return m_objGamer; };
	array& getObjComputer() { return m_objComputer; };
	void setBoard(movePieces move, bool queue);
	void setCheck(bool val,bool queue);
	ObjGame::Obj getObj(std::pair<char, size_t>& loc, bool queue);
	bool getQueue() const { return m_queue; };
	void setQueue(bool val) { m_queue = val; };
	void check(bool queue);
	bool isEmpty(std::pair<char, size_t>& loc, bool queue);
	void printVector();
private:
	std::array<ObjGame*, SIZE> m_objGamer;
	std::array<ObjGame*, SIZE> m_objComputer;
	bool m_queue;
};