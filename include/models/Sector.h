#ifndef SECTOR_H
#define SECTOR_H

#include <vector>
#include <memory>
#include <cmath>
#include "Wall.h"

struct Sector {
    float floorHeight   = 0.0f;
    float ceilingHeight = 10.0f;

    // owns every Wall in this sector
    std::vector<std::unique_ptr<Wall>> walls_;

    // one entry point into the circular list
    Wall* anyWall = nullptr;

    explicit Sector(float floor = 0.0f, float ceiling = 10.0f)
        : floorHeight(floor), ceilingHeight(ceiling)
    {}

    // create & insert a brand-new wall at the end of the ring
    // returns a raw pointer you can keep to splice further
    Wall* createWall(std::shared_ptr<Vertex> s,
                     std::shared_ptr<Vertex> e,
                     bool portal = false,
                     std::weak_ptr<Sector> nextSec = {})
    {
        auto w = std::make_unique<Wall>(std::move(s), std::move(e), portal, std::move(nextSec));
        Wall* wPtr = w.get();

        if (!anyWall) {
            // first wall: points to itself
            wPtr->prev = wPtr->next = wPtr;
            anyWall = wPtr;
        } else {
            // splice it before `anyWall` — i.e. at the “end”
            Wall* tail = anyWall->prev;
            wPtr->next = anyWall;
            wPtr->prev = tail;
            tail->next = wPtr;
            anyWall->prev = wPtr;
        }

        walls_.push_back(std::move(w));
        return wPtr;
    }

    // walk the ring in order, returning a vector of raw pointers
    std::vector<Wall*> around() const {
        std::vector<Wall*> out;
        if (!anyWall) return out;
        Wall* w = anyWall;
        do {
            out.push_back(w);
            w = w->next;
        } while (w != anyWall);
        return out;
    }

    // remove a wall from the ring (and from the vector), returning true if found
    bool removeWall(Wall* w) {
        if (!w || walls_.empty()) return false;

        // fix the ring
        w->prev->next = w->next;
        w->next->prev = w->prev;
        if (anyWall == w) {
            anyWall = (w->next == w) ? nullptr : w->next;
        }

        // now remove from walls_ (by matching the pointer)
        auto it = std::find_if(walls_.begin(), walls_.end(),
                               [&](auto &up){ return up.get() == w; });
        if (it == walls_.end()) return false;
        walls_.erase(it);
        return true;
    }
};

#endif // SECTOR_H
