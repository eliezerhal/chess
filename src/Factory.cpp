//#include "Factory.h"
//#include "ObjGame.h"
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//std::map<std::string, std::unique_ptr<ObjGame>(*)()> Factory::m_map;
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//bool Factory::registerit(const std::string& name,
//	std::unique_ptr<ObjGame>(*f)()) {
//	m_map.emplace(name, f);
//	return true;
//}
////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//std::unique_ptr<ObjGame> Factory::create(const std::string& name)
//{
//	auto it = m_map.find(name);
//	if (it == m_map.end())
//		return nullptr;
//	return it->second();
//}

#include "Factory.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::map<std::string, std::unique_ptr<ObjGame>(*)()> Factory::m_map;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Factory::registerit(const std::string& name,
	std::unique_ptr<ObjGame>(*f)()) {
	m_map.emplace(name, f);
	return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

std::unique_ptr<ObjGame> Factory::create(const std::string& name)
{
	auto it = m_map.find(name);
	if (it == m_map.end())
		return nullptr;
	return it->second();
}
