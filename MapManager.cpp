/**
 * notes:
 *   1，tmx::Map禁止使用'='傳遞地圖，這裡用std::move解決，
 *      地圖用完要記得還回去。
 *	 2，更新函式應放在遊戲回圈內才能刷新數據
 */

#include "MapManager.hpp"

MapManager::MapManager(int initMap)
{
	curMapID = initMap;

	//根據地圖個數建立地圖實體
	for (int i = 0; i < MAP_QTY; i++)
	{
		tmx::Map tmpMap;

		if (!tmpMap.load(this->mapPaths[i]))
		{
			//std::cerr << "can't find map form " << mapPaths[i] << std::endl;
			break;
		}
		std::cout << "MapManager: found map from" << mapPaths[i] << std::endl;

		mapList.emplace_back(std::move(tmpMap)); 
	}
	if (mapList.size() != MAP_QTY) //確認是否正確讀完地圖
	{
		std::cerr << "\nMapManager init failed" << std::endl;
	}
	else
	{
		std::cout << "\nMapManager init successed" << std::endl;
	}
	//初始化內部變量
	this->setCMap(std::move(mapList[curMapID]));
	this->loadCollisonObjs();
	this->setLayerQty();


	//建立初始圖層
	for (int i = 0; i < layerQty; i++)
	{
		layerList.emplace_back(new MapLayer(curCMap, i));
	}

	this->mapNameShow_Init();
	mapName_Show.setString(mapNames[curMapID]);
	clk.restart();
}

MapManager::~MapManager()
{
	this->delLayerPtr();
	mapList.clear();
}


void MapManager::update(const int mapNum, sf::Vector2f pos) //放在遊戲回圈內
{
	if (curMapID != mapNum) 
	{
		mapList[curMapID] = std::move(curCMap);      //把舊地圖所有權丟回給地圖清單

		this->setCurMap(mapNum);                     //更新地圖索引
		this->setCMap(std::move(mapList[curMapID])); //更新地圖實體
		this->setLayerQty();                         //更新圖層數量
		this->loadCollisonObjs();                    //更新碰撞框
		
		std::cout << "switched map to number " << curMapID << std::endl;
#ifdef DEBUG
		std::cout << "layerQty = " << layerQty << std::endl;
#endif // DEBUG

		this->delLayerPtr();

		for (int i = 0; i < layerQty; i++)            //根據新地圖更新所有圖層
		{
			layerList.emplace_back(new MapLayer(this->getCMap(), i));
		}

		mapName_Show.setString(mapNames[curMapID]);
		clk.restart();
	}
	this->showMapNameFor3Sec();
}

//MapLayer* MapManager::getLayers(int n)
//{
//	return layerList[n];
//}

void MapManager::draw(sf::RenderWindow& win, sf::View &v)
{
	for (auto& layer : layerList)
	{
		win.draw(*layer); 
	}

	win.setView(win.getDefaultView());
	mapName_Show.setPosition(win.getSize().x / 2.f - 
		                     mapName_Show.getGlobalBounds().width / 2.f, 50.f);
	win.draw(mapName_Show);
	win.setView(v);
}

void MapManager::setLayerQty()
{
	layerQty = curCMap.getLayers().size();
}

int MapManager::getLayerQty()
{
	return curCMap.getLayers().size();
}

int MapManager::getCurMap()
{
	return curMapID;
}

void MapManager::setCurMap(const int mapNum)
{
	curMapID = mapNum;
}

const tmx::Map& MapManager::getCMap()
{
	return curCMap;
}

void MapManager::setCMap(tmx::Map&& _cmap)
{
	curCMap = std::move(_cmap);
}

bool MapManager::isIntersect(sf::FloatRect fr)
{

	for (const auto& rect : collObjList)
	{
		//std::cout << "rect : " << " x = " << rect.left << " y = " << rect.top << " width = " << rect.width << " height = " << rect.height << std::endl;
		//std::cout << "fr   : " << " x = " << fr.left << " y = " << fr.top << " width = " << fr.width << " height = " << fr.height << std::endl;
		if (rect.intersects(fr)) return 1;
	}
	return 0;
}

void MapManager::mapNameShow_Init()
{
	if (!this->font.loadFromFile("./resources/arial.ttf")) { std::cerr << "font load failed" << std::endl; }
	mapName_Show.setFont(font);
	mapName_Show.setCharacterSize(60);
	mapName_Show.setFillColor(sf::Color::White);
	clk.restart();
}

void MapManager::showMapNameFor3Sec()
{
	if (clk.getElapsedTime().asSeconds() > 3)
	{
		mapName_Show.setString(""); 
	}
}

void MapManager::delLayerPtr()
{
	for (auto* layer : layerList) {
		delete layer;
	}
	layerList.clear();
}

void MapManager::loadCollisonObjs()
{
	collObjQty = 0;
	collObjList.clear();                          //清空碰撞框
	for (const auto& layer : curCMap.getLayers()) //遍歷圖層
	{
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			//
			const auto& objLayer = layer->getLayerAs<tmx::ObjectGroup>();
			if (objLayer.getName() == "collison")
			{
				for (const auto& obj : objLayer.getObjects())
				{
					float x      = obj.getPosition().x;
					float y      = obj.getPosition().y;
					float width  = obj.getAABB().width;
					float height = obj.getAABB().height;

					//轉乘sf::floatRect才能做碰撞檢測
					sf::FloatRect tmpFRect(x, y, width, height);
					collObjList.emplace_back(tmpFRect);
				}
				break;
			}
		}
	}
	collObjQty = collObjList.size();
#ifdef DEBUG
	std::cout << "collison Qty = " << collObjQty << std::endl;
	//for (const auto& co : collObjList)
	//{
	//	std::cout << " x = " << co.left << " y = " << co.top << " width = " << co.width << " height = " << co.height << std::endl;
	//}
#endif // DEBUG
}

std::vector<sf::FloatRect>& MapManager::getCollObjs()
{
	return collObjList;
}

bool MapManager::LoadMap(tmx::Map* _map, std::string mapPath)
{
	return _map->load(mapPath);
}
