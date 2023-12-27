#include <SFML/Graphics.hpp>
#include <iostream>
#include "simulation.hpp"
#include "node.hpp"
#include "body.hpp"
#include "theta_threshold.hpp"


float theta_threshold;

int main(int argc, char* argv[])
{

    if (argc != 3) {
        std::cout << "Usage: ./gravity numPlanets theta\n";
        exit(-1);
    }

    int numPlanets  = atoi(argv[1]);
    theta_threshold = atof(argv[2]);
    if (theta_threshold < 0) {
        std::cout << "Theta must be positive\n";
        exit(-1);
    }

    auto window = sf::RenderWindow{ { 800u, 800u }, "Barnes-Hut Gravity" };
    window.setFramerateLimit(30);
    Simulation sim(numPlanets);

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
        sim.update();
        sim.draw(window);
        window.display();
    }
}