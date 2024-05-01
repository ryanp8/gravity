#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "simulation.hpp"
#include "node.hpp"
#include "body.hpp"
#include "theta_threshold.hpp"


float theta_threshold;

int main(int argc, char* argv[])
{

    if (argc > 5) {
        std::cout << "Usage: ./gravity <numPlanets theta threads>\n";
        exit(-1);
    }
    int numPlanets  = atoi(argv[1]);
    theta_threshold = atof(argv[2]);
    int threads     = 1;
    bool debug = false;
    if (argc > 3) {
        threads = atoi(argv[3]);
    }
    if (argc > 4) {
        debug = true;
    }
    if (theta_threshold < 0) {
        std::cout << "Theta must be positive\n";
        exit(-1);
    }

    auto window = sf::RenderWindow{ { 800u, 800u }, "Barnes-Hut Gravity" };
    window.setFramerateLimit(30);
    Simulation sim(numPlanets, threads);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        sim.update(threads);
        sim.draw(window, debug);
        window.display();
    }
}