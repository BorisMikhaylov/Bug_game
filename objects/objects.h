//
// Created by Boris Mikhaylov on 2024-02-29.
//

#ifndef BUG_GAME_OBJECTS_H
#define BUG_GAME_OBJECTS_H

#include <vector>

struct Object {
    double x;
    double y;
    double r;

    [[nodiscard]] double getX() const;

    [[nodiscard]] double getY() const;
};

struct Pointer : Object {
    int checked;
    Object target;
    double distance;

    void ClearTarget();

    [[nodiscard]] double getDistance() const;

    void Retarget(std::vector<Object> &aims, std::vector<Pointer> &pointers);
};

struct Mob : Object {
    double a;
    double vx;
    double vy;
    Object target;

    void retarget(std::vector<Object> &aims, std::vector<Pointer> &pointers);

    void velocity(std::vector<Object> &punchable);

    void Move();
};


#endif //BUG_GAME_OBJECTS_H
