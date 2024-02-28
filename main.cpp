#include <iostream>
#include <vector>
#include <cmath>

#include "objects/objects.h"

double friction = 0.5;
double dt = 0.01;
double punch = 1;

void PointersRetarget(std::vector<Object> &aims, std::vector<Pointer> &pointers) {
    for (auto& p : pointers) p.ClearTarget();
    for (auto& p : pointers) p.Retarget(aims, pointers);
}


int main() {
    cout << "Hello World!\n";
}

