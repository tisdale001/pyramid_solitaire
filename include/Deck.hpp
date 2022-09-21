// Deck.hpp
// header file for a deck of cards for solitaire
#ifndef DECK_HPP 
#define DECK_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>

#include <Card.hpp>

class Deck {
    private:
    std::vector<std::shared_ptr<Card>> deckOfCards;
    std::vector<std::shared_ptr<sf::Image>> pImageVec;
    std::vector<std::shared_ptr<sf::Image>> pBackImageVec;
    std::vector<std::shared_ptr<sf::Texture>> pTextureVec;
    std::vector<std::shared_ptr<sf::Texture>> pBackTextureVec;
    std::vector<std::shared_ptr<sf::Sprite>> pFrontSpriteVec;
    std::vector<std::shared_ptr<sf::Sprite>> pBackSpriteVec;
    float scaleX = .50;
    float scaleY = .50;

    protected:
    void createDeck();
    

    public:
    Deck();
    ~Deck();
    void shuffleDeck();
    bool isEmpty();
    int dealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    int deal3Cards(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    void returnCards(std::shared_ptr<std::vector<std::shared_ptr<Card>>>);
    std::shared_ptr<sf::Sprite> getTopSprite();
};



#endif