#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "node.hpp"
#include "body.hpp"

class Simulation {
public:
    Simulation(int numPlanets);
    void draw(sf::RenderWindow &screen);
    void update();
    int numPlanets;
    std::unique_ptr<Node> tree;
    std::vector<std::shared_ptr<Body>> planets;
};