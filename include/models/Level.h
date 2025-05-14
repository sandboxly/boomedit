#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>
#include "Sector.h"

struct Level {
    std::vector<std::shared_ptr<Sector>> sectors;
};

#endif // LEVEL_H
