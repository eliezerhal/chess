#include "Menu.h"
#include "Factory.h"
#include <iostream>
#include <thread>
#include <chrono>
constexpr int MENU_WIDE = 840;
constexpr int MENU_HEIGHT = 1200;

Menu& Menu::getInstance()
{
	static Menu instance;
	return instance;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Menu::drawHelp()
{	
	m_helpp = true;
	while (m_menuWindows.isOpen())
	{
		m_menuWindows.clear();
		auto vector = drawable();
		m_menuWindows.display();
		if (auto event = sf::Event{}; m_menuWindows.waitEvent(event))
			getOptionFromUser(event, vector);
		if (!m_helpp)
			return;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::unique_ptr<ObjGame> Menu::coronation()
{
	m_coronation = true;
	m_play = false;	
	m_menuWindows.create(sf::VideoMode(MENU_HEIGHT, MENU_WIDE), "Menu");	
	activate();
	m_menuWindows.close();
	return Factory::create(m_choice);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Menu::Menu() :m_menuWindows(sf::VideoMode(MENU_HEIGHT, MENU_WIDE), "Menu"), m_menuSprite(Resources::instance().menuTexture()){}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::pair<std::pair<std::string, std::string>, std::string> Menu::initTheMenu()
{
	auto& res = Resources::instance();
	add("black", std::make_shared<ColorBlack>(res.blackTexture(), sf::Vector2f(20, 350)),m_colour);
	add("white", std::make_shared<ColorWhite>(res.whiteTexture(), sf::Vector2f(20, 250)), m_colour);

	add("player_VS_computer", std::make_shared<Computer>(res.cVSpTexture(), sf::Vector2f(30, 250)), m_options);
	add("player_VS_player", std::make_shared<Player>(res.pVSpTexture(), sf::Vector2f(30, 350)), m_options);

	add("play", std::make_shared<Play>(res.playTexture(), sf::Vector2f(30, 250)),m_player);
	add("helpbuttom", std::make_shared<helpbuttom>(res.helpbuttomTexture(), sf::Vector2f(30, 450)),m_player);

	add("exit", std::make_shared<Exit>(res.exitTexture(), sf::Vector2f(30, 350)), m_player);

	add("queen", std::make_shared<queen>(res.queenTexture(), sf::Vector2f(30, 150)), m_pieces);
	add("rook", std::make_shared<rook>(res.rookTexture(), sf::Vector2f(30, 350)), m_pieces);
	add("bishop", std::make_shared<bishop>(res.bishopTexture(), sf::Vector2f(30, 550)), m_pieces);
	add("knight", std::make_shared<knight>(res.knightTexture(), sf::Vector2f(30, 750)), m_pieces);

	add("help", std::make_shared<help>(res.helpTexture(), sf::Vector2f(0, 0)), m_help);

	activate();
	m_menuWindows.close();
	return m_data;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Menu::activate()
{
	while (m_menuWindows.isOpen())
	{
		m_menuWindows.clear();
		auto vector = drawable();
		m_menuWindows.display();
		if (auto event = sf::Event{}; m_menuWindows.waitEvent(event))
			getOptionFromUser(event, vector);
		if (m_play)
			return;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<option>& Menu::drawable()
{
	m_menuWindows.draw(m_menuSprite);
	if (m_helpp)
	{
		for (auto& i : m_help)
			i.second->getTexture(m_menuWindows);
		return m_help;
	}
	if (m_coronation)
	{
		for (auto& i : m_pieces)
			i.second->getTexture(m_menuWindows);
		return m_pieces;
	}
	if (m_data.first.first.empty())
	{
		for (auto& i : m_colour)
			i.second->getTexture(m_menuWindows);
		return m_colour;
	}
	else if (m_data.second.empty())
	{
		for (auto& i : m_options)
			i.second->getTexture(m_menuWindows);
		return m_options;
	}
	else
	{
		for (auto& i : m_player)
			i.second->getTexture(m_menuWindows);
		return m_player;
	}	
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Menu::getOptionFromUser(sf::Event event, std::vector<option>& vec)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		m_menuWindows.close();
		exit(0);
	case sf::Event::MouseButtonPressed:
		const auto location = m_menuWindows.mapPixelToCoords({ event.mouseButton.x,event.mouseButton.y });
		switch (event.mouseButton.button)
		{
		case sf::Mouse::Button::Left:
				for (auto& i : vec)
				{
					if (i.second->execute(location))
						break;
					else
						continue;
				}
				break;
		}
	}
}

void Menu::printWinning(sf::Texture picture)
{
	using namespace std::chrono_literals;
	m_win.setTexture(picture);	
	m_menuWindows.create(sf::VideoMode(MENU_HEIGHT, MENU_WIDE), "Menu");
	m_menuWindows.draw(m_win);
	m_menuWindows.display();
	std::this_thread::sleep_for(10s);
	m_menuWindows.close();
}