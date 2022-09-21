// ControllerPyramid.cpp
// Controller for Pyramid Solitaire
#ifndef CONTROLLER_CPP 
#define CONTROLLER_CPP 
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <vector>


#include <Card.hpp>
#include <Deck.hpp>
#include <ViewPyramid.hpp>
#include <ModelPyramid.hpp>
#include <ControllerPyramid.hpp>

Controller::Controller() {}
Controller::~Controller() {}

void Controller::playGame()  {
    // initiate view
    view.initiateView(model.getGraph(), model.getDrawPile(), model.getWastePile(),
    model.getDiscardPile(), model.getMovePile(), model.getDeck());
    // deal hand
    model.cardsFromDeckToDrawPile();
    model.dealTableau();

    sf::RenderWindow window(sf::VideoMode(view.getBoundsWidth(), view.getBoundsHeight()), 
    "Pyramid Solitaire", sf::Style::Close);

    while (window.isOpen()) {
		sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //std::cout << "Mouse button pressed\n";
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    Node* node = view.getClickOnGraph(mousePos);
                    std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile = view.getClickOnPiles(mousePos);
                    if (node == nullptr) {
                        // try pile
                        if (pile != nullptr) {
                            // pile was clicked
                            if (pile == model.getDrawPile()) {
                                // drawPile clicked
                                if (model.getDrawPile()->empty()) {
                                    model.cardsFromWastePileToDrawPile();
                                }
                                else {
                                    // drawPile not empty
                                    model.getMovePile()->push_back(model.getDrawPile()->back());
                                    model.getDrawPile()->pop_back();
                                    lastPile = model.getDrawPile();
                                    lastWasPile = true;
                                }
                            }
                            else if (pile == model.getWastePile()) {
                                // wastePile clicked
                                if (!model.getWastePile()->empty()) {
                                    model.getMovePile()->push_back(model.getWastePile()->back());
                                    model.getWastePile()->pop_back();
                                    lastPile = model.getWastePile();
                                    lastWasPile = true;
                                }
                            }
                        }
                    }
                    else {
                        // node was clicked
                        // check for King
                        if (node->getCard()->getValue() == 13) {
                            // add node card to movePile, animate, put in discardPile
                            model.getMovePile()->push_back(node->getCard());
                            node->popCard();
                            view.animateCards(&window);
                            while (!model.getMovePile()->empty()) {
                                model.getMovePile()->back()->setFaceUp(false);
                                model.getDiscardPile()->push_back(model.getMovePile()->back());
                                model.getMovePile()->pop_back();
                            }
                            if (model.checkWin()) {
                                std::cout << "WINNER!\n";
                                view.animateWin(&window);
                            }
                        }
                        else {
                            model.getMovePile()->push_back(node->getCard());
                            node->popCard();
                            lastNode = node;
                            lastWasPile = false;
                        }
                    }
                    
                }
            }
            if(event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //std::cout << "Mouse button released\n";
                    once = 1;
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                    Node* node = view.getClickOnGraph(mousePos);
                    //std::cout << node << std::endl;
                    std::shared_ptr<std::vector<std::shared_ptr<Card>>> pile = view.getClickOnPiles(mousePos);
                    //std::cout << pile << std::endl;
                    if (node == nullptr) {
                        // try piles
                        //std::cout << "node is null\n";
                        if (pile != nullptr) {
                            // pile was click-released on
                            if (pile == model.getWastePile()) {
                                if (!model.getMovePile()->empty()) {
                                    // drop card on wastePile
                                    if (lastWasPile) {
                                        model.getWastePile()->push_back(model.getMovePile()->back());
                                        model.getMovePile()->pop_back();
                                        model.showTopCard();
                                    }
                                    else {
                                        // last was node: cannot drop on waste pile
                                        lastNode->pushCard(model.getMovePile()->back());
                                        model.getMovePile()->pop_back();
                                    }
                                }
                            }
                            else if (pile == model.getDiscardPile()) {
                                if (!model.getMovePile()->empty()) {
                                    // drop card on discard pile face down
                                    if (lastWasPile) {
                                        model.getMovePile()->back()->setFaceUp(false);
                                        model.getDiscardPile()->push_back(model.getMovePile()->back());
                                        model.getMovePile()->pop_back();
                                        model.showTopCard();
                                    }
                                    else {
                                        // last was node: cannot drop on discard pile
                                        lastNode->pushCard(model.getMovePile()->back());
                                        model.getMovePile()->pop_back();
                                    }
                                }
                            }
                            else {
                                // illegal pile click-released on
                                if (!model.getMovePile()->empty()) {
                                    if (lastWasPile) {
                                        lastPile->push_back(model.getMovePile()->back());
                                        model.getMovePile()->pop_back();
                                    }
                                    else {
                                        // last was node: return to node
                                        lastNode->pushCard(model.getMovePile()->back());
                                        model.getMovePile()->pop_back();
                                    }
                                }
                            }
                        }
                        else {
                            // both node and pile are null
                            if (!model.getMovePile()->empty()) {
                                //std::cout << "both node and pile are null\n";
                                if (lastWasPile) {
                                    lastPile->push_back(model.getMovePile()->back());
                                    model.getMovePile()->pop_back();
                                }
                                else {
                                    // last was node: return to node
                                    lastNode->pushCard(model.getMovePile()->back());
                                    model.getMovePile()->pop_back();
                                }
                            }
                        }
                    }
                    else {
                        // node was click-released on
                        if (!model.getMovePile()->empty()) {
                            if (node->getCard()->getValue() + model.getMovePile()->back()->getValue() == 13) {
                                // add node card to movePile, animate, put in discardPile
                                model.getMovePile()->push_back(node->getCard());
                                node->popCard();
                                view.animateCards(&window);
                                while (!model.getMovePile()->empty()) {
                                    model.getMovePile()->back()->setFaceUp(false);
                                    model.getDiscardPile()->push_back(model.getMovePile()->back());
                                    model.getMovePile()->pop_back();
                                }
                                model.showTopCard();
                                if (model.checkWin()) {
                                    std::cout << "WINNER!\n";
                                    view.animateWin(&window);
                                }
                            }
                            else {
                                // cards do not add up to 13: return to last pile
                                if (lastWasPile) {
                                    lastPile->push_back(model.getMovePile()->back());
                                    model.getMovePile()->pop_back();
                                }
                                else {
                                    // last was node: return to node
                                    lastNode->pushCard(model.getMovePile()->back());
                                    model.getMovePile()->pop_back();
                                }
                            }
                        }
                        else {
                            // movePile empty: check for King
                            if (node->getCard()->getValue() == 13) {
                                // add node card to movePile, animate, put in discardPile
                                model.getMovePile()->push_back(node->getCard());
                                node->popCard();
                                view.animateCards(&window);
                                while (!model.getMovePile()->empty()) {
                                    model.getMovePile()->back()->setFaceUp(false);
                                    model.getDiscardPile()->push_back(model.getMovePile()->back());
                                    model.getMovePile()->pop_back();
                                }
                                if (model.checkWin()) {
                                    std::cout << "WINNER!\n";
                                    view.animateWin(&window);
                                }
                            }
                        }
                    }
                }
            }
            if (event.type == sf::Event::Closed) {
				window.close();
                break;
			}
            if (event.type == sf::Event::KeyReleased) {
				//std::cout << "Key Pressed" << std::endl;
				
				if (event.key.code == sf::Keyboard::Escape) {
					//std::cout << "escape Pressed" << std::endl;
					window.close();
					break;
				}
                if (event.key.code == sf::Keyboard::D) {
                    model.redeal();
                }
                if (event.key.code == sf::Keyboard::M) {
                    view.animateWin(&window);
                }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // drag move pile
            if (!model.getMovePile()->empty()) {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                sf::Vector2f cardPos = model.getMovePile()->back()->getPSprite()->getPosition();
			    if(pressedLastFrame || (mousePos.x > xPos && mousePos.y > yPos
        	    && mousePos.x - view.getBoundsWidth() < xPos && mousePos.y - 
                view.getBoundsHeight() < yPos)) {
        		    if(once) {
                        //std::cout << "if(once) actually ran\n";
            		    xDiff = mousePos.x - cardPos.x;
            		    yDiff = mousePos.y - cardPos.y;
            	    	once = 0;
        		    }
        		    xPos = mousePos.x - xDiff;
        		    yPos = mousePos.y - yDiff;
                    int j = 0;
				    for (int i = (int)model.getMovePile()->size() - 1; i >= 0; i--) {
					    model.getMovePile()->at(i)->getPSprite()->setPosition(xPos + 50 * j, yPos);
                        j++;
				    }
    		    }
    		    pressedLastFrame = true;
		    }
        }
        view.draw(&window);
    }
    
}

int main() {
    Controller controller = Controller();
    controller.playGame();

    return 0;
}

#endif