// AnimationWrapper.hpp
// Header file for animating cards in Pyramid Solitaire
#ifndef ANIMATIONWRAPPER_HPP
#define ANIMATIONWRAPPER_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <iostream>
// include Header files


class AnimationWrapper {
    private:
    std::shared_ptr<sf::Sprite> card;
    float beginXPos;
    float beginYPos;
    float endXPos;
    float endYPos;
    int numFrames;
    float x_to_move;
    float y_to_move;
    int wrapperID = 0;

    public:
    AnimationWrapper(std::shared_ptr<sf::Sprite> card_, float beginXPos_, float beginYPos_, float endXPos_, 
    float endYPos_, int numFrames_);
    ~AnimationWrapper();
    void advance(int frame);

    void setID(int num);
    int getID();
    std::shared_ptr<sf::Sprite> getPSprite();
};

#endif