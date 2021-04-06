#pragma once
#include <iostream>
#include <memory>
//#include <map>
//#include <array>
//#include <vector>
//#include <iterator>
//#include <string>
////#include "ObjGame.h"
//class ObjGame;
//
//// ================   class Factory   ============================
//class Factory {
//public:
//	static std::unique_ptr<ObjGame> create(const std::string& name);
//	static bool registerit(const std::string& name,
//		std::unique_ptr<ObjGame>(*f)());
//private:
//	static std::map<std::string, std::unique_ptr<ObjGame>(*)() > m_map;
//};


#pragma once
#include <iostream>
#include <memory>
#include <map>
#include <array>
#include <vector>
#include <iterator>
#include <string>
#include "ObjGame.h"


// ================   class Factory   ============================
class Factory {
public:
	static std::unique_ptr<ObjGame> create(const std::string& name);
	static bool registerit(const std::string& name,
		std::unique_ptr<ObjGame>(*f)());
private:
	static std::map<std::string, std::unique_ptr<ObjGame>(*)() > m_map;
};


