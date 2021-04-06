#include "Algorithm.h"
#include "ObjGame.h"
#include "Controller.h"
#include "Board.h"
#include <iostream>
#include <memory>
#include <time.h>
#include <exception>

//typedef std::pair<std::shared_ptr<ObjGame>, std::pair<char, size_t>> pair;
typedef std::pair <pair, int> map;
typedef std::map<ObjGame::Obj, int> mapVal;

mapVal valOfObj{ {ObjGame::Obj::King, 10000}, {ObjGame::Obj::Queen, 9}, {ObjGame::Obj::Rook, 5}, {ObjGame::Obj::Bishop, 3}, {ObjGame::Obj::Knight, 3}, {ObjGame::Obj::Pawn, 1}, {ObjGame::Obj::Non, 0} };

Algorithm& Algorithm::getInstance()
{
	static Algorithm instance;
	return instance;
}

std::pair<ObjGame*, std::pair<char, size_t>> Algorithm::getMoving() 
{
	try {
		std::pair<char, size_t> loc;
		ObjGame* obj;
		while (true)
		{
			int og = rand() % 16;
			obj = Board::getInstance().getObjects(Controller::getInstance().getQueue())[og].get();
			if (obj)
				obj->checkAllMovesLegal(obj);
			if (obj->getMoves().size() != 0)
			{
				int move = rand() % obj->getMoves().size();
				loc = obj->getMoves()[move];
				break;
			}
		}
		auto moving = std::make_pair(obj, loc);
		return moving;
	}
	catch(std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}

/*std::pair<ObjGame*, std::pair<char, size_t>> Algorithm::getMoveing()*/
//{
//	mape move;
//	bool queue = Controller::getInstance().getQueue();
//	AlgBoard newBoard;
//	newBoard.init();
//	move = minimax(newBoard, 4, queue);
//	Controller::getInstance().setRecursive(false);
//	return move.first;
//}

int Algorithm::sumScore(AlgBoard& newBoard)
{
	int gamer = 0;
	int computer = 0;
	for (auto& i : newBoard.getObjComputer())
		computer += valOfObj[i->getName()];
	for (auto& i : newBoard.getObjGamer())
		gamer += valOfObj[i->getName()];
	return computer - gamer;
}

mape& Algorithm::minimax(AlgBoard& newBoard, int depth, bool queue)
{
	mape best_move;
	Controller::getInstance().setRecursive(true);
	best_move.second = -10000;
	for (auto& i : newBoard.getObjects(queue))
	{
		Controller::getInstance().setAlgBoard(newBoard, queue);
		i->checkAllMovesLegal(i);
		//newBoard.printVector();
		if (i->getMoves().empty())
			continue;
		for (auto j : i->getMoves())
		{
			best_move.first = std::make_pair(i, j);
			newBoard.play(std::make_pair(i, j), queue);
			if (depth == 1)
			{
				best_move.second = sumScore(newBoard);
				return best_move;
			}
			AlgBoard newBoard2 = newBoard;
			mape& option = minimax(newBoard2, depth - 1, !queue);
			if (depth % 2 == 0)
			{
				if (option.second > best_move.second)
				{
					best_move.second = option.second;
					best_move.first.second = option.first.second;
				}
				else if (option.second == best_move.second)
				{
					srand(time(NULL));
					int choice = rand() % 2;
					if (choice == 1)
					{
						best_move.second = option.second;
						best_move.first.second = option.first.second;
					}
				}
			}
		}
	}	
	return best_move;
}

