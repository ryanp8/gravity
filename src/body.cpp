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
    double fg = G * m / (r2 + DAMPENING_FACTOR);
    double theta = atan2(y - this->y, x - this->x);
    return sf::Vector2(fg * cos(theta) * SPEED, fg * sin(theta) * SPEED);
}

void Body::accelerate(std::unique_ptr<Node> &n) {
    if (n && n->body.get() == this) {
        return;
    }
    if (n->status == INTERNAL) {
        double d = (this->x - n->mx/n->mass)*(this->x - n->mx/n->mass) + (this->y - n->my/n->mass)*(this->y - n->my/n->mass);
        if (n->w / sqrt(d) < theta_threshold) {
            sf::Vector2<double> a = this->_calculateAcceleration(n->mass, n->mx/n->mass, n->my/n->mass, d);
            this->vx += a.x;
            this->vy += a.y;
        } else {
            for (int i = 0; i < NUM_SUB; i++) {
                if (n->children[i]) {
                    this->accelerate(n->children[i]);
                }
            }
        }
    } else if (n->body && n->body->active) {
        double d = (this->x - n->body->x)*(this->x - n->body->x) + (this->y - n->body->y)*(this->y - n->body->y);
        sf::Vector2<double> a = this->_calculateAcceleration(n->body->mass, n->body->x, n->body->y, d);
        this->vx += a.x;
        this->vy += a.y;
    }
}

void Body::update() {
    this->x += this->vx;
    this->y += this->vy;
}