#ifndef SECTOR_H
#define SECTOR_H

#include <vector>
#include <memory>
#include "Wall.h"

struct Sector {
    float floorHeight;
    float ceilingHeight;
    std::vector<std::shared_ptr<Wall>> walls;

    Sector(float floor = 0.0f, float ceiling = 10.0f)
        : floorHeight(floor), ceilingHeight(ceiling) {}
};

#endif // SECTOR_H
