//
// Created by Boris Mikhaylov on 2024-02-29.
//

#ifndef BUG_GAME_OBJECTS_H
#define BUG_GAME_OBJECTS_H

#include <vector>

struct Game;

struct Object {
    uint64_t id;
    double x;
    double y;
    double r;

    [[nodiscard]] double getX() const;

    [[nodiscard]] double getY() const;
};

struct Queen : Object {

};

struct Pointer : Object {
    int checked;
    Object target;
    double distance;

    void ClearTarget();

    [[nodiscard]] double getDistance() const;

    void retarget(std::vector<Object> &aims, std::vector<Pointer> &pointers, std::vector<Object> &obstacles);
};

struct Mob : Object {
    double acceleration;
    double vx;
    double vy;
    Object target;

    void retarget(std::vector<Object> &aims, std::vector<Pointer> &pointers, std::vector<Object> &obstacles);

    void Move(Game &game);
};

struct Finder : Mob {

};

struct Feeder : Mob {

};

struct Food : Object {

};

struct Wall : Object {

};

struct Game {
    double friction = 0.5;
    double dt = 0.01;
    double punch = 1;

    Queen mainPlayer;
    std::vector<Mob> mobs;
    std::vector<Wall> walls;
    std::vector<Pointer> pointers;
    std::vector<Food> food;

    void velocity(std::vector<Object> &punchable);
};


#endif //BUG_GAME_OBJECTS_H
