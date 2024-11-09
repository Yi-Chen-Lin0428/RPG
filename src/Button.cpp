#include "Button.hpp"



Button::Button(std::string _name, sf::Vector2f pos, std::string texturePath, int w, int h, float xScale, float yScale)
    : name(_name), lastState(0), currentState(0)
{
    btn.setScale(xScale, yScale);

    if (!btnTexture.loadFromFile(texturePath))
    {
        std::cerr << "ERROR: button Texture load failed! " << std::endl;
    }
    this->animationComponent = new AnimationComponent(btn, btnTexture);

    animationComponent->addAnimation("idle",      0.2f, 0, 0, 0, 0, w, h);
    animationComponent->addAnimation("mouseover", 0.2f, 1, 0, 0, 0, w, h);
    animationComponent->addAnimation("clicked",   0.2f, 2, 0, 0, 0, w, h);
    animationComponent->play("idle", 0.016f);
    btn.setPosition(pos);
}

Button::~Button() 
{
    delete this->animationComponent;
}

int Button::getState(MouseState& _mouseState)
{
    mouseState = _mouseState;
    int newState;

    _currentState = isClicked();
    if (_currentState == 1 && lastState == 0) //¥¿½tÄ²µo
    {
        lastState = _currentState;
        newState = clicked;
    }
    else if (isMouseOver())
    {
        newState = mouseOver;
    }
    else
    {
        newState = idle;
    }

    if (_currentState != lastState)
    {
        lastState = _currentState;
    }



    if (newState != currentState) {
        currentState = newState;
        switch (currentState) {
        case clicked:
            animationComponent->play("clicked", 0.016f);
            break;
        case mouseOver:
            animationComponent->play("mouseover", 0.016f);
            break;
        case idle:
            animationComponent->play("idle", 0.016f);
            break;
        }
    }

    return currentState;
}

sf::Sprite Button::getSprite()
{
    return btn;
}

std::string Button::getName()
{
    return name;
}

bool Button::isClicked()
{
    sf::FloatRect bounds = btn.getGlobalBounds();
    return (bounds.contains(static_cast<sf::Vector2f>(mouseState.pos)) && mouseState.left == 1);
}

bool Button::isMouseOver()
{
    sf::FloatRect bounds = btn.getGlobalBounds();
    return bounds.contains(static_cast<sf::Vector2f>(mouseState.pos));
}

void Button::initAnimation()
{

}

