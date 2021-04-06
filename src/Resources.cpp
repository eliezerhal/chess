#include "Resources.h"

Resources& Resources::instance()
{
	static Resources instance;
	return instance;
}

Resources::Resources()
{
	m_board.loadFromFile("chess.png");
	m_menu.loadFromFile("Menu.png");
	m_pawn.loadFromFile("Pawn.png");
	m_king.loadFromFile("King.png");
	m_knight.loadFromFile("Knight.png");
	m_bishop.loadFromFile("Bishop.png");
	m_rook.loadFromFile("Rook.png");
	m_queen.loadFromFile("Queen.png");
	m_pawnB.loadFromFile("PawnB.png");
	m_kingB.loadFromFile("KingB.png");
	m_knightB.loadFromFile("KnightB.png");
	m_bishopB.loadFromFile("BishopB.png");
	m_rookB.loadFromFile("RookB.png");
	m_queenB.loadFromFile("QueenB.png");
	m_queenB.loadFromFile("QueenB.png");
	m_exit.loadFromFile("Exit.png");
	m_white.loadFromFile("colorWhite.png");
	m_black.loadFromFile("colorBlack.png");
	m_play.loadFromFile("Play.png");
	m_cVSp.loadFromFile("pVSc.png");
	m_pVSp.loadFromFile("pVSp.png");
	m_help.loadFromFile("Help.png");
	m_helpbuttom.loadFromFile("helpbuttom.png");
	m_font.loadFromFile("snap.ttf");
	m_winner.loadFromFile("winning.png");
	m_lose.loadFromFile("losing.png");
	m_tie.loadFromFile("tie.png");
}
