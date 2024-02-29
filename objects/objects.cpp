//
// Created by Boris Mikhaylov on 2024-02-29.
//

#include "objects.h"


// Distance between objects
double Dist(Object &o1, Object &o2) {
    return sqrt((o1.x - o2.x) * (o1.x - o2.x) + (o1.y - o2.y) * (o1.y - o2.y));
}


// Сhecks if objects see each other
bool Sees(std::vector<Object> &obstacles, Object &o1, Object &o2) {
    bool sees = true;
    int L = obstacles.size();
    for (int i = 0; i < L; i++) {
        if (abs((o2.x - o1.x) * (o1.y - obstacles[i].y) - (o1.x - obstacles[i].x) * (o2.y - o1.y)) /
            sqrt(pow(o2.x - o1.x, 2) + pow(o2.y - o1.y, 2)) < obstacles[i].r &&
            (o2.x - o1.x) * (obstacles[i].x - o1.x) + (o2.y - o1.y) * (obstacles[i].y - o1.y) > 0 &&
            (o1.x - o2.x) * (obstacles[i].x - o2.x) + (o1.y - o2.y) * (obstacles[i].y - o2.y) > 0) {
            sees = false;
        }
    }
    return sees;
}

void Pointer::ClearTarget() {
    this->checked = 0;
}

double Pointer::getDistance() const {
    return this->distance;
}

void Pointer::retarget(std::vector<Object> &aims, std::vector<Pointer> &pointers, std::vector<Object> &obstacles) {
    if (this->checked == 0) {
        double mindist = 100000000;
        int L = aims.size();
        for (int i = 0; i < L; i++) {
            if (Dist(*this, aims[i]) < mindist && Sees(obstacles, *this, aims[i])) {
                mindist = Dist(*this, aims[i]);
                this->target = aims[i];
            }
        }
        L = pointers.size();
        for (int i = 0; i < L; i++) {
            if (pointers[i].checked == 0) {
                pointers[i].retarget(aims, pointers, obstacles);
            } else {
                if (Dist(*this, pointers[i]) + pointers[i].distance < mindist && Sees(obstacles, *this, pointers[i])) {
                    mindist = Dist(*this, pointers[i]) + pointers[i].distance;
                    this->target = pointers[i];
                }
            }
        }
        this->checked = 1;
        this->distance = mindist;
    }
}

void Mob::retarget(std::vector<Object> &aims, std::vector<Pointer> &pointers, std::vector<Object> &obstacles) {
    double mindist = 100000000;
    int L = aims.size();
    for (int i = 0; i < L; i++) {
        if (Dist(*this, aims[i]) < mindist && Sees(obstacles, *this, aims[i])) {
            mindist = Dist(*this, aims[i]);
            this->target = aims[i];
        }
    }
    L = pointers.size();
    for (int i = 0; i < L; i++) {
        if (Dist(*this, pointers[i]) + pointers[i].getDistance() < mindist && Sees(obstacles, *this, pointers[i])) {
            mindist = Dist(*this, pointers[i]) + pointers[i].getDistance();
            this->target = pointers[i];
        }
    }
}

void Mob::Move(Game& game) {
    this->x += this->vx * game.dt;
    this->y += this->vy * game.dt;
}

double Object::getX() const {
    return x;
}

double Object::getY() const {
    return y;
}

void Game::velocity(std::vector<Object> &punchable) {
    for (auto &mob: mobs) {

        double ax = mob.acceleration * (mob.target.getX() - mob.x) /
                    sqrt(pow(mob.target.getX() - mob.x, 2) + pow(mob.target.getY() - mob.y, 2));
        double ay = mob.acceleration * (mob.target.getY() - mob.y) /
                    sqrt(pow(mob.target.getX() - mob.x, 2) + pow(mob.target.getY() - mob.y, 2));
        for (auto &item: punchable) {
            if (mob.id == item.id) continue;
            if (mob.r + item.r > Dist(mob, item)) {
                ax += punch * (item.getX() - mob.x) /
                      sqrt(pow(item.getX() - mob.x, 2) + pow(item.getY() - mob.y, 2));
                ay += punch * (item.getY() - mob.y) /
                      sqrt(pow(item.getX() - mob.x, 2) + pow(item.getY() - mob.y, 2));
            }
        }
        mob.vx += ax * dt;
        mob.vy += ay * dt;
        mob.vx *= 1 - friction * dt;
        mob.vy *= 1 - friction * dt;
    }

}
