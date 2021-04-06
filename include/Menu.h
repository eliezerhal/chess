#pragma once
#include "Resources.h"
#include "Board.h"
#include "Command.h"
#include <memory>
#include <string>
#include <vector>

using option = std::pair<std::string, std::shared_ptr<Command>>;
using Data = std::pair<std::pair<std::string, std::string>, std::string>;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Menu
{
public:
	void add(std::string name, std::shared_ptr<Command> c, std::vector<option>& vec) { vec.emplace_back(option(name, move(c))); }
	void activate();
	static Menu& getInstance();
	void getOptionFromUser(sf::Event event, std::vector<option>& vec);
	Data initTheMenu();
	std::vector<option>& drawable();
	void setData(std::string val) { m_data.second = val; };
	void setColor(std::string val) {val == "white"? (m_data.first.first = val, m_data.first.second = "black"): (m_data.first.first = val, m_data.first.second = "white"); };
	void setplay(bool val) {m_play = val;};
	void drawColor();
	void printWinning(sf::Texture picture);
	Data getData() { return m_data; };
	void setChoice(std::string pieces) {	m_choice = pieces; m_play = true;	};
	void drawHelp();
	void setHelp() { m_helpp = false; };
	std::unique_ptr<ObjGame> coronation();
	~Menu() {};

private:
	Menu();
	bool m_play = false;
	sf::RenderWindow m_menuWindows;
	sf::Sprite m_menuSprite;
	bool m_coronation = false;
	std::vector<option> m_options;
	std::vector<option> m_pieces;
	std::vector<option> m_colour;
	std::vector<option> m_player;
	std::vector<option> m_help;
	std::vector< std::pair<std::string, std::unique_ptr<Command>>> m_colors;
	std::string m_choice;
	sf::Sprite m_win;
	bool m_helpp = false;
	Data m_data;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
