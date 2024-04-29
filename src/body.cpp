#include "body.hpp"

Body::Body(double x, double y, double mass, double vx, double vy):
    x(x), y(y), mass(mass), vx(vx), vy(vy), active(true){};

void Body::draw(sf::RenderWindow &screen) {
    sf::CircleShape c(1);
    c.setFillColor(sf::Color(255,255,255));
    c.setPosition(this->x, this->y);
    screen.draw(c);
}

sf::Vector2<double> Body::_calculateAcceleration(double m, double x, double y, double r2) {
    // Use dampening factor for better visualization-> Otherwise bodies will fly away too quickly
    double fg = G * m / (r2 + DAMPENING_FACTOR); // Newton's Law of Gravitation
    double theta = atan2(y - this->y, x - this->x);
    return sf::Vector2(fg * cos(theta) * SPEED, fg * sin(theta) * SPEED);
}

void Body::accelerate(const std::unique_ptr<Node> &nodePtr) {

    Node *n = nodePtr.get();
    if (n->body && n->body.get() == this) {
        return;
    }
    // For internal nodes, check if they are too far away.
    // If so, then use the center of mass and mass of the internal node for calculations and stop traversing.
    // If not, then continue to the traverse the tree and use individual body values when
    // we come across an external node that contains a planet and that cannot be further traversed.
    if (n->status == INTERNAL) {
        double d = this->dist_squared(n->mx/n->mass, n->my/n->mass);
        if (n->w / sqrt(d) < theta_threshold) {
            sf::Vector2<double> a = this->_calculateAcceleration(n->mass, n->mx/n->mass, n->my/n->mass, d);
            this->vx += a.x;
            this->vy += a.y;
        } else {
            for (int i = 0; i < NUM_SUB; i++) {
                if (n->children[i])  {
                    this->accelerate(n->children[i]);
                }
            }
        }
    } else if (n->body && n->body->active) {
        double d = this->dist_squared(n->body->x, n->body->y);
        sf::Vector2<double> a = this->_calculateAcceleration(n->body->mass, n->body->x, n->body->y, d);
        this->vx += a.x;
        this->vy += a.y;
    }
}

void Body::update() {
    this->x += this->vx;
    this->y += this->vy;
}

double Body::dist_squared(double x2, double y2) {
    return (this->x - x2)*(this->x - x2) + (this->y - y2)*(this->y - y2);
}