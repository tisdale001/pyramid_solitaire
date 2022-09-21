// ControllerPyramid.hpp
// Header file for controller for pyramid solitaire
#ifndef CONTROLLER_HPP 
#define CONTROLLER_HPP 

#include <vector>
#include <memory>

#include<Node.hpp>
#include <Card.hpp>
#include <ViewPyramid.hpp>
#include <ModelPyramid.hpp>

class Controller {
    private:
    Model model = Model();
    View view = View();
    bool pressedLastFrame = true;
	int once = 1;
	int xPos = 0;
	int yPos = 0;
	int xDiff = 0;
	int yDiff = 0;
    std::shared_ptr<std::vector<std::shared_ptr<Card>>> lastPile = nullptr;
    Node* lastNode = nullptr;
    bool lastWasPile = true;

    public:
    Controller();
    ~Controller();
    void playGame();
};

#endif