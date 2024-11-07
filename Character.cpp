#include "Character.hpp"


Character::Character(int _role)
{
    role = _role; //角色選擇
    this->initTexture();
    this->initSprite();
    this->initPos(sf::Vector2f(170.f, 250.f)); //在大廳的初始位置
    this->setSpd(5);
}

Character::~Character()
{

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

void Character::setSpd(int s)
{
    spd = s;
}

int Character::getSpd()
{
    return spd;
}

void Character::update(std::vector<sf::FloatRect>& fr)
{
    dis = sf::Vector2f(0.f, 0.f);
    lastPos = this->getPos();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        dis.y -= spd;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        dis.y += spd;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        dis.x -= spd;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        dis.x += spd;
    }

    nextBnds = this->getGBnds();
    nextBnds.left += dis.x;
    nextBnds.top += dis.y;

    isCollided = this->isIntersect(nextBnds, fr);

    if (!isCollided) { player.move(dis); }
    else { this->setPos(lastPos); }

}

void Character::draw(sf::RenderWindow& win)
{
    win.draw(player);
}

sf::FloatRect Character::getGBnds()
{
    return player.getGlobalBounds();
}

bool Character::isIntersect(sf::FloatRect fr, std::vector<sf::FloatRect>& frList)
{
    for (const auto& rect : frList)
    {
        //std::cout << "rect : " << " x = " << rect.left << " y = " << rect.top << " width = " << rect.width << " height = " << rect.height << std::endl;
        //std::cout << "fr   : " << " x = " << fr.left << " y = " << fr.top << " width = " << fr.width << " height = " << fr.height << std::endl;
        if (rect.intersects(fr)) return 1;
    }
    return 0;
}


void Character::initTexture()
{
    if (!characterTexture.loadFromFile("./resources/Player_idle.png", sf::IntRect(0, 0, 32, 32)))
    {
        std::cerr << "character Texture load failed! " << std::endl;
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