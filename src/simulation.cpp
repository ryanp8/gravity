#include "simulation.hpp"

Simulation::Simulation(int numPlanets)
    // tree(0, 0, 800)
    {
        srand(time(NULL));
        for (int i = 0; i < numPlanets; i++) {
            this->planets.push_back(std::make_shared<Body>(rand() % 800, rand() % 800, 100, 0, 0));
        }
    };

void Simulation::update(sf::RenderWindow &screen, int num_threads) {
    auto tree = std::make_unique<Node>(0, 0, 800);
    for (auto &planet : this->planets) {
        if (planet->active) {
            tree->insert(planet, 1);
        }
    }


    for (auto &p : this->planets) {
        if (p->active) {
            p->accelerate(tree);
            p->update();
        }
    }
    tree->drawBodies(screen);
}