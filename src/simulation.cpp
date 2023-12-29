#include "simulation.hpp"

Simulation::Simulation(int numPlanets):
    tree(new Node(0, 0, 800))
    {
        srand(time(NULL));
        for (int i = 0; i < numPlanets; i++) {
            this->planets.push_back(std::make_shared<Body>(rand() % 800, rand() % 800, 100, 0, 0));
        }
        // this->planets.push_back(std::shared_ptr<Body>(new Body(600, 200, 500000, 0, 0)));
        // this->planets.push_back(std::shared_ptr<Body>(new Body(300, 500, 50000, 0, 0)));
        // this->planets.push_back(std::shared_ptr<Body>(new Body(200, 400, 10000, 0, 0)));
        // this->planets.push_back(std::shared_ptr<Body>(new Body(600, 400, 5000, 0, 0)));

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

void Simulation::updateChunk(int chunk, int num_threads, std::shared_ptr<Node> tree, std::vector<std::shared_ptr<Body>> planets){
    for (int i = chunk; i < planets.size(); i += num_threads) {
        std::shared_ptr<Body> p = planets[i];
        if (p->active) {
            p->accelerate(tree);
            p->update();
        }
    }
}

void Simulation::test(int i) {
    std::cout << "Thread " << i << "\n";
}

void Simulation::update(int num_threads) {
    this->tree = std::make_shared<Node>(0, 0, 800);
    for (auto planet : this->planets) {
        if (planet->active) {
            this->tree->insert(planet, 1);
        }
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; i++) {
        // threads.push_back(std::thread(&test, i));
        threads.push_back(std::thread(&updateChunk, i, num_threads, this->tree, this->planets));
    }
    for (auto &thread : threads) {
        thread.join();
    }
    // for (auto planet : this->planets) {
    //     if (planet->active) {
    //         planet->accelerate(this->tree);
    //     }
    // }
    // for (auto planet : this->planets) {
    //     if (planet->active) {
    //         planet->update();
    //     }
    // }
}