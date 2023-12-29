#include "node.hpp"

#include <iostream>

Node::Node(double x, double y, int w, int status):
    x(x),
    y(y),
    mass(0),
    mx(0),
    my(0),
    w(w),
    status(status)
    {};

void Node::insert(std::shared_ptr<Body> p, int depth) {
    if (this->status == EXTERNAL) {
        if (!this->body) {
            this->body = p;
        } else {
            this->status = INTERNAL;
            double midW = this->w / 2;
            std::shared_ptr<Body> p2 = this->body;
            this->body = NULL;
            this->children[0] = std::make_shared<Node>(this->x + midW, this->y, midW);
            this->children[1] = std::make_shared<Node>(this->x, this->y, midW);
            this->children[2] = std::make_shared<Node>(this->x, this->y + midW, midW);
            this->children[3] = std::make_shared<Node>(this->x + midW, this->y + midW, midW);

            // If two bodies are very close to each other, the collide elastically.
            // One of the bodies is marked as inactive so it does not affect future calculations.
            // TODO: make more accurate
            if (depth < 12) {
                // Keep on trying to insert the overlapping bodies until they are in different quadrants
                // or until they are too close
                this->insert(p, depth + 1);
                this->insert(p2, depth + 1);
            } else {
                this->status = EXTERNAL;
                p->mass += p2->mass;
                p->vx = (p->mass * p->vx + p2->mass * p2->vx) / (p->mass + p2->mass);
                p->vy = (p->mass * p->vy + p2->mass * p2->vy) / (p->mass + p2->mass);
                p2->active = false;
                this->body = p;
            }
        }
    } else {
        int q = this->_findQuadrant(p);

        // Accumulate the mass and center of mass for the internal node the the body goes into
        this->mass += p->mass;
        this->mx += p->mass * p->x;
        this->my += p->mass * p->y;
        this->children[q]->insert(p, depth + 1);
    }
}

int Node::_findQuadrant(std::shared_ptr<Body> p) {
    double midW = this->w / 2;
    if (p->x > this->x + midW) {
        if (p->y < this->y + midW) {
            return 0;
        }
        return 3;
    } else if (p->y < this->y + midW) {
        return 1;
    } else {
        return 2;
    }
}


void Node::_drawNode(sf::RenderWindow &screen) {
    sf::RectangleShape rect(sf::Vector2f(this->w, this->w));
    rect.setFillColor(sf::Color(0));
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color(0, 255, 0));
    rect.setPosition(this->x, this->y);
    screen.draw(rect);
}

void Node::draw(sf::RenderWindow &screen) {
    this->_drawNode(screen);
    for (int i = 0; i < NUM_SUB; i++) {
        if (this->children[i]) {
            this->children[i]->draw(screen);
        }
    }
}

void Node::drawBodies(sf::RenderWindow &screen) {
    if (this->status == EXTERNAL && this->body) {
        this->body->draw(screen);
    } else if (this->status == INTERNAL) {
        for (int i = 0; i < NUM_SUB; i++) {
            if (this->children[i]) {
                this->children[i]->drawBodies(screen);
            }
        }
    }
}

