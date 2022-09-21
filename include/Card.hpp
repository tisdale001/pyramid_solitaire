// Card.hpp for Pyramid Solitaire
#ifndef CARD_HPP 
#define CARD_HPP
#include <SFML/Graphics/Sprite.hpp>
#include<string>
#include<memory>

class Card {
    private:
    std::string symbol;
    std::string suit;
    std::string color;
    int value;
    std::shared_ptr<sf::Sprite> p_sprite;
    std::shared_ptr<sf::Sprite> p_back_sprite;
    bool faceUp;

    public:
    Card(std::string sym, std::string st, std::string clr, int val, std::shared_ptr<sf::Sprite> p_spr, 
    std::shared_ptr<sf::Sprite> p_bk_spr);
    ~Card();
    std::string getSymbol();
    std::string getSuit();
    std::string getColor();
    int getValue();
    std::shared_ptr<sf::Sprite> getPSprite();
    bool getFaceUp();
    void setFaceUp(bool);
    
};

#endif