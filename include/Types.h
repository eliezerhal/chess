#pragma once
#include "ObjGame.h"
#include <iostream>
#include <memory>
#include <array>
#include <algorithm>
#include <utility>
#include <SFML/Graphics.hpp>

typedef std::pair<char, size_t> pair;
typedef std::pair<ObjGame*, pair> movePieces;
typedef std::array<std::pair<bool, sf::Vector2f>, SIZE> dataPieces;
typedef std::array<std::unique_ptr<ObjGame>, SIZE> array;
typedef std::pair<ObjGame*, std::pair<char, size_t>> gPair;

const int SIZE = 16;
const int BOARD = 8;
const int PIECES_HEIGHT = 168;
const int PLACE_PIECES = 125;
