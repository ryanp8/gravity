#include <SFML/Graphics.hpp>
#include <iostream>
#include "simulation.hpp"
#include "node.hpp"
#include "body.hpp"


int main(int argc, char* argv[])
{

    if (argc != 2) {
        std::cout << "Usage: ./gravity numPlanets\n";
        exit(-1);
    }
    auto window = sf::RenderWindow{ { 800u, 800u }, "Barnes-Hut Gravity" };
    window.setFramerateLimit(30);
    Simulation sim(atoi(argv[1]));

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