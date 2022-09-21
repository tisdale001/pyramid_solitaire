// AnimationWrapper.cpp
// Wrapper class for animating cards in Pyramid Solitaire
#ifndef ANIMATIONWRAPPER_CPP
#define ANIMATIONWRAPPER_CPP

//Include Header files
#include <AnimationWrapper.hpp>

AnimationWrapper::AnimationWrapper(std::shared_ptr<sf::Sprite> card_, float beginXPos_, float beginYPos_, float endXPos_, 
float endYPos_, int numFrames_) {
    card = card_;
    //std::cout << "Checkpoint 1\n";
    beginXPos = beginXPos_;
    beginYPos = beginYPos_;
    //std::cout << "Checkpoint 2\n";
    endXPos = endXPos_;
    endYPos = endYPos_;
    numFrames = numFrames_;
    x_to_move = (float)((endXPos - beginXPos) / numFrames);
    y_to_move = (float)((endYPos - beginYPos) / numFrames);
    //std::cout << y_to_move << std::endl;
    //std::cout << "Checkpoint 3\n";
    card->setPosition(beginXPos, beginYPos);
    
}

AnimationWrapper::~AnimationWrapper() {}

// advances position of sprite one small step and changes begin position
void AnimationWrapper::advance(int frame) {
    //std::cout << "Checkpoint 1\n";
    this->beginXPos += x_to_move * frame;
    this->beginYPos += y_to_move * frame;
    //std::cout << "Checkpoint 2\n";
    card->setPosition(beginXPos, beginYPos);
}

void AnimationWrapper::setID(int num) {
    wrapperID = num;
}
int AnimationWrapper::getID() {
    return wrapperID;
}
std::shared_ptr<sf::Sprite> AnimationWrapper::getPSprite() {
    return card;
}

#endif