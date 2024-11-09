#include "Text.hpp"

Text::Text(){}

Text::~Text(){}


void Text::initText(int _size, std::string _s_string, sf::Color _color, bool setOrgAtCenter, std::string _font, sf::Uint32 _style)
{
    size = _size;
    color = _color;
    s_string = _s_string;
    font_t = _font;
    style = _style;

    sf::String unicodeString = sf::String::fromUtf8(s_string.begin(), s_string.end());

    if (!font.loadFromFile("./resources/" + font_t + ".ttf"))
    {
        std::cerr << "ERROR: font load failed" << std::endl;
    }

    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(style);
    text.setString(unicodeString);
    textRect = text.getLocalBounds();

    if (setOrgAtCenter)
    {
        text.setOrigin(sf::Vector2f(textRect.width / 2 + text.getPosition().x,
                                    textRect.height / 2 + text.getPosition().y));
    }
}

void Text::initText(int _size, int _s_string, sf::Color _color, bool setOrgAtCenter, std::string _font, sf::Uint32 _style)
{
    size = _size;
    color = _color;
    s_string = std::to_string(_s_string);
    font_t = _font;
    style = _style;

    //text.setPosition(sf::Vector2f(0.f, 0.f));

    if (!font.loadFromFile("./resources/" + font_t + ".ttf"))
    {
        std::cerr << "ERROR: font load failed" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setStyle(style);
    text.setString(s_string);
    textRect = text.getLocalBounds();
    if (setOrgAtCenter)
    {
        text.setOrigin(sf::Vector2f(textRect.width / 2 + text.getPosition().x,
                                    textRect.height / 2 + text.getPosition().y));
    }
}

void Text::setPos(float x, float y)
{
    text.setPosition(x, y);
}
