// Card.cpp for Pyramid Solitaire
#ifndef CARD_CPP 
#define CARD_CPP
//#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include<string>
//include header files
#include<Card.hpp>


//public methods
Card::Card(std::string sym, std::string st, std::string clr, int val, std::shared_ptr<sf::Sprite> p_spr, 
std::shared_ptr<sf::Sprite> p_bk_spr):
    symbol(sym),
    suit(st),
    color(clr),
    value(val),
    p_sprite(p_spr),
    p_back_sprite(p_bk_spr),
    faceUp(false)
{}

Card::~Card() {}

std::string Card::getSymbol() {
    return symbol;
}
std::string Card::getSuit() {
    return suit;
}
std::string Card::getColor() {
    return color;
}
int Card::getValue() {
    return value;
}
std::shared_ptr<sf::Sprite> Card::getPSprite() {
    if (faceUp == true) {
        return p_sprite;
    }
    return p_back_sprite; 
}
bool Card::getFaceUp() {
    return faceUp;
}
void Card::setFaceUp(bool b) {
    faceUp = b;
}


#endif