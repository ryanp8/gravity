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

    /*Draws a dot on the screen at position (this->x, this->y)*/
    void draw(sf::RenderWindow &screen);

    /* Traverses the quadtree to calculate the
    force caused by each node. Applies Barnes-Hut Algorithm, so nodes that are too
    far away (depending on the provided theta_threshold) are not traversed.
    */
    void accelerate(std::unique_ptr<Node> &n);

    /*Adjust the current position given the x and y velocity*/
    void update();
    double x, y, mass, vx, vy;
    bool active;
private:
    /* Use Newton's Law of Gravitation to calculate the force that another body located
    at (x, y) with mass m has on this body.
    Result is used by the accelerate() function.*/
    sf::Vector2<double> _calculateAcceleration(double m, double x, double y, double r2);

    double dist_squared(double x2, double y2);
};