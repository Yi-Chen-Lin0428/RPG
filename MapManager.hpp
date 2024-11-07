/*********************************************************************
 * \file   MapManager.hpp
 * \brief  包含MapManager類別聲明，用於管理地圖相關操作。
 * "SFMLOrthogonalLayer.hpp"是tmxLite提供的正交2D地圖渲染器
 * 來源:https://github.com/fallahn/tmxlite/blob/master/SFMLExample/src/SFMLOrthogonalLayer.hpp
 * \author Lin, YiChen
 * \date   2024.11.7
 *********************************************************************/

#pragma once

#include "tmxlite/Map.hpp"
#include "SFMLOrthogonalLayer.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

#define MAP_WIDTH  (int)960 ///地圖寬度
#define MAP_HIGHTH (int)640 ///地圖高度
#define MAP_QTY    5        ///地圖數量

/**
 * \brief  管理所有地圖載入，切換，渲染，更新，碰撞檢測等操作
 */
class MapManager
{
public:
	MapManager(int initMap);
	~MapManager();
	void update(const int mapNum, sf::Vector2f);
	void draw(sf::RenderWindow& win, sf::View& v);
	void setLayerQty();
	int getLayerQty();
	int getCurMap();
	void setCurMap(const int mapNum);
	const tmx::Map& getCMap();
	void setCMap(tmx::Map&& _cmap);
	//void drawCurMap();
	bool isIntersect(const sf::FloatRect fr);
	std::vector<sf::FloatRect>& getCollObjs();

private:
	std::vector<tmx::Map> mapList;
	std::vector<MapLayer*> layerList;
	std::vector<sf::FloatRect> collObjList;

	tmx::Map curCMap;
	sf::Clock clk;
	sf::Font font;
	sf::Text mapName_Show;

	int curMapID;
	int layerQty;
	int collObjQty;

	void mapNameShow_Init();
	void showMapNameFor3Sec();

	void delLayerPtr();
	bool LoadMap(tmx::Map* _map, std::string mapPath); //unused
	void loadCollisonObjs();

	enum mapNum
	{
		hall,
		matrix,
		yard,
		garage,
		gas_tation
	};

	std::string mapPaths[5] = {
		"./resources/hall.tmx",
		"./resources/matrix.tmx",
		"./resources/yard.tmx",
		"./resources/garage.tmx",
		"./resources/gas_station.tmx"
	};

	std::string mapNames[MAP_QTY] = {
		"Hall", 
		"Matrix", 
		"Yard", 
		"Garage", 
		"Gas Station"
	};
};



