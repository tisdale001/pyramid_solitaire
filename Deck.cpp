// deck.cpp
// a deck of cards for pyramid solitaire
//g++ -std=c++17 Card.cpp Deck.cpp -I./include/ -o deck -lsfml-graphics -lsfml-window -lsfml-system
#ifndef DECK_CPP 
#define DECK_CPP

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <Deck.hpp>


void Deck::createDeck() {
    // create front images
    std::vector<std::string> INameVec{"../aceOfHearts.png", "../twoOfHearts.png", "../threeOfHearts.png", 
    "../fourOfHearts.png", "../fiveOfHearts.png", "../sixOfHearts.png", "../sevenOfHearts.png", "../eightOfHearts.png",
    "../nineOfHearts.png", "../tenOfHearts.png", "../jackOfHearts.png", "../queenOfHearts.png", "../kingOfHearts.png",
    "../aceOfDiamonds.png", "../twoOfDiamonds.png", "../threeOfDiamonds.png", "../fourOfDiamonds.png", "../fiveOfDiamonds.png",
    "../sixOfDiamonds.png", "../sevenOfDiamonds.png", "../eightOfDiamonds.png", "../nineOfDiamonds.png", "../tenOfDiamonds.png",
    "../jackOfDiamonds.png", "../queenOfDiamonds.png", "../kingOfDiamonds.png", "../aceOfSpades.png", "../twoOfSpades.png", 
    "../threeOfSpades.png", "../fourOfSpades.png", "../fiveOfSpades.png", "../sixOfSpades.png", "../sevenOfSpades.png",
    "../eightOfSpades.png", "../nineOfSpades.png", "../tenOfSpades.png", "../jackOfSpades.png", "../queenOfSpades.png", 
    "../kingOfSpades.png", "../aceOfClubs.png", "../twoOfClubs.png", "../threeOfClubs.png", "../fourOfClubs.png", "../fiveOfClubs.png",
    "../sixOfClubs.png", "../sevenOfClubs.png", "../eightOfClubs.png", "../nineOfClubs.png", "../tenOfClubs.png", 
    "../jackOfClubs.png", "../queenOfClubs.png", "../kingOfClubs.png"}; // change this to all .png files
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Image> p_image = std::make_shared<sf::Image>();
        p_image->loadFromFile(INameVec[i]);
        pImageVec.push_back(p_image);
    }
    // create front textures
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Texture> p_texture = std::make_shared<sf::Texture>();
        p_texture->loadFromImage(*pImageVec[i]);
        pTextureVec.push_back(p_texture);
    }
    // create front sprites
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Sprite> p_sprite = std::make_shared<sf::Sprite>();
        p_sprite->setTexture(*pTextureVec[i]);
        p_sprite->setScale(scaleX, scaleY);
        pFrontSpriteVec.push_back(p_sprite);
    }
    //create back image
    std::shared_ptr<sf::Image> p_back_image = std::make_shared<sf::Image>();
    p_back_image->loadFromFile("../backOfCard.png"); //add backOfCard.png here
    pBackImageVec.push_back(p_back_image);
    // create back texture
    std::shared_ptr<sf::Texture> p_back_texture = std::make_shared<sf::Texture>();
    p_back_texture->loadFromImage(*pBackImageVec[0]);
    pBackTextureVec.push_back(p_back_texture);
    // create back sprites
    for (int i = 0; i < 52; i++) {
        std::shared_ptr<sf::Sprite> p_back_sprite = std::make_shared<sf::Sprite>();
        p_back_sprite->setTexture(*pBackTextureVec[0]);
        p_back_sprite->setScale(scaleX, scaleY);
        pBackSpriteVec.push_back(p_back_sprite);
    }
    // create cards
    std::vector<std::string> symbolVec{"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    // hearts
    for (int i = 1; i < 14; i++) {
        std::shared_ptr<Card> card = std::make_shared<Card>(symbolVec[i - 1], "H", "R", i, 
            pFrontSpriteVec[i - 1], pBackSpriteVec[i - 1]);
        deckOfCards.push_back(card);
    }
    // diamonds
    for (int i = 1; i < 14; i++) {
        std::shared_ptr<Card> card = std::make_shared<Card>(symbolVec[i - 1], "D", "R", i, 
            pFrontSpriteVec[i + 12], pBackSpriteVec[i + 12]);
        deckOfCards.push_back(card);
    }
    // spades
    for (int i = 1; i < 14; i++) {
        std::shared_ptr<Card> card = std::make_shared<Card>(symbolVec[i - 1], "S", "B", i, 
            pFrontSpriteVec[i + 25], pBackSpriteVec[i + 25]);
        deckOfCards.push_back(card);
    }
    // clubs
    for (int i = 1; i < 14; i++) {
        std::shared_ptr<Card> card = std::make_shared<Card>(symbolVec[i - 1], "C", "B", i, 
            pFrontSpriteVec[i + 38], pBackSpriteVec[i + 38]);
        deckOfCards.push_back(card);
    }
    
    

}
void Deck::shuffleDeck() {
    //create vector and copy to it
    std::vector<std::shared_ptr<Card>> copyVec;
    long unsigned int size = deckOfCards.size();
    for (long unsigned int i = 0; i < size; i++) {
        copyVec.push_back(deckOfCards.back());
        deckOfCards.pop_back();
    }
    //put back at random
    srand(time(NULL));
    while (!copyVec.empty()) {
        int num = rand() % copyVec.size();
        deckOfCards.push_back(copyVec[num]);
        copyVec.erase(copyVec.begin() + num);
    }
    
}
Deck::Deck() {
    createDeck();
    shuffleDeck();
}

Deck::~Deck() {
    deckOfCards.clear();
    pImageVec.clear();
    pBackImageVec.clear();
    pTextureVec.clear();
    pBackTextureVec.clear();
    pFrontSpriteVec.clear();
    pBackSpriteVec.clear();
}
bool Deck::isEmpty() {
    if (deckOfCards.empty()) {
        return true;
    }
    return false;
}
int Deck::dealCard(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!deckOfCards.empty()) {
        std::shared_ptr<Card> p_card = deckOfCards.back();
        p_card->setFaceUp(false);
        pile->push_back(p_card);
        deckOfCards.pop_back();
        return 1;
    }
    return -1;
}
int Deck::deal3Cards(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!deckOfCards.empty()) {
        if (deckOfCards.size() > 2) {
            for (int i = 0; i < 3; i++) {
                dealCard(pile);
            }
            return 3;
        } else if (deckOfCards.size() == 2) {
            for (int i = 0; i < 2; i++) {
                dealCard(pile);
            }
            return 2;
        } else if (deckOfCards.size() == 1) {
            dealCard(pile);
            return 1;
        }
    }
    return -1;
}
void Deck::returnCards(std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile) {
    if (!pile->empty()) {
        while (!pile->empty()) {
            std::shared_ptr<Card> p_card = pile->back();
            p_card->setFaceUp(false);
            deckOfCards.push_back(p_card);
            pile->pop_back();
        }
    }
    return;
}
std::shared_ptr<sf::Sprite> Deck::getTopSprite() {
    return deckOfCards.back()->getPSprite();
}


#endif