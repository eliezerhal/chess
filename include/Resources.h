#pragma once
#include <SFML/Graphics.hpp>

class Resources
{
public:
	static Resources& instance();
	const sf::Texture& kingTexture()const { return m_king; }
	const sf::Texture& menuTexture()const { return m_menu; }
	const sf::Texture& queenTexture()const { return m_queen; }
	const sf::Texture& rookTexture()const { return m_rook; }
	const sf::Texture& knightTexture()const { return m_knight; }
	const sf::Texture& bishopTexture()const { return m_bishop; }
	const sf::Texture& pawnTexture()const { return m_pawn; }
	const sf::Texture& getBoard()const { return m_board; };
	const sf::Texture& kingBTexture()const { return m_kingB; }
	const sf::Texture& queenBTexture()const { return m_queenB; }
	const sf::Texture& rookBTexture()const { return m_rookB; }
	const sf::Texture& knightBTexture()const { return m_knightB; }
	const sf::Texture& bishopBTexture()const { return m_bishopB; }
	const sf::Texture& pawnBTexture()const { return m_pawnB; }
	const sf::Texture& exitTexture()const { return m_exit; }	
	const sf::Texture& whiteTexture()const { return m_white; }
	const sf::Texture& blackTexture()const { return m_black; }
	const sf::Texture& playTexture()const { return m_play; }
	const sf::Texture& cVSpTexture()const { return  m_cVSp; }
	const sf::Texture& pVSpTexture()const { return   m_pVSp; }
	const sf::Texture& helpTexture()const { return  m_help; }
	const sf::Texture& helpbuttomTexture()const { return   m_helpbuttom; }
	const sf::Texture& winner()const { return   m_winner; }
	const sf::Texture& lose()const { return   m_lose; }
	const sf::Texture& tie()const { return   m_tie; }
	const sf::Font& getFontTexture()const { return m_font; };
	Resources();
private:

	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;
	sf::Texture m_board;
	sf::Texture m_menu;
	sf::Texture m_king;
	sf::Texture m_pawn;
	sf::Texture m_queen;
	sf::Texture m_rook;
	sf::Texture m_knight;
	sf::Texture m_bishop;
	sf::Texture m_kingB;
	sf::Texture m_pawnB;
	sf::Texture m_queenB;
	sf::Texture m_rookB;
	sf::Texture m_knightB;
	sf::Texture m_bishopB;
	sf::Texture m_exit;
	sf::Texture m_helpbuttom;
	sf::Texture m_help;	
	sf::Texture m_white;
	sf::Texture m_black;
	sf::Texture m_cVSp;
	sf::Texture m_pVSp;
	sf::Texture m_play;
	sf::Texture m_winner;
	sf::Texture m_tie;
	sf::Texture m_lose;
	sf::Font m_font;
};