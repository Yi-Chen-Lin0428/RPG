#pragma once

#ifndef _LIFE_ENTITY_
#define _LIFE_ENTITY_

#include <iostream>

typedef struct
{
	int _maxHP, _maxMP;
	int _HP, _MP;
	int _phy_atk, _mag_atk;
	int _phy_defense, _mag_defense;
	float _spd;
}LiftEntityInitTypeDef;


class LifeEntity
{
public:
	LifeEntity(std::string _name, LiftEntityInitTypeDef* LifeEntityInitStruct);
	~LifeEntity() = default;

	int getHP();
	int getMP();
	float getSpd();
	int getAtk();
	int getDefense();

	void setHP(int);
	void setMP(int);
	void setMaxHPMP(int, int);
	void setSpd(float);

	void gainHP(int);
	void gainMP(int);

	bool isAlive() const;

private:
	std::string name;
	int maxHP, maxMP;
	int HP, MP;
	int phy_atk, mag_atk;
	int phy_defense, mag_defense;
	float spd;
	//int power;
};

#endif // _LIFE_ENTITY_
