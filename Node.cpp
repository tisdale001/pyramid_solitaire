// Node.cpp
// This represents a node in a graph in pyramid solitaire
#ifndef NODE_CPP 
#define NODE_CPP
//#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics/Sprite.hpp>
#include<vector>
//#include<string>
//include header files
#include<Card.hpp>
#include<Node.hpp>

Node::Node() {}
Node::~Node() {}
bool Node::empty() {
    return card_vec.empty();
}
void Node::popCard() {
    if (!card_vec.empty()) {
        card_vec.pop_back();
    }
}
std::shared_ptr<Card> Node::getCard() {
    if (!card_vec.empty()) {
        return card_vec.back();
    }
    return nullptr;
}
void Node::pushCard(std::shared_ptr<Card> card) {
    card_vec.push_back(card);
}

#endif