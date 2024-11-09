#include "LifeEntity.hpp"

LifeEntity::LifeEntity(std::string _name, LiftEntityInitTypeDef* LifeEntityInitStruct)
    : maxHP(LifeEntityInitStruct->_maxHP),
      maxMP(LifeEntityInitStruct->_maxMP),
      HP(LifeEntityInitStruct->_HP),
      MP(LifeEntityInitStruct->_MP),
      phy_atk(LifeEntityInitStruct->_phy_atk),
      mag_atk(LifeEntityInitStruct->_mag_atk),
      phy_defense(LifeEntityInitStruct->_phy_defense),
      mag_defense(LifeEntityInitStruct->_mag_defense),
      spd(LifeEntityInitStruct->_spd) {}

int LifeEntity::getHP()
{ 
    return HP; 
}

int LifeEntity::getMP() 
{ 
    return MP; 
}

float LifeEntity::getSpd() 
{
    return spd; 
}

int LifeEntity::getDefense()
{
    return phy_defense + mag_defense; 
}

void LifeEntity::setHP(int newHP) 
{
    HP = (newHP > maxHP) ? maxHP : newHP; 
}

void LifeEntity::setMP(int newMP) 
{ 
    MP = (newMP > maxMP) ? maxMP : newMP;
}

void LifeEntity::setMaxHPMP(int newMaxHP, int newMaxMP) 
{ 
    maxHP = newMaxHP; 
    maxMP = newMaxMP; 
}

void LifeEntity::setSpd(float newSpd)
{
    spd = newSpd;
}

void LifeEntity::gainHP(int amount) 
{ 
    HP = (HP + amount > maxHP) ? maxHP : HP + amount; 
}

void LifeEntity::gainMP(int amount)
{ 
    MP = (MP + amount > maxMP) ? maxMP : MP + amount;
}

bool LifeEntity::isAlive() const
{ 
    return HP > 0;
}
