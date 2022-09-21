// ModelPyramid.cpp
// Model for pyramid solitaire
#ifndef MODEL_CPP 
#define MODEL_CPP

#include<vector>
#include<iostream>

//include header files
#include<Deck.hpp>
#include<Card.hpp>
#include<Node.hpp>
#include<ModelPyramid.hpp>



Model::Model() {
    createGraph();
}
Model::~Model() {
    //std::cout << "Model destructor called\n";
}
void Model::createGraph() {
    // add nodes to pyramid graph
    for (int i = 0; i < 8; i++) {
        std::vector<Node> v1;
        for (int j = 0; j < i + 1; j++) {
            v1.push_back(Node());
        }
        graph->push_back(v1);
    }
}
void Model::allCardsToDeck() {
    //put all tableau cards in wastePile
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (!graph->at(i).at(j).empty()) {
                wastePile->push_back(graph->at(i).at(j).getCard());
                graph->at(i).at(j).popCard();
            }
        }
    }
    // return all cards to deck
    if (!drawPile->empty()) {
        deck->returnCards(drawPile);
    }
    if (!wastePile->empty()) {
        deck->returnCards(wastePile);
    }
    if (!discardPile->empty()) {
        deck->returnCards(discardPile);
    }
    if (!movePile->empty()) {
        deck->returnCards(movePile);
    }
    
}
void Model::dealTableau() {
    // does not check if drawPile is full
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < i + 1; j++) {
            drawPile->back()->setFaceUp(true);
            graph->at(i).at(j).pushCard(drawPile->back());
            drawPile->pop_back();
        }
    }
    showTopCard();
}

void Model::cardsFromDeckToDrawPile() {
    // puts all cards from deck to drawPile
    while (!deck->isEmpty()) {
        deck->dealCard(drawPile);
    }
}

void Model::redeal() {
    // returns all cards to deck, shuffles, puts all cards in drawPile, deals tableau
    allCardsToDeck();
    deck->shuffleDeck();
    cardsFromDeckToDrawPile();
    dealTableau();
}

void Model::showTopCard() {
    if (!drawPile->empty()) {
        drawPile->back()->setFaceUp(true);
    }
}

void Model::cardsFromWastePileToDrawPile(){
    while (!wastePile->empty()) {
        wastePile->back()->setFaceUp(false);
        drawPile->push_back(wastePile->back());
        wastePile->pop_back();
    }
    showTopCard();
}

void Model::cardToMovePile(std::shared_ptr<Card> card) {
    movePile->push_back(card);
}
void Model::cardsFromMovePile(std::shared_ptr<std::vector<std::shared_ptr<Card>>> to_pile) {
    while (!movePile->empty()) {
        to_pile->push_back(movePile->back());
        movePile->pop_back();
        if (to_pile == discardPile) {
            to_pile->back()->setFaceUp(false);
        }
    }
}

bool Model::checkWin() {
    return graph->at(0).at(0).empty();
}

std::shared_ptr<std::vector<std::vector<Node>>> Model::getGraph() {
    return graph;
}

std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getMovePile() {
    return movePile;
}
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getDrawPile() {
    return drawPile;
}
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getWastePile() {
    return wastePile;
}
std::shared_ptr<std::vector<std::shared_ptr<Card>>> Model::getDiscardPile() {
    return discardPile;
}
std::shared_ptr<Deck> Model::getDeck() {
    return deck;
}


#endif