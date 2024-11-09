/*********************************************************************
 * \file   MapManager.hpp
 * \brief  地圖管理器，負責地圖加載，圖層渲染，地圖切換，並可返回地圖所有資源
 *	       渲染庫: "SFMLOrthogonalLayer.hpp"是tmxLite提供的正交2D地圖渲染器
 *		   來源:https://github.com/fallahn/tmxlite/blob/master/SFMLExample/src/SFMLOrthogonalLayer.hpp
 * 
 * registered func:
 *     -mapSwitchEventHandler(mapSwitchEvent& eve)
 * 
 * \author Lin, YiChen
 * \date   2024.11.7
 *********************************************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "tmxlite/Map.hpp"
#include "SFMLOrthogonalLayer.hpp"
#include "Text.hpp"
#include "EventSystem.hpp"
#include "CollisonDetecter.hpp"


#define MAP_WIDTH  (int)960 ///地圖寬度
#define MAP_HIGHTH (int)640 ///地圖高度
#define MAP_QTY    5        ///地圖數量

/**
 * \brief  管理所有地圖載入，切換，渲染，更新，碰撞檢測等操作
 */
class MapManager
{
public:
	MapManager(EventSystem& eventSys, int initMap);
	~MapManager();
	void update();
	void draw(sf::RenderWindow& win);
	void setLayerQty();
	int getLayerQty();
	int getCurMap();
	void setCurMap(const int mapNum);
	const tmx::Map& getCMap();
	void setCMap(tmx::Map&& _cmap);
	std::vector<sf::FloatRect>& getCollObjs();
	std::vector<triggerObj_typedef>& getTriggerObjs();

private:
	bool LoadMap(tmx::Map* _map, std::string mapPath); //unused
	template <class T>
	void loadObjs(std::vector<T>& RectList, std::string layerName);
	void showMapNameFor3Sec();
	void delLayerPtr();

	void mapSwitchEventHandler(mapSwitchEvent& eve);

	EventSystem& eventSys;
	Text mapName_Show;
	std::vector<tmx::Map> mapList;
	std::vector<MapLayer*> layerList;
	std::vector<sf::FloatRect> collObjList;
	std::vector<triggerObj_typedef> triggerObjList;
	tmx::Map curCMap;
	sf::Clock clk;
	sf::Font font;

	int curMapID;   
	int lastMapID;
	int layerQty;

	enum mapNum
	{
		hall,
		matrix,
		yard,
		garage,
		gas_tation
	};

	std::string mapNames[MAP_QTY] = {
		"Hall", 
		"Matrix", 
		"Yard", 
		"Garage", 
		"Gas_Station"
	};
};



