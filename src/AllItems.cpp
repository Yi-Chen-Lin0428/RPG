#include "AllItems.hpp"


void _updateSprite(sf::Sprite& s, const sf::Vector2f& _playerPos, Direction _movement, sf::Vector2f& _dis)
{
    if (_dis != sf::Vector2f(0.f, 0.f))
    {
        switch (_movement)
        {
            case Direction::Up:
                s.setRotation(270);
                s.setPosition(_playerPos.x, _playerPos.y + 30);
                break;
            case Direction::Down:
                s.setRotation(90);
                s.setPosition(_playerPos.x + 30, _playerPos.y + 5);
                break;
            case Direction::Left:
                s.setRotation(180);
                s.setPosition(_playerPos.x + 30, _playerPos.y + 40);
                break;
            case Direction::Right:
                s.setRotation(0);
                s.setPosition(_playerPos.x, _playerPos.y);
                break;
            }
    }
    else
    {
        s.setRotation(90);
        s.setPosition(_playerPos.x + 30, _playerPos.y + 5);
    }
}

////////////////////////////////////////////////////////////////////////////
///                                                                      ///
///                               基礎類別                                ///
///                                                                      ///
////////////////////////////////////////////////////////////////////////////

/*-----------------------基礎武器類別定義-----------------------*/
Weapon::Weapon(std::string _name, int _size, int _price, int _damage, int _atkSpeed, std::string texturePath)
    : name(_name), size(_size), price(_price), damage(_damage), atkSpeed(_atkSpeed)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cout << "ERROR: weapon texture load failed " << std::endl;
    }
    sprite.setTexture(texture);
}

void Weapon::init()
{
    BBox.setSize(sf::Vector2f(32, 32));
    BBox.setFillColor(sf::Color::Transparent);
    BBox.setOutlineThickness(1.f);
    sprite.setScale(1.5, 1.5);
}

void Weapon::update(const sf::Vector2f& _playerPos, Direction _movement, sf::Vector2f& _dis)
{
    _updateSprite(sprite, _playerPos, _movement, _dis);
}

void Weapon::draw(sf::RenderWindow& win)
{
    win.draw(sprite);
}

const sf::Vector2f Weapon::getPos()
{
    return sprite.getPosition();
}

void Weapon::setPos(float x, float y)
{
    sprite.setPosition(sf::Vector2f(x, y));
}

const sf::Sprite Weapon::getSprite()
{
    return sprite;
}

const std::string Weapon::getName() const
{
    return name;
}

const int Weapon::getWeight() const
{
    return size;
}

const int Weapon::getDamage() const
{
    return damage;
}

const int Weapon::getPrice() const
{
    return price;
}

void Weapon::attack(sf::Vector2f target_pos, sf::Vector2f playerPos) {}
/*-----------------------基礎武器類別定義-----------------------*/


/*-----------------------基礎防具類別定義-----------------------*/
Armor::Armor(std::string _name, int _size, int _price, int _defenseVal, std::string texturePath)
    : name(_name), size(_size), price(_price), defenseVal(_defenseVal)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cout << "ERROR: armor texture load failed " << std::endl;
    }
    sprite.setTexture(texture);
}

sf::Sprite Armor::getSprite()
{
    return sprite;
}

std::string Armor::getName() const
{
    return name;
}

int Armor::getWeight() const
{
    return size;
}

void Armor::defense() {}
/*-----------------------基礎防具類別定義-----------------------*/


/*-----------------------基礎藥水類別定義-----------------------*/
Potion::Potion(std::string _name, int _size, int _price, int _val, std::string texturePath)
    :name(_name), size(_size), price(_price), val(_val)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cout << "ERROR: potion texture load failed " << std::endl;
    }
    sprite.setTexture(texture);
}

sf::Sprite Potion::getSprite()
{
    return sprite;
}

std::string Potion::getName() const
{
    return name;
}

int Potion::getWeight() const
{
    return size;
}

void Potion::use() {}
/*-----------------------基礎藥水類別定義-----------------------*/




////////////////////////////////////////////////////////////////////////////
///                                                                      ///
///                               衍生類別                                ///
///                                                                      ///
////////////////////////////////////////////////////////////////////////////

/*-----------------------斧頭類別定義-----------------------*/
Ax::Ax() : Weapon("ax", 10, 20, 10, 10, "./resources/shop/ax.png") {}

void Ax::attack(sf::Vector2f target_pos, sf::Vector2f playerPos) {}

Weapon* Ax::clone() const 
{
    return new Ax();
}

/*-----------------------手槍類別定義-----------------------*/
Pistol::Pistol() : Weapon("pistol", 20, 150, 30, 30, "./resources/shop/pistol.png") {}

void Pistol::attack(sf::Vector2f target_pos, sf::Vector2f playerPos) {}

Weapon* Pistol::clone() const
{
    return new Pistol();
}

/*-----------------------步槍類別定義-----------------------*/
Rifle::Rifle() : Weapon("rifle", 40, 200, 50, 60, "./resources/shop/rifle.png"), dir(Direction::Idle) {}

void Rifle::update(const sf::Vector2f& _playerPos, Direction _movement, sf::Vector2f& _dis)
{
    dir = _movement;

    //更新武器位置
    _updateSprite(sprite, _playerPos, _movement, _dis);

    //更新子彈
    for (auto& bullet : bulletList)
    {
        bullet.update(0.016f);
    }

    //檢查並移除失效子彈
    bulletList.erase(std::remove_if(bulletList.begin(), bulletList.end(), 
                                    [](const Bullet& b) {return !b.isAlive(); }), 
                     bulletList.end());
}

void Rifle::draw(sf::RenderWindow& win)
{
    win.draw(sprite);

    for (auto& bullet : bulletList)
    {
        bullet.draw(win);
    }
}

void Rifle::attack(sf::Vector2f target_pos, sf::Vector2f playerPos)
{
    float attackInterval = 5.0f / atkSpeed; 

    if (fireSpd.getElapsedTime().asSeconds() < attackInterval) { return; }
    fireSpd.restart();

    bulletList.emplace_back(playerPos, target_pos, 1000.f); // 修正为目标方向
}

Weapon* Rifle::clone() const
{
    return new Rifle();
}

/*-----------------------小刀類別定義-----------------------*/
Knife::Knife() : Weapon("knife", 1, 1, 5, 2, "./resources/shop/Knife.png") {}

void Knife::attack(sf::Vector2f target_pos, sf::Vector2f playerPos) {}

Weapon* Knife::clone() const
{
    return new Knife();
}

/*-----------------------霰彈槍類別定義-----------------------*/
Pump::Pump() : Weapon("pump", 80, 300, 100, 10, "./resources/shop/pump.png") {}

void Pump::attack(sf::Vector2f target_pos, sf::Vector2f playerPos) {}

Weapon* Pump::clone() const
{
    return new Pump();
}

/*-----------------------空物品類別定義-----------------------*/
None::None() : Weapon("none", 0, 0, 0, 0, "./resources/shop/unstock.png") {}

void None::attack(sf::Vector2f target_pos, sf::Vector2f playerPos) {}

Weapon* None::clone() const
{
    return new None();
}

/*-----------------------子彈類別定義-----------------------*/
Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, float speed)
    : position(pos), speed(speed), alive(true)
{
    shape.setRadius(5.f); 
    shape.setFillColor(sf::Color::Red);    
    shape.setPosition(position);

    // 計算單位方向向量
    float magnitude = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    velocity = (magnitude == 0.0f) ? sf::Vector2f(0.f, 0.f) : dir / magnitude * speed;
}

void Bullet::update(float dt) {
    if (!alive) return;

    position += velocity * dt;
    shape.setPosition(position);
    
    if (position.x < 0 || position.x > 960 || position.y < 0 || position.y > 640) {
        alive = false; 
    }
}

void Bullet::draw(sf::RenderWindow& window) {
    if (alive) {
        window.draw(shape);
    }
}

bool Bullet::isAlive() const {
    return alive;
}


