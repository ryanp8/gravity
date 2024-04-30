#include "simulation.hpp"


std::mutex m;
std::condition_variable notifyWorkers;
std::condition_variable notifyCoordinator;
int waitGroup = 0;

Simulation::Simulation(int numPlanets, int numThreads):
    tree(new Node(0, 0, 800))
    {
        srand(time(NULL));
        for (int i = 0; i < numPlanets; i++) {
            this->planets.push_back(std::make_shared<Body>(rand() % 800, rand() % 800, 100, 0, 0));
        }

        for (int i = 0; i < numThreads; i++) {
            workers.push_back(std::thread(&updateChunk, i, numThreads, this->tree, this->planets));
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
    this->tree->drawBodies(screen);
}

void Simulation::updateChunk(int chunk, int num_threads, std::shared_ptr<Node> tree, std::vector<std::shared_ptr<Body>> planets) {
    while (true) {
        {
            std::unique_lock lock(m);
            notifyWorkers.wait(lock);
        }
        for (int i = chunk; i < planets.size(); i += num_threads) {
            std::shared_ptr<Body> p = planets[i];
            if (p->active) {
                p->accelerate(tree);
                p->update();
            }
        }
        {
            std::lock_guard lock(m);
            waitGroup++;
            notifyCoordinator.notify_one();
        }
    }

}

void Simulation::update(int numThreads) {
    this->tree->x = 0;
    this->tree->y = 0;
    this->tree->w = 800;
    this->tree->mx = 0;
    this->tree->my = 0;
    this->tree->mass = 0;
    this->tree->status = EXTERNAL;

    for (auto planet : this->planets) {
        if (planet->active) {
            this->tree->insert(planet, 1);
        }
    }

    {
        std::lock_guard lock(m);
        waitGroup = 0;
        notifyWorkers.notify_all();
    }

    while (true) {
        std::unique_lock lock(m);
        notifyCoordinator.wait(lock, [&]{
            return waitGroup == numThreads;
        });
        break;
    }
}