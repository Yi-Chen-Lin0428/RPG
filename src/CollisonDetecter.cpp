#include "CollisonDetecter.hpp"

std::unordered_map<std::string, int> getTriggerType =
{
    {"sw2map0", 0},
    {"sw2map1", 1},
    {"sw2map2", 2},
    {"sw2map3", 3},
    {"sw2map4", 4},
    {"blood_bag", 5},
    {"shop1", 6},
    {"shop2", 7},
    {"shop3", 8},
    {"bed", 9}
};

bool collisonDetect(sf::FloatRect playerRect, std::vector<sf::FloatRect>& obstacleList)
{
    for (const auto& rect : obstacleList)
    {
        if (rect.intersects(playerRect)) return true;
        
    }
    return false;
}


std::pair<triggerObj_typedef, bool> collisonDetect(sf::FloatRect playerRect, std::vector<triggerObj_typedef>& obstacleList)
{
    for (const auto& obstacleStruct : obstacleList)
    {
        if (obstacleStruct.oRect.intersects(playerRect))
        {
            return{ obstacleStruct, true };
        }
    }
    return { triggerObj_typedef{}, false };
}
