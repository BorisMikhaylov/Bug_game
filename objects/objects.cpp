//
// Created by Boris Mikhaylov on 2024-02-29.
//

#include "objects.h"

double Dist(Object &o1, Object &o2) {
    return sqrt((o1.x - o2.x) * (o1.x - o2.x) + (o1.y - o2.y) * (o1.y - o2.y));
}

bool Sees(std::vector<Object> &visible, Object &o1, Object &o2) {
    int sees = 1;
    int L = visible.size();
    for (int i = 0; i < L; i++) {
        if (abs((o2.x - o1.x) * (o1.y - visible[i].y) - (o1.x - visible[i].x) * (o2.y - o1.y)) /
            sqrt(pow(o2.x - o1.x, 2) + pow(o2.y - o1.y, 2)) < visible[i].r &&
            (o2.x - o1.x) * (visible[i].x - o1.x) + (o2.y - o1.y) * (visible[i].y - o1.y) > 0 &&
            (o1.x - o2.x) * (visible[i].x - o2.x) + (o1.y - o2.y) * (visible[i].y - o2.y) > 0) {
            sees = 0;
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

void Pointer::Retarget(std::vector<Object> &aims, std::vector<Pointer> &pointers) {
    if (this->checked == 0) {
        double mindist = 100000000;
        int L = aims.size();
        for (int i = 0; i < L; i++) {
            if (Dist(*this, aims[i]) < mindist && Sees(this, aims[i])) {
                mindist = Dist(*this, aims[i]);
                this->target = aims[i];
            }
        }
        L = pointers.size();
        for (int i = 0; i < L; i++) {
            if (pointers[i].checked == 0) {
                pointers[i].Retarget(aims, pointers);
            } else {
                if (Dist(*this, pointers[i]) + pointers[i].distance < mindist && Sees(this, pointers[i])) {
                    mindist = Dist(*this, pointers[i]) + pointers[i].distance;
                    this->target = pointers[i];
                }
            }
        }
        this->checked = 1;
        this->distance = mindist;
    }
}

void Mob::retarget(std::vector<Object> &aims, std::vector<Pointer> &pointers) {
    double mindist = 100000000;
    int L = aims.size();
    for (int i = 0; i < L; i++) {
        if (Dist(*this, aims[i]) < mindist && Sees(this, aims[i])) {
            mindist = Dist(*this, aims[i]);
            this->target = aims[i];
        }
    }
    L = pointers.size();
    for (int i = 0; i < L; i++) {
        if (Dist(*this, pointers[i]) + pointers[i].getDistance() < mindist && Sees(this, pointers[i])) {
            mindist = Dist(*this, pointers[i]) + pointers[i].getDistance();
            this->target = pointers[i];
        }
    }
}

void Mob::velocity(std::vector<Object> &punchable) {
    double ax = this->a * (this->target.getX() - this->x) /
                sqrt(pow(this->target.getX() - this->x, 2) + pow(this->target.getY() - this->y, 2));
    double ay = this->a * (this->target.getY() - this->y) /
                sqrt(pow(this->target.getX() - this->x, 2) + pow(this->target.getY() - this->y, 2));
    int L = punchable.size();
    for (int i = 0; i < L; i++) {
        if (this->r + punchable[i].r > Dist(*this, punchable[i])) {
            ax += punch * (punchable[i].getX() - this->x) /
                  sqrt(pow(punchable[i].getX() - this->x, 2) + pow(punchable[i].getY() - this->y, 2));
            ay += punch * (punchable[i].getY() - this->y) /
                  sqrt(pow(punchable[i].getX() - this->x, 2) + pow(punchable[i].getY() - this->y, 2));
        }
    }
    this->vx += ax * dt;
    this->vy += ay * dt;
    this->vx *= 1 - friction;
    this->vy *= 1 - friction;
}

void Mob::Move() {
    this->x += this->vx * dt;
    this->y += this->vy * dt;
}

double Object::getX() const {
    return x;
}

double Object::getY() const {
    return y;
}
