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

    /*Draws the recursive quadtree regions*/
    void draw(sf::RenderWindow &screen);

    /*Traverses the quadtree and draws active bodies*/
    void drawBodies(sf::RenderWindow &screen);

    /*Inserts a planet into the quadtree*/
    void insert(std::shared_ptr<Body> p, int depth);
    double x, y, mass, mx, my;
    int w, status;
    std::shared_ptr<Body> body;
    std::array<std::shared_ptr<Node>, NUM_SUB> children;
private:
    void _drawNode(sf::RenderWindow &screen);

    /*Calculates which quadrant of an internal node that a new body should be put into.
    Quadrants are numbered the same as those on the cartesian plane.
    */
    int _findQuadrant(std::shared_ptr<Body> p);
};