// ViewPyramid.cpp
// View for Pyramid Solitaire
#ifndef VIEW_CPP 
#define VIEW_CPP
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
//#include <utility>
//#include <Vector2.hpp>
#include <iostream>

#include <Card.hpp>
#include <Deck.hpp>
#include <Node.hpp>
#include <ViewPyramid.hpp>

View::View() {}
View::~View() {
    //std::cout << "View destructor called\n";
}
void View::initiateView(std::shared_ptr<std::vector<std::vector<Node>>> graph_, 
std::shared_ptr<std::vector<std::shared_ptr<Card>>> drawPile_, 
std::shared_ptr<std::vector<std::shared_ptr<Card>>> wastePile_, 
std::shared_ptr<std::vector<std::shared_ptr<Card>>> discardPile_, 
std::shared_ptr<std::vector<std::shared_ptr<Card>>> movePile_, std::shared_ptr<Deck> deck_) {
    graph = graph_;
    drawPile = drawPile_;
    wastePile = wastePile_;
    discardPile = discardPile_;
    movePile = movePile_;
    deck = deck_;
    cardHeight = deck->getTopSprite()->getGlobalBounds().height;
    cardWidth = deck->getTopSprite()->getGlobalBounds().width;
    stackDistance = (int)(cardHeight / 2);
    image.create(bounds_width, bounds_height, sf::Color::Black);
    texture.loadFromImage(image);
    sprite.setTexture(texture);

}
Node* View::getClickOnGraph(sf::Vector2f mousePos) {
    // check nodes from bottom to top
    for (int i = 6; i >= 0; i--) {
        for (int j = 0; j < i + 1; j++) {
            if (!graph->at(i).at(j).empty()) {
                if (graph->at(i + 1).at(j).empty() && graph->at(i + 1).at(j + 1).empty()) {
                    if (graph->at(i).at(j).getCard()->getPSprite()->getGlobalBounds().contains(mousePos)) {
                        //std::cout << "i=" << i << " j=" << j << std::endl;
                        return &(graph->at(i).at(j));
                    }
                }
            }
        }
    }
    return nullptr;
}
std::shared_ptr<std::vector<std::shared_ptr<Card>>> View::getClickOnPiles(sf::Vector2f mousePos) {
    // checks empty spaces, does not check if pile is empty
    // return pile clicked
    float x = mousePos.x;
    float y = mousePos.y;
    // drawPile
    if (x > startPointX - cardWidth / 2 - cardWidth * 3 && x < startPointX - cardWidth / 2 - cardWidth * 2 &&
    y > startPointY + stackDistance * 6 + cardHeight + distBtwPiles && y < startPointY + stackDistance * 6 + 
    cardHeight * 2 + distBtwPiles) {
        //std::cout << "drawPile\n";
        return drawPile;
    }
    // wastePile
    if (x > startPointX - cardWidth / 2 - cardWidth * 2 + distBtwPiles && x < startPointX - cardWidth / 2 - 
    cardWidth + distBtwPiles &&
    y > startPointY + stackDistance * 6 + cardHeight + distBtwPiles && y < startPointY + stackDistance * 6 + 
    cardHeight * 2 + distBtwPiles) {
        //std::cout << "wastePile\n";
        return wastePile;
    }
    // discard pile
    if (x > startPointX - cardWidth / 2 - cardWidth + distBtwPiles * 2 && x < startPointX - cardWidth / 2
     + distBtwPiles * 2 && y > startPointY + stackDistance * 6 + cardHeight + distBtwPiles && y < startPointY 
     + stackDistance * 6 + cardHeight * 2 + distBtwPiles) {
        //std::cout << "discardPile\n";
        return discardPile;
    }

    
    return nullptr;
}
void View::setPosition() {
    // set position of all sprites except movePile
    // set position of sprites in graph
    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0) {
            // even numbered row, odd number of cards
            for (int j = 0; j < i + 1; j++) {
                if (!graph->at(i).at(j).empty()) {
                    graph->at(i).at(j).getCard()->getPSprite()->setPosition(startPointX - cardWidth / 2 - cardWidth * (i / 2) + 
                    cardWidth * j, startPointY + stackDistance * i);
                }
            }
        }
        else {
            // odd numbered row, even number of cards
            for (int j = 0; j < i + 1; j++) {
                if (!graph->at(i).at(j).empty()) {
                    graph->at(i).at(j).getCard()->getPSprite()->setPosition(startPointX - cardWidth * (i + 1) / 2 +
                    cardWidth * j, startPointY + stackDistance * i);
                }
            }
        }
    }
    // set position for sprites in piles
    if (!drawPile->empty()) {
        drawPile->back()->getPSprite()->setPosition(startPointX - cardWidth / 2 - cardWidth * 3, startPointY + stackDistance * 6 +
        cardHeight + distBtwPiles);
    }
    if (!wastePile->empty()) {
        wastePile->back()->getPSprite()->setPosition(startPointX - cardWidth / 2 - cardWidth * 3 + cardWidth + distBtwPiles,
        startPointY + stackDistance * 6 + cardHeight + distBtwPiles);
    }
    if (!discardPile->empty()) {
        discardPile->back()->getPSprite()->setPosition(startPointX - cardWidth / 2 - cardWidth * 3 + cardWidth * 2 + distBtwPiles * 2,
        startPointY + stackDistance * 6 + cardHeight + distBtwPiles);
    }
}
void View::draw(sf::RenderWindow* window) {
    window->clear();
    // set all sprite positions
    setPosition();
    // draw all relevant sprites in graph
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (!graph->at(i).at(j).empty()) {
                window->draw(*(graph->at(i).at(j).getCard()->getPSprite()));
            }
        }
    }
    // draw all relevant sprites in piles
    if (!drawPile->empty()) {
        window->draw(*(drawPile->back()->getPSprite()));
    }
    if (!wastePile->empty()) {
        window->draw(*(wastePile->back()->getPSprite()));
    }
    if (!discardPile->empty()) {
        window->draw(*(discardPile->back()->getPSprite()));
    }
    // draw sprites in movePile: back to front
    if (!movePile->empty()) {
        for (int i = (int)movePile->size() - 1; i >= 0; i--) {
            window->draw(*(movePile->at(i)->getPSprite()));
        }
    }
    window->display();

}
void View::animateCards(sf::RenderWindow* window) {
    // animate cards in movePile to discardPile
    if (movePile->empty()) {
        return;
    }
    int num_frames = 50;
    sf::Vector2f beg_pos = movePile->back()->getPSprite()->getPosition();
    //sf::Sprite* card_sprite = movePile->back()->getPSprite();
    float x1 = beg_pos.x;
    float y1 = beg_pos.y;
    float x2 = startPointX - cardWidth / 2 - cardWidth + distBtwPiles * 2;
    float y2 = startPointY + stackDistance * 6 + cardHeight + distBtwPiles;
    
    float x_to_move = (x2 - x1) / num_frames;
    float y_to_move = (y2 - y1) / num_frames;
    // animate card
    for (int i = 0; i < num_frames; i++) {
        x1 += x_to_move;
        y1 += y_to_move;
        int k = 0;
        for (int j = (int)movePile->size() - 1; j >= 0; j--) {
            movePile->at(j)->getPSprite()->setPosition(x1 + 50 * k, y1);
            k++;
        }
        draw(window);
    }
}

// creates animation after a win
void View::animateWin(sf::RenderWindow* window) {
    srand((unsigned) time(0));
    Deck deck1 = Deck();
    Deck deck2 = Deck();
    Deck deck3 = Deck();
    Deck deck4 = Deck();
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> card_vec = std::make_shared<std::vector<std::shared_ptr<Card>>>();
    while (!deck1.isEmpty()) {
        deck1.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck2.isEmpty()) {
        deck2.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck3.isEmpty()) {
        deck3.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    while (!deck4.isEmpty()) {
        deck4.dealCard(card_vec);
        card_vec->back()->setFaceUp(true);
    }
    // continue while loop till key is pressed or mouse clicked
    bool animation = true;
    while (animation) {
        sf::Event event;
        while (window->pollEvent(event)) {
            
            if (event.type == sf::Event::Closed) {
				//window->close();
                animation = false;
                break;
			}
            else if (event.type == sf::Event::KeyReleased) {
                animation = false;
                break;
            }
        }
        if (animation == false) {
            break;
        }
        // code card burst here
        // create wrapper vec
        int numFrames = 2400;
        std::vector<AnimationWrapper> ani_vec;
        int i = 0;
        for (auto item : *card_vec) {
            AnimationWrapper wrapper = AnimationWrapper(item->getPSprite(), bounds_width / 2 - cardWidth / 2, 
                bounds_height / 2 - cardHeight / 2,
                (rand() % (bounds_width + 200)) - 100, (rand() % (bounds_height + 200)) - 100, numFrames);
            wrapper.setID(i);
            ani_vec.push_back(wrapper);
            i++;
        }
        // iterate through ani_vec, adding one each time
        for (int i = 0; i < (int)ani_vec.size() - 1; i++) {
            window->clear();
            for (int j = 0; j < i + 1; j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
        // keep animating more frames
        for (int i = (int)ani_vec.size(); i < (int)ani_vec.size() + 200; i++) {
            window->clear();
            for (int j = 0; j < (int)ani_vec.size(); j++) {
                ani_vec.at(j).advance(i - ani_vec.at(j).getID());
                window->draw(*(ani_vec.at(j).getPSprite()));
            }
            window->display();
        }
    }
}

int View::getBoundsWidth() {
    return bounds_width;
}
int View::getBoundsHeight() {
    return bounds_height;
}

#endif