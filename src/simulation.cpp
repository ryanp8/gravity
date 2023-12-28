#include "simulation.hpp"

Simulation::Simulation(int numPlanets):
    tree(new Node(0, 0, 800))
    {
        srand(time(NULL));
        for (int i = 0; i < numPlanets; i++) {
            this->planets.push_back(std::make_shared<Body>(rand() % 800, rand() % 800, 1000, 0, 0));
        }
        // this->planets.push_back(std::shared_ptr<Body>(new Body(100, 100, 100000000, 0, 0)));
        // this->planets = std::vector<std::shared_ptr<Body>>{
        //     std::shared_ptr<Body>(new Body(200, 200, 500, 0, 0)),
        //     std::shared_ptr<Body>(new Body(600, 200, 500, 0, 0)),
        //     std::shared_ptr<Body>(new Body(200, 600, 500, 0, 0)),
        //     std::shared_ptr<Body>(new Body(600, 600, 500, 0, 0)),
        //     std::shared_ptr<Body>(new Body(600, 600, 500, 0, 0))
        // };
    };

void Simulation::draw(sf::RenderWindow &screen) {
    // this->tree->draw(screen);
    this->tree->drawBodies(screen);
}

void Simulation::update() {
    this->tree = std::make_unique<Node>(0, 0, 800);
    for (auto planet : this->planets) {
        if (planet->active) {
            this->tree->insert(planet, 1);
        }
    }
    for (auto planet : this->planets) {
        if (planet->active) {
            planet->accelerate(this->tree);
        }
    }
    for (auto planet : this->planets) {
        if (planet->active) {
            planet->update();
        }
    }
}