// ViewPyramid.hpp
// Header file for View in Pyramid Solitaire
#ifndef VIEW_HPP 
#define VIEW_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <memory>
//#include <utility>
//#include <Vector2.hpp>

#include <Card.hpp>
#include <Deck.hpp>
#include <Node.hpp>
#include <AnimationWrapper.hpp>

class View {
    private:
    int bounds_width = 900;
	int bounds_height = 900;
	int stackDistance = 0; // set stackDistance to be cardHeight/2
    int distBtwPiles = 50;
    int cardHeight = 0; // set cardHeight with sprite.getSize()
    int cardWidth = 0; // set cardWidth with sprite.getSize()
    int startPointX = (int)(bounds_width / 2); 
    int startPointY = 100;
    sf::Image image; // initiate
    sf::Texture texture; // initiate
    sf::Sprite sprite; // initiate
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> wastePile; // initiate all below
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> discardPile;
    std::shared_ptr<std::vector<std::vector<Node>>> graph;
    std::shared_ptr<Deck> deck;

    public:
    View();
    ~View();
    void initiateView(std::shared_ptr<std::vector<std::vector<Node>>>, std::shared_ptr<std::vector<std::shared_ptr<Card>>>, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>>, std::shared_ptr<std::vector<std::shared_ptr<Card>>>, 
    std::shared_ptr<std::vector<std::shared_ptr<Card>>>, std::shared_ptr<Deck>);
    Node* getClickOnGraph(sf::Vector2f);
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> getClickOnPiles(sf::Vector2f);
    void setPosition();
    void draw(sf::RenderWindow*);
    void animateCards(sf::RenderWindow*);
    void animateWin(sf::RenderWindow* window);
    int getBoundsWidth();
    int getBoundsHeight();
    
};

#endif