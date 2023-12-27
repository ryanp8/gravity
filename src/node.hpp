#pragma once
#include <SFML/Graphics.hpp>
#include "body.hpp"
#include <array>

#define EXTERNAL 0
#define INTERNAL 1
#define NUM_SUB 4

class Body;
class Node {
public:
    Node(double x, double y, int w, int status=EXTERNAL);
    void draw(sf::RenderWindow &screen);
    void drawBodies(sf::RenderWindow &screen);
    void insert(std::shared_ptr<Body> p, int depth);
    double x, y, mass, mx, my;
    int w, status;
    std::shared_ptr<Body> body;
    std::array<std::unique_ptr<Node>, NUM_SUB> children;
private:
    void _drawNode(sf::RenderWindow &screen);
    int _findQuadrant(std::shared_ptr<Body> p);
};