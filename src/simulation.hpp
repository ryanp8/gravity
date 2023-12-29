#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <time.h>
#include "node.hpp"
#include "body.hpp"

class Simulation {
public:
    Simulation(int numPlanets);

    /*Traverses the quadtree and draws active bodies to the screen.*/
    void draw(sf::RenderWindow &screen);

    /*Inserts each planet into the quadtree. Then calculates the forces on each body,
    updating the body's velocity in the process. Once all the forces have been calculated,
    each body's position is updated*/
    void update(int num_threads);

    int numPlanets;
    std::shared_ptr<Node> tree;
    std::vector<std::shared_ptr<Body>> planets;
private:
    static void updateChunk(int chunk, int num_threads, std::shared_ptr<Node> tree, std::vector<std::shared_ptr<Body>> planets);

    static void test(int);
};