#include "Character.hpp"

LiftEntityInitTypeDef* Character::initLifeEntity()
{
    LiftEntityInitTypeDef s;
    s._maxHP = 500;
    s._maxMP = 100;
    s._HP = 500;
    s._MP = 100;
    s._phy_atk = 70;
    s._mag_atk = 30;
    s._phy_defense = 50;
    s._mag_defense = 20;
    s._spd = 5;

    return &s;
}

Character::Character(EventSystem& _eventSys, int _role, std::string _name, int _initMap)
    :eventSys(_eventSys), role(_role), LifeEntity(_name, initLifeEntity())
{
    /*------------------註冊call back函式------------------*/
    eventSys.subscribe<moveMentEvent>(EventType::e_moveMent, [this](moveMentEvent& eve)
    {
        this->moveMentEventHandler(eve);
    });
    eventSys.subscribe<equipEvent>(EventType::e_equip, [this](equipEvent& eve)
    {
        this->equipEventHandler(eve);
    });
    eventSys.subscribe<attackEvent>(EventType::e_attack, [this](attackEvent& eve)
    {
        this->attackEventHandler(eve);
    });
    /*----------------------------------------------------*/
    this->initTexture();
    this->initAnimation();
    this->initSprite();
    this->initPos(mapInitPos[_initMap]); //在大廳的初始位置
    name.initText(18, _name, sf::Color::Yellow, 1, "Arial");

    playerBBox.setFillColor(sf::Color::Transparent);
    playerBBox.setOutlineThickness(1.f);
    playerBBox.setSize(sf::Vector2f(getGBnds().width, getGBnds().height));

    weapon = Rifle().clone();
    weapon->init();
    std::cout << "INFO: current weapon is " << this->weapon->getName() << std::endl;
    std::cout << "INFO: Character init successes" << std::endl;
}

Character::~Character()
{
    delete animationComponent;
    delete weapon;
}

sf::Vector2f Character::getPos()
{
    return player.getPosition();
}

void Character::setPos(sf::Vector2f pos)
{
    player.setPosition(pos);
}

void Character::move(sf::Vector2f d)
{
    player.move(d);
}

//TODO : 移動速度補償 
void Character::update(std::vector<sf::FloatRect>& fr)
{
    //每張地圖初始位置設定
    static int lastMap = curMap;
    
    if (curMap != lastMap)
    {
        player.setPosition(curMap == 0 ? lastPos : mapInitPos[curMap]);
        lastMap = curMap;
    }
    dis = sf::Vector2f(0.f, 0.f);

    /*----------------------------角色移動處理--------------------------*/
    Direction movement = Direction::Idle;
    if (dir.up    && !UIListening) { movement = Direction::Up;    dis.y -= getSpd(); }
    if (dir.down  && !UIListening) { movement = Direction::Down;  dis.y += getSpd(); }
    if (dir.left  && !UIListening) { movement = Direction::Left;  dis.x -= getSpd(); }
    if (dir.right && !UIListening) { movement = Direction::Right; dis.x += getSpd(); }

    this->updateAnimation(movement);
    this->collisonHandler(fr);
    /*-----------------------------------------------------------------*/
    name.text.setPosition(getPos() + sf::Vector2f(16.f, -20.f)); //更新名字位置
    playerBBox.setPosition(getPos());
    /*--------------------------武器顯示位置處理------------------------*/
    weapon->update(getPos(), movement, dis);
    if (changeWeapon)
    {
        weapon->init();
        changeWeapon = 0;
    }
    /*-----------------------------------------------------------------*/
}

void Character::draw(sf::RenderWindow& win)
{
    win.draw(name.text);
    win.draw(player);
#ifdef DEBUG //顯示邊界框
    win.draw(playerBBox);
    if (weapon != nullptr)
    {
        weapon->draw(win);
    }
#endif // DEBUG
}

sf::FloatRect Character::getGBnds()
{
    return player.getGlobalBounds();
}

void Character::updateAnimation(Direction _movement)
{
    if (dis != sf::Vector2f(0.f, 0.f))
    {
        switch (_movement)
        {
            case Direction::Up:    animationComponent->play("WALK_UP",    0.016f, dis.y, getSpd()); break;
            case Direction::Down:  animationComponent->play("WALK_DOWN",  0.016f, dis.y, getSpd()); break;
            case Direction::Left:  animationComponent->play("WALK_LEFT",  0.016f, dis.x, getSpd()); break;
            case Direction::Right: animationComponent->play("WALK_RIGHT", 0.016f, dis.x, getSpd()); break;
        }
    }
    else
    {
        animationComponent->play("IDLE", 0.016f);
    }
}

void Character::triggerHandler(std::vector<triggerObj_typedef>& triggerObjList)
{
    triggerObj_typedef trigStruct;
    static bool isCollided = 0, isCollided_ls = 0;

    if (moved)
    {
        std::tie(trigStruct, isCollided) = collisonDetect(getGBnds(), triggerObjList);
        if (isCollided == 1 && isCollided_ls == 0) //只觸發一次
        {
            isCollided_ls = isCollided;

            if (trigStruct.oClass == "portal") //傳送門偵測並發布事件
            {
                mapSwitchEvent eve(0);
                switch (getTriggerType[trigStruct.oName])
                {
                case sw2map1:
                    lastPos = getPos();
                    eve = mapSwitchEvent(1);
                    curMap = 1;
                    break;
                case sw2map2:
                    lastPos = getPos();
                    eve = mapSwitchEvent(2);
                    curMap = 2;
                    break;
                case sw2map3:
                    lastPos = getPos();
                    eve = mapSwitchEvent(3);
                    curMap = 3;
                    break;
                case sw2map4:
                    lastPos = getPos();
                    eve = mapSwitchEvent(4);
                    curMap = 4;
                    break;
                case sw2map0:
                    eve = mapSwitchEvent(0);
                    curMap = 0;
                }
                eventSys.publish(eve);
            }
            else if (trigStruct.oClass == "shop")
            {
                openShopEvent shopEve(0);
                switch (getTriggerType[trigStruct.oName])
                {
                case shop1: shopEve = openShopEvent(1); break;
                case shop2: shopEve = openShopEvent(2); break;
                case shop3: shopEve = openShopEvent(3); break;
                default:    shopEve = openShopEvent(0); break;
                }
                eventSys.publish(shopEve);
            }
#if DEBUG
            std::cout << "INFO: "
                << std::setw(10) << std::left << "Trigger Class"
                << ": " << std::setw(10) << trigStruct.oClass
                << " | " << "Name"
                << ": " << trigStruct.oName << std::endl;
#endif // DEBUG
        }
        if (isCollided != isCollided_ls) isCollided_ls = isCollided;
    }
}

void Character::collisonHandler(std::vector<sf::FloatRect>& fr)
{
    sf::Vector2f _lastPos = getPos();
    if (dis != sf::Vector2f(0.f, 0.f)) {

        nextBnds = getGBnds();
        nextBnds.left += dis.x;
        if (collisonDetect(nextBnds, fr))
        {
            dis.x = 0;
            playerBBox.setOutlineColor(sf::Color::Red);
        }else { playerBBox.setOutlineColor(sf::Color::Green); }
        
        nextBnds = getGBnds();
        nextBnds.top += dis.y;
        if (collisonDetect(nextBnds, fr))
        {
            dis.y = 0;
            playerBBox.setOutlineColor(sf::Color::Red);
        }
        player.move(dis);
        moved = 1;
    }
    else 
    {
        playerBBox.setOutlineColor(sf::Color::Green);
        player.setPosition(_lastPos);
        moved = 0;
    }
}

void Character::initAnimation()
{
    animationComponent = new AnimationComponent(player, characterTexture);

    animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 32, 32);
    animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 32, 32);
    animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 32, 32);
    animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 32, 32);
    animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 32, 32);
    animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 32, 32);
    animationComponent->play("IDLE", 0.016f);
}

void Character::initTexture()
{
    if (!characterTexture.loadFromFile("./resources/PLAYER_SHEET2.png"))
    {
        std::cerr << "ERROR: character Texture load failed! " << std::endl;
    }
}

void Character::initSprite()
{
    player.setTexture(characterTexture);
}

void Character::initPos(sf::Vector2f pos)
{
    this->setPos(pos);
}

void Character::attackEventHandler(attackEvent& eve)
{
    //std::cout << "INFO: attack!!!" << std::endl
    sf::Vector2f worldMousePos = eve.win->mapPixelToCoords(static_cast<sf::Vector2i>(eve.mousePos));
    sf::Vector2f targetPos = worldMousePos - getPos();
    weapon->attack(targetPos, getPos());
}

/**
 * note 因為武器裝備後sprite位置會被改變，
 *      防止物品丟回背包後顯示位置不對，
 *      這裡丟回去的是物品的克隆，也就是新的實體
 * 
 * \param eve
 */

void Character::equipEventHandler(equipEvent& eve)
{
    changeWeapon = 1;
    boughtEvent boughtEve(weapon->clone());    //把現在裝備的武器丟回背包
    eventSys.publish(boughtEve);
    weapon = nullptr;

    weapon = eve.weapon;
    std::cout << "INFO: current weapon is " << weapon->getName() << std::endl;
}

void Character::moveMentEventHandler(moveMentEvent& eve)
{
    dir = eve.dir;
    UIListening = eve.isUIListening;
}
