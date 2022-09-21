// Node.hpp
// Header file for node in a graph for pyramid solitaire
#ifndef NODE_HPP 
#define NODE_HPP
//#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>

//include header files
#include<Card.hpp>

class Node {
    private:
    std::vector<std::shared_ptr<Card>> card_vec;

    public:
    Node();
    ~Node();
    bool empty();
    void popCard();
    std::shared_ptr<Card> getCard();
    void pushCard(std::shared_ptr<Card>);
    
};


#endif