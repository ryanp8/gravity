#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "node.hpp"
#include "theta_threshold.hpp"

#define G 1
#define SPEED 0.2
#define DAMPENING_FACTOR 1000000

class Node;
class Body {
public:
    Body(double x, double y, double mass, double vx, double vy);
    void draw(sf::RenderWindow &screen);
    void accelerate(std::unique_ptr<Node> &n);
    void update();
    double x, y, mass, vx, vy;
    bool active;
private:
    sf::Vector2<double> _calculateAcceleration(double m, double x, double y, double r2);
};