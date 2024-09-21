#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>



namespace TetrisGame{
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveDown,
		Rotate,
		Drop,
		Hold,
		ActionCount
	};
}


namespace TetrisBlocks
{
	enum BlockType
	{
			T,
			I,
			S,
			Z,
			L,
			J,
			SQ,
			BlockTypeCount
	};
	
	enum Material
	{
		None          = 0,       // 0
		InActiveBlock = 1,
		Floor         = 2,
		Wall				  = 3,
		ActiveBlock   = 4,
	};
	
	static std::map<BlockType, sf::Color> mapColor = {
		{BlockType::T, sf::Color(102, 0, 102)},
		{BlockType::I, sf::Color(64, 164, 223)},
		{BlockType::S, sf::Color(123, 200, 80)},
		{BlockType::Z, sf::Color(136, 0, 0)},
		{BlockType::J, sf::Color(0, 128, 255)},
		{BlockType::L, sf::Color(255, 102, 102)},
		{BlockType::SQ, sf::Color(255, 204, 51)},
		{BlockType::BlockTypeCount, sf::Color(0, 0, 0, 0)}
	};
}

struct TetrisBoardSpec 
{

	TetrisBoardSpec(int numGridx_,
									int numGridy_,
									int sizeGrid_,
									sf::Color colorBoundary_,
									sf::Color colorLine_,
									sf::Vector2i posBoard_,
									sf::Vector2i locationSpawn_)
	:	numGridx(numGridx_)
	, numGridy(numGridy_)
	, sizeGrid(sizeGrid_)
	, colorBoundary(colorBoundary_)
	, colorLine(colorLine_)
	, posBoard(posBoard_)
	, locationSpawn(locationSpawn_)
	{

	}
		TetrisBoardSpec()
	:	numGridx(26)
	, numGridy(12)
	, sizeGrid(20)
	, colorBoundary(sf::Color(0, 0, 0, 0))
	, colorLine(sf::Color(0, 0, 0, 0))
	, posBoard(sf::Vector2i(150, 50))
	, locationSpawn(sf::Vector2i(13, 0))
	{

	}
	
	// 	TetrisBoardSpec()
	// :	numGridx(26)
	// , numGridy(12)
	// , sizeGrid(20)
	// , colorBoundary(sf::Color(0, 0, 0, 0))
	// , colorLine(sf::Color(0, 0, 0, 0))
	// , posBoard(sf::Vector2i(150, 50))
	// , locationSpawn(sf::Vector2i(13, 0))
	// {

	// }
	int numGridx;
	int numGridy;
	int sizeGrid;
	sf::Color colorBoundary;
	sf::Color colorLine;
	sf::Vector2i posBoard;
	sf::Vector2i locationSpawn;
};

	// int keyboardSensitivity;