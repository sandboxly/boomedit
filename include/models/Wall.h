#ifndef WALL_H
#define WALL_H

#include <memory>
#include "Vertex.h"

class Sector; // Forward declaration

struct Wall {
    std::shared_ptr<Vertex> startVertex;
    std::shared_ptr<Vertex> endVertex;
    bool isPortal;
    std::weak_ptr<Sector> nextSector;

    Wall(std::shared_ptr<Vertex> start,
         std::shared_ptr<Vertex> end,
         bool portal = false,
         std::weak_ptr<Sector> next = {})
        : startVertex(std::move(start)),
        endVertex(std::move(end)),
        isPortal(portal),
        nextSector(std::move(next)) {}
};

#endif // WALL_H
