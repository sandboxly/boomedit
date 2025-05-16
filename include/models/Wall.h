#ifndef WALL_H
#define WALL_H

#include <memory>
#include "Vertex.h"

struct Sector;  // forward

struct Wall {
    std::shared_ptr<Vertex> startVertex;
    std::shared_ptr<Vertex> endVertex;
    bool                    isPortal    = false;
    std::weak_ptr<Sector>   nextSector;  // for portals

    // intrusive doubly-linked ring pointers
    Wall* prev = nullptr;
    Wall* next = nullptr;

    Wall(std::shared_ptr<Vertex> s,
         std::shared_ptr<Vertex> e,
         bool portal = false,
         std::weak_ptr<Sector> nextSec = {})
        : startVertex(std::move(s))
        , endVertex(std::move(e))
        , isPortal(portal)
        , nextSector(std::move(nextSec))
    {}
};

#endif // WALL_H
