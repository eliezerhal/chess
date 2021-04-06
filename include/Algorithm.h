#pragma once
#include "ObjGame.h"
#include "AlgBoard.h"
class Controller;

typedef std::pair <std::pair<ObjGame*, std::pair<char, size_t>>, int> mape;

class Algorithm
{
public:
	~Algorithm() = default;
	static Algorithm& getInstance();
	std::pair<ObjGame*, std::pair<char, size_t>> getMoving();
	int sumScore(AlgBoard& newBoard);
	mape& minimax(AlgBoard& newBoard, int depth, bool queue);

private:
	Algorithm() {srand(time(NULL));};
	int m_score = 0;
};
