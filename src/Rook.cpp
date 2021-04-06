#include <Rook.h>
#include <Controller.h>

bool Rook::m_registerit = Factory::registerit("Rook",
	[]() -> std::unique_ptr<ObjGame>
	{ return std::make_unique<Rook>(); });

bool Rook::checkingLoc(std::pair<char, size_t> loc)
{
	if (!ObjGame::checkingLoc(loc))
		return false;
	return ((m_loc.first == loc.first || loc.second == m_loc.second) && m_checking.allEmpty(m_loc, loc));
}

void Rook::initData(std::pair<bool, sf::Vector2f> pair)
{
	initLoc(pair);
	m_name = Obj::Rook;
	if (pair.first)
		initTexture(Resources::instance().rookTexture());
	else
		initTexture(Resources::instance().rookBTexture());

}